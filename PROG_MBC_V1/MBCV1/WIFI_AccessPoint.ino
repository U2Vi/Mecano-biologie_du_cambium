
#define BP_WIFI          15

//variables pour la sortie de mode AP Automatique
long int tempsExitWithDelay = 0; 
//int dureeExitWithDelay = 100000; // Var. à modifier dans les configues 
int dureeExitWithDelay = 1000000; // Var. à modifier dans les configues 
//Identifiants d'acces à l'ESP en mode accessPoint 
const char* ssid = Nom_reseau;
const char* password = Mot_de_passe_reseau;
//Config. Wifi
String local_ip_redirect = "192.168.4.1"; //pour les fonctions de redirection
IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);


//Init wifi ap mode
void init_WIFI_AP()
  {
      pinMode(BP_WIFI, INPUT);
  }

//Prépart l'ESP32 en mode AP.
void StartInit_WIFI_AP()
  {
    if(debugESSENTIAL){Serial.println("---------------------- Wifi AP pre-start --------------------------");}
    if(debugESSENTIAL){Serial.println();}
    if(debugESSENTIAL){Serial.print("Setting soft-AP configuration ... ");}
    if(debugESSENTIAL){Serial.println(WiFi.softAPConfig(local_ip, gateway, subnet) ? "Ready" : "Failed!");}
    if(debugESSENTIAL){Serial.print("Setting soft-AP ... ");}
    if(debugESSENTIAL){Serial.println(WiFi.softAP(ssid,password) ? "Ready" : "Failed!");}
    if(debugESSENTIAL){Serial.print("Soft-AP IP address = ");}
    if(debugESSENTIAL){Serial.println(WiFi.softAPIP());}
    if(debugESSENTIAL){Serial.println("-------------------------------------------------------------------");}
    delay(10);
    
    //Liste des pages et des fonctions qui leurs sont associées 
    server.on("/", handle_OnConnect);
    server.on("/reset", handle_reset);
    server.on("/frequenceDesMesures", frequenceDesMesures);
    server.on("/readForceNValue48", readForceNValue48);
    server.on("/readForceNValue47", readForceNValue47);
    server.on("/readForceNValue46", readForceNValue46);
    server.on("/readForceNValue45", readForceNValue45);
    server.on("/readForceNValue44", readForceNValue44);
    server.on("/readForceNValue43", readForceNValue43);
    server.on("/readForceNValue42", readForceNValue42);
    server.on("/readForceNValue41", readForceNValue41);
    server.on("/readForceNValue40", readForceNValue40);
    server.on("/readForceNValue39", readForceNValue39);
    server.on("/readForceNValue38", readForceNValue38);
    server.on("/readForceNValue37", readForceNValue37);
    server.on("/readForceNValue36", readForceNValue36);
    server.on("/readForceNValue35", readForceNValue35);
    server.on("/readForceNValue34", readForceNValue34);
    server.on("/readForceNValue33", readForceNValue33);
    server.on("/readForceNValue32", readForceNValue32);
    server.on("/readForceNValue31", readForceNValue31);
    server.on("/readForceNValue30", readForceNValue30);
    server.on("/readForceNValue29", readForceNValue29);
    server.on("/readForceNValue28", readForceNValue28);
    server.on("/readForceNValue27", readForceNValue27);
    server.on("/readForceNValue26", readForceNValue26);
    server.on("/readForceNValue25", readForceNValue25);
    server.on("/readForceNValue24", readForceNValue24);
    server.on("/readForceNValue23", readForceNValue23);
    server.on("/readForceNValue22", readForceNValue22);
    server.on("/readForceNValue21", readForceNValue21);
    server.on("/readForceNValue20", readForceNValue20);
    server.on("/readForceNValue19", readForceNValue19);
    server.on("/readForceNValue18", readForceNValue18);
    server.on("/readForceNValue17", readForceNValue17);
    server.on("/readForceNValue16", readForceNValue16);
    server.on("/readForceNValue15", readForceNValue15);
    server.on("/readForceNValue14", readForceNValue14);
    server.on("/readForceNValue13", readForceNValue13);
    server.on("/readForceNValue12", readForceNValue12);
    server.on("/readForceNValue11", readForceNValue11);
    server.on("/readForceNValue10", readForceNValue10);
    server.on("/readForceNValue9", readForceNValue9);
    server.on("/readForceNValue8", readForceNValue8);
    server.on("/readForceNValue7", readForceNValue7);
    server.on("/readForceNValue6", readForceNValue6);
    server.on("/readForceNValue5", readForceNValue5);
    server.on("/readForceNValue4", readForceNValue4);
    server.on("/readForceNValue3", readForceNValue3);
    server.on("/readForceNValue2", readForceNValue2);
    server.on("/readForceNValue1", readForceNValue1);
    server.on("/readForceTValue48", readForceTValue48);
    server.on("/readForceTValue47", readForceTValue47);
    server.on("/readForceTValue46", readForceTValue46);
    server.on("/readForceTValue45", readForceTValue45);
    server.on("/readForceTValue44", readForceTValue44);
    server.on("/readForceTValue43", readForceTValue43);
    server.on("/readForceTValue42", readForceTValue42);
    server.on("/readForceTValue41", readForceTValue41);
    server.on("/readForceTValue40", readForceTValue40);
    server.on("/readForceTValue39", readForceTValue39);
    server.on("/readForceTValue38", readForceTValue38);
    server.on("/readForceTValue37", readForceTValue37);
    server.on("/readForceTValue36", readForceTValue36);
    server.on("/readForceTValue35", readForceTValue35);
    server.on("/readForceTValue34", readForceTValue34);
    server.on("/readForceTValue33", readForceTValue33);
    server.on("/readForceTValue32", readForceTValue32);
    server.on("/readForceTValue31", readForceTValue31);
    server.on("/readForceTValue30", readForceTValue30);
    server.on("/readForceTValue29", readForceTValue29);
    server.on("/readForceTValue28", readForceTValue28);
    server.on("/readForceTValue27", readForceTValue27);
    server.on("/readForceTValue26", readForceTValue26);
    server.on("/readForceTValue25", readForceTValue25);
    server.on("/readForceTValue24", readForceTValue24);
    server.on("/readForceTValue23", readForceTValue23);
    server.on("/readForceTValue22", readForceTValue22);
    server.on("/readForceTValue21", readForceTValue21);
    server.on("/readForceTValue20", readForceTValue20);
    server.on("/readForceTValue19", readForceTValue19);
    server.on("/readForceTValue18", readForceTValue18);
    server.on("/readForceTValue17", readForceTValue17);
    server.on("/readForceTValue16", readForceTValue16);
    server.on("/readForceTValue15", readForceTValue15);
    server.on("/readForceTValue14", readForceTValue14);
    server.on("/readForceTValue13", readForceTValue13);
    server.on("/readForceTValue12", readForceTValue12);
    server.on("/readForceTValue11", readForceTValue11);
    server.on("/readForceTValue10", readForceTValue10);
    server.on("/readForceTValue9", readForceTValue9);
    server.on("/readForceTValue8", readForceTValue8);
    server.on("/readForceTValue7", readForceTValue7);
    server.on("/readForceTValue6", readForceTValue6);
    server.on("/readForceTValue5", readForceTValue5);
    server.on("/readForceTValue4", readForceTValue4);
    server.on("/readForceTValue3", readForceTValue3);
    server.on("/readForceTValue2", readForceTValue2);
    server.on("/readForceTValue1", readForceTValue1);
    server.on("/identifiantsWifi", identifiantsWifi);
    server.on("/newCalibTempHmdR", newCalibTempHmdR);
    server.on("/nombreCapteurs", nombreCapteurs);
    server.on("/calibDateHeure", calibDateHeure);
    server.on("/calibTempHmdR", calibTempHmdR);
    server.on("/newCalibFSRJX", newCalibFSRJX);
    server.on("/configWIFI", configWIFI);
    server.on("/configMESURES", configMESURES);
    server.on("/configCAPTEURS", configCAPTEURS);
    server.on("/configAUTRE", configAUTRE);
    server.on("/calibFSRJX", calibFSRJX);
    server.on("/readADCV", handleADCVValue);
    server.on("/readADCN", handleADCNValue);
    server.on("/readTIME", handleTIMEValue);
    server.on("/readTMPB", handleTMPBValue);
    server.on("/newCalibADC", newCalibADC);
    server.on("/readTMP", handleTMPValue);
    server.on("/readHRB", handleHRBValue);
    server.on("/readHR", handleHRValue);
    server.onNotFound(handle_NotFound);
    server.on("/calibFSR", calibFSR);
    server.on("/calibADC", calibADC);
    server.on("/newDate", newDate);
    server.begin();

    if(debugESSENTIAL){Serial.println("HTTP server started ...");}
  }


//Fonction de mise en mode AP
void App_Bp_WIFI()
  {
    if(digitalRead(BP_WIFI) == 0)
      {
        LED_BiColor_R_ON();
        while(digitalRead(BP_WIFI) == 0){delay(10);} //Fonction bloquante pour attendre le relachement du bp 
        for (uint8_t i = 0; i < 50; i++)  //Attente d'un deuxieme app pendant 10s
          {
            if(digitalRead(BP_WIFI) == 0) // Si deuxieme app pendant les 10s
              {
                StartInit_WIFI_AP();
                while(1)
                  {
                    LED_BiColor_V_ON();
                    WIFI_Mode_AP(); //(fonction blocante, reset obligatoire pour sortir du mode AP)
                  }
                return; //Sécuritée si on sort de la boucle
              }
            LED_BiColor_R(100);
          }
      }
  }


//Mise en mode AP
void WIFI_Mode_AP()
  {
    server.handleClient();
    exitWithDelay();
  }

//Si un client est connecté
void handle_OnConnect() 
  {
    tempsExitWithDelay = 0;
    server.send(200, "text/html", SendHTML()); 
  }

//Send Force (N) value (on channel "1") only to client ajax request 
void readForceNValue1()
  {
     server.send(200, "text/plane", ForceNForWeb(1));
  }
void readForceNValue2()
  {
     server.send(200, "text/plane", ForceNForWeb(2));
  }
void readForceNValue3()
  {
     server.send(200, "text/plane", ForceNForWeb(3));
  }
void readForceNValue4()
  {
     server.send(200, "text/plane", ForceNForWeb(4));
  }
void readForceNValue5()
  {
     server.send(200, "text/plane", ForceNForWeb(5));
  }
void readForceNValue6()
  {
     server.send(200, "text/plane", ForceNForWeb(6));
  }
void readForceNValue7()
  {
     server.send(200, "text/plane", ForceNForWeb(7));
  }
void readForceNValue8()
  {
     server.send(200, "text/plane", ForceNForWeb(8));
  }
void readForceNValue9()
  {
     server.send(200, "text/plane", ForceNForWeb(9));
  }
void readForceNValue10()
  {
     server.send(200, "text/plane", ForceNForWeb(10));
  }
void readForceNValue11()
  {
     server.send(200, "text/plane", ForceNForWeb(11));
  }
void readForceNValue12()
  {
     server.send(200, "text/plane", ForceNForWeb(12));
  }
void readForceNValue13()
  {
     server.send(200, "text/plane", ForceNForWeb(13));
  }
void readForceNValue14()
  {
     server.send(200, "text/plane", ForceNForWeb(14));
  }
void readForceNValue15()
  {
     server.send(200, "text/plane", ForceNForWeb(15));
  }
void readForceNValue16()
  {
     server.send(200, "text/plane", ForceNForWeb(16));
  }
void readForceNValue17()
  {
     server.send(200, "text/plane", ForceNForWeb(17));
  }
void readForceNValue18()
  {
     server.send(200, "text/plane", ForceNForWeb(18));
  }
void readForceNValue19()
  {
     server.send(200, "text/plane", ForceNForWeb(19));
  }
void readForceNValue20()
  {
     server.send(200, "text/plane", ForceNForWeb(20));
  }
void readForceNValue21()
  {
     server.send(200, "text/plane", ForceNForWeb(21));
  }
void readForceNValue22()
  {
     server.send(200, "text/plane", ForceNForWeb(22));
  }
void readForceNValue23()
  {
     server.send(200, "text/plane", ForceNForWeb(23));
  }
void readForceNValue24()
  {
     server.send(200, "text/plane", ForceNForWeb(24));
  }
void readForceNValue25()
  {
     server.send(200, "text/plane", ForceNForWeb(25));
  }
void readForceNValue26()
  {
     server.send(200, "text/plane", ForceNForWeb(26));
  }
void readForceNValue27()
  {
     server.send(200, "text/plane", ForceNForWeb(27));
  }
void readForceNValue28()
  {
     server.send(200, "text/plane", ForceNForWeb(28));
  }
void readForceNValue29()
  {
     server.send(200, "text/plane", ForceNForWeb(29));
  }
void readForceNValue30()
  {
     server.send(200, "text/plane", ForceNForWeb(30));
  }
void readForceNValue31()
  {
     server.send(200, "text/plane", ForceNForWeb(31));
  }
void readForceNValue32()
  {
     server.send(200, "text/plane", ForceNForWeb(32));
  }
void readForceNValue33()
  {
     server.send(200, "text/plane", ForceNForWeb(33)); 
  }
void readForceNValue34()
  {
     server.send(200, "text/plane", ForceNForWeb(34));
  }
void readForceNValue35()
  {
     server.send(200, "text/plane", ForceNForWeb(35));
  }
void readForceNValue36()
  {
     server.send(200, "text/plane", ForceNForWeb(36));
  }
void readForceNValue37()
  {
     server.send(200, "text/plane", ForceNForWeb(37));
  }
void readForceNValue38()
  {
     server.send(200, "text/plane", ForceNForWeb(38));
  }
void readForceNValue39()
  {
     server.send(200, "text/plane", ForceNForWeb(39));
  }
void readForceNValue40()
  {
     server.send(200, "text/plane", ForceNForWeb(40));
  }
void readForceNValue41()
  {
     server.send(200, "text/plane", ForceNForWeb(41));
  }
void readForceNValue42()
  {
     server.send(200, "text/plane", ForceNForWeb(42));
  }
void readForceNValue43()
  {
     server.send(200, "text/plane", ForceNForWeb(43));
  }
void readForceNValue44()
  {
     server.send(200, "text/plane", ForceNForWeb(44));
  }
void readForceNValue45()
  {
     server.send(200, "text/plane", ForceNForWeb(45));
  }
void readForceNValue46()
  {
     server.send(200, "text/plane", ForceNForWeb(46));
  }
void readForceNValue47()
  {
     server.send(200, "text/plane", ForceNForWeb(47));
  }
void readForceNValue48()
  {
     server.send(200, "text/plane", ForceNForWeb(48));
  }

//Send Force (V) value (on channel "1") only to client ajax request 
void readForceTValue1()
  {
     server.send(200, "text/plane", ADCNumOut(1)); 
  }
void readForceTValue2()
  {
     server.send(200, "text/plane", ADCNumOut(2));
  }
void readForceTValue3()
  {
     server.send(200, "text/plane", ADCNumOut(3));
  }
void readForceTValue4()
  {
     server.send(200, "text/plane", ADCNumOut(4));
  }
void readForceTValue5()
  {
     server.send(200, "text/plane", ADCNumOut(5));
  }
void readForceTValue6()
  {
     server.send(200, "text/plane", ADCNumOut(6));
  }
void readForceTValue7()
  {
     server.send(200, "text/plane", ADCNumOut(7));
  }
void readForceTValue8()
  {
     server.send(200, "text/plane", ADCNumOut(8));
  }
void readForceTValue9()
  {
     server.send(200, "text/plane", ADCNumOut(9));
  }
void readForceTValue10()
  {
     server.send(200, "text/plane", ADCNumOut(10));
  }
void readForceTValue11()
  {
     server.send(200, "text/plane", ADCNumOut(11));
  }
void readForceTValue12()
  {
     server.send(200, "text/plane", ADCNumOut(12));
  }
void readForceTValue13()
  {
     server.send(200, "text/plane", ADCNumOut(13));
  }
void readForceTValue14()
  {
     server.send(200, "text/plane", ADCNumOut(14));
  }
void readForceTValue15()
  {
     server.send(200, "text/plane", ADCNumOut(15));
  }
void readForceTValue16()
  {
     server.send(200, "text/plane", ADCNumOut(16));
  }
void readForceTValue17()
  {
     server.send(200, "text/plane", ADCNumOut(17));
  }
void readForceTValue18()
  {
     server.send(200, "text/plane", ADCNumOut(18));
  }
void readForceTValue19()
  {
     server.send(200, "text/plane", ADCNumOut(19));
  }
void readForceTValue20()
  {
     server.send(200, "text/plane", ADCNumOut(20));
  }
void readForceTValue21()
  {
     server.send(200, "text/plane", ADCNumOut(21));
  }
void readForceTValue22()
  {
     server.send(200, "text/plane", ADCNumOut(22));
  }
void readForceTValue23()
  {
     server.send(200, "text/plane", ADCNumOut(23));
  }
void readForceTValue24()
  {
     server.send(200, "text/plane", ADCNumOut(24));
  }
void readForceTValue25()
  {
     server.send(200, "text/plane", ADCNumOut(25));
  }
void readForceTValue26()
  {
     server.send(200, "text/plane", ADCNumOut(26));
  }
void readForceTValue27()
  {
     server.send(200, "text/plane", ADCNumOut(27));
  }
void readForceTValue28()
  {
     server.send(200, "text/plane", ADCNumOut(28));
  }
void readForceTValue29()
  {
     server.send(200, "text/plane", ADCNumOut(29));
  }
void readForceTValue30()
  {
     server.send(200, "text/plane", ADCNumOut(30));
  }
void readForceTValue31()
  {
     server.send(200, "text/plane", ADCNumOut(31));
  }
void readForceTValue32()
  {
     server.send(200, "text/plane", ADCNumOut(32));
  }
void readForceTValue33()
  {
     server.send(200, "text/plane", ADCNumOut(33));
  }
void readForceTValue34()
  {
     server.send(200, "text/plane", ADCNumOut(34));
  }
void readForceTValue35()
  {
     server.send(200, "text/plane", ADCNumOut(35));
  }
void readForceTValue36()
  {
     server.send(200, "text/plane", ADCNumOut(36));
  }
void readForceTValue37()
  {
     server.send(200, "text/plane", ADCNumOut(37));
  }
void readForceTValue38()
  {
     server.send(200, "text/plane", ADCNumOut(38));
  }
void readForceTValue39()
  {
     server.send(200, "text/plane", ADCNumOut(39));
  }
void readForceTValue40()
  {
     server.send(200, "text/plane", ADCNumOut(40));
  }
void readForceTValue41()
  {
     server.send(200, "text/plane", ADCNumOut(41));
  }
void readForceTValue42()
  {
     server.send(200, "text/plane", ADCNumOut(42));
  }
void readForceTValue43()
  {
     server.send(200, "text/plane", ADCNumOut(43)); 
  }
void readForceTValue44()
  {
     server.send(200, "text/plane", ADCNumOut(44));
  }
void readForceTValue45()
  {
     server.send(200, "text/plane", ADCNumOut(45));
  }
void readForceTValue46()
  {
     server.send(200, "text/plane", ADCNumOut(46));
  }
void readForceTValue47()
  {
     server.send(200, "text/plane", ADCNumOut(47));
  }
void readForceTValue48()
  {
     server.send(200, "text/plane", ADCNumOut(48));
  }


void configWIFI()
  {
    tempsExitWithDelay = 0;
    String msg = "<!DOCTYPE html><html>\n";
    msg +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"> \n";
    msg +="<title>ESP Acquisition Unit</title>\n";
    msg +="<style>\n";
    msg +="html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    msg +="body{margin-top: 50px;} \n";
    msg +="h1{color: #444444;margin: 50px auto 30px;} \n";
    msg +="h3{color: #444444;margin-bottom: 50px;}\n";
    msg +=".button{display: block;width: 200px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    msg +=".button-on{background-color: #1abc9c;}\n";
    msg +=".button-on:active{background-color: #16a085;}\n";
    msg +=".button-off{background-color: #34495e;}\n";
    msg +=".button-off:active{background-color: #2c3e50;}\n";
    msg +=".button-reset{background-color: #D3553A;}\n";
    msg +="p{font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    msg +="</style></head>\n";
    msg +="<body>\n";
    msg +="<h1>ESP Acquisition Unit<br>Configuration Wifi</h1> \n";
    
    msg +="R&eacute;seau WiFi &agrave; utiliser pour l'envoie de donn&eacute;es<br><br>\n";
    msg +="<form action=\"/identifiantsWifi\">\n";
 
    msg +="<label for=\"input1\">Nom du r&eacute;seau (SSID) : <br><br></label>\n";
    msg +="<input list=\"list_ssid\" id=\"input1\" name=\"input1\" value=\"\n";
    msg +=readFile(SPIFFS, "/ssidBoxWifi.txt");
    msg +="\"/>\n";
    msg +="<datalist id=\"list_ssid\">\n";
    msg +=WIFI_Scan_and_build_networks_selection();  //Affiche la liste des reseaux dispo 
    msg +="</datalist>\n";
    
    msg += "<br><br>Clef d'acc&egrave;s :<br><br><input type=\"text\" name=\"input2\" value=\"\n";
    msg +=readFile(SPIFFS, "/passwordBoxWifi.txt");
    msg +="\"><br><br><input class=\"button button-off\" type=\"submit\" value=\"Enregistrer\">\n";
    msg +="</form>\n";
    msg +="<p></p><a class=\"button button-reset\" href=\"/\"><- BACK</a> \n";

    msg +="</body></html>\n";
    server.send(200, "text/html", msg);
  }

  
void configMESURES()
  {
    tempsExitWithDelay = 0;
    String msg = "<!DOCTYPE html><html>\n";
    msg +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"> \n";
    msg +="<title>ESP Acquisition Unit</title>\n";
    msg +="<style>\n";
    msg +="html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    msg +="body{margin-top: 50px;} \n";
    msg +="h1{color: #444444;margin: 50px auto 30px;} \n";
    msg +="h3{color: #444444;margin-bottom: 50px;}\n";
    msg +=".button{display: block;width: 200px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    msg +=".button-on{background-color: #1abc9c;}\n";
    msg +=".button-on:active{background-color: #16a085;}\n";
    msg +=".button-off{background-color: #34495e;}\n";
    msg +=".button-off:active{background-color: #2c3e50;}\n";
    msg +=".button-reset{background-color: #D3553A;}\n";
    msg +="p{font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    msg +="</style></head>\n";
    msg +="<body>\n";
    msg +="<h1>ESP Acquisition Unit<br>Configuration des mesures</h1> \n";

    msg +="<form action=\"/frequenceDesMesures\">\n";
    msg +="Fr&eacute;quence des mesures (par jours) :  <br><br> <input type=\"text\" name=\"input3\" value=\"";
    msg +=readFile(SPIFFS, "/frequenceMesure.txt");
    msg +="\">  <br><br> <input class=\"button button-off\" type=\"submit\" value=\"Enregistrer\">\n";
    msg +="</form>\n";
    
    msg +="<p></p><a class=\"button button-reset\" href=\"/\"><- BACK</a> \n";
    msg +="</body></html>\n";
    server.send(200, "text/html", msg);  
  }

  
void configCAPTEURS()
  {
    tempsExitWithDelay = 0;
    String msg = "<!DOCTYPE html><html>\n";
    msg +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"> \n";
    msg +="<title>ESP Acquisition Unit</title>\n";
    msg +="<style>\n";
    msg +="html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    msg +="body{margin-top: 50px;} \n";
    msg +="h1{color: #444444;margin: 50px auto 30px;} \n";
    msg +="h3{color: #444444;margin-bottom: 50px;}\n";
    msg +=".button{display: block;width: 200px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    msg +=".button-on{background-color: #1abc9c;}\n";
    msg +=".button-on:active{background-color: #16a085;}\n";
    msg +=".button-off{background-color: #34495e;}\n";
    msg +=".button-off:active{background-color: #2c3e50;}\n";
    msg +=".button-reset{background-color: #D3553A;}\n";
    msg +="p{font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    msg +="</style></head>\n";
    msg +="<body>\n";
    msg +="<h1>ESP Acquisition Unit<br>Configuration des capteurs</h1> \n";

    msg +="<form action=\"/nombreCapteurs\">\n";
    msg +="Nombre de capteurs en place (de J1 &agrave; J48) :  <br><br> <input type=\"text\" name=\"input4\" value=\"";
    msg +=readFile(SPIFFS, "/nombreCapteurs.txt");
    msg +="\">  <br><br> <input class=\"button button-off\" type=\"submit\" value=\"Enregistrer\">\n";
    msg +="</form>\n";

    msg +="<p></p><a class=\"button button-reset\" href=\"/\"><- BACK</a> \n";
    msg +="</body></html>\n";
    server.send(200, "text/html", msg);
  }

  
void configAUTRE()
  {
    tempsExitWithDelay = 0;
    String msg = "<!DOCTYPE html><html>\n";
    msg +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"> \n";
    msg +="<title>ESP Acquisition Unit</title>\n";
    msg +="<style>\n";
    msg +="html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    msg +="body{margin-top: 50px;} \n";
    msg +="h1{color: #444444;margin: 50px auto 30px;} \n";
    msg +="h3{color: #444444;margin-bottom: 50px;}\n";
    msg +=".button{display: block;width: 200px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    msg +=".button-on{background-color: #1abc9c;}\n";
    msg +=".button-on:active{background-color: #16a085;}\n";
    msg +=".button-off{background-color: #34495e;}\n";
    msg +=".button-off:active{background-color: #2c3e50;}\n";
    msg +=".button-reset{background-color: #D3553A;}\n";
    msg +="p{font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    msg +="</style></head>\n";
    msg +="<body>\n";
    msg +="<h1>ESP Acquisition Unit<br>Configuration syst&egrave;me</h1> \n";

    //ICI

    msg +="<p></p><a class=\"button button-reset\" href=\"/\"><- BACK</a> \n";
    msg +="</body></html>\n";
    server.send(200, "text/html", msg);
  }


void calibFSRJX()
  {
    tempsExitWithDelay = 0;
    int numCapt = 0;
    for (int i = 0; i < server.args(); i++) 
      {
        if(debugALL){Serial.print("Variable : ");Serial.print(server.argName(i));Serial.print(" ---> valeur : ");Serial.println(server.arg(i));}
        if (i == 0) //Si premier tour de for c'est num capteur a calib.
          {
            numCapt = server.arg(i).toInt();
          }
        else
          {
            
          }
      }
    String msg = "<!DOCTYPE html><html>\n";
    msg +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"> \n";
    msg +="<title>ESP Acquisition Unit</title>\n";
    msg +="<style>\n";
    msg +="html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    msg +="body{margin-top: 50px;} \n";
    msg +="h1{color: #444444;margin: 50px auto 30px;} \n";
    msg +="h3{color: #444444;margin-bottom: 50px;}\n";
    msg +=".button{display: block;width: 200px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    msg +=".button-on{background-color: #1abc9c;}\n";
    msg +=".button-on:active{background-color: #16a085;}\n";
    msg +=".button-off{background-color: #34495e;}\n";
    msg +=".button-off:active{background-color: #2c3e50;}\n";
    msg +=".button-reset{background-color: #D3553A;}\n";
    msg +="p{font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    msg +="</style></head>\n";
    msg +="<body>\n";
    
    msg +="<h1>ESP Acquisition Unit<br> Calibration FSR</h1> \n";

    msg +="<h1>Proc&eacute;dure de calibration : </h1> \n";

    msg +="<DIV align=\"left\">";
    msg +="<br>\n";
    msg +="1) ...<br>\n";
    msg +="2) ...<br>\n";
    msg +="X) Le capteur est calibr&eacute; !<br>\n";
    msg +="<br><br></DIV>\n";
    
    msg +="<p>Valeur num&eacute;rique lue sur J";msg += numCapt;msg +=" : <b>\n";
    msg +="<span id=\"ForceTValue";msg += numCapt;msg +="\">\n";
    msg +=ADCNumOut(numCapt); 
    msg +="</span>\n";
    msg +="</b></p>\n";

    msg +="<form action=\"/newCalibFSRJX\">\n";

    msg +="<br>Courbe de tendance polynomiale du 5&eacute;me ordre : <br><br>\n";

    char * nomFichierCalibFSR;
    switch (numCapt) 
      {
        case 1:
          nomFichierCalibFSR = "/ctp5_1.txt";
          break;
        case 2:
          nomFichierCalibFSR = "/ctp5_2.txt";
          break;
        case 3:
          nomFichierCalibFSR = "/ctp5_3.txt";
          break;
        case 4:
          nomFichierCalibFSR = "/ctp5_4.txt";
          break;
        case 5:
          nomFichierCalibFSR = "/ctp5_5.txt";
          break;
        case 6:
          nomFichierCalibFSR = "/ctp5_6.txt";
          break;
        case 7:
          nomFichierCalibFSR = "/ctp5_7.txt";
          break;
        case 8:
          nomFichierCalibFSR = "/ctp5_8.txt";
          break;
        case 9:
          nomFichierCalibFSR = "/ctp5_9.txt";
          break;
        case 10:
          nomFichierCalibFSR = "/ctp5_10.txt";
          break;
        case 11:
          nomFichierCalibFSR = "/ctp5_11.txt";
          break;
        case 12:
          nomFichierCalibFSR = "/ctp5_12.txt";
          break;
        case 13:
          nomFichierCalibFSR = "/ctp5_13.txt";
          break;
        case 14:
          nomFichierCalibFSR = "/ctp5_14.txt";
          break;
        case 15:
          nomFichierCalibFSR = "/ctp5_15.txt";
          break;
        case 16:
          nomFichierCalibFSR = "/ctp5_16.txt";
          break;
        case 17:
          nomFichierCalibFSR = "/ctp5_17.txt";
          break;
        case 18:
          nomFichierCalibFSR = "/ctp5_18.txt";
          break;
        case 19:
          nomFichierCalibFSR = "/ctp5_19.txt";
          break;
        case 20:
          nomFichierCalibFSR = "/ctp5_20.txt";
          break;
        case 21:
          nomFichierCalibFSR = "/ctp5_21.txt";
          break;
        case 22:
          nomFichierCalibFSR = "/ctp5_22.txt";
          break;
        case 23:
          nomFichierCalibFSR = "/ctp5_23.txt";
          break;
        case 24:
          nomFichierCalibFSR = "/ctp5_24.txt";
          break;
        case 25:
          nomFichierCalibFSR = "/ctp5_25.txt";
          break;
        case 26:
          nomFichierCalibFSR = "/ctp5_26.txt";
          break;
        case 27:
          nomFichierCalibFSR = "/ctp5_27.txt";
          break;
        case 28:
          nomFichierCalibFSR = "/ctp5_28.txt";
          break;
        case 29:
          nomFichierCalibFSR = "/ctp5_29.txt";
          break;
        case 30:
          nomFichierCalibFSR = "/ctp5_30.txt";
          break;
        case 31:
          nomFichierCalibFSR = "/ctp5_31.txt";
          break;
        case 32:
          nomFichierCalibFSR = "/ctp5_32.txt";
          break;
        case 33:
          nomFichierCalibFSR = "/ctp5_33.txt";
          break;
        case 34:
          nomFichierCalibFSR = "/ctp5_34.txt";
          break;
        case 35:
          nomFichierCalibFSR = "/ctp5_35.txt";
          break;
        case 36:
          nomFichierCalibFSR = "/ctp5_36.txt";
          break;
        case 37:
          nomFichierCalibFSR = "/ctp5_37.txt";
          break;
        case 38:
          nomFichierCalibFSR = "/ctp5_38.txt";
          break;
        case 39:
          nomFichierCalibFSR = "/ctp5_39.txt";
          break;
        case 40:
          nomFichierCalibFSR = "/ctp5_40.txt";
          break;
        case 41:
          nomFichierCalibFSR = "/ctp5_41.txt";
          break;
        case 42:
          nomFichierCalibFSR = "/ctp5_42.txt";
          break;
        case 43:
          nomFichierCalibFSR = "/ctp5_43.txt";
          break;
        case 44:
          nomFichierCalibFSR = "/ctp5_44.txt";
          break;
        case 45:
          nomFichierCalibFSR = "/ctp5_45.txt";
          break;
        case 46:
          nomFichierCalibFSR = "/ctp5_46.txt";
          break;
        case 47:
          nomFichierCalibFSR = "/ctp5_47.txt";
          break;
         case 48:
          nomFichierCalibFSR = "/ctp5_48.txt";
          break;         
        default:
          break;
      }

    String paramCTP5 = String(readFile(SPIFFS, nomFichierCalibFSR));
    String CTP5_X5, CTP5_X4, CTP5_X3, CTP5_X2, CTP5_X, CTP5_Y;

    //Extrait les données d'un string de type :donnée1:donnée2:donnéeX:
    int k = 0;
    int l = 0;
    for (int i = 0; i < paramCTP5.length(); i++) 
      {
        if (i != 0 && paramCTP5.substring(i, i+1) == ":") 
        {
          l++;
          switch (l) 
            {
              case 1:
                CTP5_X5 = paramCTP5.substring(k+1,i);
                break;
              case 2:
                CTP5_X4 = paramCTP5.substring(k+1,i);
                break;
              case 3:
                CTP5_X3 = paramCTP5.substring(k+1,i);
                break; 
              case 4:
                CTP5_X2 = paramCTP5.substring(k+1,i);
                break;  
              case 5:
                CTP5_X = paramCTP5.substring(k+1,i);
                break; 
              case 6:
                CTP5_Y = paramCTP5.substring(k+1,i);
                break;               
              default:
                break;
            }
          k = i;
        }
      } 
  
    msg +="<input type=\"hidden\" id=\"input29\" name=\"input29\" value=\"\n";
    msg +=String(numCapt);
    msg +="\"/>\n";
    msg += "<br><br>x^5 : <br><br><input type=\"text\" name=\"input30\" value=\"\n";
    msg +=CTP5_X5;
    msg +="\">\n";
    msg += "<br><br>x^4 : <br><br><input type=\"text\" name=\"input31\" value=\"\n";
    msg +=CTP5_X4;
    msg +="\">\n";
    msg += "<br><br>x^3 : <br><br><input type=\"text\" name=\"input32\" value=\"\n";
    msg +=CTP5_X3;
    msg +="\">\n";
    msg += "<br><br>x^2 : <br><br><input type=\"text\" name=\"input33\" value=\"\n";
    msg +=CTP5_X2;
    msg +="\">\n";
    msg += "<br><br>x : <br><br><input type=\"text\" name=\"input34\" value=\"\n";
    msg +=CTP5_X;
    msg +="\">\n";
    msg += "<br><br>y : <br><br><input type=\"text\" name=\"input35\" value=\"\n";
    msg +=CTP5_Y;
    msg +="\">\n";
    msg +="<br><br><input class=\"button button-off\" type=\"submit\" value=\"Enregistrer\">\n";
    msg +="<p></p><a class=\"button button-reset\" href=\"/calibFSR\"><- BACK</a> \n";
    msg +="</form>\n";    


    msg +="<script>\n";
    msg +="setInterval(function(){getData";msg += 50+numCapt;msg +="();}, 500);\n";
    msg +="function getData";msg += 50+numCapt;msg +="() \n";
    msg +="  {\n";
    msg +="    var xhttp = new XMLHttpRequest();\n";
    msg +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"ForceTValue";msg += numCapt;msg +="\").innerHTML = this.responseText;}};\n";
    msg +="    xhttp.open(\"GET\", \"readForceTValue";msg += numCapt;msg +="\", true);\n"; 
    msg +="    xhttp.send();\n";
    msg +="  }\n";  
    msg +="</script>\n";
    
    msg +="</body></html>\n";
    server.send(200, "text/html", msg);
  }


void newCalibFSRJX()
  {
    tempsExitWithDelay = 0;
    if(debugESSENTIAL){Serial.println("Calibration du capteur FSR -> ok");}
    
    String msg = "<html>";
    msg +="<head>";
    msg +="<title>Redirection ...</title>";
    msg +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"/calibFSR\">";
    msg +="</head>";
    msg +="<body>";

    msg += "<br><br><center><h1 style=\"color:#7FBB1B;\">Les saisies du formulaire ont bien &eacute;t&eacute; prises en compte</h1></center><br>\n";
    msg += "<center><h4>Redirection ...</h4></center>\n";

    String CTP5_X5, CTP5_X4, CTP5_X3, CTP5_X2, CTP5_X, CTP5_Y;
    int NUMCapt;
    for (int i = 0; i < server.args(); i++) 
      {
        if(debugALL){Serial.print("Variable : ");Serial.print(server.argName(i));Serial.print(" ---> valeur : ");Serial.println(server.arg(i));}
        if (i == 0)
          {
            NUMCapt = server.arg(i).toInt();
          }
        else if (i == 1) 
          {
            CTP5_X5 = server.arg(i).c_str();
          }
        else if (i == 2) 
          {
            CTP5_X4 = server.arg(i).c_str();
          }
        else if (i == 3) 
          {
            CTP5_X3 = server.arg(i).c_str();
          }
        else if (i == 4) 
          {
            CTP5_X2 = server.arg(i).c_str();
          }
        else if (i == 5) 
          {
            CTP5_X = server.arg(i).c_str();
          }
        else if (i == 6) 
          {
            CTP5_Y = server.arg(i).c_str();
          }
        else
          {
            
          }
      }
    char * nomFichierCalibFSR;
    switch (NUMCapt) 
      {
        case 1:
          nomFichierCalibFSR = "/ctp5_1.txt";
          break;
        case 2:
          nomFichierCalibFSR = "/ctp5_2.txt";
          break;
        case 3:
          nomFichierCalibFSR = "/ctp5_3.txt";
          break;
        case 4:
          nomFichierCalibFSR = "/ctp5_4.txt";
          break;
        case 5:
          nomFichierCalibFSR = "/ctp5_5.txt";
          break;
        case 6:
          nomFichierCalibFSR = "/ctp5_6.txt";
          break;
        case 7:
          nomFichierCalibFSR = "/ctp5_7.txt";
          break;
        case 8:
          nomFichierCalibFSR = "/ctp5_8.txt";
          break;
        case 9:
          nomFichierCalibFSR = "/ctp5_9.txt";
          break;
        case 10:
          nomFichierCalibFSR = "/ctp5_10.txt";
          break;
        case 11:
          nomFichierCalibFSR = "/ctp5_11.txt";
          break;
        case 12:
          nomFichierCalibFSR = "/ctp5_12.txt";
          break;
        case 13:
          nomFichierCalibFSR = "/ctp5_13.txt";
          break;
        case 14:
          nomFichierCalibFSR = "/ctp5_14.txt";
          break;
        case 15:
          nomFichierCalibFSR = "/ctp5_15.txt";
          break;
        case 16:
          nomFichierCalibFSR = "/ctp5_16.txt";
          break;
        case 17:
          nomFichierCalibFSR = "/ctp5_17.txt";
          break;
        case 18:
          nomFichierCalibFSR = "/ctp5_18.txt";
          break;
        case 19:
          nomFichierCalibFSR = "/ctp5_19.txt";
          break;
        case 20:
          nomFichierCalibFSR = "/ctp5_20.txt";
          break;
        case 21:
          nomFichierCalibFSR = "/ctp5_21.txt";
          break;
        case 22:
          nomFichierCalibFSR = "/ctp5_22.txt";
          break;
        case 23:
          nomFichierCalibFSR = "/ctp5_23.txt";
          break;
        case 24:
          nomFichierCalibFSR = "/ctp5_24.txt";
          break;
        case 25:
          nomFichierCalibFSR = "/ctp5_25.txt";
          break;
        case 26:
          nomFichierCalibFSR = "/ctp5_26.txt";
          break;
        case 27:
          nomFichierCalibFSR = "/ctp5_27.txt";
          break;
        case 28:
          nomFichierCalibFSR = "/ctp5_28.txt";
          break;
        case 29:
          nomFichierCalibFSR = "/ctp5_29.txt";
          break;
        case 30:
          nomFichierCalibFSR = "/ctp5_30.txt";
          break;
        case 31:
          nomFichierCalibFSR = "/ctp5_31.txt";
          break;
        case 32:
          nomFichierCalibFSR = "/ctp5_32.txt";
          break;
        case 33:
          nomFichierCalibFSR = "/ctp5_33.txt";
          break;
        case 34:
          nomFichierCalibFSR = "/ctp5_34.txt";
          break;
        case 35:
          nomFichierCalibFSR = "/ctp5_35.txt";
          break;
        case 36:
          nomFichierCalibFSR = "/ctp5_36.txt";
          break;
        case 37:
          nomFichierCalibFSR = "/ctp5_37.txt";
          break;
        case 38:
          nomFichierCalibFSR = "/ctp5_38.txt";
          break;
        case 39:
          nomFichierCalibFSR = "/ctp5_39.txt";
          break;
        case 40:
          nomFichierCalibFSR = "/ctp5_40.txt";
          break;
        case 41:
          nomFichierCalibFSR = "/ctp5_41.txt";
          break;
        case 42:
          nomFichierCalibFSR = "/ctp5_42.txt";
          break;
        case 43:
          nomFichierCalibFSR = "/ctp5_43.txt";
          break;
        case 44:
          nomFichierCalibFSR = "/ctp5_44.txt";
          break;
        case 45:
          nomFichierCalibFSR = "/ctp5_45.txt";
          break;
        case 46:
          nomFichierCalibFSR = "/ctp5_46.txt";
          break;
        case 47:
          nomFichierCalibFSR = "/ctp5_47.txt";
          break;
         case 48:
          nomFichierCalibFSR = "/ctp5_48.txt";
          break;         
        default:
          break;
      }

    String ParamCTP5 = ":";
    ParamCTP5 += CTP5_X5;
    ParamCTP5 += ":";
    ParamCTP5 += CTP5_X4;
    ParamCTP5 += ":";
    ParamCTP5 += CTP5_X3;
    ParamCTP5 += ":";
    ParamCTP5 += CTP5_X2;
    ParamCTP5 += ":";
    ParamCTP5 += CTP5_X;
    ParamCTP5 += ":";
    ParamCTP5 += CTP5_Y;
    ParamCTP5 += ":";
    
    writeFile(SPIFFS, nomFichierCalibFSR, ParamCTP5.c_str());
      
    server.send(200, "text/html", msg);       //Response to the HTTP request
  }


//Send ADCV value only to client ajax request
void handleADCVValue()
  {
    server.send(200, "text/plane", ADC_to_VForWebCalib(ADC()));
  }


//Send ADCN value only to client ajax request
void handleADCNValue()
  {
    server.send(200, "text/plane", ADCNumOut(1));
  }


//Send Time value only to client ajax request
void handleTIMEValue() 
  {
    server.send(200, "text/plane", TimeForWeb()); 
  }


//Send TMP value only to client ajax request 
void handleTMPValue() 
  {
    server.send(200, "text/plane", ValuesTMPForOutput());
  }


//Send HR value only to client ajax request
void handleHRValue() 
  {
    server.send(200, "text/plane", ValuesHRForOutput());
  }


//Send TMPB value only to client ajax request
void handleTMPBValue() 
  {
    server.send(200, "text/plane", ValuesTMPForWebBrut()); 
  }


//Send HRB value only to client ajax request
void handleHRBValue() 
  {
    server.send(200, "text/plane", ValuesHRForWebBrut()); 
  }

  
void identifiantsWifi()
  {
    tempsExitWithDelay = 0;
    if(debugESSENTIAL){Serial.println("Identifiants wiFi mis à jour");}
    String message = "<html>";
    message +="<head>";
    message +="<title>Redirection ...</title>";
    message +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"\">";
    message +="</head>";
    message +="<body>";

    message += "<br><br><center><h1 style=\"color:#7FBB1B;\">Les saisies du formulaire ont bien &eacute;t&eacute; prises en compte</h1></center><br>\n";
    message += "<center><h4>Redirection ...</h4></center>\n";
    for (int i = 0; i < server.args(); i++) 
      {
        if(debugALL){Serial.print("Variable : ");Serial.print(server.argName(i));Serial.print(" ---> valeur : ");Serial.println(server.arg(i));}
        if (i == 0) //Si premier tour de for c'est la data SSID
          {
            writeFile(SPIFFS, "/ssidBoxWifi.txt", server.arg(i).c_str());
          }
        else if (i == 1) //Si sgnd tours de boucle c'est le mdp :-)
          {
            writeFile(SPIFFS, "/passwordBoxWifi.txt", server.arg(i).c_str());
          }
        else
          {
            
          }
      } 
    server.send(200, "text/html", message);       //Response to the HTTP request
  }

  
void frequenceDesMesures()
  {
    tempsExitWithDelay = 0;
    if(debugESSENTIAL){Serial.println("Fréquence des mesures mise à jour");}
    String message = "<html>";
    message +="<head>";
    message +="<title>Redirection ...</title>";
    message +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"\">";
    message +="</head>";
    message +="<body>";

    message += "<br><br><center><h1 style=\"color:#7FBB1B;\">La saisie du formulaire a bien &eacute;t&eacute; prise en compte</h1></center><br>\n";
    message += "<center><h4>Redirection ...</h4></center>\n";
    for (int i = 0; i < server.args(); i++) 
      {
        if(debugALL){Serial.print("Variable : ");Serial.print(server.argName(i));Serial.print(" ---> valeur : ");Serial.println(server.arg(i));}
        writeFile(SPIFFS, "/frequenceMesure.txt", server.arg(i).c_str());
      } 
      
    message +="</body>";
    message +="</html>";
    server.send(200, "text/html", message);       //Response to the HTTP request
  }


void newDate()
  {
    tempsExitWithDelay = 0;
    if(debugESSENTIAL){Serial.println("Datetime set");}
    String message = "<html>";
    message +="<head>";
    message +="<title>Redirection ...</title>";
    message +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"\">";
    message +="</head>";
    message +="<body>";

    message += "<br><br><center><h1 style=\"color:#7FBB1B;\">Les saisies du formulaire ont bien &eacute;t&eacute; prises en compte</h1></center><br>\n";
    message += "<center><h4>Redirection ...</h4></center>\n";

    int newDay, newMouth, newYear, newHour, newMinute, newSecond;
    
    for (int i = 0; i < server.args(); i++) 
      {
        if(debugALL){Serial.print("Variable : ");Serial.print(server.argName(i));Serial.print(" ---> valeur : ");Serial.println(server.arg(i));}
        if (i == 0) //Si premier tour de for c'est le jour
          {
            newDay = server.arg(i).toInt();
          }
        else if (i == 1) //Si sgnd tours de boucle c'est le mois
          {
            newMouth = server.arg(i).toInt();
          }
        else if (i == 2) 
          {
            newYear = server.arg(i).toInt();
          }
        else if (i == 3) 
          {
            newHour = server.arg(i).toInt();
          }
        else if (i == 4)
          {
            newMinute = server.arg(i).toInt();
          }
        else if (i == 5) 
          {
            newSecond = server.arg(i).toInt();
          }
        else
          {
            
          }
      }
    timeAdjust(newDay, newMouth, newYear, newHour, newMinute, newSecond); // Set new datetime for RTC
    server.send(200, "text/html", message);       //Response to the HTTP request
  }


void nombreCapteurs()
  {
    tempsExitWithDelay = 0;
    if(debugESSENTIAL){Serial.println("Nombre de capteurs présents mis à jour");}
    String message = "<html>";
    message +="<head>";
    message +="<title>Redirection ...</title>";
    message +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"\">";
    message +="</head>";
    message +="<body>";

    message += "<br><br><center><h1 style=\"color:#7FBB1B;\">La saisie du formulaire a bien &eacute;t&eacute; prise en compte</h1></center><br>\n";
    message += "<center><h4>Redirection ...</h4></center>\n";
    for (int i = 0; i < server.args(); i++) 
      {
        if(debugALL){Serial.print("Variable : ");Serial.print(server.argName(i));Serial.print(" ---> valeur : ");Serial.println(server.arg(i));}
        writeFile(SPIFFS, "/nombreCapteurs.txt", server.arg(i).c_str());
      } 
    message +="</body>";
    message +="</html>";
    server.send(200, "text/html", message);       //Response to the HTTP request
  }


void calibDateHeure()
  {
    tempsExitWithDelay = 0;
    String calibDateHeure = "<!DOCTYPE html><html>\n";
    calibDateHeure +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"> \n";
    calibDateHeure +="<title>ESP Acquisition Unit</title>\n";
    calibDateHeure +="<style>\n";
    calibDateHeure +="html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    calibDateHeure +="body{margin-top: 50px;} \n";
    calibDateHeure +="h1{color: #444444;margin: 50px auto 30px;} \n";
    calibDateHeure +="h3{color: #444444;margin-bottom: 50px;}\n";
    calibDateHeure +=".button{display: block;width: 200px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    calibDateHeure +=".button-on{background-color: #1abc9c;}\n";
    calibDateHeure +=".button-on:active{background-color: #16a085;}\n";
    calibDateHeure +=".button-off{background-color: #34495e;}\n";
    calibDateHeure +=".button-off:active{background-color: #2c3e50;}\n";
    calibDateHeure +=".button-reset{background-color: #D3553A;}\n";
    calibDateHeure +="p{font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    calibDateHeure +="</style></head>\n";
    calibDateHeure +="<body>\n";
    
    calibDateHeure +="<h1>ESP Acquisition Unit<br> Calibration date et heure</h1> \n";
    calibDateHeure +="<p>Date : <b>\n";
    calibDateHeure +="<span id=\"TIMEValue\">\n";
    calibDateHeure +=TimeForWeb();
    calibDateHeure +="</span>\n";
    calibDateHeure +="</b></p>\n";

    calibDateHeure +="<form action=\"/newDate\">\n";
    
    calibDateHeure +="<label for=\"input10\">Jour : <br><br></label>\n";
    calibDateHeure +="<input list=\"newDay\" id=\"input10\" name=\"input10\" value=\"\n";
    calibDateHeure +=TimeDayForWeb();
    calibDateHeure +="\"/>\n";
    calibDateHeure += "<br><br>Mois :<br><br><input type=\"text\" name=\"input11\" value=\"\n";
    calibDateHeure +=TimeMonthForWeb();
    calibDateHeure +="\">\n";
    calibDateHeure += "<br><br>Ann&eacute;e :<br><br><input type=\"text\" name=\"input12\" value=\"\n";
    calibDateHeure +=TimeYearForWeb();
    calibDateHeure +="\">\n";
    calibDateHeure += "<br><br>Heure :<br><br><input type=\"text\" name=\"input13\" value=\"\n";
    calibDateHeure +=TimeHourForWeb();
    calibDateHeure +="\">\n";
    calibDateHeure += "<br><br>Minute :<br><br><input type=\"text\" name=\"input14\" value=\"\n";
    calibDateHeure +=TimeMinuteForWeb();
    calibDateHeure +="\">\n";
    calibDateHeure += "<br><br>Seconde :<br><br><input type=\"text\" name=\"input15\" value=\"\n";
    calibDateHeure +=TimeSecondForWeb();
    calibDateHeure +="\">\n";
    calibDateHeure +="<br><br><input class=\"button button-off\" type=\"submit\" value=\"Enregistrer\">\n";
    calibDateHeure +="<p></p><a class=\"button button-reset\" href=\"/\"><- BACK</a> \n";
    calibDateHeure +="</form>\n";    

    calibDateHeure +="<script>\n";
    calibDateHeure +="setInterval(function(){getData();}, 1000);\n"; //1000mSeconds update rate
    calibDateHeure +="function getData() \n";
    calibDateHeure +="  {\n";
    calibDateHeure +="    var xhttp = new XMLHttpRequest();\n";
    calibDateHeure +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"TIMEValue\").innerHTML = this.responseText;}};\n";
    calibDateHeure +="    xhttp.open(\"GET\", \"readTIME\", true);\n"; 
    calibDateHeure +="    xhttp.send();\n";
    calibDateHeure +="  }\n";
    calibDateHeure +="</script>\n";
    
    calibDateHeure +="</body></html>\n";
    server.send(200, "text/html", calibDateHeure);
  }


void calibADC()
  {
    tempsExitWithDelay = 0;
    String calibADC = "<!DOCTYPE html><html>\n";
    calibADC +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"> \n";
    calibADC +="<title>ESP Acquisition Unit</title>\n";
    calibADC +="<style>\n";
    calibADC +="html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    calibADC +="body{margin-top: 50px;} \n";
    calibADC +="h1{color: #444444;margin: 50px auto 30px;} \n";
    calibADC +="h3{color: #444444;margin-bottom: 50px;}\n";
    calibADC +=".button{display: block;width: 200px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    calibADC +=".button-on{background-color: #1abc9c;}\n";
    calibADC +=".button-on:active{background-color: #16a085;}\n";
    calibADC +=".button-off{background-color: #34495e;}\n";
    calibADC +=".button-off:active{background-color: #2c3e50;}\n";
    calibADC +=".button-reset{background-color: #D3553A;}\n";
    calibADC +="p{font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    calibADC +="</style></head>\n";
    calibADC +="<body>\n";
    
    calibADC +="<h1>ESP Acquisition Unit<br> Calibration ADC</h1> \n";

    calibADC +="<h1>Proc&eacute;dure de calibration : </h1> \n";

    calibADC +="<DIV align=\"left\">Connecteur GROVE, J1 :<br>\n";
    calibADC +="||||||<br>\n";
    calibADC +="| . |    <- 1, GND<br>\n";
    calibADC +="| . ||   <- 2, Vcc<br>\n";
    calibADC +="| . ||   <- 3, Analog<br>\n";
    calibADC +="| . |    <- 4, ND<br>\n";
    calibADC +="||||||<br>\n";
    calibADC +="<br><br>\n";
    calibADC +="1) Connecter la broche 2 (Vcc) sur la broche 3 (Analog) du connecteur J1.<br>\n";
    calibADC +="2) Recopier la valeur num&eacute;rique lue sur J1 dans le formulaire \"Valeur num&eacute;rique\".<br>\n";
    calibADC +="3) Mesurer la tension entre la broche 2 (Vcc) et 1 (GND) du connecteur J1.<br>\n";
    calibADC +="4) Recopier la tension lu dans le formulaire \"Tension mesur&eacute;e\".<br>\n";
    calibADC +="5) D&eacute;connecter la broche 2 de la broche 3 du connecteur J1.<br>\n";
    calibADC +="6) Enregistrer.<br>\n";
    calibADC +="7) L'ADC est calibr&eacute; !<br>\n";
    calibADC +="<br><br></DIV>\n";

    calibADC +="<p>Valeur num&eacute;rique lue sur J1 : <b>\n";
    calibADC +="<span id=\"ADCNValue\">\n";
    calibADC +=ADCNumOut(1);
    calibADC +="</span>\n";
    calibADC +="</b></p>\n";

    calibADC +="<form action=\"/newCalibADC\">\n";
    
    calibADC +="<label for=\"input10\">Valeur num&eacute;rique : <br><br></label>\n";
    calibADC +="<input list=\"newDay\" id=\"input10\" name=\"input20\" value=\"\n";
    calibADC +=readFile(SPIFFS, "/offsetADCNum.txt");
    calibADC +="\"/>\n";
    calibADC += "<br><br>Tension mesur&eacute;e : <br><br><input type=\"text\" name=\"input21\" value=\"\n";
    calibADC +=readFile(SPIFFS, "/offsetADCVolt.txt");
    calibADC +="\">\n";
    calibADC +="<br><br><input class=\"button button-off\" type=\"submit\" value=\"Enregistrer\">\n";
    calibADC +="</b><br><p>Tension (apr&egrave;s calibration) lue sur J1 : <b>\n";
    calibADC +="<span id=\"ADCVValue\">\n";
    calibADC +=ADC_to_VForWebCalib(ADC());
    calibADC +="</span>V</b></p>\n";
    calibADC +="<p></p><a class=\"button button-reset\" href=\"/\"><- BACK</a> \n";
    calibADC +="</form>\n";    

    calibADC +="<script>\n";
    calibADC +="setInterval(function(){getData6();}, 500);\n"; //100mSeconds update rate
    calibADC +="function getData6() \n";
    calibADC +="  {\n";
    calibADC +="    var xhttp = new XMLHttpRequest();\n";
    calibADC +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"ADCNValue\").innerHTML = this.responseText;}};\n";
    calibADC +="    xhttp.open(\"GET\", \"readADCN\", true);\n"; 
    calibADC +="    xhttp.send();\n";
    calibADC +="  }\n";
    calibADC +="setInterval(function(){getData7();}, 500);\n"; //100mSeconds update rate
    calibADC +="function getData7() \n";
    calibADC +="  {\n";
    calibADC +="    var xhttp = new XMLHttpRequest();\n";
    calibADC +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"ADCVValue\").innerHTML = this.responseText;}};\n";
    calibADC +="    xhttp.open(\"GET\", \"readADCV\", true);\n"; 
    calibADC +="    xhttp.send();\n";
    calibADC +="  }\n";
    calibADC +="</script>\n";
    
    calibADC +="</body></html>\n";
    server.send(200, "text/html", calibADC);
  }

  
void calibTempHmdR()
  {
    tempsExitWithDelay = 0;
    String calibTempHmdR = "<!DOCTYPE html><html>\n";
    calibTempHmdR +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"> \n";
    calibTempHmdR +="<title>ESP Acquisition Unit</title>\n";
    calibTempHmdR +="<style>\n";
    calibTempHmdR +="html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    calibTempHmdR +="body{margin-top: 50px;} \n";
    calibTempHmdR +="h1{color: #444444;margin: 50px auto 30px;} \n";
    calibTempHmdR +="h3{color: #444444;margin-bottom: 50px;}\n";
    calibTempHmdR +=".button{display: block;width: 200px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    calibTempHmdR +=".button-on{background-color: #1abc9c;}\n";
    calibTempHmdR +=".button-on:active{background-color: #16a085;}\n";
    calibTempHmdR +=".button-off{background-color: #34495e;}\n";
    calibTempHmdR +=".button-off:active{background-color: #2c3e50;}\n";
    calibTempHmdR +=".button-reset{background-color: #D3553A;}\n";
    calibTempHmdR +="p{font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    calibTempHmdR +="</style></head>\n";
    calibTempHmdR +="<body>\n";
    
    calibTempHmdR +="<h1>ESP Acquisition Unit<br> Calibration date et heure</h1> \n";
    calibTempHmdR +="<p>Temp&eacute;rature : <b>\n";
    calibTempHmdR +="<span id=\"TMPBValue\">\n";
    calibTempHmdR +=ValuesTMPForWebBrut();
    calibTempHmdR +="</span>\n";
    calibTempHmdR +="&deg;C + \n";
    calibTempHmdR +=readFile(SPIFFS, "/offsetTmp.txt");
    calibTempHmdR +="&deg;C => \n";
    calibTempHmdR +="<span id=\"TMPValue\">\n";
    calibTempHmdR +=ValuesTMPForOutput();
    calibTempHmdR +="</span>\n";
    calibTempHmdR +="&deg;C\n";
    calibTempHmdR +="</b><br>Humidit&eacute; relative : <b>\n";
    calibTempHmdR +="<span id=\"HRBValue\">\n";
    calibTempHmdR +=ValuesHRForWebBrut();
    calibTempHmdR +="</span>\n";
    calibTempHmdR +="&#37; + \n";
    calibTempHmdR +=readFile(SPIFFS, "/offsetHumR.txt");
    calibTempHmdR +="&#37; => \n";
    calibTempHmdR +="<span id=\"HRValue\">\n";
    calibTempHmdR +=ValuesHRForOutput();
    calibTempHmdR +="</span>\n";
    calibTempHmdR +="&#37;\n";
    calibTempHmdR +="</b></p>\n";

    calibTempHmdR +="<form action=\"/newCalibTempHmdR\">\n";
    
    calibTempHmdR +="<label for=\"input10\">Offset temp&eacute;rature : <br><br></label>\n";
    calibTempHmdR +="<input list=\"newDay\" id=\"input10\" name=\"input20\" value=\"\n";
    calibTempHmdR +=readFile(SPIFFS, "/offsetTmp.txt");
    calibTempHmdR +="\"/>\n";
    calibTempHmdR += "<br><br>Offset humidit&eacute; relative : <br><br><input type=\"text\" name=\"input21\" value=\"\n";
    calibTempHmdR +=readFile(SPIFFS, "/offsetHumR.txt");
    calibTempHmdR +="\">\n";
    calibTempHmdR +="<br><br><input class=\"button button-off\" type=\"submit\" value=\"Enregistrer\">\n";
    calibTempHmdR +="<p></p><a class=\"button button-reset\" href=\"/\"><- BACK</a> \n";
    calibTempHmdR +="</form>\n";    

    calibTempHmdR +="<script>\n";
    calibTempHmdR +="setInterval(function(){getData2();}, 100);\n"; //100mSeconds update rate
    calibTempHmdR +="function getData2() \n";
    calibTempHmdR +="  {\n";
    calibTempHmdR +="    var xhttp = new XMLHttpRequest();\n";
    calibTempHmdR +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"TMPValue\").innerHTML = this.responseText;}};\n";
    calibTempHmdR +="    xhttp.open(\"GET\", \"readTMP\", true);\n"; 
    calibTempHmdR +="    xhttp.send();\n";
    calibTempHmdR +="  }\n";
    calibTempHmdR +="setInterval(function(){getData3();}, 100);\n"; //100mSeconds update rate
    calibTempHmdR +="function getData3() \n";
    calibTempHmdR +="  {\n";
    calibTempHmdR +="    var xhttp = new XMLHttpRequest();\n";
    calibTempHmdR +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"HRValue\").innerHTML = this.responseText;}};\n";
    calibTempHmdR +="    xhttp.open(\"GET\", \"readHR\", true);\n"; 
    calibTempHmdR +="    xhttp.send();\n";
    calibTempHmdR +="  }\n";

    calibTempHmdR +="setInterval(function(){getData4();}, 100);\n"; //100mSeconds update rate
    calibTempHmdR +="function getData4() \n";
    calibTempHmdR +="  {\n";
    calibTempHmdR +="    var xhttp = new XMLHttpRequest();\n";
    calibTempHmdR +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"TMPBValue\").innerHTML = this.responseText;}};\n";
    calibTempHmdR +="    xhttp.open(\"GET\", \"readTMPB\", true);\n"; 
    calibTempHmdR +="    xhttp.send();\n";
    calibTempHmdR +="  }\n";
    calibTempHmdR +="setInterval(function(){getData5();}, 100);\n"; //100mSeconds update rate
    calibTempHmdR +="function getData5() \n";
    calibTempHmdR +="  {\n";
    calibTempHmdR +="    var xhttp = new XMLHttpRequest();\n";
    calibTempHmdR +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"HRBValue\").innerHTML = this.responseText;}};\n";
    calibTempHmdR +="    xhttp.open(\"GET\", \"readHRB\", true);\n"; 
    calibTempHmdR +="    xhttp.send();\n";
    calibTempHmdR +="  }\n";
    calibTempHmdR +="</script>\n";
    
    calibTempHmdR +="</body></html>\n";
    server.send(200, "text/html", calibTempHmdR);
  }


void newCalibADC()
  {
    tempsExitWithDelay = 0;
    if(debugESSENTIAL){Serial.println("Calibration ADC set");}
    String message = "<html>";
    message +="<head>";
    message +="<title>Redirection ...</title>";
    message +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"\">";
    message +="</head>";
    message +="<body>";

    message += "<br><br><center><h1 style=\"color:#7FBB1B;\">Les saisies du formulaire ont bien &eacute;t&eacute; prises en compte</h1></center><br>\n";
    message += "<center><h4>Redirection ...</h4></center>\n";
    for (int i = 0; i < server.args(); i++) 
      {
        if(debugALL){Serial.print("Variable : ");Serial.print(server.argName(i));Serial.print(" ---> valeur : ");Serial.println(server.arg(i));}
        if (i == 0) //Si premier tour de for c'est offset ADC Num
          {
            writeFile(SPIFFS, "/offsetADCNum.txt", server.arg(i).c_str());
          }
        else if (i == 1) //Si sgnd tours de boucle c'est offset ADC Volt:-)
          {
            writeFile(SPIFFS, "/offsetADCVolt.txt", server.arg(i).c_str());
          }
        else
          {
            
          }
      }
    server.send(200, "text/html", message);       //Response to the HTTP request
  }

  
void newCalibTempHmdR()
  {
    tempsExitWithDelay = 0;
    if(debugESSENTIAL){Serial.println("Calibration TMP/HMDR set");}
    String message = "<html>";
    message +="<head>";
    message +="<title>Redirection ...</title>";
    message +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"\">";
    message +="</head>";
    message +="<body>";

    message += "<br><br><center><h1 style=\"color:#7FBB1B;\">Les saisies du formulaire ont bien &eacute;t&eacute; prises en compte</h1></center><br>\n";
    message += "<center><h4>Redirection ...</h4></center>\n";
    for (int i = 0; i < server.args(); i++) 
      {
        if(debugALL){Serial.print("Variable : ");Serial.print(server.argName(i));Serial.print(" ---> valeur : ");Serial.println(server.arg(i));}
        if (i == 0) //Si premier tour de for c'est offset TMP
          {
            writeFile(SPIFFS, "/offsetTmp.txt", server.arg(i).c_str());
          }
        else if (i == 1) //Si sgnd tours de boucle c'est offset HMDT :-)
          {
            writeFile(SPIFFS, "/offsetHumR.txt", server.arg(i).c_str());
          }
        else
          {
            
          }
      }
    server.send(200, "text/html", message);       //Response to the HTTP request
  }

  
void calibFSR()
  {
    tempsExitWithDelay = 0;
    int NbCapt = readFile(SPIFFS, "/nombreCapteurs.txt").toInt();
    
    String msg = "<!DOCTYPE html><html>\n";
    msg +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"> \n";
    msg +="<title>ESP Acquisition Unit</title>\n";
    msg +="<style>\n";
    msg +="html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    msg +="body{margin-top: 50px;} \n";
    msg +="h1{color: #444444;margin: 50px auto 30px;} \n";
    msg +="h3{color: #444444;margin-bottom: 50px;}\n";
    msg +=".button{display: block;width: 200px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    msg +=".button-on{background-color: #1abc9c;}\n";
    msg +=".button-on:active{background-color: #16a085;}\n";
    msg +=".button-off{background-color: #34495e;}\n";
    msg +=".button-off:active{background-color: #2c3e50;}\n";
    msg +=".button-reset{background-color: #D3553A;}\n";
    msg +="p{font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    msg +="</style></head>\n";
    msg +="<body>\n";
    
    msg +="<h1>ESP Acquisition Unit<br> Calibration FSR</h1> \n";

    msg +="<p></p><a class=\"button button-reset\" href=\"/\"><- BACK</a> \n";

    for (int i = 1; i < NbCapt+1; i++) 
      {
        msg +="<p>Force (N) lue sur J";msg += String(i);msg +=": <b>\n";
        msg +="<span id=\"ForceNValue";msg += String(i);msg +="\">\n";
        msg +=ForceNForWeb(i);
        msg +="</span> N\n";
        msg +="</b></p>\n";
        msg +="<p></p><a class=\"button button-off\" href=\"/calibFSRJX?J=";msg += String(i);msg +="\">Calibration J";msg += String(i);msg +="</a> \n";
      }

    msg +="<p></p><a class=\"button button-reset\" href=\"/\"><- BACK</a> \n";

    msg +="<script>\n";
    
    for (int i = 1; i < NbCapt+1; i++) 
      {
        msg +="setInterval(function(){getData";msg += String(50+i);msg +="();}, 2000);\n";
        msg +="function getData";msg += String(50+i);msg +="() \n";
        msg +="  {\n";
        msg +="    var xhttp = new XMLHttpRequest();\n";
        msg +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"ForceNValue";msg += String(i);msg +="\").innerHTML = this.responseText;}};\n";
        msg +="    xhttp.open(\"GET\", \"readForceNValue";msg += String(i);msg +="\", true);\n"; 
        msg +="    xhttp.send();\n";
        msg +="  }\n";  
      }

    msg +="</script>\n";
 
    msg +="</body></html>\n";
    
    server.send(200, "text/html", msg);
  }

  
void handle_NotFound() //SI commande URL no reconu 
  {
    tempsExitWithDelay = 0;
    server.send(404, "text/plain", "Not found");
  }


String SendHTML()
  {
    tempsExitWithDelay = 0;
    String ptr = "<!DOCTYPE html><html>\n";
    ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"> \n";
    ptr +="<title>ESP Acquisition Unit</title>\n";
    ptr +="<style>\n";
    ptr +="html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    ptr +="body{margin-top: 50px;} \n";
    ptr +="h1{color: #444444;margin: 50px auto 30px;} \n";
    ptr +="h3{color: #444444;margin-bottom: 50px;}\n";
    ptr +=".button{display: block;width: 200px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    ptr +=".button-on{background-color: #1abc9c;}\n";
    ptr +=".button-on:active{background-color: #16a085;}\n";
    ptr +=".button-off{background-color: #34495e;}\n";
    ptr +=".button-off:active{background-color: #2c3e50;}\n";
    ptr +=".button-reset{background-color: #D3553A;}\n";
    ptr +="p{font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    ptr +="</style></head>\n";
    
    ptr +="<body>\n";
    ptr +="<h1>M&eacute;cano-biologie du cambium <br> ESP Acquisition Unit</h1> \n";
    ptr +="<p>Mat&eacute;riel N&deg; <b>\n";
    ptr +=Numero_systeme;
    ptr +="</b> -- Version carte : <b>\n";
    ptr +=Version_carte;
    ptr +="</b> -- Version logiciel : <b>\n";
    ptr +=Version_logiciel;
    ptr +="</b><br>Nom pour le r&eacute;seau : <b>\n";
    ptr +=Nom_reseau;
    ptr +="</b><br>Cl&eacute;f mat&eacute;riel : <b>\n";
    ptr += device_key;
    ptr +="</b></p> \n";
    
    ptr +="<h3>-- -- -- -- --</h3>\n";
    ptr +="<p>Date : <b>\n";
    ptr +="<span id=\"TIMEValue\">\n";
    ptr +=TimeForWeb();
    ptr +="</span>\n";
    ptr +="<br></b>\n";
    ptr +="<br>Temp&eacute;rature : <b>\n";
    ptr +="<span id=\"TMPValue\">\n";
    ptr +=ValuesTMPForOutput();
    ptr +="</span>\n";
    ptr +="&deg;C</b>\n";
    ptr +="<br>Humidit&eacute; relative : <b>\n";
    ptr +="<span id=\"HRValue\">\n";
    ptr +=ValuesHRForOutput();
    ptr +="</span>\n";
    ptr +="&#37;</b></p><br>\n";
    ptr +="<h3>-- -- -- -- --</h3>\n";
    
    ptr +="Configuration :<br><br>\n";
    ptr +="<a class=\"button button-off\" href=\"/configWIFI\">Wifi</a>\n";
    ptr +="<a class=\"button button-off\" href=\"/configMESURES\">Mesures</a>\n";
    ptr +="<a class=\"button button-off\" href=\"/configCAPTEURS\">Capteurs</a>\n";
    ptr +="<a class=\"button button-off\" href=\"/configAUTRE\">Autre</a>\n";

    ptr +="<h3>-- -- -- -- --</h3> \n";
    
    ptr +="Calibrations :<br><br>\n";
    ptr +="<a class=\"button button-off\" href=\"/calibDateHeure\">Date / Heure</a>\n";
    ptr +="<a class=\"button button-off\" href=\"/calibADC\">ADC</a>\n";
    ptr +="<a class=\"button button-off\" href=\"/calibTempHmdR\">Temp. / Hmd.R.</a>\n";
    ptr +="<a class=\"button button-off\" href=\"/calibFSR\">FSR-X-XXX</a>\n";
    ptr +="<h3>-- -- -- -- --</h3> \n";
    ptr +="<p></p><a class=\"button button-reset\" href=\"/reset\">DECONNEXION</a> \n";
    ptr +="<p>LMGC - Laboratoire de M&eacute;canique et G&eacute;nie Civil (Service COMPEX) | CNRS - Centre National de la Recherche Scientifique | UM - Universit&eacute de Montpellier<br>By S. DYCKE<br>&copy;Copyright 2022 </p>\n";

    ptr +="<script>\n";
    // Call a function repetatively with 1 Second interval
    ptr +="setInterval(function(){getData();}, 1000);\n"; //1000mSeconds update rate
    ptr +="function getData() \n";
    ptr +="  {\n";
    ptr +="    var xhttp = new XMLHttpRequest();\n";
    ptr +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"TIMEValue\").innerHTML = this.responseText;}};\n";
    ptr +="    xhttp.open(\"GET\", \"readTIME\", true);\n"; 
    ptr +="    xhttp.send();\n";
    ptr +="  }\n";

    ptr +="setInterval(function(){getData2();}, 100);\n"; //100mSeconds update rate
    ptr +="function getData2() \n";
    ptr +="  {\n";
    ptr +="    var xhttp = new XMLHttpRequest();\n";
    ptr +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"TMPValue\").innerHTML = this.responseText;}};\n";
    ptr +="    xhttp.open(\"GET\", \"readTMP\", true);\n"; 
    ptr +="    xhttp.send();\n";
    ptr +="  }\n";

    ptr +="setInterval(function(){getData3();}, 100);\n"; //100mSeconds update rate
    ptr +="function getData3() \n";
    ptr +="  {\n";
    ptr +="    var xhttp = new XMLHttpRequest();\n";
    ptr +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"HRValue\").innerHTML = this.responseText;}};\n";
    ptr +="    xhttp.open(\"GET\", \"readHR\", true);\n"; 
    ptr +="    xhttp.send();\n";
    ptr +="  }\n";
    
    ptr +="</script>\n";
   
    ptr +="</body></html>\n";
    return ptr;
  }


void handle_reset() // Si commande reset
  {
    String message = "<html>";
    message +="<head>";
    message +="<title>Redirection ...</title>";
    message +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"\">";
    message +="</head>";
    message +="<body>";
    message +="</body></html>";
    server.send(200, "text/html", message);
    delay(1000);
    if(debugESSENTIAL){Serial.println("[RESET]");}
    ESP.restart();
  }
  

void exitWithDelay()
  {
    delay(1);
    tempsExitWithDelay++;
    //Serial.println(tempsExitWithDelay);
    LEDTIMING(dureeExitWithDelay,tempsExitWithDelay);
    if (tempsExitWithDelay > dureeExitWithDelay)
      {
        if(debugESSENTIAL){Serial.println("[RESET]");}
        ESP.restart();
      }
  }
