/** @file sim_thermo.cpp
 *  This file contains a class which simulates a thermometer.
 * 
 *  @author JR Ridgely
 *  @date   2021-Nov-18 Original file
 */

#include "sim_thermo.h"


/** @brief   Create a simulated thermometer with the given properties.
 */
SimThermometer::SimThermometer (float average, float amplitude, float period, 
                                float rando)
{
    // Save the parameters in class member data to they're not lost when this
    // constructor function exits
    _average = average;
    _amplitude = amplitude;
    _period = period;
    _rando = rando;

    // Initialize the time counter
    sim_time_count = 0;
}   


/** @brief   Compute a simulated temperature and return it.
 *  @details To make the simulation interesting, the temperature varies in a
 *           sinusoidal fashion and random noise can be added to it. 
 *  @returns The simulated temperature in degrees Celsius
 */
float SimThermometer::celsius (void)
{
    // Calculate the new simulated temperature
    float sim_temp = _average;
    sim_temp += _amplitude * sin (sim_time_count * 2 * PI / _period);
    sim_temp += random (-1000, 1000) * _rando / 1000.0;

    // Advance the count of simulated time
    sim_time_count++;

    return sim_temp;
}
