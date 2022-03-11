#ifndef SHARD_EDGE_H
#define SHARD_EDGE_H

#include <mbed.h>
#include <vitroio-sdk/debug.h>
#include <vitroio-sdk/consts.h>

namespace vitroio
{

namespace sdk
{

class ShardEdge {
public:

    /**
     * @brief Function creates instance of ShardEdge class and set
     * private variables to given input values.
     *
     * @param i2c3Enabled Pass true to enable I2C3. False to disable.
     * @param uartUserEnabled Pass true to enable UART. False to disable.
     * @param spi1Enabled Pass true to enable SPI1. False to disable.
     * @param rs232Enabled Pass true to enable RS232. False to disable.
     * @param adc1_range ADC1 range in Volts. Variable can only take values
     * 2, 4, 8, 16, 30 V. Default value is 30V.
     * @param adc2_range ADC2 range in Volts. Variable can only take values
     * 2, 4, 8, 16, 30 V. Default value is 30V.
     * @param adc3_range ADC3 range in Volts. Variable can only take values
     * 2, 4, 8, 16, 30 V. Default value is 30V.
     * @param adc4_range ADC4 range in Volts. Variable can only take values
     * 2, 4, 8, 16, 30 V. Default value is 30V.
     */
    ShardEdge(bool i2c3Enabled, bool uartUserEnabled, bool spi1Enabled,
        bool rs232Enabled, uint8_t adc1_range, uint8_t adc2_range,
        uint8_t adc3_range, uint8_t adc4_range);

    /**
     * @brief Function configures Shard Edge according to variables
     * set during instance creation.
     *
     * @return Function returns 0 on success or -1 on error.
     *
     */
    int configureShardEdge(void);

    /**
     * @brief Function reads voltage from given ADC port.
     *
     * @param adc_port ADC which is read by this function.
     *
     * @return Function returns voltage already scaled depending on
     * set ADC range.
     */
    double readVoltage(int adc_port);

    /**
     * @brief Function reads current loop value from given CL.
     *
     * @param cl_port CL which is read by this function.
     *
     * @return Function returns current already scaled in mA.
     */
    double readCurrentLoop(int cl_port);





    /**
     * @brief Function manage Shard Edge 24V output
     *
     * @param state definition for the 24V output. Variable can only take values
     * 0 for "OFF", 1 for "ON". Default value is 0.
     *
     * @return Function returns 0 on success or -1 on error.
     */
    int manageShardEdge24V(bool state);

private:
    /**
     * @brief Function reads Shard Edge revision.
     *
     * @param carrierBoardRevision Revision returned by function.
     *
     * @return Function returns 0 on success or error code otherwise.
     */
    int readCarrierBoardRev(char *carrierBoardRevision);

    /**
     * @brief Function gives values which should be passed to IO Expander
     * configuration function. ADCs ranges are taken according to values
     * passed during instance creation.
     *
     * @param adcRange Range for given ADC input.
     *
     * @return Function returns actual data which must be passed to
     * IO Expander configuration function.
     */
    uint8_t configureAdcRange(uint8_t adcRange);

    bool i2c3Enabled_;
    bool uartUserEnabled_;
    bool spi1Enabled_;
    bool rs232Enabled_;
    uint8_t adcRange[4];
    AnalogIn *adcPins[4];
    AnalogIn *clPins[4];
};

} // namespace sdk

} // namespace vitroio
#endif // SHARD_EDGE_H
