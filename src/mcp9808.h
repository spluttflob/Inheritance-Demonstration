/** @file mcp9808.h
 *  This file contains a driver for an MCP9808 digital thermometer. The driver
 *  is implemented as a child class of a base thermometer class to illustrate
 *  how class inheritance can work.
 * 
 *  @author JR Ridgely
 *  @date   2021-Nov-18 Original file
 */

#ifndef _MCP9808_H_
#define _MCP9808_H_

#include <Arduino.h>
#include <PrintStream.h>
#include <Wire.h>
#include "i2c_thermo.h"


/** @brief   Driver for the Microchip MCP9808 temperature sensor IC.
 *  @details The 7-bit I2C address of the sensor is comprised of four fixed
 *           bits, 6 through 3, which are always 0011, and three more bits that
 *           are controlled by pins A2, A1, and A0. 
 */
class MCP9808 : public I2C_Thermo
{
protected:
    // Perhaps we don't need any particular data for this sensor, just methods

public:
    MCP9808 (TwoWire* p_i2c, uint8_t i2c_address = 0x18);
    uint16_t raw_temp (void);
    float celsius (void);
};

#endif // _MCP9808_H_

