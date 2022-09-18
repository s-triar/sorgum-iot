void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case '10':
            Serial.printf("[IOc] dapat dari server: %s\n", payload);
            break;
        case sIOtype_DISCONNECT:
             Serial.printf("[IOc] Disconnected!\n");
            break;
        case sIOtype_CONNECT:
             Serial.printf("[IOc] Connected to url: %s\n", payload);

            // join default namespace (no auto join in Socket.IO V3)
            socketIO.send(sIOtype_CONNECT, "/");
            break;
        case sIOtype_EVENT:
        {
            char * sptr = NULL;
            int id = strtol((char *)payload, &sptr, 10);
            USE_SERIAL.printf("[IOc] get event: %s id: %d\n", payload, id);
            if(id) {
                payload = (uint8_t *)sptr;
            }
            DynamicJsonDocument doc(1024);
            DeserializationError error = deserializeJson(doc, payload, length);
            if(error) {
                USE_SERIAL.print(F("deserializeJson() failed: "));
                USE_SERIAL.println(error.c_str());
                return;
            }

            String eventName = doc[0];
             Serial.printf("[IOc] event name: %s\n", eventName.c_str());

            // Message Includes a ID for a ACK (callback)
            if(id) {
                // creat JSON message for Socket.IO (ack)
                DynamicJsonDocument docOut(1024);
                JsonArray array = docOut.to<JsonArray>();

                // add payload (parameters) for the ack (callback function)
                JsonObject param1 = array.createNestedObject();
                param1["now"] = millis();

                // JSON to String (serializion)
                String output;
                output += id;
                serializeJson(docOut, output);

                // Send event
                socketIO.send(sIOtype_ACK, output);
            }
        }
            break;
        case sIOtype_ACK:
             Serial.printf("[IOc] get ack: %u\n", length);
            break;
        case sIOtype_ERROR:
             Serial.printf("[IOc] get error: %u\n", length);
            break;
        case sIOtype_BINARY_EVENT:
             Serial.printf("[IOc] get binary: %u\n", length);
            break;
        case sIOtype_BINARY_ACK:
             Serial.printf("[IOc] get binary ack: %u\n", length);
            break;
    }
}

void socketSetup(){
  //USE_SERIAL.begin(115200);

    //Serial.setDebugOutput(true);
     Serial.setDebugOutput(true);

     Serial.println();
     Serial.println();
     Serial.println();

      for(uint8_t t = 4; t > 0; t--) {
           Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
           Serial.flush();
          delay(1000);
      }

    WiFiMulti.addAP("INOSE-X", "lekassembuh");

    //WiFi.disconnect();
    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }

    String ip = WiFi.localIP().toString();
    Serial.printf("[SETUP] WiFi Connected %s\n", ip.c_str());

    // server address, port and URL
//    socketIO.begin("192.168.0.15", 5000,"/socket.io/?EIO=3");
     socketIO.begin("192.168.0.23", 5000,"/socket.io/?EIO=4");

    // event handler
    socketIO.onEvent(socketIOEvent);
  
}

unsigned long messageTimestamp = 0;
void socketIoLoop(){
     socketIO.loop();

    uint64_t now = millis();

    if(now - messageTimestamp > 2000) {
        messageTimestamp = now;

        // creat JSON message for Socket.IO (event)
        DynamicJsonDocument doc(1024);
        JsonArray array = doc.to<JsonArray>();

        // add evnet name
        // Hint: socket.on('event_name', ....
        array.add("message");

        // add payload (parameters) for the event
        JsonObject param1 = array.createNestedObject();

    
     


         DynamicJsonDocument doc2(1024);
         JsonArray array2 = doc2.to<JsonArray>();
  
        
         StaticJsonDocument<200> docsensor1;
         docsensor1["id"] = idSensor1;
         docsensor1["name"] = sensor1Name;
         docsensor1["value"] = dhtTemp();


         StaticJsonDocument<200> docsensor2;
         docsensor2["id"] = idSensor2;
         docsensor2["name"] = sensor2Name;
         docsensor2["value"] = dhtHum();


         StaticJsonDocument<200> docsensor3;
         docsensor3["id"] = idSensor3;
         docsensor3["name"] = sensor3Name;
         docsensor3["value"] = ds18b20Temp();


         StaticJsonDocument<200> docsensor4;
         docsensor4["id"] = idSensor4;
         docsensor4["name"] = sensor4Name;
         docsensor4["value"] = phSensor();


         StaticJsonDocument<200> docsensor5;
         docsensor5["id"] = idSensor5;
         docsensor5["name"] = sensor5Name;
         docsensor5["value"] = soilMoisture();

         
  
         //serializeJson(doc4,dataSensor2);
         

         array2.add(docsensor1);
         array2.add(docsensor2);
         array2.add(docsensor3);
         array2.add(docsensor4);
         array2.add(docsensor5);
     
        param1["Id"] = idMikrokontroller ;
        param1["sensor"] = array2;

        // JSON to String (serializion)
        String output;
        serializeJson(doc, output);
        Serial.println(socketIO.isConnected());
        // Send event
        Serial.println(output);
        socketIO.sendEVENT(output);

        // Print JSON for debugging
       
    }
}
