from flask import Flask, render_template, request
from flask_socketio import SocketIO
import logging
logger = logging.getLogger(__name__)  # or __name__ for current module
logger.setLevel(logging.INFO)

app = Flask(__name__)
app.logger.setLevel(logging.INFO)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app=app, cors_allowed_origins="*", async_mode='eventlet')

@socketio.on('message')
def handle_message_event(msg):
    print('received msg from {} : {}'.format(request.remote_addr, str(msg)))

if __name__ == '__main__':
    socketio.run(app, host="0.0.0.0", port=5000, debug=True)
