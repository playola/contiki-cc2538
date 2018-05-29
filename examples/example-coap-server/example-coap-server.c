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
#if PLATFORM_HAS_BUTTON
  #include "dev/button-sensor.h"
#endif
/*-------------------------------------------------------*/
#define printf(...)
#define PRINT6ADDR(addr)
#define PRINTLLADDR(addr)

extern resource_t res_event;
#if PLATFORM_HAS_LEDS
  extern resource_t res_toggle;
#endif
/*-------------------------------------------------------*/
PROCESS(er_example_server, "Erbium Example Server");
AUTOSTART_PROCESSES(&er_example_server);

PROCESS_THREAD(er_example_server, ev, data) {
  PROCESS_BEGIN();

  PROCESS_PAUSE();

  printf("Starting Erbium Example Server\n");

  #ifdef RF_CHANNEL
    printf("RF channel: %u\n", RF_CHANNEL);
  #endif
  #ifdef IEEE802154_PANID
    printf("PAN ID: 0x%04X\n", IEEE802154_PANID);
  #endif
  printf("uIP buffer: %u\n", UIP_BUFSIZE);
  printf("LL header: %u\n", UIP_LLH_LEN);
  printf("IP+UDP header: %u\n", UIP_IPUDPH_LEN);
  printf("REST max chunk: %u\n", REST_MAX_CHUNK_SIZE);

  rest_init_engine();

  rest_activate_resource(&res_event, "sensors/button");
  #if PLATFORM_HAS_LEDS
    rest_activate_resource(&res_toggle, "actuators/toggle");
  #endif

  while(1) {
    PROCESS_WAIT_EVENT();
    #if PLATFORM_HAS_BUTTON
      if(ev == sensors_event && data == &button_sensor) {
        printf("******* HELLO POL *******\n");
        res_event.trigger();
      }
    #endif
  }

  PROCESS_END();
}
/*-------------------------------------------------------*/
