/*
* Author: Pol Layola Izquierdo
* Date: May 2018
*
* Sleep Mode Demo
* Configure Interrupts, Sleep Mode and Read a GPIO from CC2538 using an external sensor.
*/

#include <stdio.h>
#include "contiki.h"
#include "pressure-sensor.h"

/*-------------------------------------------------------*/
PROCESS(pressure_sensor_demo_process, "Pressure sensor demo process");
AUTOSTART_PROCESSES(&pressure_sensor_demo_process);
/*-------------------------------------------------------*/
static struct etimer et;
/*-------------------------------------------------------*/
PROCESS_THREAD(pressure_sensor_demo_process, ev, data) {

  PROCESS_BEGIN();

  sensor_init_pressure();
  sensor_init_sleep_mode();
  sensor_enable_sleep_mode();
  sensor_disable_sleep_mode();
  sensor_init_interrupts();

  while(1) {
    unsigned char pressure = 0;

    etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    pressure = sensor_get_pressure();

    printf("Pressure: %u \n", pressure);
  }

  PROCESS_END();
};
/*-------------------------------------------------------*/
