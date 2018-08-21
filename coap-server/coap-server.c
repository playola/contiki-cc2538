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
#include "libraries/sensor.h"

/*-------------------------------------------------------*/
extern resource_t res_sensor;
/*-------------------------------------------------------*/
PROCESS(coap_server, "Erbium CoAP Server");
AUTOSTART_PROCESSES(&coap_server);
/*-------------------------------------------------------*/
static struct etimer et;
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

  printf("**** Erbium CoAP Server started ****\n");

  while(1) {
    etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    res_sensor.trigger();
  }

  PROCESS_END();
}
/*-------------------------------------------------------*/
