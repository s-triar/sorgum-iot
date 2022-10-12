import requests
import json
from configparser import ConfigParser
from datetime import datetime
import jwt



# ===========================================================================================
# ===               This file handle api calling from raspberry pi to server              ===
# ===========================================================================================


config = ConfigParser()
config.read('config.ini')
URL_API = config['API']['url']
PAYLOAD_LOGIN = {'Code':config['IoTAuth']['code'],'Password':config['IoTAuth']['password']}

TOKEN=""
ID_RPI=None
ID_ESPS=[]
HEADERS = {
    'user-agent': "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36",
    'content-type':'application/json',
}

def login():
    uri = URL_API+"/api/IoT/Login"
    res =  requests.post(uri,headers=HEADERS, verify=False, data=json.dumps(PAYLOAD_LOGIN))
    if(res.status_code==200):
        resBody = res.json()
        global TOKEN
        TOKEN = 'Bearer '+resBody['accessToken']
        decoded = jwt.decode(resBody['accessToken'], options={"verify_signature": False}) # works in PyJWT >= v2.0
        global ID_RPI
        ID_RPI=decoded['sub']
        HEADERS['Authorization']=TOKEN
        return True
    return False

def submit_data_sensor(data_sensor):
    uri = URL_API+"/api/DatasCrud/AddData"
    # print(json.dumps(dataSubmit,indent=1, sort_keys=True, default=str))
    header = HEADERS.copy()
    header['Authorization']=TOKEN
    res =  requests.post(uri,headers=header, verify=False, json = data_sensor)
    print(res.reason)
    
def submit_esp_disconnect(id_esp):
    uri = URL_API+'/api/SensorCrud/Disconnect'
    header = HEADERS.copy()
    header['Authorization']=TOKEN
    res = requests.post(uri, headers=header, json = {"Id":id_esp})
    print(res.reason)

def submit_esp_connect(data):
    uri = URL_API+'/api/SensorCrud/Connect'
    header = HEADERS.copy()
    header['Authorization']=TOKEN
    res = requests.post(uri, headers=header, json = data)
    print(res.reason)
    
def req_rtc_answer(data):
    res = requests.post("http://localhost:8080/offer", json = data)
    print(res.json())
    return res.json()