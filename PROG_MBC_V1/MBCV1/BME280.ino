
#define SEALEVELPRESSURE_HPA (1013.25)

#define ADDR_i2C_BME280 0x76  //Adresse i2C

Adafruit_BME280 bme;


//Fonction d'init du BME280
void init_BME280() 
  {
    if(debugESSENTIAL){Serial.print(F("BME280 check : "));}
    unsigned status;
    status = bme.begin(ADDR_i2C_BME280);
    if(debugESSENTIAL){Serial.println(status);}
    if (!status) 
      {
        /*
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("ID of 0x60 represents a BME 280.\n");
        Serial.print("ID of 0x61 represents a BME 680.\n");*/
        if(debugESSENTIAL){Serial.println("[ERROR 708][BME] -> Couldn't find BME280");}
        CodeERREUR += "708:";
      }
  }


//Lecture TMP et HMDR AVEC offset pour le moniteur série
void BME280() 
  { 
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");
    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");
    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");
    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");
    Serial.println();
    delay(10);
  }


//Lecture HMDR AVEC offset 
String ValuesHRForOutput() 
  {
    String HR = String(bme.readHumidity()+readFile(SPIFFS, "/offsetHumR.txt").toFloat()); 
    return(HR);
  }


//Lecture TMP AVEC offset
String ValuesTMPForOutput() 
  {
    String TMP = String(bme.readTemperature()+readFile(SPIFFS, "/offsetTmp.txt").toFloat());
    return(TMP);
  }


//Lecture HMDR sans offset
String ValuesHRForWebBrut() 
  {
    String HR = String(bme.readHumidity());
    return(HR);
  }


//Lecture TMP sans offset 
String ValuesTMPForWebBrut() 
  {
    String TMP = String(bme.readTemperature());
    return(TMP);
  }
