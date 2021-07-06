#ifndef VITROIO_SDK_TRANSPORT_LAYER
#define VITROIO_SDK_TRANSPORT_LAYER

#include <mbed.h>

namespace vitroio {
namespace sdk {

struct IoVec {
    void *iov_base;
    size_t iov_len;
};

class Transport_layer {
    protected:
        uint32_t nodeId_;

        inline Transport_layer(uint32_t nodeId)
            : nodeId_(nodeId)
        {
        }

    public:
        virtual int send(uint32_t parameterId, const IoVec* iov, int iovcnt);
        virtual uint32_t timestamp();
        inline uint32_t nodeId() { return nodeId_; }
};

}
}

#endif // VITROIO_SDK_TRANSPORT_LAYER
