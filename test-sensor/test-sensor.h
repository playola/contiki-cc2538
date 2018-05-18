/*
* Author: Pol Layola
* Date: May 2018
*
* Test Sensor
* Library with functionalities to Configure and Read a digital pin from CC2538.
*   @function   configurePins   @return void
*   @function   getSensorValue  @return unsigned char
*/

#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

void configurePins(void);
unsigned char getSensorValue(void);

#endif /* PRESSURE_SENSOR_H */
