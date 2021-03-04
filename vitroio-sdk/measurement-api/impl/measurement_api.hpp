#ifndef VITROIO_SDK_MEASUREMENT_API_HPP
#define VITROIO_SDK_MEASUREMENT_API_HPP

#include <vitroio-sdk/debug.h>

#define _MEASUREMENT_API_MODULE_NAME_ "MEASUREMENT API"
#define _MEASUREMENT_API_INFO_(format, ...) VITROIO_DEBUG_INFO(_MEASUREMENT_API_MODULE_NAME_, format, ##__VA_ARGS__);
#define _MEASUREMENT_API_WARNING_(format, ...) VITROIO_DEBUG_WARNING(_MEASUREMENT_API_MODULE_NAME_, format, ##__VA_ARGS__);
#define _MEASUREMENT_API_ERROR_(format, ...) VITROIO_DEBUG_ERROR(_MEASUREMENT_API_MODULE_NAME_, format, ##__VA_ARGS__);

#define _MEASUREMENT_API_POLL_TIME_S_DEFAULT_ 30

template <uint32_t MaxParams>
vitroio::sdk::MeasurementApi<MaxParams>::MeasurementApi(EventQueue* targetQueue, uint32_t eventQueueSize) :
    valid_(false),
    evQueue_(eventQueueSize * EVENTS_EVENT_SIZE),
    evQueueThread_(NULL),
    pollEventId_(0),
    pollTimeS_(_MEASUREMENT_API_POLL_TIME_S_DEFAULT_),
    parametersCount_(0),
    onNewValuesCallback_(OnNewValuesCallback(NULL))
{
    _MEASUREMENT_API_INFO_("Constructed with external event queue 0x%x", targetQueue);

    evQueue_.chain(targetQueue);

    valid_=true;
}

template <uint32_t MaxParams>
vitroio::sdk::MeasurementApi<MaxParams>::MeasurementApi(osPriority priority, uint32_t eventQueueSize) :
    valid_(false),
    evQueue_(eventQueueSize * EVENTS_EVENT_SIZE),
    evQueueThread_(NULL),
    pollEventId_(0),
    pollTimeS_(_MEASUREMENT_API_POLL_TIME_S_DEFAULT_),
    parametersCount_(0),
    onNewValuesCallback_(OnNewValuesCallback(NULL))
{
    _MEASUREMENT_API_INFO_("Constructed with internal event queue");

    evQueueThread_ = new (nothrow) Thread(priority);
    if(!evQueueThread_){
        return;
    }
    evQueueThread_->start(callback(&evQueue_, &EventQueue::dispatch_forever));

    valid_=true;
}

template <uint32_t MaxParams>
vitroio::sdk::MeasurementApi<MaxParams>::~MeasurementApi()
{
    if(evQueueThread_){
        // thread destructor terminates the thread
        delete evQueueThread_;
    }

    _MEASUREMENT_API_INFO_("Destructed");
}

template <uint32_t MaxParams>
bool vitroio::sdk::MeasurementApi<MaxParams>::isValid() const
{
    return valid_;
}

template <uint32_t MaxParams>
bool vitroio::sdk::MeasurementApi<MaxParams>::registerSensor(AbstractSensorInterface* sensorIf)
{
    _MEASUREMENT_API_INFO_("Registered sensor 0x%x", sensorIf);

    ScopedLock<Mutex> sl(pollMutex_);

    if(parametersCount_ + sensorIf->getParametersCount() > MaxParams){
        return false;
    }

    sensorsList_.pushBack(sensorIf);
    parametersCount_ += sensorIf->getParametersCount();
    
    return true;
}

template <uint32_t MaxParams>
void vitroio::sdk::MeasurementApi<MaxParams>::setPollTime(unsigned int seconds)
{
    _MEASUREMENT_API_INFO_("Set poll time %d s", seconds);

    pollTimeS_ = seconds;

    if(pollEventId_){

        evQueue_.cancel(pollEventId_);
        pollEventId_ = evQueue_.call_every(pollTimeS_*1000, this, &MeasurementApi::pollValues);
    }
}

template <uint32_t MaxParams>
void vitroio::sdk::MeasurementApi<MaxParams>::setOnNewValuesCallback(OnNewValuesCallback callback)
{
    ScopedLock<Mutex> sl(pollMutex_);

    onNewValuesCallback_ = callback;
}

template <uint32_t MaxParams>
void vitroio::sdk::MeasurementApi<MaxParams>::startMeasurements()
{
    if(pollEventId_){
        return;
    }

    pollEventId_ = evQueue_.call_every(pollTimeS_*1000, callback(this, &MeasurementApi::pollValues));

    _MEASUREMENT_API_INFO_("Measurements started");
}

template <uint32_t MaxParams>
void vitroio::sdk::MeasurementApi<MaxParams>::stopMeasurements()
{
    if(!pollEventId_){
        return;
    }

    evQueue_.cancel(pollEventId_);
    pollEventId_=0;

    _MEASUREMENT_API_INFO_("Measurements stopped");
}

template <uint32_t MaxParams>
void vitroio::sdk::MeasurementApi<MaxParams>::getValues()
{
    _MEASUREMENT_API_INFO_("Reading values");

    impl::ListNode<AbstractSensorInterface*>* sensor = sensorsList_.first();
    valuesCount_ = 0;
    while(sensor != NULL){
        valuesCount_ += sensor->value->getValues(valuesBuffer_ + valuesCount_);
        sensor = sensor->next;
    }
   
    if( valuesCount_ != parametersCount_ ){
        _MEASUREMENT_API_WARNING_("Read %d/%d values", valuesCount_, parametersCount_);
    }
}

template <uint32_t MaxParams>
void vitroio::sdk::MeasurementApi<MaxParams>::pollValues()
{
    ScopedLock<Mutex> sl(pollMutex_);
    getValues();
    if(onNewValuesCallback_){
        onNewValuesCallback_.call(valuesBuffer_, valuesCount_);
    }
}

#endif // VITROIO_SDK_MEASUREMENT_API_HPP