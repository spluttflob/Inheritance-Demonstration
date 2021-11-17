/** @file sim_imu.h
 *    This file contains headers for a class which demonstrates class 
 *    inheritance.
 * 
 *  @author JR Ridgely
 *  @date   2020-Nov-06 Original file
 */

#include <Arduino.h>
#include "i2c_imu.h"


/** @brief   Class for a simulated IMU which pretends to be on an I2C bus.
 */
class Sim_IMU : public I2C_IMU
{
protected:
    // All the variables belonging to I2C_IMU are inherited, but we may add
    // more if there's a reason to do so
    String name;

public:
    // Constructor saves bus address and a name for the simulated IMU
    Sim_IMU (uint8_t address, const char* name);

    // The following methods were pure virtual in the parent class and must be
    // given as real functions here
    float get_ax (void);                // Get acceleration in X direction
    float get_ay (void);                // Get acceleration in X direction
    float get_az (void);                // Get acceleration in X direction

    // The following methods are supplied in the parent class; we'll override
    // one and use the other ones as inherited
    float get_y_rate (void);            // Get rotation rate about Y axis

    //  This function is defined entirely right here for convenience:
    /// A getter function which returns the name of this simulated IMU
    const String& get_name (void) { return name; }

    // The overloaded shift operator declared below must be included as a
    // "friend" of this class to be allowed access to protected class members
    friend Print& operator << (Print& printer, Sim_IMU& imu);
};

// This overloaded "<<" operator prints information specific to a simulated
// IMU, overriding the parent class's operator. Note the difference between
// overloading (function and operator thing) and overriding (a class thing)
Print& operator << (Print& printer, Sim_IMU& imu);

