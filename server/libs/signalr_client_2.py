from requests import Session
from signalr import Connection
import libs.api as api
import libs.webcam as wc
import json

with Session() as session:
    #create a connection
    connection = Connection(api.URL_API+'/signalr', session)

    #get chat hub
    chat = connection.register_hub('FarmingHub')

    #start a connection
    connection.start()

    #create new chat message handler
    def print_received_message(data):
        print('received: ', data)

    #create new chat topic handler
    def print_topic(topic, user):
        print('topic: ', topic, user)

    #create error handler
    def print_error(error):
        print('error: ', error)

    def coba(p):
        print(json.decoder(p))
        print(p['sdp'])
        print(p['type'])
        
    chat.client.on('ReqActivatingCamera', lambda x: coba(x))
    chat.client.on('open', lambda : [
    print("connection opened and handshake received ready to send messages"),
    # hub_connection.send("RPIJoinRoom", [str(api.ID_RPI)+'_RPI'])
    chat.client.invoke("RPIJoinRoom", [str(api.ID_RPI)+'_RPI'])
        # "_". join([1,2,3])])
    # hub_connection.send("RPIJoinRoom", [str(api.ID_RPI)+'_RPI'])
    
    ])
    #process errors
    connection.error += print_error
