const mongoose=require('mongoose')
const{Schema}=mongoose

const DiscoverMessage=new Schema({
     distance:{type:Number,require:true},
     angle:{type:Number,require:true},
     speed:{type:Number,require:true}
},{_id:false})

module.exports=DiscoverMessage