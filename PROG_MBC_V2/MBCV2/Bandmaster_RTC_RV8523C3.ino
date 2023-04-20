/* [OK] */

/*************************************************************************
***************************[ Functions : ]********************************
**************************************************************************
***                                                                    ***
*** Void   init_rtc_device();                                          ***
*** String RTC_getDate();                                              ***
*** Void   RTC_configDateTime(year, month, day, hour, minute, second); ***
***                                                                    ***
**************************************************************************
*************************************************************************/

#define CTRL_REGISTER_1 0x00
#define CTRL_REGISTER_2 0x01
#define CTRL_REGISTER_3 0x02

#define SECOND_REGISTER 0x03
#define MINUTE_REGISTER 0x04
#define HOUR_REGISTER   0x05
#define DAY_REGISTER    0x06
#define MOUTH_REGISTER  0x08
#define YEAR_REGISTER   0x09

void init_rtc_device(){

  delay(100); // Attendre une seconde pour laisser le temps au rv8523 de démarrer
  // Configuration des registres de contrôle pour activer le démarrage automatique
  Wire.beginTransmission(RV8523_ADDRESS);
  Wire.write(CTRL_REGISTER_1);
  Wire.write(0b00010000);
  Wire.endTransmission();
  Wire.beginTransmission(RV8523_ADDRESS);
  Wire.write(CTRL_REGISTER_2);
  Wire.write(0b00000000);
  Wire.endTransmission();
  Wire.beginTransmission(RV8523_ADDRESS);
  Wire.write(CTRL_REGISTER_3);
  Wire.write(0b00000000);
  Wire.endTransmission();

  //RTC_configDateTime(2023, 4, 1, 15, 24, 0);
  
}


String RTC_getDate(){

  // Lecture de la date et de l'heure
  int RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second;
  RTC_readDateTime(RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second);
  
  // Affichage des données lues

   String RTC_time = ""; 
    RTC_time += RTC_day;
    RTC_time += "/";
    RTC_time += RTC_month;
    RTC_time += "/";
    RTC_time += RTC_year;
    RTC_time += "-";
    RTC_time += RTC_hour;
    RTC_time += ":";
    RTC_time += RTC_minute;
    RTC_time += ":";
    RTC_time += RTC_second;

    Serial.print("[RTC] -> Get time : ");Serial.println(RTC_time);
    return(RTC_time);

}

String RTC_getDateWeb(){

  // Lecture de la date et de l'heure
  int RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second;
  RTC_readDateTime(RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second);
  
  // Affichage des données lues

   String RTC_time = ""; 
    RTC_time += RTC_year;
    RTC_time += "-";
    RTC_time += RTC_month;
    RTC_time += "-";
    RTC_time += RTC_day;
    RTC_time += "T";
    RTC_time += RTC_hour;
    RTC_time += ":";
    RTC_time += RTC_minute;
    RTC_time += ":";
    RTC_time += RTC_second;

    Serial.print("[RTC] -> Get time : ");Serial.println(RTC_time);
    return(RTC_time);

}


String RTC_getDay(){
  // Lecture de la date et de l'heure
  int RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second;
  RTC_readDateTime(RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second);
  return(String(RTC_day));
}
String RTC_getMonth(){
  // Lecture de la date et de l'heure
  int RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second;
  RTC_readDateTime(RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second);
  return(String(RTC_month));
}
String RTC_getYear(){
  // Lecture de la date et de l'heure
  int RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second;
  RTC_readDateTime(RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second);
  return(String(RTC_year));
}
String RTC_getHour(){
  // Lecture de la date et de l'heure
  int RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second;
  RTC_readDateTime(RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second);
  return(String(RTC_hour));
}
String RTC_getMinute(){
  // Lecture de la date et de l'heure
  int RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second;
  RTC_readDateTime(RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second);
  return(String(RTC_minute));
}
String RTC_getSecond(){
  // Lecture de la date et de l'heure
  int RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second;
  RTC_readDateTime(RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second);
  return(String(RTC_second));
}


String RTC_dailyIdentifier(){
  // Lecture de la date et de l'heure
  int RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second;
  RTC_readDateTime(RTC_year, RTC_month, RTC_day, RTC_hour, RTC_minute, RTC_second);

  String RTC_time = ""; 
  RTC_time += RTC_day;
  RTC_time += RTC_month;
  RTC_time += RTC_year;

  Serial.print("[RTC] -> Daily identifier :");
  Serial.println(RTC_time);
  
  return(RTC_time);
}



void RTC_writeRegister(byte reg, byte val) {
  Wire.beginTransmission(RV8523_ADDRESS);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

byte RTC_readRegister(byte reg) {
  Wire.beginTransmission(RV8523_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(RV8523_ADDRESS, (byte)1);
  if (Wire.available()) {
    return Wire.read();
  }
  return 0;
}

void RTC_configDateTime(int RTC_year, int RTC_month, int RTC_day, int RTC_hour, int RTC_minute, int RTC_second) {
  // Configuration de l'heure et de la date en format binaire
  RTC_writeRegister(SECOND_REGISTER, decimalToBcd(RTC_second));    // Seconde
  RTC_writeRegister(MINUTE_REGISTER, decimalToBcd(RTC_minute));    // Minute
  RTC_writeRegister(HOUR_REGISTER, decimalToBcd(RTC_hour));        // Heure
  RTC_writeRegister(DAY_REGISTER, decimalToBcd(RTC_day));          // Jour
  RTC_writeRegister(MOUTH_REGISTER, decimalToBcd(RTC_month));      // Mois
  //RTC_writeRegister(YEAR_REGISTER, decimalToBcd(RTC_year-2000));   // Année
  RTC_writeRegister(YEAR_REGISTER, decimalToBcd(RTC_year-2000)%100); // Année (2 derniers chiffres)
  Serial.println("[RTC] -> New time set !");
  RTC_getDate();
}

void RTC_readDateTime(int& RTC_year, int& RTC_month, int& RTC_day, int& RTC_hour, int& RTC_minute, int& RTC_second) {
  // Lecture de l'heure et de la date en format binaire
  RTC_second = bcdToDecimal(RTC_readRegister(SECOND_REGISTER) & 0x7F);
  RTC_minute = bcdToDecimal(RTC_readRegister(MINUTE_REGISTER) & 0x7F);
  RTC_hour   = bcdToDecimal(RTC_readRegister(HOUR_REGISTER) & 0x3F);
  RTC_day    = bcdToDecimal(RTC_readRegister(DAY_REGISTER) & 0x3F);
  RTC_month  = bcdToDecimal(RTC_readRegister(MOUTH_REGISTER) & 0x1F);
  RTC_year = bcdToDecimal(RTC_readRegister(YEAR_REGISTER)) + 2000;
}

byte decimalToBcd(byte val) {
  return ((val / 10 * 16) + (val % 10));
}

byte bcdToDecimal(byte val) {
  return ((val / 16 * 10) + (val % 16));
}
