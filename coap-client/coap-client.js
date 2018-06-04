/*
* Author: Pol Layola
* Date: May 2018
*
* CoAP Client
* Client that observe a sensor and prints its value.
*
* Installation: npm install coap --save
* Default port 5638. Default action 'GET'
*
* References: https://github.com/mcollina/node-coap
*/
var coap = require('coap');
var server = coap.createServer({ type: 'udp6' });

server.on('request', function(req, res) {
  res.end('Starting CoAP Client \n')
})

server.listen(function() {
  var coapObserve = {
    host: 'COAP_IP',
    pathname: '/sensors/pressure',
    observe: true,
    method: 'GET'
  };
  var req = coap.request(coapObserve);

  req.on('response', function(res) {
    var response = res.pipe(process.stdout);
    updateDatabase(response);
  })

  req.end()
});

function updateDatabase(response) {
  console.log('response ', response);
  var coapPost = {
    host: 'coap.thethings.io',
    pathname: '/v2/things/tokenID',
    method: 'POST'
  };
  var req = coap.request(coapPost);
  var payload = {
    values: [{
      key: "demo_resource",
      value:response
    }]
  };
  req.write(JSON.stringify(payload));
  req.on('response', function(res) {
    var response = res.pipe(process.stdout);
    console.log('thethings response: ', response);
  })

  req.end()
}
