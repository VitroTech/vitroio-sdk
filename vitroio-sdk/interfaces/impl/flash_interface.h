#ifndef VITROIO_SDK_FLASH_INTERFACE_H
#define VITROIO_SDK_FLASH_INTERFACE_H

#include <mbed.h>

namespace vitroio
{

namespace sdk
{

namespace impl
{

/**
 * @addtogroup interfaces
 * @{
 */

/**
 * @brief Class is a wrapper for
 * <a href="https://docs.mbed.com/docs/mbed-os-api-reference/en/latest/APIs/storage/flashiap/">mbed::FlashIAP</a>
 * module.
 */
class FlashInterface : private NonCopyable<FlashInterface>
{
public:
    /**
     * @brief Constructor intializes the interface.
     * 
     * @details 
     * There is not guarantee that the object is in valid state.
     * User should call isValid() method to determine if the object was
     * initialized successfully. When the object is in invalid state,
     * the behaviour is undefined.
     */
    explicit FlashInterface();

    /**
     * @brief Destructor
     */
    ~FlashInterface();

    /**
     * @brief Function allows to check whether the interface is in valid
     * state.
     * 
     * @note This method should be called always after creation of the object.
     * 
     * @return Function returns true if the object is valid or false otherwise.
     */
    bool isValid() const;

    /**
     * @brief Function reads data from flash memory.
     * 
     * @param buffer %Buffer where the data are to be write to.
     * @param offset Offset of the flash memory where the data are to be
     * read from.
     * @param size Size of the data to read.
     * 
     * @return Function returns VITROIO_ERR_SUCCESS on success or appropriate
     * error code otherwise.
     */
    int read(void* buffer, uint32_t offset, uint32_t size);

    /**
     * @brief Function writes data to flash memory.
     * 
     * @param buffer %Buffer with data to write.
     * @param offset Offset of the flash memory where the data are to be
     * write to.
     * @param size Size of the data to write.
     * 
     * @return Function returns VITROIO_ERR_SUCCESS on success or appropriate
     * error code otherwise.
     */
    int write(void* buffer, uint32_t offset, uint32_t size);

    /**
     * @brief Function allows to obtain maximum size of sector in flash memory.
     * 
     * @details Function can be helplful during operations on flash memory.
     * It can help avoid reallocating of memory - only buffer of maximum sector
     * size can be allocated and reused.
     * 
     * @return Function returns maximum size of sector in flash memory.
     */
    uint32_t getMaxSectorSize() const;

    /**
     * @brief Function allows to obtain sector size of flash memory
     * for specified address.
     * 
     * @param offset Flash memory offset.
     * 
     * @return Function returns sector size in bytes or 0 if not mapped.
     */
    uint32_t getSectorSize(uint32_t offset) const;

    /**
     * @brief Function allows to obtain flash memory start address.
     */
    uint32_t getFlashStartAddress() const;

    /**
     * @brief Function allows to obtain flash memory size in bytes.
     */
    uint32_t getFlashSize() const;

private:
    bool valid_;

    FlashIAP iap_;
    uint32_t maxSectorSize_;
    uint32_t flashStartAddr_;
};

/**
 * @}
 */

} // namespace impl

} // namespace sdk

} // namespace vitroio

#endif // VITROIO_SDK_FLASH_INTERFACE_H