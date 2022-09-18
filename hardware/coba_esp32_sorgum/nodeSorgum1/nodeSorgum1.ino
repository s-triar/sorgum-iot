#include <Adafruit_ADS1015.h>
#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>
//#include <SoftwareSerial.h>
//#include "ModbusMaster.h"



//-------Sensor Init-----------
//--------- DHT22 -------------
uint8_t DHTPin = 4; 
#define DHTTYPE DHT22
DHT dht(DHTPin, DHTTYPE); 


#define SENSOR_PIN  23
OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);


//----------- ADC -----------
Adafruit_ADS1115 ads(0x48);



//MOdbus

#define DE 32
//const byte code[]= {0x01, 0x03, 0x00, 0x1e, 0x00, 0x03, 0x65, 0xCD};
const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};
 
byte values[11];


#include "ModbusMaster.h" //https://github.com/4-20ma/ModbusMaster
#define MAX485_RE_NEG  32 //D4 RS485 has a enable/disable pin to transmit or receive data. Arduino Digital Pin 2 = Rx/Tx 'Enable'; High to Transmit, Low to Receive
#define Slave_ID       1
#define RX_PIN      16 //RX2 
#define TX_PIN      17  //TX2 

ModbusMaster modbus;


//WebSocket
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <SocketIOclient.h>

WiFiMulti WiFiMulti;
SocketIOclient socketIO;
#define USE_SERIAL Serial

int idMikrokontroller = 1;

int idSensor1 = 1;
int idSensor2 = 2;
int idSensor3 = 3;
int idSensor4 = 4;
int idSensor5 = 5;



String sensor1Name = "DHT22";
String sensor2Name = "DHT22";
String sensor3Name = "DS18B20";
String sensor4Name = "PH";
String sensor5Name = "Soil";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  socketSetup();

  pinMode(4, INPUT);
  pinMode(DE, OUTPUT);
  pinMode(34,INPUT);//Soil moisture
  pinMode(35,INPUT);//pH
  //Modbus2
  pinMode(MAX485_RE_NEG, OUTPUT);
  // Init in receive mode
  digitalWrite(MAX485_RE_NEG, LOW);

  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  modbus.begin(Slave_ID, Serial2);
  // Callbacks allow us to configure the RS485 transceiver correctly
  modbus.preTransmission(preTransmission);
  modbus.postTransmission(postTransmission);
  
  dht.begin();  
  DS18B20.begin(); 
  ads.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
   socketIoLoop();
   //Serial.println(sensorPayload());
   //delay(1000);

}
