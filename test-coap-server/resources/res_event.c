/*
* Author: Pol Layola
* Date: May 2018
*
* Resource event
* [...]
*/

#include <string.h>
#include "rest-engine.h"
#include "er-coap.h"

#define PRINTF(...)
#define PRINT6ADDR(addr)
#define PRINTLLADDR(addr)

static void res_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_event_handler(void);

EVENT_RESOURCE(res_event,
               "title=\"Event demo\";obs",
               res_get_handler,
               NULL,
               NULL,
               NULL,
               res_event_handler);

static void res_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset) {
  REST.set_header_content_type(response, REST.type.TEXT_PLAIN);
  REST.set_response_payload(response, buffer, snprintf((char *)buffer, preferred_size, "POL EVENT"));
}

static void res_event_handler(void) {
  if(1) {
    PRINTF("POL TICK for /%s\n", res_event.url);
    REST.notify_subscribers(&res_event);
  }
}
