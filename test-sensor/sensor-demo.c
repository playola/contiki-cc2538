/*
* Author: Pol Layola Izquierdo
* Date: May 2018
*
* Sensor Demo
* Configure and Read a GPIO from CC2538 using an external sensor.
*/

#include <stdio.h>
#include "contiki.h"
#include "test-sensor.h"

/*-------------------------------------------------------*/
PROCESS(sensor_demo_process, "Sensor demo process");
AUTOSTART_PROCESSES(&sensor_demo_process);
/*-------------------------------------------------------*/
static struct etimer et;
/*-------------------------------------------------------*/
PROCESS_THREAD(sensor_demo_process, ev, data) {

  PROCESS_BEGIN();

  configurePins();

  while(1) {
    unsigned char sensorValue = 0;

    etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    sensorValue = getSensorValue();

    printf("Sensor value: %u \n", sensorValue);
  }

  PROCESS_END();
};
/*-------------------------------------------------------*/
