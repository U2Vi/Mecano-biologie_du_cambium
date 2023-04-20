/* [~~~] */


String host = "";
String webPage = "";
int WiFiConnectAttempt = 0;

//Nb de tentatives si echec de l'envoie données réseau
int nombreDeTentativeApresEchec = 5;
int nombreDeTentative = 0;

WiFiMulti WiFiMulti;


//Test à l'init si l'esp arrive à se connecter sur un réseau wifi. 
void init_WIFI_CL() {
  int i =0;
  WiFi.mode(WIFI_STA);
    
  Serial.print("[WIFI-CLIENT] -> Identification : ");Serial.print(readFile(SPIFFS, "/ssidBoxWifi.txt"));Serial.print(":");Serial.println(readFile(SPIFFS, "/passwordBoxWifi.txt"));
  WiFiMulti.addAP(readFile(SPIFFS, "/ssidBoxWifi.txt").c_str(), readFile(SPIFFS, "/passwordBoxWifi.txt").c_str());
   
  //Wait for WiFi connection
  Serial.print("[WIFI-CLIENT] -> Waiting for WiFi to connect...");
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
    delay(500);
    i++;
    if (i>30){
      break;
    }
  }
  Serial.println(".");
  if (i<=30){
    Serial.print("Connected, IP address: ");Serial.println(WiFi.localIP());
    Serial.println("Wifi : connected");
  }else{
    CodeERREUR += "301:";
    Serial.println("[ERROR 301][WIFI-CLIENT] -> Wifi timeout ...");
  }
  Serial.print("ESP Board IP:  ");Serial.println(WiFi.localIP());Serial.print("ESP Board MAC Address:  ");Serial.println(WiFi.macAddress());

  WiFi.mode(WIFI_OFF);
  Serial.print("[WIFI-CLIENT] -> Wifi : disconnected");
}


//Démarre la connexion au wifi en mode client
void WIFI_start() {
  int i =0;
  WiFi.mode(WIFI_STA);
    
  Serial.print("[WIFI-CLIENT] -> Identifiants d'acces : ");Serial.print(readFile(SPIFFS, "/ssidBoxWifi.txt"));Serial.print(":");Serial.println(readFile(SPIFFS, "/passwordBoxWifi.txt"));
  WiFiMulti.addAP(readFile(SPIFFS, "/ssidBoxWifi.txt").c_str(), readFile(SPIFFS, "/passwordBoxWifi.txt").c_str());
   
  // wait for WiFi connection
  Serial.print("[WIFI-CLIENT] -> Waiting for WiFi to connect...");
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
    delay(500);
    i++;
    if (i>30){
      //LED_BiColor_R_ON(); //Fonction pour voyant led
      break;
    }
  }
  Serial.println(".");
  if (i<=30){
    Serial.print("[WIFI-CLIENT] -> Connected, IP address: ");Serial.println(WiFi.localIP());
    //LED_BiColor_V_ConnectOK(); // Indique par voyant (deux clignotements, 1s) que la connexion WIFI a bien été établie
    Serial.println("[WIFI-CLIENT] -> Wifi : connected");
    //LED_BiColor_V_OFF();  //Fonction pour voyant led
  }else{
    CodeERREUR += "302:";
    Serial.println("[ERROR 302][WIFI] -> L'esp n'a pas réussi à se connecter en wifi (timeout)");
    //LED_BiColor_R_ON();  //Fonction pour voyant led
  }
}


//Scan les réseau wifi disponibles
void WIFI_ScanNetworks(){   
  int numberOfNetworks = WiFi.scanNetworks();
  Serial.print("[WIFI-CLIENT] -> Scan des reseau sans fil disponibles (");Serial.print(numberOfNetworks);Serial.println(") :");
  if (numberOfNetworks == 0){
    Serial.println("[WIFI-CLIENT] -> Aucun reseau sans fil détecté !");
  }else if (numberOfNetworks == -1){
        CodeERREUR += "303:";
        Serial.print("[ERROR 303][WIFI-CLIENT] -> Erreur dans le scan des réseaux wifi");
  }else{
    for(int i =0; i<numberOfNetworks; i++){
      Serial.print("> ");Serial.print(WiFi.SSID(i));Serial.print(" : ");Serial.println(WiFi.RSSI(i));
    }
  }
}


//Fonction qui liste les reseaux wifi dispo dans la zone de texte pour indiquer le ssid en mode AP.
String WIFI_Scan_and_build_networks_selection() {   
  String CodeHTMLScanNetWk = "";
  int numberOfNetworks = WiFi.scanNetworks();
  if (numberOfNetworks == 0){
    Serial.println("[WIFI-CLIENT] -> Aucun reseau sans fil detecte !");
  }else if (numberOfNetworks == -1){
    CodeERREUR += "304:";
    Serial.print("[ERROR 304][WIFI-CLIENT] -> Erreur dans le scan des réseaux wifi");
  }else{
    for(int i =0; i<numberOfNetworks; i++){
      CodeHTMLScanNetWk = CodeHTMLScanNetWk+"<option value=\"" + WiFi.SSID(i) + "\">\n";
    }
  }
  return(CodeHTMLScanNetWk);
}


int SendToCloud(String device_data){

  host = readFile(SPIFFS, "/https_url.txt");
  webPage = readFile(SPIFFS, "/https_path.txt");
  
  WIFI_start();
  WiFiClientSecure *client = new WiFiClientSecure;
  if(client) {
    //client -> setCACert(rootCACertificate); // Donner un certificat 
    client->setInsecure();{                    // Se passer du certificat
      HTTPClient https; 
      Serial.print("[WIFI-CLIENT] -> (Construct HTTPS) begin...\n");

      String url = "";
      url += "/";
      url += webPage;
      url += "?device_key=";
      url += device_key;
      url += "&device_data=";
      url += WiFi.RSSI();
      url += "::";
      url += device_data;
        
      Serial.println("[WIFI-CLIENT] -> https://"+host+url);
            
      if (https.begin(*client, "https://"+host+url)){ 
        Serial.print("[WIFI-CLIENT] -> HTTPS GET...\n");
        int httpCode = https.GET();
        if (httpCode > 0) {
          Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY){
            String payload = https.getString();
            Serial.println("[WIFI-CLIENT] -> Http code : 200");
            Serial.println("[WIFI-CLIENT] -------------------------------------------------------------------------------------------------------------------------------------------");
            Serial.println(payload);
            Serial.println("[WIFI-CLIENT] -------------------------------------------------------------------------------------------------------------------------------------------");
            //LED_BiColor_V_ON();  //Fonction pour voyant led
            //LED_BiColor_R_OFF();
          }
        }else{
          CodeERREUR += "305:";
          Serial.printf("[ERROR 305][WIFI-CLIENT] -> GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
          //LED_BiColor_V_OFF();  //Fonction pour voyant led
          //LED_BiColor_R_ON();            
          nombreDeTentative++;
          if (nombreDeTentative <= nombreDeTentativeApresEchec){
            //On retante un envoie
            CodeERREUR += "102:";
            Serial.print("[ERROR 102][WIFI-CLIENT] -> Nouvelle tentative d'envoie de données\n");
            SendToCloud(device_data);
          }
        }
        https.end();
      }else{
        CodeERREUR += "306:";
        Serial.print("[ERROR 306][WIFI-CLIENT] -> Unable to connect\n");
        //LED_BiColor_V_OFF();  //Fonction pour voyant led
        //LED_BiColor_R_ON();
      }
    }
  delete client;
  }else{
    CodeERREUR += "307:";
    Serial.print("[ERROR 307][WIFI-CLIENT] -> Unable to create client\n");
    //LED_BiColor_V_OFF();  //Fonction pour voyant led
    //LED_BiColor_R_ON();
  }
  WiFi.mode(WIFI_OFF);
  return 1;
}
