#ifndef VITROIO_SDK_TYPES_H
#define VITROIO_SDK_TYPES_H

#define ATCA_ECC_CONFIG_SIZE        (128)        //!< size of configuration zone

/**
 * @file vitroio-sdk/types.h
 * 
 * @brief The file contains types used by vitro-shard-sdk.
 */
#include <mbed.h>

namespace vitroio
{

namespace sdk
{
/**
 * @breif type representing name (id) of application
 */
struct FirmwareId
{
    uint16_t id;
    
    /**
     * @brief Constructor initializes the structure.
     * 
     * @param id Value of name (id) of application
     */
    FirmwareId(uint16_t id);
    
    /**
     * @brief Constructor initializes the structure.
     * 
     * @param buffer buffer containing version as binary
     */
    FirmwareId(const uint8_t* buffer);
    
    bool operator!=(const FirmwareId &v);
    
    int toInt();
};
/**
 * @brief Structure representing version in format major.minor.patch.
 */
struct Version
{
    uint8_t     major;
    uint8_t     minor;
    uint8_t     patch;
    uint8_t     rc;

    /**
     * @brief Constructor initializes the structure.
     * 
     * @param amajor Value of major part of version
     * @param aminor Value of minor part of version
     * @param apatch Value of patch part of version
     * @param rc Value of realase candidate part of version
     */
    Version(uint8_t amajor, uint8_t aminor, uint8_t apatch, uint8_t rc);
    
    /**
     * @brief Constructor initializes the structure.
     * 
     * @param buffer buffer containing version as binary
     */
    Version(const uint8_t* buffer);

    bool operator>(const Version &v);
    
    int toInt();
};

/**
 * @brief Structure representing space of flash memory.
 */
struct FlashSpace
{
    /**
     * @brief Specifies offset of flash memory in bytes.
     * 
     * @note The size of flash space is specified in sectors count, therefore
     * the offset has to be aligned to the sector size (it must be an address
     * of new sector).
     */
    uint32_t offset;

    /**
     * @brief Specifies size of flash memory in sectors count.
     */
    uint32_t sectors;

    /**
     * @brief Contructor initializes the structure.
     * 
     * @param aoffset Offset value
     * @param asectors Sectors value
     */
    FlashSpace(uint32_t aoffset, uint32_t asectors);
};

} // namespace sdk

} // namespace vitroio

extern const uint8_t test_ecc_configdata[ATCA_ECC_CONFIG_SIZE];

#endif // VITROIO_SDK_TYPES_H
