/** @file inheritance.cpp
 *  This file contains a main program that creates and tests a child class.
 * 
 *  @author JR Ridgely
 *  @date   2008-Feb-03 Original file
 *  @date   2008-Mar-04 Added multiple inheritance tests
 *  @date   2008-May-06 Changed to use new serial port classes
 *  @date   2009-Jan-29 Changed again to use even newer serial port classes
 *  @date   2020-Nov-05 Ported to STM32 using the Arduino environment
 *  @date   2020-Nov-06 Morphed into inheritance demo and fixed a crash
 *  @date   2021-Nov-16 Changed from IMU to thermometer to focus on inheritance
 * 
 *  @mainpage Example of Class Inheritance
 *  In this example, we create a set of classes which all interface with
 *  temperature sensors. There is a class which operates a real temperature
 *  sensor connected to the microcontroller through an I2C bus, and there is
 *  a class which just simulates a sensor. Because both sensors (real and
 *  simulated) need to be able to return temperatures, the classes are
 *  descended from a common parent class called BaseThermometer. 
 */

#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
    #include <HardwareTimer.h>
#endif

#include <Wire.h>
#include "mcp9808.h"
#include "sim_thermo.h"


/** @brief   Task which runs the thermometer test. 
 *  @param   p_params An ignored pointer to no parameters
 */
void task_test_thermo (void* p_params)
{
    // Start the I2C (wire) interface to be used to talk to a real sensor
    Wire.begin ();

    // Create sensor object. If you look at the code below this line which runs
    // the test, you'll see that the code below doesn't change if other kinds 
    // of temperature sensor are used (the name of the sensor object changes, 
    // but not the function calls
    // MCP9808 real_thermo (&Wire, 0x18);
    SimThermometer fake_thermo (30.0, 12.0, 30.0, 1.7);

    // Print a scan showing devices found on the I2C bus
    // real_thermo.I2C_scan (Serial);

    // In the task loop, keep getting temperatures and printing them
    for (;;)
    {
        Serial << "Sim Temp, " << fake_thermo.celsius () << endl;

        delay (1000);
    }
}


/** @brief   The Arduino setup function initializes tasks and makes them run.
 */
void setup ()
{
    Serial.begin (115200);
    delay (5000);
    Serial << endl << "\033[2JME507 Inherited Method Test" << endl;

    // Create a task which makes and tests a thermometer object of some sort
    xTaskCreate (task_test_thermo, "Thermo", 2048, NULL, 5, NULL);

    #if (defined STM32L4xx || defined STM32F4xx)
        vTaskStartScheduler ();
    #endif
}


/** @brief   The Arduino loop function isn't active in this program.
 */
void loop () 
{
    delay (1000);
}

