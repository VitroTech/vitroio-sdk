#ifndef VITROIO_SDK_TRANSPORT_LAYER
#define VITROIO_SDK_TRANSPORT_LAYER

#include <mbed.h>

namespace vitroio {
namespace sdk {

/**
 * @addtogroup communication
 * @{
 */

/**
 * @brief Structure for dealing with fragmentation of IoTBlocks
 *
 */
struct IoVec {
    void *iov_base; /**<Pointer to chunk */
    size_t iov_len; /**<Length of chunk */
};

/**
 * @brief Virtual class providing interface for communication interfaces
 *
 * @details the aim of this class is to provide interfaces for basic
 * communication with other devices, for sending IoT Blocks.
 */
class Transport_layer {
    protected:
        uint32_t nodeId_;

        inline Transport_layer(uint32_t nodeId)
            : nodeId_(nodeId)
        {
        }

    public:
        /**
         * @brief Function sends given data
         *
         * @param parameterId Id of parameter sent
         * @param iov Pointer to first IoVec with data to be sent @ref IoVec
         * @param iovcnt Count of IoVects to read
         * @return int Status of sending
         */
        virtual int send(uint32_t parameterId, const IoVec* iov, int iovcnt);

        /**
         * @brief Function sends timestamp request and returns timestamp value
         *
         * @return uint32_t Received timestamp
         */
        virtual uint32_t getTimestamp();

        /**
         * @brief Returns node ID.
         *
         * @return uint32_t node ID
         */
        inline uint32_t nodeId() { return nodeId_; }
};
/**
 * @}
 */
}
}

#endif // VITROIO_SDK_TRANSPORT_LAYER
