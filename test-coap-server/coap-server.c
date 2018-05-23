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
/*-------------------------------------------------------*/
/*
 * Resources to be activated need to be imported through the extern keyword.
 * The build system automatically compiles the resources in the corresponding sub-directory.
 */
extern resource_t res_hello;

PROCESS(er_example_server, "Erbium Example Server");
AUTOSTART_PROCESSES(&er_example_server);
/*-------------------------------------------------------*/
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

  /* Initialize the REST engine. */
  rest_init_engine();

  rest_activate_resource(&res_hello, "test/hello");

  /* Define application-specific events here. */
  while(1) {
    PROCESS_WAIT_EVENT();

    if(ev == sensors_event && data == &button_sensor) {
      printf("******* HELLO, I AM THE COAP SERVER *******\n");

      /* Call the event_handler for this application-specific event. */
      res_event.trigger();

      /* Also call the separate response example handler. */
      res_separate.resume();
    }
  }

  PROCESS_END();
}
/*-------------------------------------------------------*/
