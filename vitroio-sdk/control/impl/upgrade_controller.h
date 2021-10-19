#ifndef VITROIO_SDK_UPGRADE_CONTROLLER_H
#define VITROIO_SDK_UPGRADE_CONTROLLER_H

#include <mbed.h>

#include <vitroio-sdk/utils/impl/scoped_ptr.h>
#include <vitroio-sdk/utils/impl/buffer.h>

#include <vitroio-sdk/types.h>

namespace vitroio
{

namespace sdk
{

namespace impl
{

/**
 * @addtogroup control
 * @{
 */

/**
 * @def VITROIO_UPGRADE_CONTROLLER_DEFAULT_EVENT_QUEUE_SIZE
 * 
 * @brief Defines default size of internal event queue for
 * @link vitroio::sdk::UpgradeController UpgradeController @endlink.
 */
#define VITROIO_UPGRADE_CONTROLLER_DEFAULT_EVENT_QUEUE_SIZE 32

class FlashInterface;

/**
 * @brief Class is responsible for handling upgrade data.
 */
class UpgradeController : private NonCopyable<UpgradeController>
{
public:
    /**
     * @brief Type defines signature of the callback function which is to be
     * called when the new firmware will be available.
     */ 
    typedef Callback<void()> OnNewFirmwareAvailableCallback;

    /**
     * @brief Constructor
     * 
     * @detials
     * There is not guarantee that the object is in valid state. User should
     * call isValid() method to determine if the object was initialized
     * successfully. When the object is in invalid state, the behaviour is
     * undefined. 
     * 
     * @param flash Pointer to FlashInterface object
     * @param fwId id if firmware
     * @param fwVersion Current firmware version
     * @param callback Callback that is to be called when new firmware is
     * available
     * @param eventQueue External event queue for storing controller events
     */
    explicit UpgradeController(
        FlashInterface* flash,
        FirmwareId fwId,
        Version fwVersion,
        OnNewFirmwareAvailableCallback callback,
        EventQueue* eventQueue
    );

    /**
     * @brief Destructor
     */
    ~UpgradeController();

    /**
     * @brief Function allows to check whether the controller is in valid
     * state.
     * 
     * @note This method should be called always after creation of the object.
     * 
     * @return Function returns true if the object is valid or false otherwise.
     */
    bool isValid() const;

    /**
     * @brief Function configures the controller.
     * 
     * @details Function allows to set parameters that can be not known during
     * instantiation of the controller. The controller must be configured
     * before usage.
     * 
     * @param flashSpace Specifies flash memory space for a new firmware
     */
    void configure(FlashSpace flashSpace);

    /**
     * @brief Function processes upgrade data.
     * 
     * @param data Pointer to buffer with new upgrade data
     * @param size Size of buffer with upgrade data
     */
    void processData(const uint8_t* data, uint32_t size);

private:
    /**
     * @brief The segment decoder class is a wrapper for Buffer that allows to
     * easy parsing frames with upgrade data.
     */
    class SegmentDecoder
    {
    public:
        static SegmentDecoder* create(const uint8_t* data, uint32_t size);

        ~SegmentDecoder();

        uint32_t segment();
        uint32_t segmentsCount();
        uint8_t* data();
        const uint8_t* data() const;
        uint32_t dataSize();

        bool setBuffer(const uint8_t* data, uint32_t size);

        static uint32_t allocated();
        static uint32_t deleted();

    private:
        SegmentDecoder();

        static const uint8_t dataOffset_ = 4;
        static uint32_t allocated_;
        static uint32_t deleted_;

        Buffer buffer_;
    };

    bool valid_;

    FlashInterface* flash_;
    FirmwareId fwId_;
    Version fwVersion_;
    FlashSpace flashSpace_;
    OnNewFirmwareAvailableCallback onNewFirmwareAvailableCallback_;

    EventQueue* eventQueue_;
    Mutex mutex_;

    uint32_t nextSegment_;
    Buffer sectorBuffer_;
    FlashSpace currentFlashSpace_;
    uint32_t flashedBytes_;
    bool upgradeProcessRunning_;
    bool breakIncorrectUpdate;
    //
    // TODO:
    // - consider make sizes of these queues configurable
    //
    Queue<SegmentDecoder, 64> segmentsToProcessQueue_;
    Queue<SegmentDecoder, 64> notUsedSegmentsQueue_;

    void processSegments();
    bool processSegment(SegmentDecoder* sd);

    void cleanup();

    bool writeSectorBufferToFlash();

    //
    // Inserts segment into notUsedSegmentsQueue_ or deletes it
    // when the queue is full.
    //
    void setSegmentNotUsed(SegmentDecoder* segment);

    //
    // Returns not used segment or NULL when there aren't not used segments.
    //
    SegmentDecoder* getNotUsedSegment();

    //
    // Inserts segment to segmentsToProcessQueue_.
    // Returns true on success or false when the queue is full.
    //
    bool setSegmentToProcess(SegmentDecoder* segment);

    //
    // Returns segment from segmentsToProcessQueue_ or NULL when the queue
    // is empty.
    //
    SegmentDecoder* getSegmentToProcess();
};

/**
 * @}
 */

} // namespace impl

} // namespace sdk

} // namespace vitroio

#endif // VITROIO_SDK_UPGRADE_CONTROLLER_H
