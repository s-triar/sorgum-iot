float dhtTemp(){
  float dhtTemp = dht.readTemperature();
  return dhtTemp ; // Gets the values of the temperature
}

float dhtHum(){
  float dhtHum = dht.readHumidity();
  return dhtHum ;
}

float ds18b20Temp(){
   DS18B20.requestTemperatures();
   float dstemp =  DS18B20.getTempCByIndex(0);
   return dstemp ;
 
}

//int16_t soilMoisture(){
//  int16_t adc0;
//  adc0 = ads.readADC_SingleEnded(0);
//  float adcValue = adc0 * 0.01563; //VRL
//  return  adc0;
//}

//int16_t phSensor(){
//  int16_t adc0;
//  adc0 = ads.readADC_SingleEnded(1);
//  float adcValue = adc0 * 0.01563; //VRL
//  if(adcValue<0){
//    adcValue = 0;
//  }
//  float pH = (-0.996 * adcValue) + 7.385;
//  return  adcValue;
//}

const int pinSoilMoisture = 34;
int getSoilMoistureNoModul(){
  
   int adcValue = analogRead(pinSoilMoisture);
    
   float voltValue = ((adcValue * 3.3) / 4095);
   
   int kelembapan  = -0.008195*adcValue + 15.54;
   if(kelembapan<1){
    kelembapan = 0;
   }

   if(kelembapan>10){
    kelembapan = 10;
   }
 
  return kelembapan ;
}

const int pinPh = 35;

float getPhNoModul(){
  int adcValue = analogRead(pinPh);
  
  //Hasil Kalibrasi regresi linear 
  float ph = ( -0.01304*adcValue) + 7.000;
  
  float voltValue = ((adcValue * 3.3) / 4095);//Nilai Voltage
  if(ph>7){
    ph = 7;
  }

  if(ph<0){
    ph = 0;
  }
 
  return ph;
}



String sensorPayload(){
  
//    byte val1,val2,val3;
//     val1 = nitrogen();
//     delay(250);
//     val2 = phosphorous();
//     delay(250);
//     val3 = potassium();
//     delay(250);
//    
     String Payload ="DHTTemp:";
     Payload +=  dhtTemp();
     Payload +=" DHTHum:";
     Payload +=  dhtHum();
     Payload +=" DS18B20Temp:";
     Payload +=  ds18b20Temp();
     Payload +=" SoilMoisture:";
     Payload +=  getSoilMoistureNoModul();
     Payload +=" pH:";
     Payload +=  getPhNoModul();
//     Payload +=" N:";
//     Payload +=  val1;
//     Payload +=" P:";
//     Payload +=  val2;
//     Payload +=" K:";
//     Payload +=  val3;
     return Payload;

}

//String sensorPayloadNpk(){
//  
//    byte val1,val2,val3;
//     val1 = nitrogen();
//     delay(250);
//     val2 = phosphorous();
//     delay(250);
//     val3 = potassium();
//     delay(250);
//    
//     String Payload ="N:";
//     Payload +=  val1;
//     Payload +=" P:";
//     Payload +=  val2;
//     Payload +=" K:";
//     Payload +=  val3;
//     return Payload;
//
//}



//String dataSerial;
//void rs485(){
//  while(swSerial.available() > 0){
//  delay(10);
//  char d = swSerial.read();
//  dataSerial += d;
//  }
//  if (dataSerial.length() > 0){
//    Serial.println(dataSerial);
//    dataSerial = "";
//  }
//  
//}
//
//byte nitrogen(){
//  digitalWrite(32,HIGH);
//  delay(10);
//  if(swSerial.write(nitro,sizeof(nitro))==8){
//    digitalWrite(32,LOW);
//    for(byte i=0;i<7;i++){
//    //Serial.print(mod.read(),HEX);
//    values[i] = swSerial.read();
//    Serial.print(values[i],HEX);
//    }
//    Serial.println();
//  }
//  return values[4];
//}
// 
//byte phosphorous(){
//  digitalWrite(DE,HIGH);
//  delay(10);
//  if(swSerial.write(phos,sizeof(phos))==8){
//    digitalWrite(DE,LOW);
//    for(byte i=0;i<7;i++){
//    //Serial.print(mod.read(),HEX);
//    values[i] = swSerial.read();
//    //Serial.print(values[i],HEX);
//    }
//    //Serial.println();
//  }
//  return values[4];
//}
//
//
// 
//byte potassium(){
//  digitalWrite(DE,HIGH);
//  delay(10);
//  if(swSerial.write(pota,sizeof(pota))==8){
//    digitalWrite(DE,LOW);
//    for(byte i=0;i<7;i++){
//    //Serial.print(mod.read(),HEX);
//    values[i] = swSerial.read();
//    //Serial.print(values[i],HEX);
//    }
//    //Serial.println();
//  }
//  return values[4];
//}
//
//const byte all[]= {0x01, 0x03, 0x00, 0x1e, 0x00, 0x03, 0x65, 0xCD};
//byte code(){
//  digitalWrite(DE,HIGH);
//  delay(10);
//  if(swSerial.write(all,sizeof(all))==8){
//    digitalWrite(DE,LOW);
//    for(byte i=0;i<7;i++){
//    //Serial.print(mod.read(),HEX);
//      values[i] = swSerial.read();
//      //Serial.print(values[i],HEX);
//    }
//     //Serial.println();
//  }
//  return values[4];
//}
//
//void preTransmission()
//{
//  digitalWrite(MAX485_RE_NEG, HIGH); //Switch to transmit data
//}
//void postTransmission()
//{
//  digitalWrite(MAX485_RE_NEG, LOW); //Switch to receive data
//}
//
//
//void sendModbus(){
//  //modbus.write()
//}
//long lastMillis = 0;
//
//void getModbusData(){
//  long currentMillis = millis();
//  if (currentMillis - lastMillis > 1000) 
//  {
//    uint8_t result = modbus.readInputRegisters(0x01, 2);
//    
////    if (getResultMsg(*modbus, result)) 
////    {
//      Serial.println();
//      double res_dbl = modbus.getResponseBuffer(0) / 10;
//      String res = "Temperature: " + String(res_dbl) + " C\r\n";
//      res_dbl = modbus.getResponseBuffer(1) / 10;
//      res += "Humidity: " + String(res_dbl) + " %";
//      Serial.println(res);
//   // }
//    lastMillis = currentMillis;
//  }
//}
//
//
//bool getResultMsg(ModbusMaster *node, uint8_t result) 
//{
//  String tmpstr2 = "\r\n";
//  switch (result) 
//  {
//  case node->ku8MBSuccess:
//    return true;
//    break;
//  case node->ku8MBIllegalFunction:
//    tmpstr2 += "Illegal Function";
//    break;
//  case node->ku8MBIllegalDataAddress:
//    tmpstr2 += "Illegal Data Address";
//    break;
//  case node->ku8MBIllegalDataValue:
//    tmpstr2 += "Illegal Data Value";
//    break;
//  case node->ku8MBSlaveDeviceFailure:
//    tmpstr2 += "Slave Device Failure";
//    break;
//  case node->ku8MBInvalidSlaveID:
//    tmpstr2 += "Invalid Slave ID";
//    break;
//  case node->ku8MBInvalidFunction:
//    tmpstr2 += "Invalid Function";
//    break;
//  case node->ku8MBResponseTimedOut:
//    tmpstr2 += "Response Timed Out";
//    break;
//  case node->ku8MBInvalidCRC:
//    tmpstr2 += "Invalid CRC";
//    break;
//  default:
//    tmpstr2 += "Unknown error: " + String(result);
//    break;
//  }
//  Serial.println(tmpstr2);
//  return false;
//}
