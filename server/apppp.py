import socketio
import eventlet
from engineio.async_drivers import gevent
from flask import Flask, request

sio = socketio.Server(async_mode="eventlet", cors_allowed_origins='*', engineio_logger=True)
app = Flask(__name__)

# this generates the uwsgi-runnable application

@sio.on('handshake')
def on_message(data):
    print('HandShake', data)
    sio.emit('message', {'now': 'EURUSD'})
@sio.on('message')
def handle_message_event(msg,ggg):
    print("GGGG",ggg)
    sio.emit("10","ini data dari server ws")
    #print('received msg from {} : {}'.format(request.remote_addr, str(msg)))

my_wsgi = socketio.WSGIApp(sio,app)
app = socketio.Middleware(sio, my_wsgi)



eventlet.wsgi.server(eventlet.listen(('', 5000)), app)

# if __name__ == '__main__':
    # socketio.run(app, host="0.0.0.0", port=5000, debug=True)
