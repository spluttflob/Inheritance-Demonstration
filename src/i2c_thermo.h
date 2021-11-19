/** @file i2c_thermo.h
 *  This class implements I2C functionality to support I2C based thermal
 *  sensors. Various sensors may be implemented using child classes of this
 *  one. 
 * 
 *  @author JR Ridgely
 *  @date   2021-Nov-16 JRR Original file
 */

#ifndef _I2C_THERMO_H_
#define _I2C_THERMO_H_

#include <Wire.h>
#include "base_thermo.h"


/** @brief   Base class for thermal sensors which use an I2C bus to communicate
 *           with a microcontroller.
 *  @details The I2C thermal sensors need to have an I2C bus object (such as
 *           @c Wire) to which to talk, and they each have an address on that
 *           bus, so these are saved as class member data. Methods are provided
 *           to read and write data to the sensor using I2C. A possibly helpful
 *           method is provided which can scan the I2C bus and show the 
 *           addresses at which devices have been found.
 */
class I2C_Thermo : public BaseThermometer
{
protected:
    TwoWire* _p_i2c;              ///< Pointer to the I2C interface object
    uint8_t _i2c_address;         ///< Address of this sensor on the I2C bus

    // These low-level functions are only for use within this class and/or
    // child classes of this class, so they're in the protected section
    uint16_t i2c_read_2_bytes (uint8_t reg_addr);
    void i2c_write_byte (uint8_t reg_addr, uint8_t a_byte);

public:
    I2C_Thermo (TwoWire* p_i2c, uint8_t i2c_address);

    /** @brief   Gets the I2C address of a given sensor.
     *  @details This function is declared inline because it's very simple and
     *           won't take up much memory. 
     *  @returns The sensor's I2C address, which should be from 1 to 127
     */
    uint8_t get_address (void)
    {
        return _i2c_address;
    }

    void I2C_scan (Print& device = Serial);
};

#endif // _I2C_THERMO_H_
