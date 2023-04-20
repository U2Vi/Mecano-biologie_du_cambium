
//Affiche tous les périphériques i2C disponibles sur le bus.
void Scan_I2C()
  {
    if(debugESSENTIAL){Serial.println("-------------------------- Scanner I2c ----------------------------");}
    for (uint8_t addr = 0; addr <= 127; addr++) 
      {
        Wire.beginTransmission(addr);
        if (!Wire.endTransmission()) 
          {
            if (addr == 0X76)
              {
                if(debugESSENTIAL){Serial.print("-> Adresse I2C 0x"); Serial.print(addr, HEX); Serial.println(" trouvée. Périphérique : [Capt_i2C - BME280]");} 
              }
            else if (addr == 0x48)
              {
                if(debugESSENTIAL){Serial.print("-> Adresse I2C 0x"); Serial.print(addr, HEX); Serial.println(" trouvée. Périphérique : [ADC_i2C - ADS1113]");} 
              }
            else if (addr == 0x68)
              {
                if(debugESSENTIAL){Serial.print("-> Adresse I2C 0x"); Serial.print(addr, HEX); Serial.println(" trouvée. Périphérique : [RTC_i2C - DS1339]");} 
              }
            else
              {
                if(debugESSENTIAL){Serial.print("Adresse I2C 0x"); Serial.print(addr, HEX); Serial.println(" trouvée. Périphérique : [Inconnu]");} 
              }
          }
      }
    if(debugESSENTIAL){Serial.println("-------------------------------------------------------------------");}
  }
