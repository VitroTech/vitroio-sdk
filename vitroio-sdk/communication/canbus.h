#ifndef VITROIO_SDK_CANBUS_H
#define VITROIO_SDK_CANBUS_H

#include <mbed.h>

#include <vitroio-sdk/communication/canbus_frame.h>

#include <vitroio-sdk/communication/impl/_CAN.h>

namespace vitroio
{

namespace sdk
{

/**
 * @addtogroup communication
 * @{
 */

/**
 * @def VITROIO_CANBUS_DEFAULT_FREQUENCY
 * 
 * @brief Defines default communication frequency for 
 * @link vitroio::sdk::Canbus Canbus @endlink.
 */
#define VITROIO_CANBUS_DEFAULT_FREQUENCY 125000

/**
 * @def VITROIO_CANBUS_DEFAULT_EVENT_QUEUE_SIZE
 * 
 * @brief Defines default size of internal event queue for
 * @link vitroio::sdk::Canbus Canbus @endlink.
 */
#define VITROIO_CANBUS_DEFAULT_EVENT_QUEUE_SIZE 32

/**
 * @brief Class is a wrapper for
 * <a href="https://os.mbed.com/docs/latest/apis/can.html">mbed::CAN</a> class
 * and provides interface for CanbusFrame type.
 * 
 * @details Read of incoming frames is possible only by callbacks because of
 * thread safety - the frames are read using RX IRQ.
 * 
 * The class uses an event queue for reading incoming frames. The event queue
 * can be managed by external queue specified by user or by internal queue with
 * thread of specifed priority.
 */
class Canbus : private NonCopyable<Canbus>
{
public:
    /**
     * @brief Type defines signature of callback function which is to be called
     * when a new frame will be received.
     */
    typedef Callback<void(const CanbusFrame&)> OnFrameReceivedCallback;

    /**
     * @brief Constructor initializes CAN bus and chains an internal
     * event queue to the \p targetQueue.
     * 
     * @details 
     * 
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
     * @param rd RD pin of the CAN interface
     * @param td TD pin of the CAN interface
     * @param targetQueue External event queue to which the internal queue is
     * to be chained
     * @param eventQueueSize Size of internal event queue
     * @param hz Transmission frequency in hertz
     */
    explicit Canbus(
        PinName rd, PinName td, 
        EventQueue* targetQueue, 
        uint32_t eventQueueSize = VITROIO_CANBUS_DEFAULT_EVENT_QUEUE_SIZE, 
        int hz = VITROIO_CANBUS_DEFAULT_FREQUENCY);

    /**
     * @brief Constructor initializes CAN bus and creates internal event loop
     * using thread with priority \p priority.
     * 
     * @details
     * There is not guarantee that the object is in valid state. User should
     * call isValid() method to determine if the object was initialized
     * successfully. When the object is in invalid state, the behaviour is
     * undefined. 
     * 
     * @param rd RD pin of the CAN interface
     * @param td TD pin of the CAN interface
     * @param priority Priority of thread for handling internal event queue
     * @param eventQueueSize Size of internal event queue
     * @param hz Transmission frequency in hertz
     */
    explicit Canbus(
        PinName rd, PinName td, 
        osPriority priority = osPriorityNormal, 
        uint32_t eventQueueSize = VITROIO_CANBUS_DEFAULT_EVENT_QUEUE_SIZE, 
        int hz = VITROIO_CANBUS_DEFAULT_FREQUENCY);

    /**
     * @brief Destructor
     */
    ~Canbus();

    /**
     * @brief Function allows to check whether the bus is in valid state.
     * 
     * @note This method should be called always after creation of the object.
     * 
     * @return Function returns true if the object is valid or false otherwise.
     */
    bool isValid() const;

    /**
     * @brief Functions sends frame over the bus.
     * 
     * @param frame Frame to send
     * 
     * @return Function returns VITROIO_ERR_SUCCESS on success or appropriate
     * error code otherwise.
     */
    int sendFrame(const CanbusFrame& frame);

    /**
     * @brief Function allows to set callbacks which are to be called any time
     * the frame received. 
     * 
     * @details Maximum number of callbacks that can be set is 4.
     * The callback can be unset by passing OnFrameReceivedCallback(NULL)
     * as \p callback and providing \p handle returned by this method.
     * 
     * @note When a new frame is received, all of registered callbacks will be
     * called for the same frame. Callbacks are responsible for filtering
     * incoming frames and handling only those that interest them. 
     * 
     * @param handle Handle of callback returned by this function - it should
     * be used when the specified callback is to be changed
     * 
     * @return Function returns non-negative handle of callback on success
     * or -1 otherwise.
     */
    int setOnFrameReceivedCallback(OnFrameReceivedCallback callback, int handle = -1);

private:
    static const uint32_t onFramesReceivedCallbacksCnt_ = 4;

    bool valid_;

    impl::_CAN can_;
    EventQueue evQueue_;
    Thread* evQueueThread_;
    OnFrameReceivedCallback onFrameReceivedUserCallbacks_[onFramesReceivedCallbacksCnt_];

    void rxIrqHandler();
    void onFrameReceivedCallback(CanbusFrame frame);
};

/**
 * @}
 */

} // namespace sdk

} // namespace vitroio

#endif // VITROIO_SDK_CANBUS_H