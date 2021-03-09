#ifndef ECC508_H
#define ECC508_H

#define AES_256_KEY_LEN     32
#define SLOT_8_SIZE 		416
#define ECC_DEBUG 			0
#define CRC_WIDTH 			32
#define SERIAL_NUM_SIZE		9

#include <mbed.h>
#include <vitroio-sdk/iot-block-api/impl/mbed-cryptoauthlib/cryptoauthlib/lib/cryptoauthlib.h>
namespace vitroio
{

namespace sdk
{

namespace impl
{

class Ecc508 {
public:
    ATCAIfaceCfg gCfg;
    uint8_t serial[SERIAL_NUM_SIZE];
	/**
	 * @brief Configure ECC chip to communicate over I2C bus
	 */
	Ecc508();

	/**
	 * @brief Read serial number from ECC chip
	 *
	 * @param serial_num Serial number returned by ECC chip if success
	 * 
	 * @return Function returns 0 on success or error code otherwise
	 * 
	 */
    ATCA_STATUS readSerial(uint8_t *serial_num);

	/**
	 * @brief Count SHA-256 checksum of input data
	 *
	 * @param data_to_sha Data to be hashed
	 * @param data_len Length of data to be hashed
	 * @param digest Calculated digest if success
	 * 
	 * @return Function returns 0 on success or error code otherwise
	 * 
	 */
    ATCA_STATUS countSHA256(uint8_t* data_to_sha, uint16_t data_len, uint8_t* digest);

	/**
	 * @brief Sign data using ECDSA algorithm
	 *
	 * @param data Data to be signed
	 * @param signature Calculated signature after success operation
	 * 
	 * @return Function returns 0 on success or error code otherwise
	 * 
	 */
    ATCA_STATUS signData(uint8_t *data, uint8_t *signature);

	/**
	 * @brief Verify previously generated signature
	 *
	 * @param data Data signed previously
	 * @param signature Signature of data
	 * @param isVerfied true if signature is correct, false otherwise
	 * 
	 * @return Function returns 0 on success or error code otherwise
	 * 
	 */
    ATCA_STATUS verifySignature(uint8_t *data, uint8_t *signature, bool *isVerfied);

	/**
	 * @brief Read symmetric key stored in ECC chip
	 * 
	 * @param sym_key symmetric key stored in ECC's slot
	 * 
	 * @return Function returns 0 on success or error code otherwise
	 * 
	 */
	ATCA_STATUS readSymKey(uint8_t *sym_key);
};

} // namespace impl

} // namespace sdk

} // namespace vitroio
#endif // ECC508_H
