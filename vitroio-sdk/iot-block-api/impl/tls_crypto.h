#ifndef TLS_CRYPTO_H
#define TLS_CRYPTO_H

#include <mbed.h>

namespace vitroio
{

namespace sdk
{

namespace impl
{

class TLSCrypto {
public:

	TLSCrypto();

	/**
	 * @brief Encrypt node's data with AES-256-CBC algorithm
	 *
	 * @param node_info Structure which contains data to be encrypted:
	 * - sensor data value
	 * - parameter ID
	 * 
	 * @param data_size length of data to be encrypted. Notice that if input data
	 * is multiple of block size (16 bytes), a whole new block is needed by algorithm.
	 * Output of AES-256 will have then 32 bytes, not 16.
	 * 
	 * @param blob Encrypted data with already included IV,
	 * if AES algorithm worked successfully
	 * 
	 * @return Function returns 0 on success or -1 on failure
	 * 
	 */
	int aesEncrypt(uint8_t *data,  uint16_t data_size, uint8_t *blob);

	/**
	 * @brief Decrypt data with AES-256-CBC algorithm
	 * 
	 * @param blob Previously encrypted data with AES-256-CBC algorithm
	 * 
	 * @param blob_size Size of entire BLOB (with IV included)
	 * 
	 * @param decrypted_buffer Decrypted message if success
	 *
	 * @return Function returns 0 on success or -1 on failure
	 * 
	 */
	int aesDecrypt(uint8_t *blob, uint16_t blob_size, uint8_t *decrypted_buffer);

	/**
	 * @brief Generate random data
	 *
	 * @param data Generated random data if success
	 * 
	 * @param data_len Data length to be generated in bytes.
	 * 
	 * @return Function returns 0 on success or -1 on failure
	 * 
	 */
	int genRandomData(uint8_t *data, uint16_t data_len);
};

} // namespace impl

} // namespace sdk

} // namespace vitroio

#endif // TLS_CRYPTO_H
