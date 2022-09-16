const { io } = require("socket.io-client");
const socket = io("http://192.168.0.23:5000");
setInterval(()=>{
    socket.emit("message","hello from nodejs mypc");
},5000)