/*
* Author: Pol Layola
* Date: May 2018
*
* CoAP Client
* Client that observe a sensor and prints its value.
*
* Installation: npm install coap -g --save
* Default port 5638. Default action 'GET'
*
* References: https://github.com/mcollina/node-coap
*/
var coap = require('coap');
var server = coap.createServer({ type: 'udp6' });

server.on('request', function(req, res) {
  res.end('Starting CoAP Client \n')
})

var options = {
  host: [COAP_IP],
  pathname: '/sensors/pressure',
  observe: true
};
server.listen(function() {
  var req = coap.request(options);

  req.on('response', function(res) {
    var response = res.pipe(process.stdout);
    console.log('response: ', response);
  })

  req.end()
});
