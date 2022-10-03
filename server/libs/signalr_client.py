import logging
from signalrcore.hub_connection_builder import HubConnectionBuilder
import libs.api as api
import libs.webcam as wc

# ===========================================================================================
# ===     This file handle signalr calling/event from raspberry pi to server              ===
# ===========================================================================================

def do_signaling_rtc(param):
    res = wc.offer(param)
    hub_connection.send('AnswerReqCamera', res)

server_url = api.URL_API+"/FarmingHub"
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
hub_connection.on_open(lambda : [print("connection opened and handshake received ready to send messages"),hub_connection.send("RPIJoinRoom", [str(api.ID_RPI)+'_RPI'])])
hub_connection.on_close(lambda : print("connection closed"))
hub_connection.on("ReqActivatingCamera", do_signaling_rtc)


