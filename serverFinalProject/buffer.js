const message_modle = require('./models/BaseMessage')

const parseBuffer = (buffer) => {
      let message = {}
      message.type = Buffer.from(buffer).readInt8(0)
      message.message = {}
      if (message.type == 1) {
            message.message.status = Buffer.from(buffer).readInt8(2)
      } else {
            message.message.distance = Buffer.from(buffer).readFloatLE(2);
            message.message.angle = Buffer.from(buffer).readFloatLE(6);
            message.message.speed = Buffer.from(buffer).readFloatLE(10);
      }
      let messageMongoose = new message_modle(message)
      message_modle.validate(messageMongoose).then(_ => {
            messageMongoose.save();
            console.log(message);
      }).catch(err => {
            console.log(err);
      })
}

module.exports = parseBuffer