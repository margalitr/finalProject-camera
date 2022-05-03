// var buf1 = Buffer.from('abcdefghijkl');
// var buf2 = Buffer.from('HELLO');

// //Copy buf2 into parts of buf1:
// buf2.copy(buf1, 2,2,5);

// console.log(buf1.toString());
// var data =  [1,44,5,5];

// // Create a buffer
// var buf = new ArrayBuffer(4);
// // Create a data view of it
// var view = new DataView(buf);

// // set bytes
// data.forEach(function (b, i) {
//     view.setUint8(i, b);
// });

// // Read the bits as a float; note that by doing this, we're implicitly
// // converting it from a 32-bit float into JavaScript's native 64-bit double
// var num = view.getFloat32(0);
// // Done
// console.log(num);
let data="hvhvhvhvh"
let s=[]
for (let index = 0; index < data.length; index++) {
      s.push(data.charCodeAt(index)); 
}
console.log(s);
let num=Buffer.from(s).readFloatBE(0)
console.log(num);
num=Buffer.from(s).readInt16BE(0)
console.log(num);
num=Buffer.from(s).readFloatBE(4)
console.log("num",num);