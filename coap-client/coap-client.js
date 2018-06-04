/*
* NodeJs CoAP Client
*
* Installation: npm install coap --save
* Default port 5683. Default action 'GET'
*
* References: https://github.com/mcollina/node-coap
*/
const coap = require('coap');
const server = coap.createServer({ type: 'udp6' });

server.on('request', (req, res) => {
  res.end('Starting CoAP Client \n')
})

server.listen(() => {
  const req = coap.request({
    host: 'coap://[COAP_IP]/sensors/pressure',
    observe: true
  });

  req.on('response', (res) => {
    console.log("res ", res)
    res.pipe(process.stdout)
    res.on('end', () => {
      console.log("Stopping CoAP Client");
      process.exit(0)
    })
  })

  req.end()
});
