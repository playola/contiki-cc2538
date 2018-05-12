/*
* Author: Pol Layola Izquierdo
* Date: May 2018
*
* Test Sensor
* Library with functionalities to Configure and Read a digital pin from CC2538.
*   @function   configurePins   @return void
*   @function   getSensorValue  @return unsigned char
*/

#ifndef PRESSURE_SENSOR
#define PRESSURE_SENSOR

void configurePins(void);
unsigned char getSensorValue(void);

#endif /* PRESSURE_SENSOR */
