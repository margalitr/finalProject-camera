const port = 80
const net = require('net');
const mongoose = require('mongoose')
const parseBuffer = require('./buffer')

const server = new net.Server();

async function main() {
    await mongoose.connect('mongodb://localhost:27017/buffer')
}

main().then(_ => {
    server.listen(port, function () {
        console.log(`Server listening for connection requests on socket localhost:${port}.`);
    });
}).catch(err => {
    console.log(err);
})

server.on('connection', function (socket) {
    console.log('A new connection has been established.');
    socket.on('data', function (chunk) {
        parseBuffer(chunk);
    });
    socket.on('close', function () {
        console.log('Closing connection with the client');
    });
    socket.on('error', function (err) {
        console.log(`Error: ${err}`);
    });
});

