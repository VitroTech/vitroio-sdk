#ifndef VITROIO_SDK_CAN_LAYER
#define VITROIO_SDK_CAN_LAYER

#include <mbed.h>
#include "transport_layer.h"

#include <vitroio-sdk/communication/canbus.h>

namespace vitroio {

namespace sdk {
    class Can_layer: public Transport_layer {
            Canbus *bus_;
            uint32_t timestamp_;

            void frameReceivedCallback(const CanbusFrame& frame);
            int computeCRC(const IoVec *iov, int iovcnt, uint32_t *crc_value);

        public:
            Can_layer(Canbus *bus, uint32_t nodeId);

            int send(uint32_t parameterId, const IoVec* iov, int iovcnt);
            uint32_t getTimestamp();
    };
}

}

#endif // VITROIO_SDK_CAN_LAYER
