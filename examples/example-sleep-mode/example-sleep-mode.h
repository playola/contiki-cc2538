/*
* Author: Pol Layola
* Date: May 2018
*
* Example Sleep Mode
* Library with functionalities to configure Interrupts and Sleep Mode for CC2538.
*   @function   configureSleepMode    @return void
*   @function   enableSleepMode       @return void
*   @function   disableSleepMode      @return void
*   @function   configureInterrupts   @return void
*/

#ifndef SLEEP_MODE_H
#define SLEEP_MODE_H

void configureSleepMode(void);
void enableSleepMode(void);
void disableSleepMode(void);
void configureInterrupts(void);

#endif /* SLEEP_MODE_H */
