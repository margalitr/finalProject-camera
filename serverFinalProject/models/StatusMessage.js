const mongoose=require('mongoose')
const{Schema}=mongoose

const StatusMessage=new Schema({
     status:{type:Number,require:true}
},{_id:false})

module.exports=StatusMessage