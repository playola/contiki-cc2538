/*
* Author: Pol Layola
* Date: May-August 2018
*
* Sensor
* Library with functionalities of sleep mode and interrupts from CC2538.
*/

#ifndef SLEEP_MODE_H
#define SLEEP_MODE_H

void configureSleepMode(void);
void enableSleepMode(void);
void disableSleepMode(void);
void configureInterrupts(void);

#endif /* SLEEP_MODE_H */
