import logging
from signalrcore.hub_connection_builder import HubConnectionBuilder
import libs.api as api
# import libs.webcam as wc
import json

# from server.libs.api import ID_ESPS
# from asyncio import run
# ===========================================================================================
# ===     This file handle signalr calling/event from raspberry pi to server              ===
# ===========================================================================================

# def do_signaling_rtc(p):
#     print(p[0])
#     # print(sdp,type,"============================================================================")
#     # sdp, type = await wc.offer(hub_connection, p[0])
#     res = api.req_rtc_answer(p[0])
#     print("-------------------------------------------------")
#     # print(sdp)
#     # print(type)
#     hub_connection.send('AnswerReqCamera', ["1", res['sdp'],res['type']])

server_url = api.URL_API+"/FarmingHub"
handler = logging.StreamHandler()
handler.setLevel(logging.DEBUG)
hub_connection = HubConnectionBuilder()\
            .with_url(server_url,options={"verify_ssl": False, "headers": {
                    'user-agent': "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36",\
                    'content-type':'application/json',\
                }})\
            .with_automatic_reconnect({
                "type": "raw",
                "keep_alive_interval": 10,
                "reconnect_interval": 5,
                "max_attempts": 5
            })\
            .build()
            # .configure_logging(logging.DEBUG)\
            # .configure_logging(logging.DEBUG,socket_trace=True, handler=handler)\
                

def generate_data():
    temp = {}
    temp['Id']=str(api.ID_RPI)+'_RPI'
    temp['ESPIds']=api.ID_ESPS
    return json.dump(temp)

hub_connection.on_open(lambda : [
    print("connection opened and handshake received ready to send messages"),

    # hub_connection.send("RPIJoinRoom", [str(api.ID_RPI)+'_RPI'])

    
    hub_connection.send("RPIJoinRoom", [generate_data()])
    
    ])

def coba(p):
    print("+++++++++++++++++++++++++++++++++++")
    res = p[0]
    print()
    print(res['sdp'])
    print(res['type'])

def coba2(c):
    print("===================================")
    print(c)
hub_connection.on_error(lambda data: print(f"An exception was thrown closed{data.error}"))
hub_connection.on_close(lambda : print("connection closed"))
# hub_connection.on("ReqActivatingCamera", lambda x: do_signaling_rtc(x))
# hub_connection.on("coba_terima", lambda x: coba2(x))


