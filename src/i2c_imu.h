/** @file i2c_imu.h
 *    This file contains headers for a class which demonstrates class 
 *    inheritance.
 * 
 *  @author JR Ridgely
 *  @date   2020-Nov-06 Original file
 */

#include <Arduino.h>


/** @brief   Base class for IMU's which are on an I2C bus.
 */
class I2C_IMU
{
protected:
    uint8_t i2c_address;                  ///< Address of IMU on the I2C bus

public:
    I2C_IMU (uint8_t address);          // Constructor saves bus address

    // The following methods are pure virtual in this class, meaning that they
    // are specified here, but no function is supplied. This means that one can
    // never create an object of class I2C_IMU; it may only be used as a base
    // class for implementations that work with a real or simulated IMU
    virtual float get_ax (void) = 0;    ///< Get acceleration in X direction
    virtual float get_ay (void) = 0;    ///< Get acceleration in Y direction
    virtual float get_az (void) = 0;    ///< Get acceleration in Z direction

    // The following methods will be supplied in this class; they may be
    // overridden in descendent classes or inherited from this base class
    virtual float get_x_rate (void);    ///< Get rotation rate about X axis
    virtual float get_y_rate (void);    ///< Get rotation rate about Y axis
    virtual float get_z_rate (void);    ///< Get rotation rate about Z axis

    // The following method is specified completely in this file; it may be
    // overridden in descendent classes or inherited and used as given here
    virtual void reset (void) { }       ///< Optional method to reset IMU

    // The overloaded shift operator declared below must be included as a
    // "friend" of this class to be allowed access to protected class members
    friend Print& operator << (Print& printer, I2C_IMU& imu);

    virtual Print& operator << (Print& printer);
};

// // Here we overload the "<<" operator so that when there's a reference to 
// // an item of a child class of Print (such as Serial) on the left of the
// // operator and an I2C_IMU on the right, information about the IMU is shown
// // virtual Print& operator << (Print& printer);
// Print& operator << (Print& printer, I2C_IMU& imu);
