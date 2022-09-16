#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>

#include <ArduinoJson.h>

#include <WebSocketsClient.h>
#include <SocketIOclient.h>

WiFiMulti wifiMulti;
SocketIOclient socketIOClient;

#define USE_SERIAL Serial
#define SSID_primary        "INOSE-X"
#define WIFI_PWD_primary    "lekassembuh"
#define SERVER_IP "192.168.0.23"
#define SERVER_PORT 5000

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
//    socketIOClient.begin(SERVER_IP, SERVER_PORT);
  socketIOClient.begin(SERVER_IP, SERVER_PORT,"/socket.io/?EIO=4");
}

void loop() {
   DynamicJsonDocument doc(1024);
        JsonArray array = doc.to<JsonArray>();
uint64_t now = millis();
        // add evnet name
        // Hint: socket.on('event_name', ....
        array.add("message");

        // add payload (parameters) for the event
        JsonObject param1 = array.createNestedObject();
//        param1["now"] = (uint32_t) now;
        param1["now"] = "DARI ESP32";
        // JSON to String (serializion)
        String output;
        serializeJson(doc, output);
    Serial.println(output);
    socketIOClient.sendEVENT(output);
    String o = "[\"message\",{\"now\":\"esp is ready\"}]" ;
    socketIOClient.sendEVENT(o);
Serial.println(socketIOClient.isConnected());
//socketIOClient.send("message","dari esp32");
    socketIOClient.loop();
    delay(1000);
}
