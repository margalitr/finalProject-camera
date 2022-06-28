const mongoose=require('mongoose')
const{Schema}=mongoose

const DiscoverMessage=require('./DiscoverMessage')
const StatusMessage=require('./StatusMessage')

const BaseMessage=new Schema({
    type:{type:String,required:true},
    message:{type:mongoose.Schema.Types.Mixed,required:true}
})

const mes=mongoose.model('Message',BaseMessage)

module.exports=mes