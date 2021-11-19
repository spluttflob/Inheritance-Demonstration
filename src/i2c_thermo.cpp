/** @file i2c_thermo.cpp
 *  This class implements I2C functionality to support I2C based thermal
 *  sensors. Various sensors may be implemented using child classes of this
 *  one. 
 * 
 *  @author JR Ridgely
 *  @date   2021-Nov-16 JRR Original file
 */

#include <Arduino.h>
#include <PrintStream.h>
#include "i2c_thermo.h"


/** @brief   Set up the base class for I2C temperature sensors.
 *  @details This constructor does things which all I2C temperature sensors 
 *           need to do. Child classes will do device specific setup. The
 *           parent class's constructor is called on the @c :BaseThermometer()
 *           line; the parent class constructor doesn't take any parameters.
 *  @param   p_i2c A pointer to an I2C ("TwoWire" in Arduino-ese) object which 
 *           has already been set up (created and its @c .begin() method run)
 *  @param   i2c_address The address of a specific sensor on the I2C bus
 */
I2C_Thermo::I2C_Thermo (TwoWire* p_i2c, uint8_t i2c_address)
    : BaseThermometer ()
{
    // Save the parameters in class member data so they're not lost when the
    // constructor exits
    _p_i2c = p_i2c;
    _i2c_address = i2c_address;
}


/** @brief   Scan the I2C bus and print a list of the devices which have been
 *           found.
 *  @details This function is modified from the example at
 *           @c https://playground.arduino.cc/Main/I2cScanner/.
 *  @param   device A pointer to the stream such as @c Serial on which the
 *           results of the scan are to be printed. If nothing is specified, 
 *           the default (@c Serial) will be used
 */
void I2C_Thermo::I2C_scan (Print& device)
{
    uint8_t error;
    uint8_t nDevices = 0;

    device << "I2C Scan: ";
    for (uint8_t address = 8; address < 127; address++)
    {
        // Use the pointer _p_i2c to access the I2C bus object (usually "Wire")
        // Use the return value of endTransmisstion() to see if a device
        // has acknowledged the address
        _p_i2c->beginTransmission (address);
        error = _p_i2c->endTransmission (); 

        if (error == 0)
        {
            device << "0x" << hex << (uint16_t)address << dec << " ";
            nDevices++;
        }
        else if (error == 1)
        {
            device << "I2C timeout at " << hex 
                   << (uint16_t)address << dec << endl;
        }
        delay (2);
    }
    if (nDevices)
    {
        device << endl;
    }
    else
    {
        device << "No I2C devices found" << endl;
    }
}


/** @brief   Read two bytes from registers in an I2C sensor.
 *  @param   reg_addr The address of the register @b within the sensor (not the
 *           address of the sensor; that's known from class member data)
 *  @returns The two bytes read, combined into a 16 bit integer
 */
uint16_t I2C_Thermo::i2c_read_2_bytes (uint8_t reg_addr)
{
    uint16_t from_sensor;            // Holds bytes sent to us by sensor

    // Get an I2C communication going to the I2C address of the sensor
    _p_i2c->beginTransmission (_i2c_address);

    // Tell the sensor which register address we want to read
    _p_i2c->write (reg_addr);

    // End this part of the communication. If error is nonzero, return (-1)
    uint8_t error = _p_i2c->endTransmission ();
    if (error)
    {
        return 0xFFFF;
    }

    // Now request two bytes of data
    _p_i2c->requestFrom (_i2c_address, 2);

    // If we have received two bytes, put 'em together and return 'em
    if (2 <= _p_i2c->available ()) 
    { 
        from_sensor = _p_i2c->read ();      // Receive high byte first
        from_sensor <<= 8;                  // Shift it to higher 8 bits
        from_sensor |= _p_i2c->read ();     // Receive low byte as lower 8 bits
    }
    else
    {
        from_sensor = 0xFFFF;               // Return -1 as an error code
    }
    return from_sensor;
}


/** @brief   Write a single-byte number to a register in an I2C sensor.
 *           (Not currently implemented)
 *  @param   reg_addr The register address within the sensor to which to write
 *  @param   a_byte The byte to be written
 */
void I2C_Thermo::i2c_write_byte (uint8_t reg_addr, uint8_t a_byte)
{
    Serial << "ERROR: I2C_thermo::i2c_write_byte() not implemented" << endl;
}


