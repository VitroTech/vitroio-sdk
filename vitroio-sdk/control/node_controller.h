#ifndef VITROIO_SDK_NODE_CONTROLLER_H
#define VITROIO_SDK_NODE_CONTROLLER_H

#include <mbed.h>

#include <vitroio-sdk/control/node_controller.h>
#include <vitroio-sdk/communication/canbus_frame.h>
#include <vitroio-sdk/types.h>

#include <vitroio-sdk/utils/impl/scoped_ptr.h>
#include <vitroio-sdk/interfaces/impl/flash_interface.h>
#include <vitroio-sdk/interfaces/impl/environment_interface.h>
#include <vitroio-sdk/control/impl/upgrade_controller.h>
#include <vitroio-sdk/communication/transport_layer.h>

namespace vitroio
{

namespace sdk
{

/**
 * @addtogroup control
 * @{
 */

/**
 * @def VITROIO_NODE_CONTROLLER_DEFAULT_EVENT_QUEUE_SIZE
 * 
 * @brief Defines default size of internal event queue for
 * @link vitroio::sdk::NodeController NodeController @endlink.
 */
#define VITROIO_NODE_CONTROLLER_DEFAULT_EVENT_QUEUE_SIZE 32

class Canbus;

/**
 * @brief Class is a main component of the node firmware.
 * 
 * @details The class handles standard operations of vitroio system such like
 * firmware upgrade and initialization of communication with gateway. It
 * requires flash memory space for storing environment variables.
 * 
 * The class uses an event loop for handling events. The event queue can be
 * managed by external queue specified by user or by internal queue with thread
 * of specifed priority.  
 * 
 * @note The controller occupies one of
 * @link Canbus::OnFrameReceivedCallback OnframeReceivedCallbacks @endlink
 * of Canbus object passed to the constructor.
 */
class NodeController : private NonCopyable<NodeController>
{
public:
    /**
     * @brief Contructor initializes the controller and chains an internal
     * event queue to the \p targetQueue.
     * 
     * @note Thread which handles \p targetQueue must be run before usage
     * of this class (construction of the object can be done earlier).
     * 
     * @details Initilization includes all of necessary components.
     * 
     * There is not guarantee that the object is in valid state. User should
     * call isValid() method to determine if the object was initialized
     * successfully. When the object is in invalid state, the behaviour is
     * undefined. 
     * 
     * The constructor uses
     * <a href="https://os.mbed.com/docs/v5.8/mbed-os-api-doxy/classevents_1_1_event_queue.html#a2a05f85dbf893b9d72657fa629ccf79d">mbed::EventQueue::chain</a>
     * method for connection to \p targetQueue.
     * 
     * @param canbus Pointer to Canbus object
     * @param fwId id of firmware
     * @param fwVersion Version of firmware
     * @param environmentFlashSpace Specifies flash memory space for storing
     * environment variables
     * @param regionAFlashSpace Specifies region A of flash memory space
     * intended for firmware
     * @param regionBFlashSpace Specifies region B of flash memory space
     * intended for firmware
     * @param targetQueue External event queue to which the internal queue is
     * to be chained
     * @param eventQueueSize Size of internal event queue
     */
    explicit NodeController(
        Canbus* canbus,
        const FirmwareId& fwId,
        const Version& fwVersion, 
        FlashSpace environmentFlashSpace,
        FlashSpace regionAFlashSpace,
        FlashSpace regionBFlashSpace,
        EventQueue* targetQueue, 
        uint32_t eventQueueSize = VITROIO_NODE_CONTROLLER_DEFAULT_EVENT_QUEUE_SIZE);

    /**
     * @brief Contructor initializes the controller and creates internal event
     * loop using thread with priority \p priority.
     * 
     * @details Initilization includes all of necessary components.
     * 
     * There is not guarantee that the object is in valid state. User should
     * call isValid() method to determine if the object was initialized
     * successfully. When the object is in invalid state, the behaviour is
     * undefined. 
     * 
     * @param canbus Pointer to Canbus object
     * @param fwId id of firmware
     * @param fwVersion Version of firmware
     * @param environmentFlashSpace Specifies flash memory space for storing
     * environment variables
     * @param regionAFlashSpace Specifies region A of flash memory space
     * intended for firmware
     * @param regionBFlashSpace Specifies region B of flash memory space
     * intended for firmware
     * @param priority Priority of thread for handling internal events
     * @param eventQueueSize Size of internal event queue
     */
    explicit NodeController(
        Canbus* canbus,
        const FirmwareId& fwId,
        const Version& fwVersion, 
        FlashSpace environmentFlashSpace,
        FlashSpace regionAFlashSpace,
        FlashSpace regionBFlashSpace,
        osPriority priority = osPriorityNormal, 
        uint32_t eventQueueSize = VITROIO_NODE_CONTROLLER_DEFAULT_EVENT_QUEUE_SIZE);
    
    /**
     * @brief Contructor initializes the controller and creates internal event
     * loop using thread with priority \p priority.
     * 
     * @details Initilization includes all of necessary components.
     * 
     * There is not guarantee that the object is in valid state. User should
     * call isValid() method to determine if the object was initialized
     * successfully. When the object is in invalid state, the behaviour is
     * undefined. 
     * 
     * @param canbus Pointer to Canbus object
     * @param fwId id of firmware
     * @param fwVersion Version of firmware
     * @param priority Priority of thread for handling internal events
     * @param eventQueueSize Size of internal event queue
     */
    NodeController(
        Canbus* canbus,
        const FirmwareId& fwId,
        const Version& fwVersion, 
        osPriority priority = osPriorityNormal, 
        uint32_t eventQueueSize = VITROIO_NODE_CONTROLLER_DEFAULT_EVENT_QUEUE_SIZE);

    /**
     * @brief Contructor initializes the controller and chains an internal
     * event queue to the \p targetQueue.
     * 
     * @note Thread which handles \p targetQueue must be run before usage
     * of this class (construction of the object can be done earlier).
     * 
     * @details Initilization includes all of necessary components.
     * 
     * There is not guarantee that the object is in valid state. User should
     * call isValid() method to determine if the object was initialized
     * successfully. When the object is in invalid state, the behaviour is
     * undefined. 
     * 
     * The constructor uses
     * <a href="https://os.mbed.com/docs/v5.8/mbed-os-api-doxy/classevents_1_1_event_queue.html#a2a05f85dbf893b9d72657fa629ccf79d">mbed::EventQueue::chain</a>
     * method for connection to \p targetQueue.
     * 
     * @param canbus Pointer to Canbus object
     * @param fwId id of firmware
     * @param fwVersion Version of firmware
     * @param targetQueue External event queue to which the internal queue is
     * to be chained
     * @param eventQueueSize Size of internal event queue
     */
    NodeController(
        Canbus* canbus,
        const FirmwareId& fwId,
        const Version& fwVersion, 
        EventQueue* targetQueue, 
        uint32_t eventQueueSize = VITROIO_NODE_CONTROLLER_DEFAULT_EVENT_QUEUE_SIZE);
    
    ~NodeController();

    /**
     * @brief Function allows to check whether the controller is in valid
     * state.
     * 
     * @note This method should be called always after creation of the object.
     */
    bool isValid();

    /**
     * @brief Function initializes communication with gateway. This method
     * blocks until the communication is not initialized and no error occurred.
     *
     * @return Function returns VITROIO_ERR_SUCCESS when the communication was
     * initialized successfully or appropriate error code otherwise.
     */
    int initCommunication(Transport_layer* layer);

    /**
     * @brief Function initializes communication with gateway. This method
     * blocks until the communication is not initialized and no error occurred.
     *
     * @return Function returns VITROIO_ERR_SUCCESS when the communication was
     * initialized successfully or appropriate error code otherwise.
     */
    int initCommunication(uint32_t sync_time, Transport_layer* layer);

    /**
     * @brief Function allows to obtain node ID assigned by gateway during
     * initialization of communication.
     * 
     * @note To obtain node ID, the communication with gateway must be
     * initialized successfully.
     * 
     * @return Function returns node ID or 0 when the ID is not assigned. 
     */
    uint32_t nodeId();

private:
    bool valid_;

    EventQueue evQueue_;
    impl::ScopedPtr<Thread> evQueueThread_;

    impl::FlashInterface flash_;
    impl::EnvironmentInterface env_;
    impl::UpgradeController upg_;
    Canbus* canbus_;
    FirmwareId fwId_;
    Version fwVer_;
    uint64_t id_;
    uint32_t nodeId_;
    FlashSpace regionAFlashSpace_;
    FlashSpace regionBFlashSpace_;

    Mutex mutex_;

    void setNodeId(uint32_t id);

    int onFrameReceivedCallbackHandle_;

    void onFrameReceivedCallback(const CanbusFrame&);

    void handleNodeIdResponseFrame(const CanbusFrame& frame);
    void handleUpgradeFrame(const CanbusFrame& frame);
    void handleProvisioningFrame(const CanbusFrame& frame);

    void onNewFirmwareAvailableCallback();

    uint64_t getHardwareId();
};

/**
 * @}
 */

} // namespace sdk

} // namespace vitroio

#endif // VITROIO_SDK_NODE_CONTROLLER_H
