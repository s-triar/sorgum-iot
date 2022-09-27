import cv2
import io,zlib
from signalrcore.hub_connection_builder import HubConnectionBuilder
import logging
import numpy as np
import base64
def encode_ndarray(np_array):    #utility function
    bytestream = io.BytesIO()
    np.save(bytestream, np_array)
    uncompressed = bytestream.getvalue()
    compressed = zlib.compress(uncompressed,level=1)   #level can be 0-9, 0 means no compression
    return compressed

any_numpy_array = np.zeros((4,150,150,3))
encoded_array = encode_ndarray(any_numpy_array)
# headers = {'Content-Type': 'application/octet-stream'}
# resp = requests.post(endpoint, data=encoded_array,headers=headers)


# vid= cv2.VideoCapture(0)

server_url = "https://localhost:7219/DataParamSensorHub"
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
hub_connection.on_open(lambda : [print("connection opened and handshake received ready to send messages"),hub_connection.send('JoinRoom', "3-_-iot")])
hub_connection.on_close(lambda : print("connection closed"))
hub_connection.start()
# hub_connection.send('Strem', [{'g':'dari aku'}])
try:
  # ret, frame = vid.read()
  # frame = cv2.resize(frame,(128,128))
  # retval, buffer = cv2.imencode('.jpg', frame)
  # jpg_as_text = base64.b64encode(buffer)
  # hub_connection.on_open(lambda : [print("connection opened and handshake received ready to send messages"),hub_connection.send("Stremc", [jpg_as_text])])
#   hub_connection.on_close(lambda : print("connection closed"))
#   hub_connection.on("UserSendCommand", print)
  hub_connection.start()
#  time.sleep(10)
    # print("try")
    # # time.sleep((1))
  
  while True:
         r=""
except Exception as e:
    hub_connection.stop()
    print(e)

# with Session() as session:
#     #create a connection
#     connection = Connection("https://a96d-140-0-40-217.ap.ngrok.io", session)

#     #get chat hub
#     chat = connection.register_hub('stream')

#     #start a connection
#     connection.start()

#     #create new chat message handler
#     # def print_received_message(data):
#     #     print('received: ', data)

#     # #create new chat topic handler
#     # def print_topic(topic, user):
#     #     print('topic: ', topic, user)

#     # #create error handler
#     # def print_error(error):
#     #     print('error: ', error)

#     #receive new chat messages from the hub
#     # chat.client.on('newMessageReceived', print_received_message)

#     # #change chat topic
#     # chat.client.on('topicChanged', print_topic)

#     # #process errors
#     # connection.error += print_error

#     #start connection, optionally can be connection.start()
#     with connection:

#         #post new message
#         # chat.server.invoke('send', 'Python is here')

#         #change chat topic
#         chat.server.invoke('SendVideoData', [{'Index':7,'Part':'abc dari mas faqih'}])

#         #invoke server method that throws error
#         # chat.server.invoke('requestError')

#         #post another message
#         # chat.server.invoke('send', 'Bye-bye!')

#         #wait a second before exit
#         connection.wait(1)