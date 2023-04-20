//---------------------------------------------------------------------------------------------------
//  By S. DYCKE
//
//  LMGC - Laboratoire de Mécanique et Génie Civil (Service COMPEX)
//  CNRS - Centre National de la Recherche Scientifique
//  UM   - Université de Montpellier
//
//      Arduino IDE          1.8.19 
//      µC                   ESP32-WROOM-32E
#define Version_logiciel    "MBCAMBIUM-V1.1.0-SD"
#define Version_carte       "670A-V1.0SD"
#define Numero_systeme      "002"
#define device_key          ""
#define Nom_reseau          "DataLog_2_MecanoBioloCambium"
#define Mot_de_passe_reseau ""
//
//  ©Copyright 2022
//
//  Source ESP AP : https://lastminuteengineers.com/creating-esp8266-web-server-arduino-ide/
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



#include <Arduino.h>          //Librairie pour ajout des fonctions Arduino
#include "Wire.h"             //Librairie pour bus i2C
#include "SPI.h"              //Librairie pour bus SPI

#include <WiFi.h>             //Librairie WiFi
#include <WebServer.h>        //Librairie WiFi pour le mode AP
#include <WiFiClientSecure.h> //Librairie pour HTTPS
#include <HTTPClient.h>       //Librairie pour gestion HTTP
#include <WiFiMulti.h>        //Librairie WiFi

#include "SPIFFS.h"           //Librairie pour Flash mem. -> SPIFFS
#include "FS.h"               //Librairie pour Flash mem.   
#include "SD.h"               //Librairie pour utilisation carte SD

#include "ADS1X15.h"          //Librairie pour fonctionnementt ADC

#include "RTClib.h"           //Librairie date pour le RTC DS1339

#include <Adafruit_Sensor.h>  //Librairie pour capteurs adafruit (BME280)
#include <Adafruit_BME280.h>  //Librairie pour capteurs BME280




//Config des broches de contrôle des MuxIN (et LEDs R/V)
#define IO_2_MuxADC_et_LedRV_RWifi 25
#define IO_3_MuxADC_et_LedRV_VWifi 17

//PArametre pour activer ou non les erreur et informations sur port série
bool debugALL = false;
bool debugESSENTIAL = true;

//Variable des codes d'erreurs
String CodeERREUR = "000-";
/******************************************************
000 => L'enregistrement des erreurs est opérationel
1XX => Information
3XX => Erreur client
4XX => Erreur serveur
7XX => Erreur problématique avec le matériel 
8XX => Erreur critique avec le matériel 
******************************************************/

//Variable pour le calc des prises de mesures
int Heure = 0;
int Minute = 0;
int Temps = 0;

int Heure2 = 0;
int Minute2 = 0;
int Temps2 = 0;

void setup() 
  {
    Serial.begin(115200);
    Wire.begin();
    
    if(debugESSENTIAL){Serial.println("");Serial.println("");Serial.println("@=@=@=@=@=@=@=@=@=@=@=@=@=@=@= SETUP =@=@=@=@=@=@=@=@=@=@=@=@=@=@=@");}

    init_LEDs();
    init_74HC4051();
    ledInitMode(1);

    Scan_I2C();
    
    init_Flash_memory();
    init_DS1339();
    init_BME280();
    init_ADC_ADS1113();

    init_WIFI_AP();
    init_WIFI_CL();
    WIFI_ScanNetworks();

    init_SD();
    ledInitMode(0);

    
    if(debugESSENTIAL){Serial.println("@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@");}
  }


void loop() 
  {
    App_Bp_WIFI(); //Pour la mise en mode AP (configuration données AP)
    LEDALL(50);    //Effets lumineux avec les leds
    //Time();
    //BME280();


    //Calc des prises de mesure. Min : 1/jour Max : 1440/jour  (1440/jour ou 1 mesure toute les minutes).  720 pour tt les 2min | 144 pour les 10min
    Heure = TimeHourForWeb().toInt();
    Minute = TimeMinuteForWeb().toInt();
    if (Heure != 0) //Gestion du moment ou il sera 00hXX
      {
        Heure = Heure-1;
      }
    Temps = (Heure*60)+Minute;
    if (Temps%(1440/(readFile(SPIFFS, "/frequenceMesure.txt").toInt())) == 0)
      {
        LED_BiColor_R_ON(); 
        webOutput();
        SDOutput();
        LED_BiColor_R_ON(); 
        //SDOutput();
        //LED_BiColor_R_ON(); 
        //serialOutput();
        //LED_BiColor_R_ON(); 
        
        if(debugESSENTIAL){Serial.print("Fin de cycle de mesures");}
        LED_BiColor_R_OFF(); 
        LED_BiColor_V_OFF(); 
        while (TimeMinuteForWeb().toInt() <= Minute) 
          {
            if(debugESSENTIAL){Serial.print(".");}
            delay(1000);
          }
        if(debugESSENTIAL){Serial.println(".");}
        if(debugESSENTIAL){Serial.println("-------------------------");}
      }


      
//Données sur la carte SD tt les 10min
    Heure2 = TimeHourForWeb().toInt();
    Minute2 = TimeMinuteForWeb().toInt();
    if (Heure2 != 0) //Gestion du moment ou il sera 00hXX
      {
        Heure2 = Heure2-1;
      }
    Temps2 = (Heure2*60)+Minute2;
    if ((Temps2%(1440/144)) == 0) //144 == tout les 10 minutes
      {
        
        LED_BiColor_R_ON(); 
        SDOutput();
        LED_BiColor_R_ON(); 
 
        
        if(debugESSENTIAL){Serial.print("Fin de cycle de mesures");}
        LED_BiColor_R_OFF(); 
        LED_BiColor_V_OFF(); 
        while (TimeMinuteForWeb().toInt() <= Minute2) 
          {
            if(debugESSENTIAL){Serial.print(".");}
            delay(1000);
          }
        if(debugESSENTIAL){Serial.println(".");}
        if(debugESSENTIAL){Serial.println("-------------------------");}
      }

      
  }
