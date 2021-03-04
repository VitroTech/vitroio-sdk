#ifndef VITROIO_SDK_ABSTRACT_SENSOR_INTERFACE_H
#define VITROIO_SDK_ABSTRACT_SENSOR_INTERFACE_H

#include <stdint.h>

#include <vitroio-sdk/measurement-api/abstract_sensor_driver.h>

namespace vitroio
{

namespace sdk
{

/**
 * @addtogroup measurement-api
 * @{
 */

/**
 * @brief Structure representing sensor parameters values.
 */
struct SensorParameterValue
{
    /**
     * @brief Type of the sensor parameters ID.
     */
    typedef uint32_t ParameterT;
    /**
     * @brief Type of the sensor parameters value.
     */
    typedef uint32_t ValueT;
    
    /**
     * @brief Identifier of sensor parameter.
     */
    ParameterT parameter;
    /**
     * @brief Value of sensor parameter.
     */
    ValueT value;
};

/**
 * @brief Virtual class providing interface for sensor interfaces classes. 
 * 
 * @details The aim of this interface is to allow for reading measurement
 * parameters of all of the sensors in uniform way.
 */
class AbstractSensorInterface 
{
public:
    /**
     * @brief Constructor.
     * 
     * @param driver Pointer to sensors driver object inherited from
     * @ref AbstractSensorDriver.
     */
    AbstractSensorInterface(AbstractSensorDriver* driver) :
        driver_(driver)
    {}
    
    /**
     * @brief Destructor.
     */
    virtual ~AbstractSensorInterface()
    {}

    /**
     * @brief Function allows to obtain parameters measured by the sensor.
     * 
     * @return Function returns pointer to array of sensor parameters codes.
     */
    virtual const uint32_t* getParameters() const = 0;

    /**
     * @brief Function allows to obtain count of parameters measured by
     * the sensor.
     * 
     * @return Function returns number of sensor parameters - it is size
     * of array returned by #getParameters function.
     */
    virtual uint32_t getParametersCount() const = 0;

    /**
     * @brief Function allows to obtain current values of parameters measured
     * by the sensor.
     * 
     * @param values Buffer for parameters values, its size have to be
     * at least count of sensor parameters.
     * 
     * @return Function returns number of read values.
     */ 
    virtual uint32_t getValues(SensorParameterValue* values) = 0;

protected:
    /**
     * @brief Function allows to obtain pointer to sensor driver.
     * 
     * @return Function returns pointer to sensor driver passed to the
     * constructor.
     */
    AbstractSensorDriver* driver()
    {
        return driver_;
    }

private:
    AbstractSensorDriver* driver_;
};

/**
 * @}
 */

} // namespace sdk

} // namespace vitroio

#endif // VITROIO_SDK_ABSTRACT_SENSOR_INTERFACE_H