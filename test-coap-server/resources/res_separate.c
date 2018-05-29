/*
* Author: Pol Layola
* Date: May 2018
*
* Resource separate
* [...]
*/

#include <string.h>
#include "rest-engine.h"
#include "er-coap-separate.h"
#include "er-coap-transactions.h"

static void res_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_resume_handler(void);

SEPARATE_RESOURCE(res_separate,
                  "title=\"Separate demo\"",
                  res_get_handler,
                  NULL,
                  NULL,
                  NULL,
                  res_resume_handler);

/* A structure to store the information required for the separate handler */
typedef struct application_separate_store {

  /* Provided by Erbium to store generic request information such as remote address and token. */
  coap_separate_t request_metadata;

  /* Add fields for addition information to be stored for finalizing, e.g.: */
  char buffer[16];
} application_separate_store_t;

#define COAP_MAX_OPEN_SEPARATE   2

static uint8_t separate_active = 0;
static application_separate_store_t separate_store[COAP_MAX_OPEN_SEPARATE];

static void res_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset) {
  /*
   * Example allows only one open separate response.
   * For multiple, the application must manage the list of stores.
   */
  if(separate_active >= COAP_MAX_OPEN_SEPARATE) {
    coap_separate_reject();
  } else {
    ++separate_active;

    /* Take over and skip response by engine. */
    coap_separate_accept(request, &separate_store->request_metadata);
    /* Be aware to respect the Block2 option, which is also stored in the coap_separate_t. */

    /*
     * At the moment, only the minimal information is stored in the store (client address, port, token, MID, type, and Block2).
     * Extend the store, if the application requires additional information from this handler.
     * buffer is an example field for custom information.
     */
    snprintf(separate_store->buffer, sizeof(separate_store->buffer), "StoredInfo");
  }
}
static void res_resume_handler() {
  if(separate_active) {
    coap_transaction_t *transaction = NULL;
    if((transaction = coap_new_transaction(separate_store->request_metadata.mid, &separate_store->request_metadata.addr, separate_store->request_metadata.port))) {
      coap_packet_t response[1]; /* This way the packet can be treated as pointer as usual. */

      /* Restore the request information for the response. */
      coap_separate_resume(response, &separate_store->request_metadata, REST.status.OK);

      coap_set_payload(response, separate_store->buffer, strlen(separate_store->buffer));

      /*
       * Be aware to respect the Block2 option, which is also stored in the coap_separate_t.
       * As it is a critical option, this example resource pretends to handle it for compliance.
       */
      coap_set_header_block2(response, separate_store->request_metadata.block2_num, 0, separate_store->request_metadata.block2_size);

      /* Warning: No check for serialization error. */
      transaction->packet_len = coap_serialize_message(response, transaction->packet);
      coap_send_transaction(transaction);
      /* The engine will clear the transaction (right after send for NON, after acked for CON). */

      /* FIXME there could me more! */
      separate_active = 0;
    } else {
      /*
       * Set timer for retry, send error message, ...
       * The example simply waits for another button press.
       */
    }
  }
}
