// Node Coap Client
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
    console.log("Observe success ", payload);
  });
  .catch(err => {
    console.log("Observe fail ", err)
  });


// NodeJs Child Process
const { exec } = require('child_process');

exec('coap get coap://[COAP_IP]:5638/sensors/pressure --observe', (error, stdout, stderr) => {
  if (error) {
    console.error(`exec error: ${error}`);
    return;
  }
  console.log(`stdout: ${stdout}`);
  console.log(`stderr: ${stderr}`);
});
