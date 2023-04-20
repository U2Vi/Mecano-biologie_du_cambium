

#define CMD_MEAS_HIGHREP 0x2400 // Commande pour une mesure de haute précision


String getTmp(){
  uint16_t rawHum, rawTemp; // Variables pour stocker les données brutes
  float hum, temp; // Variables pour stocker les données converties
  
  // Envoi de la commande de mesure de haute précision
  Wire.beginTransmission(SHT85_ADDRESS);
  Wire.write(CMD_MEAS_HIGHREP >> 8); // Envoi de l'octet de poids fort de la commande
  Wire.write(CMD_MEAS_HIGHREP & 0xFF); // Envoi de l'octet de poids faible de la commande
  Wire.endTransmission();
  delay(15); // Attente de la fin de la mesure
  
  // Lecture des données brutes
  Wire.requestFrom(SHT85_ADDRESS, 6);
  if(Wire.available() == 6) {
    rawTemp = Wire.read() << 8;
    rawTemp |= Wire.read();
    Wire.read();
    rawHum = Wire.read() << 8;
    rawHum |= Wire.read();
    Wire.read();
    
    // Conversion des données brutes en température et humidité relative
    temp = -45.0 + 175.0 * (float)rawTemp / 65535.0;
    //hum = 100.0 * (float)rawHum / 65535.0;

  Serial.print("[SHT85] -> temperature : ");Serial.println(temp);

  return(String(temp));
  }
}


String getHmd(){
  uint16_t rawHum, rawTemp; // Variables pour stocker les données brutes
  float hum, temp; // Variables pour stocker les données converties
  
  // Envoi de la commande de mesure de haute précision
  Wire.beginTransmission(SHT85_ADDRESS);
  Wire.write(CMD_MEAS_HIGHREP >> 8); // Envoi de l'octet de poids fort de la commande
  Wire.write(CMD_MEAS_HIGHREP & 0xFF); // Envoi de l'octet de poids faible de la commande
  Wire.endTransmission();
  delay(15); // Attente de la fin de la mesure
  
  // Lecture des données brutes
  Wire.requestFrom(SHT85_ADDRESS, 6);
  if(Wire.available() == 6) {
    rawTemp = Wire.read() << 8;
    rawTemp |= Wire.read();
    Wire.read();
    rawHum = Wire.read() << 8;
    rawHum |= Wire.read();
    Wire.read();
    
    // Conversion des données brutes en température et humidité relative
    //temp = -45.0 + 175.0 * (float)rawTemp / 65535.0;
    hum = 100.0 * (float)rawHum / 65535.0;
    
    Serial.print("[SHT85] -> humidity : ");Serial.println(hum);
    return(String(hum));
  }
}
