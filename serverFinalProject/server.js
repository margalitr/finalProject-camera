const port = 80
// const ip='http://localhost'
// const exp=require('express')
// const app=exp()
const net = require('net');

function  parseBuffer(buffer) {
    console.log(buffer[0]);
        let message = {}
        message.type = parseInt(buffer);
        if (message.type == 1) {
            message.status = buffer[2];
        } else {
            message.distance =buffer[2];
            message.angle = buffer[6];
            message.speed = buffer[10];
            // memcpy((void*)(&distance), (void*)(messageBuffer + 2), 4);
            // memcpy((void*)(&angle), (void*)(messageBuffer + 6), 4);
            // memcpy((void*)(&speed), (void*)(messageBuffer + 10), 4);
        }
        console.log(message);
    }

const server = new net.Server();
server.listen(port, function () {
    console.log(`Server listening for connection requests on socket localhost:${port}.`);
});

server.on('connection', function (socket) {
    console.log('A new connection has been established.');
    socket.write('Hello, client.');
    socket.on('data', function (chunk) {
        console.log(`Data received from client: ${chunk.toString()}.`);
        console.log(chunk);
        for (let i = 0; i < 5; i++) {
            console.log(chunk[i]); 
        }

        parseBuffer(chunk);
        //console.log("buffer",Buffer);
        //printBuffer(buffer);
    });
    socket.on('end', function () {
        console.log('Closing connection with the client');
    });
    socket.on('error', function (err) {
        console.log(`Error: ${err}`);
    });
});



// let printBuffer = (buffer) => {
//     console.log("{message : type=", buffer.type);
//     if (message.type == 1) {
// console.log("");
//     }
// }
//server.listen(port,()=>console.log(`server is listening at ${ip}:${port}`))


// app.get('/',(req,res)=>{
//     console.log("jjjj");
// })
