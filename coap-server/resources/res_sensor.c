/*
* Author: Pol Layola
* Date: May 2018
*
* Resource sensor
* Event that sends sensor paylod when the event is triggered.
*/

#include <stdio.h>
#include <string.h>
#include "rest-engine.h"
#include "er-coap.h"
#include "../sensor.h"
/*-------------------------------------------------------*/
static void res_get_handler(
  void *request,
  void *response,
  uint8_t *buffer,
  uint16_t preferred_size,
  int32_t *offset
);
/*-------------------------------------------------------*/
static void res_event_handler(void);
/*-------------------------------------------------------*/
EVENT_RESOURCE(res_event,
               "title=\"Event sensor\";obs",
               res_get_handler,
               NULL,
               NULL,
               NULL,
               res_event_handler);
/*-------------------------------------------------------*/
static void res_get_handler(
  void *request,
  void *response,
  uint8_t *buffer,
  uint16_t preferred_size,
  int32_t *offset
) {
  unsigned char sensorValue = getSensorValue();
  printf("Setting sensor value to: %u", sensorValue);
  REST.set_header_content_type(response, REST.type.TEXT_PLAIN);
  REST.set_response_payload(response, buffer, snprintf((char *)buffer, preferred_size, sensorValue));
}
/*-------------------------------------------------------*/
static void res_event_handler(void) {
  if(1) {
    printf("Sending sensor value");
    REST.notify_subscribers(&res_event);
  }
}
/*-------------------------------------------------------*/
