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
  var req = coap.request({
    host: 'coap://[COAP_IP]/sensors/pressure',
    observe: true
  });

  req.on('response', function(res) {
    console.log('res ', res)
    res.pipe(process.stdout)
    res.on('end', function() {
      console.log('Stopping CoAP Client');
      process.exit(0)
    })
  })

  req.end()
});
