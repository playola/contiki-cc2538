/*
* Author: Pol Layola
* Date: May 2018
*
* CoAP Server
* Erbium CoAP server using external libraries for read sensors, sleep mode and interrupts.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contiki.h"
#include "contiki-net.h"
#include "rest-engine.h"
#include "gpio.h"
#include "ioc.h"
#include "libraries/sensor.h"

#define SENSOR_PORT       0             /* Port 0*/
#define SENSOR_PORT_BASE  GPIO_C_BASE   /* Base C */

/*-------------------------------------------------------*/
extern resource_t res_sensor;
/*-------------------------------------------------------*/
PROCESS(coap_server, "Erbium CoAP Server");
AUTOSTART_PROCESSES(&coap_server);
/*-------------------------------------------------------*/
static struct etimer et;
/*-------------------------------------------------------*/
void interruptCallback(void) {
  printf("interrupt callback \n");
  res_sensor.trigger();
}
/*-------------------------------------------------------*/
PROCESS_THREAD(coap_server, ev, data) {
  PROCESS_BEGIN();

  PROCESS_PAUSE();

  printf("Starting Erbium CoAP Server\n");

  printf("**** Setting IEEE 802.15.4 parameters ****\n");
  #ifdef RF_CHANNEL
    printf("RF channel: %u\n", RF_CHANNEL);
  #endif
  #ifdef IEEE802154_PANID
    printf("PAN ID: 0x%04X\n", IEEE802154_PANID);
  #endif

  rest_init_engine();
  rest_activate_resource(&res_sensor, "sensors/pressure");

  configurePins(); /* Configure pins to read sensor value */

  /* Sleep mode and interrupts */
  configureSleepMode();
  enableSleepMode();
  disableSleepMode();
  configureInterrupts();

  ioc_set_over(SENSOR_PORT_BASE, SENSOR_PORT, IOC_OVERRIDE_PDE);
  gpio_register_callback(interruptCallback, SENSOR_PORT_BASE, SENSOR_PORT);

  printf("**** Erbium CoAP Server started ****\n");

  while(1) {
    etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }

  PROCESS_END();
}
/*-------------------------------------------------------*/
