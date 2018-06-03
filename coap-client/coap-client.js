const coap = require("node-coap-client").CoapClient;

const observeOptions = {
  resource: 'coap://[COAP_IP]:5683/sensors/pressure',
  method: 'get',
  callback: () => console.log("callback method"),
  payload: [],
  options: []
}
const { resource, method, callback, payload, options } = observeOptions;

coap.observe(resource, method, callback, payload, options)
  .then(payload => {
    console.log("Observe success");
  });
  .catch(err => {
    console.log("Observe fail")
  });
