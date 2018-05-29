/*
* Author: Pol Layola
* Date: May 2018
*
* Example Sensor
* Functionalities to Configure and Read a digital pin from CC2538.
*   @function   configurePins   @return void
*   @function   getSensorValue  @return unsigned char
*/

#include <stdio.h>
#include "contiki.h"
#include "gpio.h"
#include "dev/example-sensor.h"

#define SENSOR_GPIO  GPIO_C_BASE  /* Port Base C */
#define SENSOR_MASK  0x01         /* GPIO pin 0 */

/*-------------------------------------------------------*/
/*
* Configure GPIO
*/
void configurePins(void)
{
  GPIO_SET_INPUT(SENSOR_GPIO, SENSOR_MASK);
}
/*-------------------------------------------------------*/
/*
* Read sensor from a GPIO
*/
unsigned char getSensorValue(void)
{
  char sensorValue = 0;
  return sensorValue = GPIO_READ_PIN(SENSOR_GPIO, SENSOR_MASK);
}
/*-------------------------------------------------------*/
