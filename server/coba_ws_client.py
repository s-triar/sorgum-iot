from doctest import debug_script
import socketio
import requests

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

# sio.connect('http://192.168.0.36')
# sio.emit('message', {'now': 'EURUSD'})

base_url = 'https://e076-140-0-40-217.ap.ngrok.io/api'


def showPlant(url):
    x = requests.get(url)
    print(x.text)

def addPlant(url, name, latinname, description, plantparam):
    data = {
        'Name': name,
        'LatinName': latinname,
        'Description': description,
        'PlantParameter': plantparam
    }

    response = requests.post(url, json = data)
    response = response.text

    return response



# url_showplant = '/PlantCrud/ShowPlants'
url_showplant = '/PlantCrud/AddPlant'
url = base_url+url_showplant
name = 'TESTERNAME'
latinmane = 'TESTERLATINNAME'
description = 'TESTERDESCRIPTION'
print(addPlant)
