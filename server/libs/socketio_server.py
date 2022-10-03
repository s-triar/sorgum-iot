import socketio
from flask import Flask, request
import requests
import libs.api as api




# ===========================================================================================
# ===               This file handle websocket between rapsberry pi and esp 32            ===
# ===========================================================================================

sio = socketio.Server(async_mode="eventlet", cors_allowed_origins='*', engineio_logger=True)
app = Flask(__name__)

SLAVES={}


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
    if (sid in SLAVES):
        api.submit_esp_disconnect(SLAVES[sid])
        del SLAVES[sid]
    
@sio.on("handshake")
def handshake(sid,dd):
    print('HandShake', dd,sid)
    if(sid not in SLAVES):
        SLAVES[sid]=dd['Id']
        api.submit_esp_connect(dd)
    # sio.emit('message', {'now': 'EURUSD'})
    
@sio.on('message')
def handle_message_event(msg,data):
    api.submit_data_sensor(data)

my_wsgi = socketio.WSGIApp(sio,app)
app = socketio.Middleware(sio, my_wsgi)