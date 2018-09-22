/*
* Author: Pol Layola
* Date: October 2018
*
* Sensor
* Library with functionalities to Configure and Read a digital pin from CC2538.
*   @function   configurePins   @return void
*   @function   getSensorValue  @return unsigned char
*/

#ifndef SENSOR_H
#define SENSOR_H

void configurePins(void);
unsigned char getSensorValue(void);

#endif /* SENSOR_H */
