import socketio

# standard Python
sio = socketio.Client()

@sio.event
def connect():
    print("I'm connected!")

@sio.event
def connect_error():
    print("The connection failed!")

@sio.on('server_response')
def on_res(data):
    print(data)
    
@sio.on('handshake')
def on_message(data):
    print('HandShake', data)
    sio.emit('message', {'now': 'EURUSD'})
    
# @sio.on('price')
# def on_message(data):
#     print('Price Data ', data)

sio.connect('http://127.0.0.1:5000')
sio.emit('message', {'now': 'EURUSD'})