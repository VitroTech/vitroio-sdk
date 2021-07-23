#ifndef VITROIO_SDK_CAN_LAYER
#define VITROIO_SDK_CAN_LAYER

#include <mbed.h>
#include "transport_layer.h"

#include <vitroio-sdk/communication/canbus.h>

namespace vitroio {

namespace sdk {
/**
 * @addtogroup communication
 * @{
 */
    /**
     * @brief This class implements CAN bus transport layer for IoT Blockss
     * 
     */
    class Can_layer: public Transport_layer {
            Canbus *bus_;
            uint32_t timestamp_;

            /**
             * @brief Callback on frame receive
             * 
             * @param frame Received frame
             */
            void frameReceivedCallback(const CanbusFrame& frame);

            /**
             * @brief Function computes CRC of data send via CAN bus to Crystal
             * 
             * @param iov Chunks of data 
             * @param iovcnt Count of chunks 
             * @param crc_value Pointer to save CRC
             * @return int Status
             */
            int computeCRC(const IoVec *iov, int iovcnt, uint32_t *crc_value);

        public:

            /**
             * @brief Construct a new Can_layer object
             * 
             * @param bus Pointer to Canbus object 
             * @param nodeId nodeId value
             */
            Can_layer(Canbus *bus, uint32_t nodeId);

            /**
             * @brief Function sends given data
             * 
             * @param parameterId Id of parameter sent
             * @param iov Pointer to first IoVec with data to be sent @ref IoVec
             * @param iovcnt Count of IoVects to read
             * @return int Status of sending
             */
            int send(uint32_t parameterId, const IoVec* iov, int iovcnt);

            /**
             * @brief Function sends timestamp request and returns timestamp value
             * 
             * @return uint32_t Received timestamp
             */
            uint32_t getTimestamp();
    };
/**
 * @}
 */
}

}

#endif // VITROIO_SDK_CAN_LAYER
