/** @file base_thermo.h
 *  This file contains a base class for temperature sensors. It is not for
 *  production use, only for use as a demonstration of class inheritance.
 * 
 *  @author JR Ridgely
 *  @date   2021-Nov-16 JRR Original file
 */

#ifndef _BASE_THERMO_H_
#define _BASE_THERMO_H_

#include <Arduino.h>


/** @brief   A base class for many sorts of thermometers.
 */
class BaseThermometer
{
protected:


public:
    // This default constructor doesn't do much
    BaseThermometer (void);

    /** @brief   Pure virtual method to get temperature in degrees Celsius.
     *  @details This method is declared and set "equal" to zero, meaning it
     *           doesn't exist and @b must be declared in child classes. As
     *           this method doesn't exist, one cannot create an object of 
     *           class @c BaseThermometer; one must create objects of child
     *           classes which override this method with something that works.
     *  @returns The measured temperature in degrees Celsius
     */
    virtual float celsius (void) = 0;

    /** @brief   Return the measured temperature in degrees Fahrenheit.
     *  @details Most sensors return Celsius temperature by default, so this
     *           method gets the Celsius temperature and converts it. Child
     *           classes can just use this method and not creeate their own. If
     *           a sensor measures Fahrenheit directly, it can override this
     *           method. This method is declared inline, meaning instead of it
     *           being called as a function (with saving stuff on the stack and
     *           branching and returning), its code will replace the function
     *           call wherever this function is called. That makes things run a
     *           little bit faster but may take a bit of extra program space. 
     *  @returns The measured temperature in Fahrenheit
     */
    virtual float fahrenheit (void)
    {
        return celsius () * 9 / 5 + 32;
    }

};

#endif // _BASE_THERMO_H_

