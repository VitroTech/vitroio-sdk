#ifndef VITROIO_SDK_ABSTRACT_SENSOR_DRIVER_H
#define VITROIO_SDK_ABSTRACT_SENSOR_DRIVER_H

#include <stdint.h>

namespace vitroio
{
    
namespace sdk
{

/**
 * @addtogroup measurement-api
 * @{
 */

/**
 * @brief Virtual class providing interface for sensor drivers. 
 * 
 * @details The aim of this class is to provide interface for basic
 * communication with sensor i.e. initialization, deinitialization, reading,
 * writing and optionally performing sensor specific operations.
 */
class AbstractSensorDriver 
{
public:
    AbstractSensorDriver()
    {}
    
    virtual ~AbstractSensorDriver()
    {}

    /**
     * @brief Function initializes the sensor.
     * 
     * @return Function returns 0 on success or appropriate error code
     * otherwise.
     */
    virtual int open() = 0;

    /**
     * @brief Function deinitializes the sensor.
     */
    virtual void close() = 0;

    /**
     * @brief Function allows to read specified amount of data from provided
     * address.
     * 
     * @param buffer Buffer to which the data will be read.
     * @param address Address from which the data will be read.
     * @param bytes Number of bytes to read.
     * 
     * @return Function returns 0 on success or appropriate error code
     * otherwise.
     */
    virtual int read(char* buffer, uint32_t address, uint32_t bytes) = 0;

    /**
     * @brief Function allows to write specified amount of data to provided
     * address.
     * 
     * @param buffer Buffer with data which will be wrote.
     * @param address Address to which the data will be wrote. 
     * @param bytes Number of bytes to write.
     * 
     * @return Function returns 0 on success or appropriate error code
     * otherwise.
     */
    virtual int write(const char* buffer, uint32_t address, uint32_t bytes) = 0;

    /**
     * @brief Function allows to perform sensor specific operation.
     * 
     * @param request Type of operation to perform.
     * @param value Operation parameters.
     * 
     * @return Function returns 0 on success or appropriate error code
     * otherwise.
     */
    virtual int ioctl(int request, void* value) = 0;
};

/**
 * @}
 */

} // namespace sdk

} // namespace vitroio

#endif // VITROIO_SDK_ABSTRACT_SENSOR_DRIVER_H