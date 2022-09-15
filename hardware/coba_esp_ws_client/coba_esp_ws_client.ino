#include <SocketIoClient.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Hash.h>

#define USE_SERIAL  Serial
#define SSID_primary        "INOSE-X"
#define WIFI_PWD_primary    "lekassembuh"
#define SERVER_IP "192.168.0.15"
#define SERVER_PORT 5000

ESP8266WiFiMulti wifiMulti;
SocketIoClient socketIOClient;

void setup() {

//// set up serial communication
    USE_SERIAL.begin(115200);
    USE_SERIAL.setDebugOutput(true);

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

//// connect to some access point
    wifiMulti.addAP(SSID_primary, WIFI_PWD_primary);

    while(wifiMulti.run() != WL_CONNECTED) {
        delay(500);
        USE_SERIAL.print("Looking for WiFi ");
    }

    USE_SERIAL.printf("Connected to %s\n", WiFi.SSID().c_str());
    USE_SERIAL.printf("My local IP address is %s\n", WiFi.localIP().toString().c_str());

//// set up socket communication
    socketIOClient.begin(SERVER_IP, SERVER_PORT);
}

void loop() {
    socketIOClient.emit("message", "\"hi there :)\"");
    socketIOClient.loop();
    delay(1000);
}
