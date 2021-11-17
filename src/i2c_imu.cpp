/** @file i2c_imu.cpp
 *    This file contains source code for a class which demonstrates class 
 *    inheritance.
 * 
 *  @author JR Ridgely
 *  @date   2020-Nov-06 Original file
 */

#include <PrintStream.h>
#include "i2c_imu.h"


/** @brief   Base IMU constructor which saves the I2C address.
 *  @param   address The address of the IMU on its I2C bus
 */
I2C_IMU::I2C_IMU (uint8_t address)
{
    this->i2c_address = address;
}


/** @brief   Return the rate of rotation about the X axis.
 *  @details The rotation rate returned by this base class is zero; this might
 *           be useful if using an accelerometer as a dirt-cheap IMU that
 *           isn't sensitive to rotation rate. OK, this is a lame excuse.
 *  @returns The rotation rate about the X axis
 */
float I2C_IMU::get_x_rate (void)
{
    return 0.0;
}


/** @brief   Return the rate of rotation about the Y axis.
 *  @details The rotation rate returned by this base class is zero; this might
 *           be useful if using an accelerometer as a dirt-cheap IMU that
 *           isn't sensitive to rotation rate. 
 *  @returns The rotation rate about the Y axis
 */
float I2C_IMU::get_y_rate (void)
{
    return 0.0;
}


/** @brief   Return the rate of rotation about the Z axis.
 *  @details The rotation rate returned by this base class is zero; this might
 *           be useful if using an accelerometer as a dirt-cheap IMU that
 *           isn't sensitive to rotation rate. 
 *  @returns The rotation rate about the Z axis
 */
float I2C_IMU::get_z_rate (void)
{
    return 0.0;
}


/** @brief   Overloaded operator which prints information about this IMU.
 *  @param   printer A reference to the @c Print child object such as @c Serial
 *           to which the information will be written
 *  @details This operator depends on the @c Arduino-PrintStream package from
 *           @c https://github.com/spluttflob/Arduino-PrintStream.git
 *  @returns A reference to the printer object so that the string of @c <<
 *           operators on one line can keep going
 */
Print& operator << (Print& printer, I2C_IMU& imu)
{
    printer << "IMU at address 0x" << hex << imu.i2c_address << dec << endl;
    return printer;
}

