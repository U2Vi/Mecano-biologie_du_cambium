//---------------------------------------------------------------------------------------------------
//  By Sébastien DYCKE
//
//  LMGC - Laboratoire de Mécanique et Génie Civil (Service COMPEX)
//  CNRS - Centre National de la Recherche Scientifique
//  UM   - Université de Montpellier
//
#define Arduino_IDE                      "1.8.19"
#define uC                               "ESP32-S3-WROOM-1-N4R2"
#define Version_logiciel                 "CHAKAL-V2.0.0-SD"
#define Version_carte_DYBoard_Bandmaster "946A-V2"
#define Version_carte_DYBoard_Collector  "A21-V1"
#define Numero_systeme                   "1"
#define device_key                       ""
#define Nom_reseau                       "DataLog_1_MBCV2"
#define Mot_de_passe_reseau              ""
//
//  ©Copyright 2023
//
// ------------------------------------------------------------------------------------------------
//          .,*****,.               .,**,.                                      ,/
//     ,*,*************,*,    ,****************,                         .*//////*
//  .**********************//**********************                ,////////////, 
// ,*********************/////***********************       .*/////////////////*  
//.*****,   .**********////////*************************///////////////////////   
//******,    *********/////////********************(####(/////////////////////*   
//******,    ********//////////*****************#########/////////////////////.   
//******,    *******///////////**************/############////////////////////,   
//******,    *****,*/.        *,        .***#*          /#(//,         *//////*   
//******,    ******,    .,..      .,..    ,.    .*//,     /.    .**,.    //////   
//******,    *****,   ./////*    ******       .#######/       ,////////////////*  
//******,    *****,   ./////*    ******       .#######*       ,///////****//////, 
//******,    *****,   ./////*    ******    ,     .,,.      ,     ...     ////////.
//******,    *****.   ./////*    ******    (##*            ///.       ,///////////
//*******.            /////////************(###########.   ///////////////////////
//*********.       .,//////////*************(/   /##(*    ,///////////////////////
//,********************////////**************(.         .//////////////////////// 
// ,********************//////*****************#######/////////////////////////*  
//  ,*********************///*******************/##(/////////////////////////,    
//    ,******************** .********************  .//////////////////////.       
//       .,***********,.         ,**********.           ,///////////*             
//------------------------------------------------------------------------------------------------ 




//@=@=@=@=@ Library @=@=@=@=@=@=@=@=@=@=@=
#include "Wire.h"             //Librairy for I2C
#include "SPIFFS.h"           //Librairy for Flash mem. -> SPIFFS
//#include "FS.h"               //Librairy for flash mem.   
#include "SD.h"               //Librairy for SD card

#include <WiFi.h>             //Librairie WiFi
#include <WebServer.h>        //Librairie WiFi pour le mode AP
#include <WiFiClientSecure.h> //Librairie pour HTTPS
#include <HTTPClient.h>       //Librairie pour gestion HTTP
#include <WiFiMulti.h>        //Librairie WiFi
//@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=

//@=@=@=@=@ Settings @=@=@=@=@=@=@=@=@=@=@
#define DYBoard_Collector  true
#define DYBoard_Transducer true
#define DYBoard_Feeder     false
//@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=

//@=@=@=@=@ i2C Address @=@=@=@=@=@=@=@=@=
#define RV8523_ADDRESS   0x68 //RTC
#define BQ27441_ADDRESS  0x55 //Fuell Gauge 
#define BME680_ADDRESS   0x77 //Sensor
#define BME688_ADDRESS   0x76 //Sensor
#define SHT85_ADDRESS    0x44 //Sensor
// Collector card :
#define PCA9542_ADDRESS  0x71 //Mux I2C   (0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77)
#define PCAL6416_ADDRESS 0x20 //GPIO Exp  (0x20, 0x21)
// Transducer card :
#define ADS1113_ADDRESS  0x49 //ADC       (0x48, 0x49, 0x4A, 0x4B)
//@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=

//@=@=@=@=@ Pin definitions @=@=@=@=@=@=@=
//I2C
#define I2C_SDA       3
#define I2C_SCL       4
//Aux
#define PWR_AUX_3V3   38
#define PWR_AUX_5V    39
#define BP_WIFI       46
#define broche_CS_SD  8
#define broche_CS_AUX 10
//@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=

//@=@=@=@=@ Variable definitions @=@=@=@=@
String CodeERREUR = "000";
int timeCalc      = 0;
int timeHour      = 0;
int timeMinute    = 0;
//@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=



// /!\ FAIRE LECHANTILLONAGE ADC :)



void setup(){

  init_peripheral_devices();
  
  power_3V3(true);
  power_5V(true);

  init_rtc_device();
  init_Flash_memory();
  init_gpio_exp_device();
  
  //init_ADC_device();
  //init_BME_device();
  
  testing_i2C(); 

  init_SD_device();
  Serial.println("");
}



void loop(){

  delay(500);
  App_Bp_WIFI();



  //**************************************************************************

  //Calc des prises de mesure. Min : 1/jour Max : 1440/jour  (1440/jour ou 1 mesure toute les minutes).  720 pour tt les 2min | 144 pour les 10min
  timeHour = RTC_getHour().toInt();
  timeMinute = RTC_getMinute().toInt();
  if (timeHour != 0){ //Gestion du moment ou il sera 00hXX
    timeHour = timeHour-1;
  }
  timeCalc = (timeHour*60)+timeMinute;
  if (timeCalc%(1440/(readFile(SPIFFS, "/frequenceMesure.txt").toInt())) == 0){ 
    dataOutput();
    Serial.print("Fin de cycle de mesures");
    while (RTC_getMinute().toInt() <= timeMinute) {
      Serial.print(".");
      delay(1000);
    }
    Serial.println(".");
    Serial.println("-------------------------");
    delay(100);
    //RESET SOFT
    ESP.restart();
  }

  //**************************************************************************

}




String connValue(int k, int l) {
  Serial.print("[LOGS] -> Connector J");
  Serial.print(k);
  Serial.print(".");
  Serial.println(l);
  int Moy;
  sensorSelect(k ,l);
  delay(5);
  Moy = ADCNoSampling(); //ADC();
  delay(5);
  return(String(Moy));
}



float convFactBar(float voltage) {
  float bar = 0;
  bar = 6*0.000001*(voltage*1000)*(voltage*1000)+0.0281*(voltage*1000);
  return(bar);
}

void dataOutput(){

  int buffer_ADC = 0;
    
  String toWebData = ""; 
  toWebData += Numero_systeme;
  toWebData += "::";
  toWebData += CodeERREUR;
  toWebData += "::";
  toWebData += RTC_getDateWeb();
  toWebData += "::";
  toWebData += readFile(SPIFFS, "/nombreCapteurs.txt");
  toWebData += "::TMP:";
  toWebData += getTmp();
  toWebData += "::HMD:";
  toWebData += getHmd();

  String toSDData = ""; 
  toSDData += RTC_getDate();
  toSDData += ",";
  toSDData += Numero_systeme;
  toSDData += ",";
  toSDData += CodeERREUR;
  toSDData += ",";
  toSDData += getTmp();
  toSDData += ",";
  toSDData += getHmd();
  toSDData += ",";
    
  toSDData += readFile(SPIFFS, "/nombreCapteurs.txt");

  for (int i = 1; i <= 32; i++) {
    for (int j = 0; j <= 1; j++) {
      toWebData += "::";
      toWebData += "J";
      toWebData += String(i);
      toWebData += ".";
      toWebData += String(j);
      toWebData += ":";

      toSDData += ",";
        
      sensorSelect(i ,j);
      delay(5);
      buffer_ADC = ADC();
      toWebData += String(buffer_ADC);
      toSDData += String(buffer_ADC);
      delay(5);
    }
  }

  toSDData += "\n";   
  Serial.print("[DATA OUT] -> Données à inscrire dans la carte SD :");Serial.println(toSDData);
  String nameFile = "/data_"; 
  nameFile += RTC_dailyIdentifier();
  nameFile += ".txt"; 
  appendFileInSD(SD, nameFile.c_str(), toSDData.c_str());

  Serial.print("[DATA OUT] -> Données à envoyer au cloud :");Serial.println(toWebData);
  SendToCloud(toWebData);
}
