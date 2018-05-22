/*
* Author: Pol Layola
* Date: May 2018
*
* Project conf
* Library with configuration for CC2538 pins, 802.15.4 network and CoAP.
*
* Structure following "contiki-conf.h", "project-conf.h" and "platform-conf.h".
*/

#ifndef PROJECT_CONF_H
#define PROJECT_CONF_H

/* CC2538 configuration */
#define SENSOR_GPIO             GPIO_C_BASE  /* Port Base C */
#define SENSOR_MASK             0x01         /* GPIO pin 0 */

/* IEEE802.15.4 configuration */
#define RF_CHANNEL              RF_CHANNEL
#define IEEE802154_PANID        IEEE802154_PANID

/* CoAP configuration */
// Define here CoAP configuration

#endif /* PROJECT_CONF_H */
