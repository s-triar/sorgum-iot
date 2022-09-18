import cv2
from threading import Thread
from signalrcore.hub_connection_builder import HubConnectionBuilder
import logging
import base64
import requests 

global CAMERA_MUST_RUN
CAMERA_MUST_RUN=False
global VIDEO_CAP
VIDEO_CAP = cv2.VideoCapture(0)

class SlaveCamera:
    def __init__(self):
        self._running = True
        
    def run(self):
        global CAMERA_MUST_RUN
        global VIDEO_CAP
        while(CAMERA_MUST_RUN):
            
            # TODO post image to server
            ret, frame = VIDEO_CAP.read()
            frame = cv2.resize(frame,(128,128))
            retval, buffer = cv2.imencode('.jpg', frame)
            jpg_as_text = base64.b64encode(buffer)
            headers = {'Content-Type': 'application/octet-stream'}
            resp = requests.post(endpoint, data=buffer,headers=headers)

def buildWebSocket():
    server_url = "https://37ca-140-0-40-217.ap.ngrok.io/Stream"
    handler = logging.StreamHandler()
    handler.setLevel(logging.DEBUG)
    hubCont = HubConnectionBuilder()\
          .with_url(server_url,options={"verify_ssl": False, "headers": {
                    'user-agent': "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36",\
                    'content-type':'application/json',\
                }})\
          .configure_logging(logging.DEBUG,socket_trace=True, handler=handler)\
          .with_automatic_reconnect({
            "type": "raw",
            "keep_alive_interval": 10,
            "reconnect_interval": 2,
            "max_attempts": 2
          }).build()
    return hubCont

def doUserCommand(x):
    global CAMERA_MUST_RUN
    CAMERA_MUST_RUN=x
    print("user command: ",x)


hubCont = buildWebSocket()
hubCont.on_open(lambda : [
    print("connection opened and handshake received ready to send messages"),
    hubCont.send("JoinRoom", [])
])
hubCont.on_close(lambda : print("connection closed"))
hubCont.on("CameraSendCommand", doUserCommand)
hubCont.start()

try:
        # (V) TODO looping while true
        while True:
            r=""
except Exception as ex:
    CAMERA_MUST_RUN=False