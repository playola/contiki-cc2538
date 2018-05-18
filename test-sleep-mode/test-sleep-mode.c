/*
* Author: Pol Layola
* Date: May 2018
*
* Test Sleep Mode
* Functionalities to Configure Interrupts and Sleep Mode for CC2538.
*   @function   configureSleepMode    @return void
*   @function   enableSleepMode       @return void
*   @function   disableSleepMode      @return void
*   @function   configureInterrupts   @return void
*/

#include <stdio.h>
#include "contiki.h"
#include "gpio.h"
#include "dev/pressure-sensor.h"

#define SENSOR_GPIO  GPIO_C_BASE  /* Port Base C */
#define SENSOR_MASK  0x01         /* GPIO pin 0 */

/* Configure and initialize sleep mode */
void configureSleepMode(void) {
  printf("Configure Default Sleep Mode\n");
  // Default Sleep Mode ??
  /*
  // Initialize Low Power Mode
  lpm_init();
  // Enter sleep mode
  lpm_sleep();
  // Set power mode
  // SYS_CTRL_PM_NOACTION, SYS_CTRL_PM_1, SYS_CTRL_PM_2 or SYS_CTRL_PM_3
  SysCtrlPowerModeSet(uint32_t ui32PowerMode);
  */
}
/*-------------------------------------------------------*/
/* Enable sleep mode */
void enableSleepMode(void) {
  printf("Enabling Sleep Mode\n");
}
/*-------------------------------------------------------*/
/* Disable sleep mode */
void disableSleepMode(void) {
  printf("Disable Sleep Mode\n");
}
/*-------------------------------------------------------*/
/* Configure and initialize wake up interrupt */
void configureInterrupts(void) {
  printf("Configure interrupts\n");
  /*
  // Enable wake up interrupt - SYS_CTRL_IWE register
  // Power-up interrupt type
  GPIOPowIntTypeSet(SENSOR_GPIO, SENSOR_MASK, GPIO_POW_RISING_EDGE);
  // Clear pending GPIO power-up interrupts
  GPIOPowIntClear(SENSOR_GPIO, SENSOR_MASK);
  // Enable power-up interrupt
  GPIOPowIntEnable(SENSOR_GPIO, SENSOR_MASK);
  */
  printf("Enable interrupt triggering\n");
  // Enable interrupt triggering here
  printf("Enable interrupt\n");
  GPIO_ENABLE_INTERRUPT(SENSOR_GPIO, SENSOR_MASK);
  // Triggering type: falling edge or rising edge
  printf("Set power up on falling edge\n");
  GPIO_POWER_UP_ON_FALLING(SENSOR_GPIO, SENSOR_MASK);
  // Enable power-up interrupt triggering
  printf("Enable power up interrupt\n");
  GPIO_ENABLE_POWER_UP_INTERRUPT(SENSOR_GPIO, SENSOR_MASK);
}
/*-------------------------------------------------------*/
