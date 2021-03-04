#ifndef VITROIO_SDK_MEASUREMENT_API_H
#define VITROIO_SDK_MEASUREMENT_API_H

#include <mbed.h>

#include <vitroio-sdk/measurement-api/abstract_sensor_interface.h>

#include <vitroio-sdk/utils/impl/list.h>

namespace vitroio
{

namespace sdk
{

/**
 * @addtogroup measurement-api
 * @{
 */

/**
 * @def VITROIO_MEASUREMENT_API_DEFAULT_EVENT_QUEUE_SIZE
 * 
 * @brief Defines default size of internal event queue for
 * @link vitroio::sdk::MeasurementApi MeasurementApi @endlink.
 */
#define VITROIO_MEASUREMENT_API_DEFAULT_EVENT_QUEUE_SIZE 2

/**
 * @brief Class is responsible for cycling readings of measurement data using
 * registered sensors.
 * 
 * @details The class uses an event loop for handling events. The event queue
 * can be managed by external queue specified by user or by internal queue with
 * thread of specifed priority.
 * 
 * @tparam MaxParams Specifies maximum number of sensors parameters that can be
 * handled
 */
template <uint32_t MaxParams>
class MeasurementApi : private NonCopyable< MeasurementApi<MaxParams> >
{
public:
    /**
     * @brief Type defines signature of callback function which is to be called
     * when a new measurement values are read.
     */
    typedef Callback<void(SensorParameterValue*, int)> OnNewValuesCallback;

    /**
     * @brief Contructor chains an internal event queue to the
     * \p targetQueue.
     * 
     * @details 
     * There is not guarantee that the object is in valid state. User should
     * call isValid() method to determine if the object was initialized
     * successfully. When the object is in invalid state, the behaviour is
     * undefined. 
     * 
     * The contructor uses
     * <a href="https://os.mbed.com/docs/v5.8/mbed-os-api-doxy/classevents_1_1_event_queue.html#a2a05f85dbf893b9d72657fa629ccf79d">mbed::EventQueue::chain</a>
     * method for connection to \p targetQueue.
     * 
     * @note Thread which handles \p targetQueue must be run before usage
     * of this class (construction of the object can be done earlier).
     * 
     * @param targetQueue External event queue to which the internal queue is
     * to be chained
     * @param eventQueueSize Size of internal event queue
     */
    explicit MeasurementApi(
        EventQueue* targetQueue, 
        uint32_t eventQueueSize = VITROIO_MEASUREMENT_API_DEFAULT_EVENT_QUEUE_SIZE);

    /**
     * @brief Contructor creates internal event loop using thread with priority
     * \p priority.
     * 
     * @details
     * There is not guarantee that the object is in valid state. User should
     * call isValid() method to determine if the object was initialized
     * successfully. When the object is in invalid state, the behaviour is
     * undefined. 
     * 
     * @param priority Priority of thread for handling internal event queue
     * @param eventQueueSize Size of internal event queue
     */
    explicit MeasurementApi(
        osPriority priority = osPriorityNormal, 
        uint32_t eventQueueSize = VITROIO_MEASUREMENT_API_DEFAULT_EVENT_QUEUE_SIZE);

    /**
     * @brief Destructor frees resources and stops event loop.
     */
    ~MeasurementApi();

    /**
     * @brief Function allows to check whether the object is in valid
     * state.
     * 
     * @note This method should be called always after creation of the object.
     * 
     * @return Function returns true if the object is valid or false otherwise.
     */
    bool isValid() const;

    /**
     * @brief Function registers sensor from which the measurement data
     * is to be read.
     * 
     * @param sensorIf Pointer to sensor interface to register
     * 
     * @return Function returns true on success or false if parameters count
     * exceeded @p MaxParams.
     */
    bool registerSensor(AbstractSensorInterface* sensorIf);

    /**
     * @brief Function sets interval between readings of measurement values.
     * 
     * @param seconds Interval in seconds
     */
    void setPollTime(unsigned int seconds);

    /**
     * @brief Function sets callback which will be called when the new values
     * are read.
     * 
     * @note Callback set by this method will be executed in another thread
     * (event loop).
     */
    void setOnNewValuesCallback(OnNewValuesCallback callback);

    /**
     * @brief Function starts cycling reading of measurement values.
     * 
     * @note Function is not blocking. When new values are read the callback
     * set by client will be executed in another thread.
     */
    void startMeasurements();

    /**
     * @brief Function stops reading of measurements values.
     */
    void stopMeasurements();

private:
    bool valid_;

    EventQueue evQueue_;
    Thread* evQueueThread_;
    Mutex pollMutex_;
    int pollEventId_;
    unsigned int pollTimeS_;
    uint32_t parametersCount_;
    OnNewValuesCallback onNewValuesCallback_;

    uint32_t valuesCount_;
    SensorParameterValue valuesBuffer_[MaxParams];

    impl::List<AbstractSensorInterface*> sensorsList_;

    void getValues();
    void pollValues();
};

#include <vitroio-sdk/measurement-api/impl/measurement_api.hpp>

/**
 * @}
 */

} // namespace sdk

} // namespace vitroio

#endif // VITROIO_SDK_MEASUREMENT_API_H