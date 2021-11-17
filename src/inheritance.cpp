/** @file inheritance.cpp
 *    This file contains a main program that creates and tests a child class.
 * 
 *  @author JR Ridgely
 *  @date   2008-Feb-03 Original file
 *  @date   2008-Mar-04 Added multiple inheritance tests
 *  @date   2008-May-06 Changed to use new serial port classes
 *  @date   2009-Jan-29 Changed again to use even newer serial port classes
 *  @date   2020-Nov-05 Ported to STM32 using the Arduino environment
 *  @date   2020-Nov-06 Morphed into inheritance demo and fixed a crash
 */

#include <Arduino.h>
#include <PrintStream.h>
#include "sim_imu.h"


/// A pointer to an IMU object which will be of a child class, not I2C_IMU
I2C_IMU* p_imu = NULL;


/** @brief   The Arduino setup function runs all the tests in this program.
 */
void setup ()
{
    Serial.begin (115200);
    delay (1000);
    Serial << endl << "\033[2JME507 Inherited Method Test" << endl;

    // Create a simulated IMU object. If you look at the code below this line
    // which runs the test, that code doesn't change if other kinds of IMU are
    // used. The object must be static so it's not gone when setup() has exited
    static Sim_IMU wobbly (0x42, "Wobbly");
    p_imu = &wobbly;
}


/** @brief   The Arduino loop function runs some sort of IMU and prints the
 *           accelerations it has found.
 *  @details This function uses a pointer to the IMU object, p_imu, and it
 *           doesn't know nor care which descendent class of I2C_IMU it's
 *           using; it just calls methods that every IMU class supplies. 
 *           If we add a new class that works with an IMU invented next year,
 *           this code won't have to change at all to use that new IMU.
 */
void loop () 
{
    if (p_imu)            // Only do this if the IMU pointer points to an IMU
    {
        // Serial << "AX: " << p_imu->get_ax ()
        //     << ", AY: " << p_imu->get_ay () << ", AZ: " << p_imu->get_az ()
        //     << ", RotX: " << p_imu->get_x_rate () 
        //     << ", RotY: " << p_imu->get_y_rate ()
        //     << ", RotZ: " << p_imu->get_z_rate () << endl;

        Serial << *p_imu << endl;
    }
    delay (1000);
}

