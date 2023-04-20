
String host = "sd-radio.fr";
String webPage = "bdd_dbs5464607_MBC.php";
int WiFiConnectAttempt = 0;

//Nb de tentatives si echec de l'envoie données réseau
int nombreDeTentativeApresEchec = 5;
int nombreDeTentative = 0;

WiFiMulti WiFiMulti;


//Test à l'init si l'esp arrive à se connecter sur un réseau wifi. 
void init_WIFI_CL() 
  {
    int i =0;
    WiFi.mode(WIFI_STA);
    
    if(debugESSENTIAL){Serial.print("Identifiants d'acces : ");Serial.print(readFile(SPIFFS, "/ssidBoxWifi.txt"));Serial.print(":");Serial.println(readFile(SPIFFS, "/passwordBoxWifi.txt"));}
    WiFiMulti.addAP(readFile(SPIFFS, "/ssidBoxWifi.txt").c_str(), readFile(SPIFFS, "/passwordBoxWifi.txt").c_str());
   
    //Wait for WiFi connection
    if(debugESSENTIAL){Serial.print("Waiting for WiFi to connect...");}
    while ((WiFiMulti.run() != WL_CONNECTED)) 
      {
        if(debugESSENTIAL){Serial.print(".");}
        delay(500);
        i++;
        if (i>30)
          {
            //LED_BiColor_R_ON(); //Fonction pour voyant led
            break;
          }
      }
    if(debugESSENTIAL){Serial.println(".");}
    if (i<=30)
      {
        if(debugESSENTIAL){Serial.print("Connected, IP address: ");Serial.println(WiFi.localIP());}
        //LED_BiColor_V_ConnectOK(); // Indique par voyant (deux clignotements, 1s) que la connexion WIFI a bien été établie
        if(debugESSENTIAL){Serial.println("Wifi : connected");}
        //LED_BiColor_V_OFF();  //Fonction pour voyant led
      }
    else
      {
        CodeERREUR += "301:";
        if(debugESSENTIAL){Serial.println("[ERROR 301][WIFI] -> L'esp n'a pas réussi à se connecter en wifi (timeout)");}
        //LED_BiColor_R_ON();  //Fonction pour voyant led
      }
      
    if(debugESSENTIAL){Serial.print("ESP Board IP:  ");Serial.println(WiFi.localIP());Serial.print("ESP Board MAC Address:  ");Serial.println(WiFi.macAddress());}

    WiFi.mode(WIFI_OFF);
    if(debugESSENTIAL){Serial.print("Wifi : disconnected");}
  }


//Démarre la connexion au wifi en mode client
void WIFI_start() 
  {

    int i =0;
    
    WiFi.mode(WIFI_STA);
    
    if(debugESSENTIAL){Serial.print("Identifiants d'acces : ");Serial.print(readFile(SPIFFS, "/ssidBoxWifi.txt"));Serial.print(":");Serial.println(readFile(SPIFFS, "/passwordBoxWifi.txt"));}
    WiFiMulti.addAP(readFile(SPIFFS, "/ssidBoxWifi.txt").c_str(), readFile(SPIFFS, "/passwordBoxWifi.txt").c_str());
   
    // wait for WiFi connection
    if(debugESSENTIAL){Serial.print("Waiting for WiFi to connect...");}
    while ((WiFiMulti.run() != WL_CONNECTED)) 
      {
        if(debugESSENTIAL){Serial.print(".");}
        delay(500);
        i++;
        if (i>30)
          {
            LED_BiColor_R_ON(); //Fonction pour voyant led
            break;
          }
      }
    if(debugESSENTIAL){Serial.println(".");}
    if (i<=30)
      {
        if(debugESSENTIAL){Serial.print("Connected, IP address: ");Serial.println(WiFi.localIP());}
        LED_BiColor_V_ConnectOK(); // Indique par voyant (deux clignotements, 1s) que la connexion WIFI a bien été établie
        if(debugESSENTIAL){Serial.println("Wifi : connected");}
        LED_BiColor_V_OFF();  //Fonction pour voyant led
      }
    else
      {
        CodeERREUR += "302:";
        if(debugESSENTIAL){Serial.println("[ERROR 302][WIFI] -> L'esp n'a pas réussi à se connecter en wifi (timeout)");}
        LED_BiColor_R_ON();  //Fonction pour voyant led
      }
  }


//Scan les réseau wifi disponibles
void WIFI_ScanNetworks()
  {   
    int numberOfNetworks = WiFi.scanNetworks();
    if(debugESSENTIAL){Serial.print("Scan des reseau sans fil disponibles (");Serial.print(numberOfNetworks);Serial.println(") :");}
    if (numberOfNetworks == 0)
      {
        if(debugESSENTIAL){Serial.println("Aucun reseau sans fil détecté !");}
      }
    else if (numberOfNetworks == -1)
      {
        CodeERREUR += "303:";
        if(debugESSENTIAL){Serial.print("[ERROR 303][WIFI] -> Erreur dans le scan des réseaux wifi");}
      }
    else
      {
        for(int i =0; i<numberOfNetworks; i++)
          {
            if(debugESSENTIAL){Serial.print("> ");Serial.print(WiFi.SSID(i));Serial.print(" : ");Serial.println(WiFi.RSSI(i));}
          }
      }
  }


//Fonction qui liste les reseaux wifi dispo dans la zone de texte pour indiquer le ssid en mode AP.
String WIFI_Scan_and_build_networks_selection() 
  {   
    String CodeHTMLScanNetWk = "";
    int numberOfNetworks = WiFi.scanNetworks();
    if (numberOfNetworks == 0)
      {
        if(debugESSENTIAL){Serial.println("Aucun reseau sans fil detecte !");}
      }
    else if (numberOfNetworks == -1)
      {
        CodeERREUR += "304:";
        if(debugESSENTIAL){Serial.print("[ERROR 304][WIFI] -> Erreur dans le scan des réseaux wifi");}
      }
    else
      {
        for(int i =0; i<numberOfNetworks; i++)
          {
            CodeHTMLScanNetWk = CodeHTMLScanNetWk+"<option value=\"" + WiFi.SSID(i) + "\">\n";
          }
      }
    return(CodeHTMLScanNetWk);
  }


int SendToCloud(String device_data)
  {
    WIFI_start();
    WiFiClientSecure *client = new WiFiClientSecure;
    if(client) 
      {
        //client -> setCACert(rootCACertificate); // Donner un certificat 
        client->setInsecure();                    // Se passer du certificat
          { 
            HTTPClient https; 
            if(debugESSENTIAL){Serial.print("[HTTPS] begin...\n");}

            String url = "";
            url += "/";
            url += webPage;
            url += "?device_key=";
            url += device_key;
            url += "&device_data=";
            url += device_data;
            url += "::";
            url += WiFi.RSSI();
        
            if(debugESSENTIAL){Serial.println("https://"+host+url);}
            
            if (https.begin(*client, "https://"+host+url)) 
              { 
                if(debugESSENTIAL){Serial.print("[HTTPS] GET...\n");}
                int httpCode = https.GET();
                if (httpCode > 0) 
                  {
                    if(debugESSENTIAL){Serial.printf("[HTTPS] GET... code: %d\n", httpCode);}
                    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
                      {
                        String payload = https.getString();
                        if(debugESSENTIAL){Serial.print("Http code : 200");}
                        if(debugALL){Serial.println(payload);}
                        LED_BiColor_V_ON();  //Fonction pour voyant led
                        LED_BiColor_R_OFF();
                      }
                  } 
                else 
                  {
                    CodeERREUR += "305:";
                    if(debugESSENTIAL){Serial.printf("[ERROR 305][HTTPS] -> GET... failed, error: %s\n", https.errorToString(httpCode).c_str());}
                    LED_BiColor_V_OFF();  //Fonction pour voyant led
                    LED_BiColor_R_ON();
                    
                    nombreDeTentative++;
                    if (nombreDeTentative <= nombreDeTentativeApresEchec)
                      {
                        //On retante un envoie
                        CodeERREUR += "102:";
                        if(debugESSENTIAL){Serial.print("[ERROR 102][HTTPS] -> Nouvelle tentative d'envoie de données\n");}
                        SendToCloud(device_data);
                      }
                  }
                https.end();
              } 
            else 
              {
                CodeERREUR += "306:";
                if(debugESSENTIAL){Serial.print("[ERROR 306][HTTPS] -> Unable to connect\n");}
                LED_BiColor_V_OFF();  //Fonction pour voyant led
                LED_BiColor_R_ON();
              }
          }
        delete client;
      } 
    else 
      {
        CodeERREUR += "307:";
        if(debugESSENTIAL){Serial.print("[ERROR 307][HTTPS] -> Unable to create client\n");}
        LED_BiColor_V_OFF();  //Fonction pour voyant led
        LED_BiColor_R_ON();
      }
    WiFi.mode(WIFI_OFF);
  }
