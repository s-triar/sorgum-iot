//#include <Adafruit_ADS1015.h>
#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
//#include <SoftwareSerial.h>
//#include "ModbusMaster.h"



//-------Sensor Init-----------
//--------- DHT22 -------------
uint8_t DHTPin = 23; 
#define DHTTYPE DHT22
DHT dht(DHTPin, DHTTYPE); 


#define SENSOR_PIN  4
OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);


//----------- ADC -----------
//Adafruit_ADS1115 ads(0x48);



//MOdbus

//#define DE 32
////const byte code[]= {0x01, 0x03, 0x00, 0x1e, 0x00, 0x03, 0x65, 0xCD};
//const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
//const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
//const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};
// 
//byte values[11];
//
//
//#include "ModbusMaster.h" //https://github.com/4-20ma/ModbusMaster
//#define MAX485_RE_NEG  32 //D4 RS485 has a enable/disable pin to transmit or receive data. Arduino Digital Pin 2 = Rx/Tx 'Enable'; High to Transmit, Low to Receive
//#define Slave_ID       1
//#define RX_PIN      16 //RX2 
//#define TX_PIN      17  //TX2 
//
//ModbusMaster modbus;


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






//int idMikrokontroller = 3;
//
//int idSensor1 = 8;
//int idSensor2 = 6;
//int idSensor3 = 9;
//int idSensor4 = 15;
//int idSensor5 = 7;

int idMikrokontroller = 2;

int idSensor1 = 5;
int idSensor2 = 3;
int idSensor3 = 4;
int idSensor4 = 14;
int idSensor5 = 1;

//int idMikrokontroller = 4;
//
//int idSensor1 = 12;
//int idSensor2 = 11;
//int idSensor3 = 13;
//int idSensor4 = 16;
//int idSensor5 = 10;

String sensor1Name = "Suhu Udara";
String sensor2Name = "Kelembaban Udara";
String sensor3Name = "Suhu Tanah";
String sensor4Name = "Ph Tanah";
String sensor5Name = "Kelembaban Tanah";

//SoftwareSerial swSerial(16,17);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  socketSetup();

  pinMode(4, INPUT);
//  pinMode(DE, OUTPUT);
  pinMode(34,INPUT);//Soil moisture
  pinMode(35,INPUT);//pH
  //Modbus2
  //pinMode(MAX485_RE_NEG, OUTPUT);
  // Init in receive mode
  //digitalWrite(MAX485_RE_NEG, LOW);
//
//  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
//  swSerial.begin(9600);
//  
//  modbus.begin(Slave_ID, Serial2);
//  // Callbacks allow us to configure the RS485 transceiver correctly
//  modbus.preTransmission(preTransmission);
//  modbus.postTransmission(postTransmission);
  
  dht.begin();  
  DS18B20.begin(); 
//  ads.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
   socketIoLoop();
   //Serial.println(sensorPayload());
   //delay(1000);
   //delay(1000);

}
