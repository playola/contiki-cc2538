/*
* Author: Pol Layola
* Date: May 2018
*
* Resource Sensor
* Example that returns a string when we make an action from the client.
*/

#include <stdlib.h>
#include <string.h>
#include "rest-engine.h"
/*-------------------------------------------------------*/
static void res_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
/*-------------------------------------------------------*/
/*
* A handler function named [resource name]_handler must be implemented for each RESOURCE.
* A buffer for the response payload is provided through the buffer pointer. Simple resources can ignore
* preferred_size and offset, but must respect the REST_MAX_CHUNK_SIZE limit for the buffer.
* If a smaller block size is requested for CoAP, the REST framework automatically splits the data.
*/
RESOURCE(res_sensor,
         "title=Resource sensor",
         res_get_handler,
         NULL,
         NULL,
         NULL);
/*-------------------------------------------------------*/
/*
* Resource sensor handler
*/
static void res_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset) {

  const char *len = NULL;
  /* Some data that has the length up to REST_MAX_CHUNK_SIZE. For more, see the chunk resource. */
  char const *const message = "Resource sensor say Hello World!";
  int length = 12;

  /* The query string can be retrieved by rest_get_query() or parsed for its key-value pairs. */
  if(REST.get_query_variable(request, "len", &len)) {
    length = atoi(len);
    if(length < 0) {
      length = 0;
    }
    if(length > REST_MAX_CHUNK_SIZE) {
      length = REST_MAX_CHUNK_SIZE;
    }
    memcpy(buffer, message, length);
  } else {
    memcpy(buffer, message, length);
  }

  REST.set_header_content_type(response, REST.type.TEXT_PLAIN);
  REST.set_header_etag(response, (uint8_t *)&length, 1);
  REST.set_response_payload(response, buffer, length);
}
/*-------------------------------------------------------*/
