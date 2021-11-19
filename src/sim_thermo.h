/** @file sim_thermo.h
 *  This file contains a class which simulates a thermometer.
 * 
 *  @author JR Ridgely
 *  @date   2021-Nov-18 Original file
 */

#ifndef _SIM_THERMO_H_
#define _SIM_THERMO_H_

#include "base_thermo.h"


/** @brief   Class which simulates a thermometer.
 *  @details This class simulates a thermometer by producing slowly varying
 *           readings around room temperature (ish) with some added random
 *           noise. It might be useful to test temperature logging or control
 *           software as one waits for actual sensors to come by SnailMail. 
 */
class SimThermometer : public BaseThermometer
{
protected:
    uint32_t sim_time_count;   ///< Number of runs, approximate simulated time 
    float _average;            ///< The average simulated temperature
    float _amplitude;          ///< The amplitude of sinusoidal variations
    float _period;             ///< The period of sinusoidal variations
    float _rando;              ///< The amplitude of random variations added on

public:
    SimThermometer (float average, float amplitude, float period, 
                    float rando);
    float celsius (void);
};


#endif // _SIM_THERMO_H_

