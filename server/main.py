from email import message
# from re import L
# import libs.api as api

# if(api.TOKEN=="" or api.TOKEN == None):
#     # (V) TODO Login
#     api.login()

import libs.socketio_server as socketio_app
# from engineio.async_drivers import gevent
import libs.webcam as webcam
# import libs.signalr_client as signalr_app
import eventlet

# signalr_app.hub_connection.start()
eventlet.wsgi.server(eventlet.listen(('', 5000)), socketio_app.app)
# if __name__ == '__main__':
#     try:
    
#         while True:
#             r=""

#     except Exception as e:
#         hub_connection.stop()
#         print(e)

# if __name__ == '__main__':
    # socketio.run(app, host="0.0.0.0", port=5000, debug=True)
