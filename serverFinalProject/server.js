const port = 80
// const ip='http://localhost'
// const exp=require('express')
// const app=exp()
const net = require('net');

function parseBuffer(buffer) {
    let message = {}
    message.type =Buffer.from(buffer).readInt8(0)
    if (message.type == 1) {
        message.status = Buffer.from(buffer).readInt8(2)
    } else {
        message.distance = Buffer.from(buffer).readFloatLE(2);
        message.angle = Buffer.from(buffer).readFloatLE(6);
        message.speed = Buffer.from(buffer).readFloatLE(10);
    
    }
    console.log(message);
}

const server = new net.Server();
server.listen(port, function () {
    console.log(`Server listening for connection requests on socket localhost:${port}.`);
});

server.on('connection', function (socket) {
    console.log('A new connection has been established.');
    socket.on('data', function (chunk) {
        console.log(`Data received from client: ${chunk.toString()}.`);
        parseBuffer(chunk);
    });
    socket.on('close', function () {
        console.log('Closing connection with the client');
    });
    socket.on('error', function (err) {
        console.log(`Error: ${err}`);
    });
});

