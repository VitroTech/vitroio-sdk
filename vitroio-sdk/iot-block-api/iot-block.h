#ifndef IOT_BLOCK_H
#define IOT_BLOCK_H

#include <vitroio-sdk/communication/canbus.h>
#include <vitroio-sdk/communication/transport_layer.h>

#define AES_BLOCK_SIZE          16

#define AES_IV_LEN              16

/**
 * @brief Size of parameter Id field
 * 
 */
#define PARAMETER_ID_SIZE       2

/**
 * @brief Size of node Id field
 * 
 */
#define NODE_ID_SIZE            9

/**
 * @brief Size of timestamp
 * 
 */
#define TIMESTAMP_SIZE          4

/**
 * @brief Size of SHA256 digest
 * 
 */
#define SHA256_DIGEST_SIZE      32

/**
 * @brief Size of ECDSA signature
 * 
 */
#define ECDSA_SIGNATURE_SIZE    64

/**
 * @brief Additional data to be sent with blob.
 * 
 */
#define METADATA_SIZE (PARAMETER_ID_SIZE + NODE_ID_SIZE + TIMESTAMP_SIZE + \
    SHA256_DIGEST_SIZE + ECDSA_SIGNATURE_SIZE) 

#define MAX_BLOCK_SIZE (7 * 255)
#define MAX_PD_SIZE (MAX_BLOCK_SIZE - METADATA_SIZE)

#define DATA_BLOB_SIZE          AES_IV_LEN + DATA_TO_ENCRYPT_SIZE
#define CAN_DATA_SIZE           147

#define TIMESTAMP_REQUEST_PARAMETER_ID 0x40

namespace vitroio
{

namespace sdk
{

/**
 * @brief Class is an API for creating and sending IoT Blocks
 * 
 * @details The class wraps all crypto operations needed for creating IoT blocks.
 * The last prepared block is stored in an object of this class and the pointer
 * to the block can be acquired with get_iot().
 * 
 */

class IoTBlock {
public:

    /**
     * @brief Structure contains node's data needed for encryption and final
     * CAN frame
     * 
     * @details All members of structure are required to be sent in CAN frame.
     * Sensor's value is encrypted and together with Intialization Vector
     * creates blob.
     * nodeID, parameterID and timestamp are evident and placed at the top of
     * encrypted data.
     * digest is a result of SHA256 hash function on blob + parameterID +
     * nodeID + timestamp.
     * signature is created only on digest.
     * 
     * @note Structure has packed attribute to ensure that it is placed in
     * non-padded, contiguous memory area
     */

    struct __attribute__((packed)) Frame
    {
        uint16_t parameterID;
        uint8_t nodeID[NODE_ID_SIZE];
        uint32_t timestamp;
        uint8_t blob[MAX_PD_SIZE];
        uint8_t digest[SHA256_DIGEST_SIZE];
        uint8_t signature[ECDSA_SIGNATURE_SIZE];
    };

    /**
     * @brief IoTBlock predefined sizes.
     * 
     */
    typedef enum{
        SIZE_S = 16,
        SIZE_M = 128,
        SIZE_L = 512,
        SIZE_XL = 1024
    } IoTBlock_Sizes_t;

    /**
     * @brief Construct a new IoT Block object
     * 
     * @param comm Pointer to transport layer to be used.
     */
    IoTBlock(Transport_layer *comm);

    /**
     * @brief Prepare IoT block consisting of the Initialize Vector, encrypted
     * data, parameter ID, node Id, timestamp, digest, and signature
     *
     * @param data sensor data value
     * 
     * @param parameter sensor's data type ID
     * 
     */
    void make(uint32_t data, uint32_t parameter);

    /**
     * @brief Prepare IoT block consisting of the Initialize Vector, encrypted
     * data, parameter ID, node Id, timestamp, digest, and signature
     * 
     * @param data Pointer to data to be encrypted
     * @param dataLen Length of data given
     * @param parameter Parameter ID 
     */
    void make(void* data, size_t dataLen, uint32_t parameter);

    /**
     * @brief Prepare IoT block consisting of the Initialize Vector, encrypted
     * data, parameter ID, node Id, timestamp, digest, and signature. Make sure
     * that there is enough data for given size.
     * 
     * @param data Pointer to data to be encrypted
     * @param size IoTBlock size @ref IoTBlock_Sizes_t
     * @param parameter Parameter ID 
     */
    void make(void* data, IoTBlock_Sizes_t size, uint32_t parameter);

    /**
     * @brief Send IoT Block by CAN bus. Before sending, the Block has to be
     * prepared with the make() method
     * 
     */
    void send();


    /**
     * @brief Return pointer to Frame structure. The structure contains
     * whole IoT block.
     * 
     */
    Frame* get_frame();

    /**
     * @brief Return pointer to uint8_t array of CAN_DATA_SIZE size. The array
     * contains whole IoT block.
     * 
     */
    uint8_t* get_frame_as_array();

    /**
     * @brief Prints whole Iot Block data.
     * 
     */
    void print();

    /**
     * @brief Get the blob size
     * 
     * @return uint32_t 
     */
    uint32_t get_blob_size();

private:
    Transport_layer* comm_port;
    uint32_t frameSize;
    uint32_t blobSize;
    
    int create_blob(const uint8_t* plaintext, uint16_t plaintext_len, uint8_t* blob);
};

} // namespace sdk

} // namespace vitroio

#endif // IOT_BLOCK_H
