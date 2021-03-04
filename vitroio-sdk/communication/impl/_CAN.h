#ifndef VITROIO_SDK_CAN_H
#define VITROIO_SDK_CAN_H

#include <mbed.h>

namespace vitroio
{

namespace sdk
{

namespace impl
{ 

/**
 * @addtogroup communication
 * @{
 */

/**
 * @brief The _CAN class is a simple extenstion of
 * <a href="https://os.mbed.com/docs/latest/apis/can.html">mbed::CAN</a> class.
 * 
 * @details The class inherits from
 * <a href="https://os.mbed.com/docs/latest/apis/can.html">mbed::CAN</a> class.
 * The aim of this class is to provide @ref read_from_irq() method which does
 * not use mutex, because mutexes cannot be used from ISR context. When we want
 * to read messages using IRQ, the only way to clear IRQ is reading of the
 * data. There is an issue on mbed-os github:
 * https://github.com/ARMmbed/mbed-os/issues/5374
 * 
 * @note When the @ref read_from_irq() method is in use, the @ref read() method
 * should not be used in code, because the @ref read_from_irq() method does not
 * guarantee thread safety.
 */
class _CAN : public CAN
{
public:
    _CAN(PinName rd, PinName td, int hz);

    ~_CAN();

    int read_from_irq(CANMessage &msg, int handle=0);

private:
};

/**
 * @}
 */

} // namespace impl

} // namespace sdk

} // namespace vitroio

#endif // VITROIO_SDK_CAN_H