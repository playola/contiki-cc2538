/*
* Author: Pol Layola
* Date: May-August 2018
*
* Sensor
* Configure and Read a digital pin from CC2538.
*   @function   configurePins   @return void
*   @function   getSensorValue  @return unsigned char
*/

#include <stdio.h>
#include "contiki.h"
#include "gpio.h"

#define SENSOR_PORT   GPIO_C_NUM    /* Port C */
#define SENSOR_MASK   0x01          /* Port mask */
/*-------------------------------------------------------*/
/*
* Configure GPIO pin
*/
void configurePins(void) {
  /* Software controlled */
  GPIO_SOFTWARE_CONTROL(SENSOR_PORT, SENSOR_MASK);

  /* Set pin to input */
  GPIO_SET_INPUT(SENSOR_PORT, SENSOR_MASK);
}
/*-------------------------------------------------------*/
/*
* Read sensor from a GPIO
*/
unsigned char getSensorValue(void) {
  char sensorValue = 0;
  return sensorValue = GPIO_READ_PIN(SENSOR_PORT, SENSOR_MASK);
}
/*-------------------------------------------------------*/
