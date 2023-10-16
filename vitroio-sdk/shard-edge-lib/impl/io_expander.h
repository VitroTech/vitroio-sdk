#ifndef IO_EXPANDER_H
#define IO_EXPANDER_H

#include <mbed.h>
#include <vitroio-sdk/debug.h>
#include <vitroio-sdk/consts.h>

#define IOEXPANDER_CMD_READ_0           0x00
#define IOEXPANDER_CMD_READ_1           0x01
#define IOEXPANDER_CMD_WRITE_0          0x02
#define IOEXPANDER_CMD_WRITE_1          0x03
#define IOEXPANDER_CMD_CONFIGURE_0      0x06
#define IOEXPANDER_CMD_CONFIGURE_1      0x07

namespace vitroio
{

namespace sdk
{

namespace impl
{

class IOExpander {
public:

    /**
     * @brief Creates instance of IOExpander class.
     *
     * @param sda_pin SDA pin of I2C.
     * @param scl_pin SCL pin of I2C.
     *
     */
    IOExpander(PinName sda_pin, PinName scl_pin);

    /**
     * @brief Destructor for IOExpander class.
     */
    ~IOExpander();

    /**
     * @brief Function configures IOs direction of port to output
     * or input state. Each IO of given port can be configured
     * independently.
     *
     * @param address I2C address of IO Expander.
     * @param port_number Port number which will be configured.
     * This variable can only take value 0x00 or 0x01.
     * @param config Direction of each IO in configured port.
     * 0 means output, 1 means input.
     *
     * @return Function returns 0 on success or appropriate error code
     * otherwise.
     */
    int configurePort(int address, uint8_t port_number, char config);

    /**
     * @brief Function reads state of given input port.
     *
     * @param address I2C address of IO Expander.
     * @param port_number Port number which will be read.
     * This variable can only take value 0x00 or 0x01.
     * @param portState If read successfully, this variable contains
     * state of each input of read port.
     *
     * @return Function returns 0 on success or appropriate error code
     * otherwise.
     */
    int readInputPort(int address, uint8_t port_number, char *portState);

    /**
     * @brief Function writes state to given output port.
     *
     * @param address I2C address of IO Expander.
     * @param port_number Port number which will be written.
     * This variable can only take value 0x00 or 0x01.
     * @param data Data which will be written to port. Each bit corresponds
     * to an output IO number.
     *
     * @return Function returns 0 on success or appropriate error code
     * otherwise.
     */
    int writeOutputPort(int address, uint8_t port_number, char data);

private:
    I2C* i2c_;
};

} // namespace impl

} // namespace sdk

} // namespace vitroio
#endif // IO_EXPANDER_H
