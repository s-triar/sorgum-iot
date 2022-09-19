from email import message
from re import L
import socketio
import eventlet
from engineio.async_drivers import gevent
from flask import Flask, request
import requests
import logging
from signalrcore.hub_connection_builder import HubConnectionBuilder

URLSERVER="https://412d-140-0-40-217.ngrok.io"
IDMINIPC=1
slaves={}


sio = socketio.Server(async_mode="eventlet", cors_allowed_origins='*', engineio_logger=True)
app = Flask(__name__)



# this generates the uwsgi-runnable application
@sio.event
def connect(sid, environ, auth):
    print('connect ', sid)
    print('environ',environ)
    print('auth',auth)
    # print('data',data)

@sio.event
def disconnect(sid):
    print('disconnect ', sid)
    if (sid in slaves):
    	 
        url_add = URLSERVER+'/api/SensorCrud/Disconnect'
        send = requests.post(url_add, json = {"Id":slaves[sid]})
        print(send)
        del slaves[sid]
    
@sio.on("handshake")
def handshake(sid,dd):
    print('HandShake', dd,sid)
    if(sid not in slaves):
        slaves[sid]=dd['Id']
        url_add = URLSERVER+'/api/SensorCrud/Connect'
        send = requests.post(url_add, json = dd)
        print(send)

    # sio.emit('message', {'now': 'EURUSD'})
@sio.on('message')
def handle_message_event(msg,ggg):
    print("GGGG",ggg)
    url_add = URLSERVER+'/api/DatasCrud/AddData'
    send = requests.post(url_add, json = ggg)

    print(send)
    # response = ggg['message']['sensor']
    # for i in (len(response)):
    #     id = i
    # sio.emit("10","ini data dari server ws")
    #print('received msg from {} : {}'.format(request.remote_addr, str(msg)))

my_wsgi = socketio.WSGIApp(sio,app)
app = socketio.Middleware(sio, my_wsgi)

server_url = URLSERVER+"/DataParamSensorHub"
handler = logging.StreamHandler()
handler.setLevel(logging.DEBUG)
hub_connection = HubConnectionBuilder()\
            .with_url(server_url,options={"verify_ssl": False, "headers": {
                    'user-agent': "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36",\
                    'content-type':'application/json',\
                }})\
          .configure_logging(logging.DEBUG,socket_trace=True, handler=handler)\
            .configure_logging(logging.DEBUG)\
            .with_automatic_reconnect({
                "type": "raw",
                "keep_alive_interval": 10,
                "reconnect_interval": 5,
                "max_attempts": 5
            }).build()
hub_connection.on_open(lambda : [print("connection opened and handshake received ready to send messages"),hub_connection.send("JoinRoom", [str(IDMINIPC)+'-_-iot'])])
hub_connection.on_close(lambda : print("connection closed"))
hub_connection.start()

eventlet.wsgi.server(eventlet.listen(('', 5000)), app)

# if __name__ == '__main__':
    # socketio.run(app, host="0.0.0.0", port=5000, debug=True)
