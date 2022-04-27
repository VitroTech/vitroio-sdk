#ifndef VITROIO_SDK_ENVIRONMENT_INTERFACE_H
#define VITROIO_SDK_ENVIRONMENT_INTERFACE_H

#include <mbed.h>

#include <vitroio-sdk/types.h>
#include <vitroio-sdk/consts.h>

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

#define VITROIO_ENVIRONMENT_INTERFACE_BOOT_REGION_A 0x0A
#define VITROIO_ENVIRONMENT_INTERFACE_BOOT_REGION_B 0x0B

class FlashInterface;

/**
 * @brief Class is wrapper for FlashInterface. It allows to read/write
 * environment variables stored in flash memory.
 */
class EnvironmentInterface : private NonCopyable<EnvironmentInterface>
{
public:
    /**
     * @brief The Variable enum specifies supported environment variables.
     */
    enum Variable
    {
        ENVVAR_CURRENT_BOOT_REGION,
        ENVVAR_NEXT_BOOT_REGION,
        ENVVAR_TIMESTAMP
    };

    /**
     * @brief Constructor initializes the interface.
     * 
     * @details Intialization includes verification whether the provided flash
     * memory size is enough, reading of environment variables from flash
     * memory and writing default values when variables are not set.
     * 
     * There is not guarantee that the object is in valid state.
     * User should call isValid() method to determine if the object was
     * initialized successfully. When the object is in invalid state,
     * the behaviour is undefined.
     * 
     * @param flash Pointer to FlashInterface object.
     * @param flashSpace Specifies flash memory space for storing environment
     * variables
     */
    explicit EnvironmentInterface(FlashInterface* flash, FlashSpace flashSpace);

    /**
     * @brief Destructor
     */
    ~EnvironmentInterface();

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
     * @brief Function saves environment variables to the flash memory.
     * 
     * @return Function returns VITROIO_ERR_SUCCESS on success or appropriate
     * error code otherwise.
     */
    int save();

    /**
     * @brief Function allows to get value of environment \p variable.
     * 
     * @param variable Variable for which the value is to be get.
     * 
     * @return Function returns value of \p variable.
     * 
     * @note If the \p variable is unknown the function will return 0.
     * Therefore it is important to use variables defined in
     * @link EnvironmentInterface::Variable Variable @endlink enum.
     */
    uint32_t getVariable(Variable variable) const;
    void getVariableIOKeys(uint8_t* retValue, uint32_t offset, uint32_t bytes) const;
    /**
     * @brief Function allows to set value of environment \p variable.
     * 
     * @param variable @link EnvironmentInterface::Variable Variable @endlink
     * for which the value is to be set.
     * @param value Value of \p variable to set.
     * 
     * @note If the \p variable is unknown the function will just return.
     * Therefore it is important to use variables defined in
     * @link EnvironmentInterface::Variable Variable @endlink enum.
     */
    void setVariable(Variable variable, uint32_t value);
    void setVariableIOKeys(uint8_t* value, uint32_t offset, uint32_t bytes);

private:
    bool valid_;

    FlashInterface* flash_;
    FlashSpace flashSpace_;
    uint8_t environment_[VITROIO_CONSTS_ENVIRONMENT_REQUIRED_FLASH_SIZE];

    void setDefaults();

    // Auxiliary method for internal usage to avoid double allocating of buffer
    // (prevent memory fragmentation).
    // Method assumes that the buffer size is minimum maxSectorSize of flash.
    int save(uint8_t* buffer);

    uint32_t getVariable(uint32_t offset, uint32_t bytes) const;
    void setVariable(uint32_t value, uint32_t offset, uint32_t bytes);
};

/**
 * @}
 */

} // namespace impl

} // namespace sdk

} // namespace vitroio

#endif // VITROIO_SDK_ENVIRONMENT_INTERFACE_H
