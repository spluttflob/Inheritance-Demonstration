/** @file mcp9808.cpp
 *  This file contains a driver for an MCP9808 digital thermometer. The driver
 *  is implemented as a child class of a base thermometer class to illustrate
 *  how class inheritance can work.
 * 
 *  @author JR Ridgely
 *  @date   2021-Nov-18 Original file
 */

#include "mcp9808.h"

// These constants are only used in this file, so they're made global here
const uint8_t REG_CONFIG = 0x01;    ///< Configuration register
const uint8_t REG_T_UPPER = 0x02;   ///< Upper boundary temperature register
const uint8_t REG_T_LOWER = 0x03;   ///< Lower boundary temperature register
const uint8_t REG_T_CRIT = 0x04;    ///< Critical temperature register
const uint8_t REG_T_AMB = 0x05;     ///< Ambient measured temperature register
const uint8_t REG_MFR_ID = 0x06;    ///< Manufacturer ID register
const uint8_t REG_DEV_ID = 0x07;    ///< Device ID and revision register
const uint8_t REG_RESOL = 0x08;     ///< Resolution register
const uint8_t MFR_ID = 0x54;    ///< Expected value in Manufacturer ID register


/** @brief   Create an MCP9808 sensor interface object.
 *  @param   p_i2c A pointer to an I2C ("TwoWire" in Arduino-ese) object which 
 *           has already been set up (created and its @c .begin() method run)
 *  @param   i2c_address The address of this sensor on the I2C bus (default is
 *           0x18, the address on an unadjusted Adafruit breakout board)
 */
MCP9808::MCP9808 (TwoWire* p_i2c, uint8_t i2c_address)
    : I2C_Thermo (p_i2c, i2c_address)
{
    // Check to ensure that there's really a valid sensor there and that it
    // returns the expected manufacturer specified ID number
    uint16_t test_bytes = i2c_read_2_bytes (REG_MFR_ID);
    if (test_bytes != MFR_ID)
    {
        Serial << "ERROR: Invalid MFR ID " << test_bytes << " from MCP9808(?)"
               << endl;
    }
}


/** @brief   Read a raw temperature (uncalibrated binary number) from the 
 *           sensor.
 *  @returns The 16-bit number containing the bytes returned by the sensor
 */
uint16_t MCP9808::raw_temp (void)
{
    return i2c_read_2_bytes (REG_T_AMB);
}


/** @brief   Get a measurement of the MCP9808's temperature in degrees Celsius.
 *  @details First the raw data is obtained from the sensor, then it's 
 *           converted into a Celsius reading. Note that if you want a reading
 *           in Fahrenheit ('cause this is Merica) that conversion is already
 *           supplied in the (grand)parent class @c BaseThermometer.
 *  @returns The measured temperature in Celsius
 */
float MCP9808::celsius (void)
{
    uint16_t raw_data = raw_temp ();
    float cooked_temp = (raw_data & 0x000F) / 16.0;
    cooked_temp += (float)((raw_data & 0x0FF0) >> 4);
    if (raw_data & 0x1000)
    {
        cooked_temp *= -1.0;
    }
    return cooked_temp;
}
