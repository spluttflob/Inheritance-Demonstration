/** @file sim_imu.cpp
 *    This file contains headers for a class which demonstrates class 
 *    inheritance.
 * 
 *  @author JR Ridgely
 *  @date   2020-Nov-06 Original file
 */

#include <Arduino.h>
#include <PrintStream.h>
#include "sim_imu.h"


/** @brief   Construct a simulated IMU.
 *  @details This constructor creates a simulated IMU by calling its parent
 *           constructor to save the I2C address (which will subsequently be
 *           ignored) and saving the simulated IMU name here.
 */
Sim_IMU::Sim_IMU (uint8_t address, const char* name)
    : I2C_IMU (address)
{
    // The Arduino String class actually overloads the "=" operator so one can
    // set the contents of the string from a character array
    this->name = name;
}

/** @brief   Get the currently simulated acceleration in the X direction.
 *  @details We're simulating something that is wobbling bizarrely around.
 *  @returns The simulated X acceleration
 */
float Sim_IMU::get_ax (void)
{
    return (sin (millis () / 5000.0));
}


/** @brief   Get the currently simulated acceleration in the Y direction.
 *  @details In this direction, there's just a little noise rather than large
 *           and crazy motions. 
 *  @returns The simulated Y acceleration
 */
float Sim_IMU::get_ay (void)
{
    return ((float)(random (1000) / 10000.0));
}


/** @brief   Get the currently simulated acceleration in the Z direction.
 *  @details We're simulating something that is wobbling bizarrely around.
 *  @returns The simulated Z acceleration
 */
float Sim_IMU::get_az (void)
{
    return (cos (millis () / 5000.0));
}


/** @brief   Get the currently simulated rotation about the X axis.
 *  @returns The simulated Y rotation
 */
float Sim_IMU::get_y_rate (void)
{
    return -3.14;                       // In rotations per fortnight
}


/** @brief   Overloaded operator which prints information about this IMU.
 *  @param   printer A reference to the @c Print child object such as @c Serial
 *           to which the information will be written
 *  @details This operator depends on the @c Arduino-PrintStream package from
 *           @c https://github.com/spluttflob/Arduino-PrintStream.git
 *  @returns A reference to the printer object so that the string of @c <<
 *           operators on one line can keep going
 */
Print& operator << (Print& printer, Sim_IMU& imu)
{
    // Print the simulated I2C address as the parent class does
    printer << "Simulated IMU at address 0x" << hex << imu.i2c_address 
            << dec << endl;

    // Also print the simulated accelerations and angular rates
    printer << "AX: " << imu.get_ax () << ", AY: " << imu.get_ay () << ", AZ: " 
            << imu.get_az () << ", RotX: " << imu.get_x_rate () << ", RotY: " 
            << imu.get_y_rate () << ", RotZ: " << imu.get_z_rate () << endl;
    return printer;
}

