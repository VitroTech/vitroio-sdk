#ifndef VITROIO_SDK_CANBUS_FRAME_H
#define VITROIO_SDK_CANBUS_FRAME_H

#include <mbed.h>

namespace vitroio
{

namespace sdk
{

/**
 * @addtogroup communication
 * @{
 */

/**
 * @brief Class is a wrapper for
 * <a href="https://os.mbed.com/docs/v5.10/mbed-os-api-doxy/classmbed_1_1_c_a_n_message.html">mbed::CANMessage</a>.
 * It provides interface allowing creation of frames complied with vitroio
 * protocol.
 */
class CanbusFrame
{
public:
    CanbusFrame();

    ~CanbusFrame();

    /**
     * @brief Function allows to set node ID for the frame.
     * 
     * @param id Node ID to set
     */
    void setNodeId(uint32_t id);

    /**
     * @brief Function allows to set parameter ID for the frame.
     * 
     * @param id Parameter ID to set
     */
    void setParameterId(uint32_t id);

    /**
     * @brief Function allows to set data length of the frame.
     * 
     * @param length Data length in bytes
     * 
     * @return Function returns true on success or false otherwise.
     */
    bool setDataLength(uint32_t length);
    
    /**
     * @brief Function allows to obtain node ID from the frame.
     * 
     * @return Function returns node ID of the frame.
     */
    uint32_t nodeId() const;

    /**
     * @brief Function allows to obtain parameter ID from the frame.
     * 
     * @return Function returns parameter ID of the frame.
     */
    uint32_t parameterId() const;

    /**
     * @brief Function allows to obtain data length of the frame.
     * 
     * @return Function returns length of the frame data.
     */
    uint32_t dataLength() const;

    /**
     * @brief Function allows to obtain maximum data length of the frame.
     * 
     * @return Function returns maximum size of frame data. 
     */
    uint32_t maxDataLength() const;

    /**
     * @brief Function allows a direct access to the frame data for
     * modifications.
     * 
     * @note This function should be used with dataLength() function to avoid
     * exceeding address range.
     * 
     * @return Function returns pointer to buffer of frame data.
     */
    char* data();

    /**
     * @brief Function allows to get frame data for reading.
     * 
     * @note This function should be used with dataLength() function to avoid
     * exceeding address range.
     * 
     * @return Function returns constant pointer to buffer of frame data.
     */
    const char* data() const;

private:
    friend class Canbus;

    CANMessage message_;

    CANMessage* message();
    const CANMessage* message() const;
};

/**
 * @}
 */

} // namespace sdk

} // namespace vitroio

#endif // VITROIO_SDK_CANBUS_FRAME_H