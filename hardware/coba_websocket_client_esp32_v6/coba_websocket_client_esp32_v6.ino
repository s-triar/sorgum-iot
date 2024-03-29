//https://github.com/Valgueiro/esp32_SocketIO/blob/master/socketIO.ino
#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <SocketIoClient.h>

#define USE_SERIAL Serial

WiFiMulti WiFiMulti;
SocketIoClient webSocket;

// CONST VARIABLES
const char *ssid = "INOSE-X";
const char *pass = "lekassembuh";
const char *HOST = "192.168.0.23:5000";

void event(const char *payload, size_t length){
    USE_SERIAL.printf("got message: %s\n", payload);
}



void setup(){
    USE_SERIAL.begin(9600);

    USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for (uint8_t t = 4; t > 0; t--){
        USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }   


    // Connect to WIFI
    WiFiMulti.addAP(ssid, pass);

    while (WiFiMulti.run() != WL_CONNECTED){
        delay(100);
    }

    // Receive events from server
    webSocket.on("event", event);

    webSocket.begin(HOST);
}

int count = 0;

void loop(){
    webSocket.loop();
    count++;
    if (count == 18000){
        count = 0;

        // Send data to Server
        webSocket.emit("message", "Hello from esp32!");
    }
}
