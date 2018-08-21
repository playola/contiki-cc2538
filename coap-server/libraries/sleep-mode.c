/*
* Author: Pol Layola
* Date: May-August 2018
*
* Example Sleep Mode
* Configure Interrupts and Sleep Mode for CC2538.
*   @function   configureSleepMode    @return void
*   @function   enableSleepMode       @return void
*   @function   disableSleepMode      @return void
*   @function   configureInterrupts   @return void
*/

#include <stdio.h>
#include "contiki.h"
#include "gpio.h"

#define SENSOR_PORT       0             /* Port 0*/
#define SENSOR_PORT_BASE  GPIO_C_BASE   /* Base C */
#define SENSOR_MASK       0x01          /* GPIO pin 0 */

/*-------------------------------------------------------*/
/* Configure and initialize wake up interrupt */
void configureInterrupts(void) {
  printf("Configure interrupts\n");
  /* Enable edge detection */
  GPIO_DETECT_EDGE(SENSOR_PORT_BASE, SENSOR_MASK);

  /* Single edge */
  GPIO_TRIGGER_SINGLE_EDGE(SENSOR_PORT_BASE, SENSOR_MASK);

  /* Trigger interrupt on Falling edge */
  GPIO_POWER_UP_ON_FALLING(SENSOR_PORT, SENSOR_MASK);
  GPIO_DETECT_FALLING(SENSOR_PORT_BASE, SENSOR_MASK);

  /* Enable power-up interrupt triggering */
  GPIO_ENABLE_INTERRUPT(SENSOR_PORT_BASE, SENSOR_MASK);
  GPIO_ENABLE_POWER_UP_INTERRUPT(SENSOR_PORT, SENSOR_MASK);
}
/*-------------------------------------------------------*/
