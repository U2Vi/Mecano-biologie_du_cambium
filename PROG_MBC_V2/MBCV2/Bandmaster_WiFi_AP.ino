/* [~~~] */


//FONCTION : WIFI_Mode_AP();

char buffer_[15]; //Variable pour convertion float en string avec des chiffres apres le vigule. utilisé pour mean et difference
float bar;
float voltage;

int paramPrintFloat = 5;

String valueConn0;
String valueConn1;

int valueNum = 32768;
float tensionRef = 2.048;







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

//Prépart l'ESP32 en mode AP.
void StartInit_WIFI_AP(){

  Serial.print("[WIFI-CAP ->  Display of the number of 0s after the decimal point defined on");Serial.print(readFile(SPIFFS, "/paramPrintFloat.txt"));
  paramPrintFloat = readFile(SPIFFS, "/paramPrintFloat.txt").toInt();

  /*Serial.print("[WIFI-CAP ->  Conversion factor in bar defined on");Serial.print(readFile(SPIFFS, "/calibConvBar.txt"));
  convFactBar = readFile(SPIFFS, "/calibConvBar.txt").toFloat();*/
  
  Serial.println("---------------------- Wifi AP pre-start --------------------------");
  Serial.println();
  Serial.print("[WIFI-AP] -> Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_ip, gateway, subnet) ? "Ready" : "Failed!");
  Serial.print("[WIFI-AP] -> Setting soft-AP ... ");
  Serial.println(WiFi.softAP(ssid,password) ? "Ready" : "Failed!");
  Serial.print("[WIFI-AP] -> Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
  Serial.println("-------------------------------------------------------------------");
  delay(10);
    
  //Liste des pages et des fonctions qui leurs sont associées 
  server.on("/", handle_OnConnect);
  server.on("/reset", handle_reset);
  server.on("/frequenceDesMesures", frequenceDesMesures);

  server.on("/dataSensorsHub", dataSensorsHub);

  server.on("/connector64", connector64);
  server.on("/connector63", connector63);
  server.on("/connector62", connector62);
  server.on("/connector61", connector61);
  server.on("/connector60", connector60);
  server.on("/connector59", connector59);
  server.on("/connector58", connector58);
  server.on("/connector57", connector57);
  server.on("/connector56", connector56);
  server.on("/connector55", connector55);
  server.on("/connector54", connector54);
  server.on("/connector53", connector53);
  server.on("/connector52", connector52);
  server.on("/connector51", connector51);
  server.on("/connector50", connector50);
  server.on("/connector49", connector49);
  server.on("/connector48", connector48);
  server.on("/connector47", connector47);
  server.on("/connector46", connector46);
  server.on("/connector45", connector45);
  server.on("/connector44", connector44);
  server.on("/connector43", connector43);
  server.on("/connector42", connector42);
  server.on("/connector41", connector41);
  server.on("/connector40", connector40);
  server.on("/connector39", connector39);
  server.on("/connector38", connector38);
  server.on("/connector37", connector37);
  server.on("/connector36", connector36);
  server.on("/connector35", connector35);
  server.on("/connector34", connector34);
  server.on("/connector33", connector33);
  server.on("/connector32", connector32);
  server.on("/connector31", connector31);
  server.on("/connector30", connector30);
  server.on("/connector29", connector29);
  server.on("/connector28", connector28);
  server.on("/connector27", connector27);
  server.on("/connector26", connector26);
  server.on("/connector25", connector25);
  server.on("/connector24", connector24);
  server.on("/connector23", connector23);
  server.on("/connector22", connector22);
  server.on("/connector21", connector21);
  server.on("/connector20", connector20);
  server.on("/connector19", connector19);
  server.on("/connector18", connector18);
  server.on("/connector17", connector17);
  server.on("/connector16", connector16);
  server.on("/connector15", connector15);
  server.on("/connector14", connector14);
  server.on("/connector13", connector13);
  server.on("/connector12", connector12);
  server.on("/connector11", connector11);
  server.on("/connector10", connector10);
  server.on("/connector9", connector9);
  server.on("/connector8", connector8);
  server.on("/connector7", connector7);
  server.on("/connector6", connector6);
  server.on("/connector5", connector5);
  server.on("/connector4", connector4);
  server.on("/connector3", connector3);
  server.on("/connector2", connector2);
  server.on("/connector1", connector1);

  server.on("/difference", difference);
  server.on("/mean", mean);
  
  server.on("/identifiantsWifi", identifiantsWifi);
  /*server.on("/newCalibTempHmdR", newCalibTempHmdR);*/
  server.on("/nombreCapteurs", nombreCapteurs);
  server.on("/calibDateHeure", calibDateHeure);
  /*server.on("/calibTempHmdR", calibTempHmdR);*/
  server.on("/configWIFI", configWIFI);
  server.on("/configMESURES", configMESURES);
  server.on("/configCAPTEURS", configCAPTEURS);
  /*server.on("/configAUTRE", configAUTRE);*/
  /*server.on("/readADCV", handleADCVValue);*/
  /*server.on("/readADCN", handleADCNValue);*/
  server.on("/readTIME", handleTIMEValue);
  /*server.on("/readTMPB", handleTMPBValue);*/
  /*server.on("/newCalibADC", newCalibADC);*/
  /*server.on("/readTMP", handleTMPValue);*/
  /*server.on("/readHRB", handleHRBValue);*/
  /*server.on("/readHR", handleHRValue);*/
  server.onNotFound(handle_NotFound);
  server.on("/dataSensors", dataSensors);
  server.on("/newDate", newDate);
  server.on("/configDisplay", configDisplay);
  server.on("/formConfigDisplay", formConfigDisplay);
  server.on("/getTmp", handleGetTmp);
  server.on("/getHmd", handleGetHmd);
  server.on("/paramHTTPS", paramHTTPS);
  server.on("/configHTTPS", configHTTPS);
  
  server.begin();
  Serial.println("[WIFI-AP] -> HTTP server started ...");
}


//Mise en mode AP
void WIFI_Mode_AP(){
  server.handleClient();
  exitWithDelay();
}

//Si un client est connecté
void handle_OnConnect() {
  tempsExitWithDelay = 0;
  server.send(200, "text/html", SendHTML()); 
}



//Send pressur (Bar) value only to client ajax request 
void connector1(){
  valueConn0 = connValue(1, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector2(){
  valueConn0 = connValue(2, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector3(){
  valueConn0 = connValue(3, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector4(){
  valueConn0 = connValue(4, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector5(){
  valueConn0 = connValue(5, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector6(){
  valueConn0 = connValue(6, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector7(){
  valueConn0 = connValue(7, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector8(){
  valueConn0 = connValue(8, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector9(){
  valueConn0 = connValue(9, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector10(){
  valueConn0 = connValue(10, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector11(){
  valueConn0 = connValue(11, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector12(){
  valueConn0 = connValue(12, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector13(){
  valueConn0 = connValue(13, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector14(){
  valueConn0 = connValue(14, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector15(){
  valueConn0 = connValue(15, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector16(){
  valueConn0 = connValue(16, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector17(){
  valueConn0 = connValue(17, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector18(){
  valueConn0 = connValue(18, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector19(){
  valueConn0 = connValue(19, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector20(){
  valueConn0 = connValue(20, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector21(){
  valueConn0 = connValue(21, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector22(){
  valueConn0 = connValue(22, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector23(){
  valueConn0 = connValue(23, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector24(){
  valueConn0 = connValue(24, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector25(){
  valueConn0 = connValue(25, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector26(){
  valueConn0 = connValue(26, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector27(){
  valueConn0 = connValue(27, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector28(){
  valueConn0 = connValue(28, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector29(){
  valueConn0 = connValue(29, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector30(){
  valueConn0 = connValue(30, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector31(){
  valueConn0 = connValue(31, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector32(){
  valueConn0 = connValue(32, 0);
  voltage = (float)valueConn0.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}






//Connector33 = J1.1, Connector 34 = J2.1, etc ...
void connector33(){
  valueConn1 = connValue(1, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector34(){
  valueConn1 = connValue(2, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector35(){
  valueConn1 = connValue(3, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector36(){
  valueConn1 = connValue(4, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector37(){
  valueConn1 = connValue(5, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector38(){
  valueConn1 = connValue(6, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector39(){
  valueConn1 = connValue(7, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector40(){
  valueConn1 = connValue(8, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector41(){
  valueConn1 = connValue(9, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector42(){
  valueConn1 = connValue(10, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector43(){
  valueConn1 = connValue(11, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector44(){
  valueConn1 = connValue(12, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector45(){
  valueConn1 = connValue(13, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector46(){
  valueConn1 = connValue(14, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector47(){
  valueConn1 = connValue(15, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector48(){
  valueConn1 = connValue(16, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector49(){
  valueConn1 = connValue(17, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector50(){
  valueConn1 = connValue(18, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector51(){
  valueConn1 = connValue(19, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector52(){
  valueConn1 = connValue(20, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector53(){
  valueConn1 = connValue(21, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector54(){
  valueConn1 = connValue(22, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector55(){
  valueConn1 = connValue(23, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector56(){
  valueConn1 = connValue(24, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector57(){
  valueConn1 = connValue(25, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector58(){
  valueConn1 = connValue(26, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector59(){
  valueConn1 = connValue(27, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector60(){
  valueConn1 = connValue(28, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector61(){
  valueConn1 = connValue(29, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector62(){
  valueConn1 = connValue(30, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector63(){
  valueConn1 = connValue(31, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}
void connector64(){
  valueConn1 = connValue(32, 1);
  voltage = (float)valueConn1.toInt()*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn1); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
}


void difference(){

  int valueConn = valueConn0.toInt()-valueConn1.toInt();
  voltage = (float)valueConn*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
  
  //server.send(200, "text/plane", String(dtostrf((valueConn0.toFloat()-valueConn1.toFloat()), 8, 6, buffer_)));
  
}
void mean(){

  int valueConn = ((valueConn0.toInt()+valueConn1.toInt())/2);
  voltage = (float)valueConn*tensionRef/valueNum;
  bar = convFactBar(voltage);
  String msg = "<b>"; msg += String(dtostrf(bar, 8, paramPrintFloat, buffer_)); msg += "</b>Bar  -  [ <b>"; msg += String(valueConn0); msg += "</b> (16bit) | <b>"; msg += String(dtostrf(voltage, 8, paramPrintFloat, buffer_)); msg += "</b>V ]";
  server.send(200, "text/plane", msg);
  
  //server.send(200, "text/plane", String(dtostrf((valueConn0.toFloat()+valueConn1.toFloat()/2), 8, 6, buffer_)));
}


/*//Send ADCV value only to client ajax request
void handleADCVValue(){
  server.send(200, "text/plane", "!0487!");
}
//Send ADCN value only to client ajax request
void handleADCNValue(){
  server.send(200, "text/plane", "!2594!");
}*/
//Send Time value only to client ajax request
void handleTIMEValue() {
  server.send(200, "text/plane", RTC_getDate()); 
}
//Send TMP value only to client ajax request 
void handleGetHmd() {
  server.send(200, "text/plane", getHmd());
}
//Send HR value only to client ajax request
void handleGetTmp() {
  server.send(200, "text/plane", getTmp());
}

/*//Send TMPB value only to client ajax request
void handleTMPBValue() {
  server.send(200, "text/plane", "!7850!"); 
}
//Send HRB value only to client ajax request
void handleHRBValue() {
  server.send(200, "text/plane", "!0028!"); 
}*/


void configWIFI(){
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
  msg +=readFile(SPIFFS, "/SSIDBoxWifi.txt");
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


void configDisplay(){
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
  msg +="<h1>ESP Acquisition Unit<br>Configuration Display</h1> \n";
    
  msg +="<br><br>\n";
  msg +="<form action=\"/formConfigDisplay\">\n";
  msg += "<br><br>Nombre de '0' apr&egrave;s la virgule pour l'affichage des valeurs flotantes :<br><br><input type=\"text\" name=\"input1\" value=\"\n";
  msg +=readFile(SPIFFS, "/paramPrintFloat.txt");
  msg +="\"/>\n";
  msg += "<br><br>Facteur de convertion des donn&egrave;es num&egrave;riques en bar :<br><br><input type=\"text\" name=\"input2\" value=\"\n";
  msg +=readFile(SPIFFS, "/calibConvBar.txt");
  msg +="\"><br><br><input class=\"button button-off\" type=\"submit\" value=\"Enregistrer\">\n";
  msg +="</form>\n";
  
  msg +="<p></p><a class=\"button button-reset\" href=\"/\"><- BACK</a> \n";

  msg +="</body></html>\n";
  server.send(200, "text/html", msg);
}



  
void configMESURES(){
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

  
void configCAPTEURS(){
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
  msg +="Nombre de capteurs en place (de J1 &agrave; J32) :  <br><br> <input type=\"text\" name=\"input4\" value=\"";
  msg +=readFile(SPIFFS, "/nombreCapteurs.txt");
  msg +="\">  <br><br> <input class=\"button button-off\" type=\"submit\" value=\"Enregistrer\">\n";
  msg +="</form>\n";

  msg +="<p></p><a class=\"button button-reset\" href=\"/\"><- BACK</a> \n";
  msg +="</body></html>\n";
  server.send(200, "text/html", msg);
}


/*
void configAUTRE(){
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
*/


  
void identifiantsWifi(){
  tempsExitWithDelay = 0;
  Serial.println("[HTML] -> Identifiants wiFi mis à jour");
  String message = "<html>";
  message +="<head>";
  message +="<title>Redirection ...</title>";
  message +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"\">";
  message +="</head>";
  message +="<body>";

  message += "<br><br><center><h1 style=\"color:#7FBB1B;\">Les saisies du formulaire ont bien &eacute;t&eacute; prises en compte</h1></center><br>\n";
  message += "<center><h4>Redirection ...</h4></center>\n";
  for (int i = 0; i < server.args(); i++) {
    Serial.print("[HTML] -> Variable : ");Serial.print(server.argName(i));Serial.print(" ---> value : ");Serial.println(server.arg(i));
    if (i == 0){ //Si premier tour de for c'est la data SSID
      writeFile(SPIFFS, "/ssidBoxWifi.txt", server.arg(i).c_str());
    }else if (i == 1){ //Si sgnd tours de boucle c'est le mdp :-)
      writeFile(SPIFFS, "/passwordBoxWifi.txt", server.arg(i).c_str());
    }else{
    }
  } 
  server.send(200, "text/html", message);       //Response to the HTTP request
}



void formConfigDisplay(){
  tempsExitWithDelay = 0;
  Serial.println("[HTML] -> Paramétres d'affichage mis à jours.");
  String message = "<html>";
  message +="<head>";
  message +="<title>Redirection ...</title>";
  message +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"\">";
  message +="</head>";
  message +="<body>";

  message += "<br><br><center><h1 style=\"color:#7FBB1B;\">Les saisies du formulaire ont bien &eacute;t&eacute; prises en compte</h1></center><br>\n";
  message += "<center><h4>Redirection ...</h4></center>\n";
  for (int i = 0; i < server.args(); i++) {
    Serial.print("[HTML] -> Variable : ");Serial.print(server.argName(i));Serial.print(" ---> value : ");Serial.println(server.arg(i));
    if (i == 0){
      writeFile(SPIFFS, "/paramPrintFloat.txt", server.arg(i).c_str());
    /*}else if (i == 1){ //Si sgnd tours de boucle c'est le mdp :-)
      writeFile(SPIFFS, "/calibConvBar.txt", server.arg(i).c_str());*/
    }else{
    }
  } 

  Serial.print("[WIFI-CAP ->  Display of the number of 0s after the decimal point defined on");Serial.print(readFile(SPIFFS, "/paramPrintFloat.txt"));
  paramPrintFloat = readFile(SPIFFS, "/paramPrintFloat.txt").toInt();
  /*Serial.print("[WIFI-CAP ->  Conversion factor in bar defined on");Serial.print(readFile(SPIFFS, "/calibConvBar.txt"));
  convFactBar = readFile(SPIFFS, "/calibConvBar.txt").toFloat();*/
  
  server.send(200, "text/html", message);       //Response to the HTTP request
}





  
void frequenceDesMesures(){
  tempsExitWithDelay = 0;
  Serial.println("[HTML] -> Fréquence des mesures mise à jour");
  String message = "<html>";
  message +="<head>";
  message +="<title>Redirection ...</title>";
  message +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"\">";
  message +="</head>";
  message +="<body>";

  message += "<br><br><center><h1 style=\"color:#7FBB1B;\">La saisie du formulaire a bien &eacute;t&eacute; prise en compte</h1></center><br>\n";
  message += "<center><h4>Redirection ...</h4></center>\n";
  for (int i = 0; i < server.args(); i++) {
    Serial.print("[HTML] -> Variable : ");Serial.print(server.argName(i));Serial.print(" ---> value : ");Serial.println(server.arg(i));
    writeFile(SPIFFS, "/frequenceMesure.txt", server.arg(i).c_str());
  } 
      
  message +="</body>";
  message +="</html>";
  server.send(200, "text/html", message);       //Response to the HTTP request
}


void newDate(){
  tempsExitWithDelay = 0;
  Serial.println("[HTML] -> Datetime set");
  String message = "<html>";
  message +="<head>";
  message +="<title>Redirection ...</title>";
  message +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"\">";
  message +="</head>";
  message +="<body>";

  message += "<br><br><center><h1 style=\"color:#7FBB1B;\">Les saisies du formulaire ont bien &eacute;t&eacute; prises en compte</h1></center><br>\n";
  message += "<center><h4>Redirection ...</h4></center>\n";

  int newDay, newMouth, newYear, newHour, newMinute, newSecond;
    
  for (int i = 0; i < server.args(); i++) {
    Serial.print("Variable : ");Serial.print(server.argName(i));Serial.print(" ---> value : ");Serial.println(server.arg(i));
    if (i == 0){ //Si premier tour de for c'est le jour
      newDay = server.arg(i).toInt();
    }else if (i == 1){ //Si sgnd tours de boucle c'est le mois   
      newMouth = server.arg(i).toInt();
    }else if (i == 2){
      newYear = server.arg(i).toInt();
    }else if (i == 3){
      newHour = server.arg(i).toInt();
    }else if (i == 4){
      newMinute = server.arg(i).toInt();
    }else if (i == 5){
      newSecond = server.arg(i).toInt();
    }else{     
    }
  }
  //timeAdjust(newDay, newMouth, newYear, newHour, newMinute, newSecond); // Set new datetime for RTC
  RTC_configDateTime(newYear, newMouth, newDay, newHour, newMinute, newSecond);
  server.send(200, "text/html", message);       //Response to the HTTP request
}


void nombreCapteurs(){
  tempsExitWithDelay = 0;
  Serial.println("Nombre de capteurs présents mis à jour");
  String message = "<html>";
  message +="<head>";
  message +="<title>Redirection ...</title>";
  message +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"\">";
  message +="</head>";
  message +="<body>";

  message += "<br><br><center><h1 style=\"color:#7FBB1B;\">La saisie du formulaire a bien &eacute;t&eacute; prise en compte</h1></center><br>\n";
  message += "<center><h4>Redirection ...</h4></center>\n";
  for (int i = 0; i < server.args(); i++) {
    Serial.print("Variable : ");Serial.print(server.argName(i));Serial.print(" ---> value : ");Serial.println(server.arg(i));
    writeFile(SPIFFS, "/nombreCapteurs.txt", server.arg(i).c_str());
  } 
  message +="</body>";
  message +="</html>";
  server.send(200, "text/html", message);       //Response to the HTTP request
}


void calibDateHeure(){
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
    calibDateHeure +="??3174??";
    calibDateHeure +="</span>\n";
    calibDateHeure +="</b></p>\n";

    calibDateHeure +="<form action=\"/newDate\">\n";
    
    calibDateHeure +="<label for=\"input10\">Jour : <br><br></label>\n";
    calibDateHeure +="<input list=\"newDay\" id=\"input10\" name=\"input10\" value=\"\n";
    calibDateHeure +=RTC_getDay();
    calibDateHeure +="\"/>\n";
    calibDateHeure += "<br><br>Mois :<br><br><input type=\"text\" name=\"input11\" value=\"\n";
    calibDateHeure +=RTC_getMonth();
    calibDateHeure +="\">\n";
    calibDateHeure += "<br><br>Ann&eacute;e :<br><br><input type=\"text\" name=\"input12\" value=\"\n";
    calibDateHeure +=RTC_getYear();
    calibDateHeure +="\">\n";
    calibDateHeure += "<br><br>Heure :<br><br><input type=\"text\" name=\"input13\" value=\"\n";
    calibDateHeure +=RTC_getHour();
    calibDateHeure +="\">\n";
    calibDateHeure += "<br><br>Minute :<br><br><input type=\"text\" name=\"input14\" value=\"\n";
    calibDateHeure +=RTC_getMinute();
    calibDateHeure +="\">\n";
    calibDateHeure += "<br><br>Seconde :<br><br><input type=\"text\" name=\"input15\" value=\"\n";
    calibDateHeure +=RTC_getSecond();
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


void dataSensorsHub(){
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
        msg +="<p>Pression (Bar) lue sur J";msg += String(i);msg +=": <b>\n";
        /*msg +="<span id=\"connector";msg += String(i);msg +="\">\n";
        msg +="??????????";   //msg +=ForceNForWeb(i);
        msg +="</span> N\n";*/
        msg +="</b></p>\n";
        msg +="<p></p><a class=\"button button-off\" href=\"/dataSensors?J=";msg += String(i);msg +="\">Donn&eacute;es J";msg += String(i);msg +=".0 et J";msg += String(i);msg +=".1</a> \n";
      }

    msg +="<p></p><a class=\"button button-reset\" href=\"/\"><- BACK</a> \n";
    

   /* msg +="<script>\n";
    
    for (int i = 1; i < NbCapt+1; i++) 
      {
        msg +="setInterval(function(){getData";msg += String(50+i);msg +="();}, 2000);\n";
        msg +="function getData";msg += String(50+i);msg +="() \n";
        msg +="  {\n";
        msg +="    var xhttp = new XMLHttpRequest();\n";
        msg +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"connector";msg += String(i);msg +="\").innerHTML = this.responseText;}};\n";
        msg +="    xhttp.open(\"GET\", \"connValue";msg += String(i);msg +="\", true);\n"; 
        msg +="    xhttp.send();\n";
        msg +="  }\n";  
      }

    msg +="</script>\n";*/
 
    msg +="</body></html>\n";
    
    server.send(200, "text/html", msg);
}


void dataSensors(){
  
  tempsExitWithDelay = 0;
  int numCapt = 0;
    
  for (int i = 0; i < server.args(); i++) {
      Serial.print("Variable : ");Serial.print(server.argName(i));Serial.print(" ---> valeur : ");Serial.println(server.arg(i));
      if (i == 0){ //Si premier tour de for c'est num capteur a calib.
          numCapt = server.arg(i).toInt();
      }else{
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
    
  msg +="<h1>ESP Acquisition Unit</h1> \n";

  msg +="<h1>Pressure sensor data : </h1> \n";
    
  msg +="<p>Value read on J";msg += numCapt;msg +=".0 : \n";
  msg +="<span id=\"connectorX-0\">\n";
  
  /*valueConn0 = connValue(numCapt, 0);
  voltage = (float)valueConn0.toInt() * 2.048 / 32768.0;
  bar = (voltage*1000)*0.0167;
  msg += String(dtostrf(bar, 8, 6, buffer_));
  msg += "</b>Bar  -  [<b>";
  msg += valueConn0; 
  msg += "</b> (16bit) | <b>";
  msg += String(dtostrf(voltage, 8, 6, buffer_)); 
  msg += "</b>V ]";*/

  msg +="</p><p>Value read on J";msg += numCapt;msg +=".1 : \n";
  msg +="<span id=\"connectorX-1\">\n";
  //valueConn1 = connValue(numCapt, 1);
  //msg +=valueConn1; 
  
  /*valueConn1 = connValue(numCapt, 1);
  voltage = (float)valueConn1.toInt() * 2.048 / 32768.0;
  bar = (voltage*1000)*0.0167;
  msg += String(dtostrf(bar, 8, 6, buffer_));
  msg += "</b>Bar  -  [ <b>";
  msg += valueConn1; 
  msg += "</b> (16bit) | <b>";
  msg += String(dtostrf(voltage, 8, 6, buffer_));
  msg += "</b>V ]";*/
  
  msg +="</span>\n";
  
  msg +="</p>\n";
  msg +="<h1> Mean : </h1>";
  msg +="<p>";
  msg +="<span id=\"mean\">\n";
  //msg +=String(dtostrf((valueConn0.toFloat()+valueConn1.toFloat()/2), 8, 6, buffer_));
  msg +="</span>\n";
  msg +="</p>\n";
  
  msg +="<h1> Difference : </h1>";
  msg +="<p>";
  msg +="<span id=\"difference\">\n";
  //msg +=String(dtostrf((valueConn0.toFloat()-valueConn1.toFloat()), 8, 6, buffer_));
  msg +="</span>\n";
  msg +="</p>\n";
  msg +="<br><br><br><a class=\"button button-reset\" href=\"dataSensorsHub\"><- BACK</a> \n";
  

  msg +="<script>\n";
  msg +="setInterval(function(){getData0();}, 200);\n";
  msg +="function getData0() \n";
  msg +="  {\n";
  msg +="    var xhttp = new XMLHttpRequest();\n";
  msg +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"connectorX-0\").innerHTML = this.responseText;}};\n";
  msg +="    xhttp.open(\"GET\", \"connector";msg += numCapt;msg +="\", true);\n"; 
  msg +="    xhttp.send();\n";
  msg +="  }\n";  
  msg +="</script>\n";

  msg +="<script>\n";
  msg +="setInterval(function(){getData1();}, 200);\n";
  msg +="function getData1() \n";
  msg +="  {\n";
  msg +="    var xhttp = new XMLHttpRequest();\n";
  msg +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"connectorX-1\").innerHTML = this.responseText;}};\n";
  msg +="    xhttp.open(\"GET\", \"connector";msg += numCapt+32;msg +="\", true);\n"; 
  msg +="    xhttp.send();\n";
  msg +="  }\n";  
  msg +="</script>\n";

  msg +="<script>\n";
  msg +="setInterval(function(){getData2();}, 200);\n";
  msg +="function getData2() \n";
  msg +="  {\n";
  msg +="    var xhttp = new XMLHttpRequest();\n";
  msg +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"difference\").innerHTML = this.responseText;}};\n";
  msg +="    xhttp.open(\"GET\", \"difference\", true);\n"; 
  msg +="    xhttp.send();\n";
  msg +="  }\n";  
  msg +="</script>\n";

  msg +="<script>\n";
  msg +="setInterval(function(){getData3();}, 200);\n";
  msg +="function getData3() \n";
  msg +="  {\n";
  msg +="    var xhttp = new XMLHttpRequest();\n";
  msg +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"mean\").innerHTML = this.responseText;}};\n";
  msg +="    xhttp.open(\"GET\", \"mean\", true);\n"; 
  msg +="    xhttp.send();\n";
  msg +="  }\n";  
  msg +="</script>\n";
    
  msg +="</body></html>\n";
  server.send(200, "text/html", msg);
}


  
void handle_NotFound(){ //SI commande URL no reconu 
  tempsExitWithDelay = 0;
  server.send(404, "text/plain", "Not found");
}

String SendHTML(){
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
    ptr +=Version_carte_DYBoard_Bandmaster;
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
    ptr +=RTC_getDate();
    ptr +="</span>\n";
    ptr +="<br></b>\n";
    ptr +="<br>Temp&eacute;rature : <b>\n";
    ptr +="<span id=\"getTmp\">\n";
    ptr += getTmp();
    ptr +="</span>\n";
    ptr +="&deg;C</b>\n";
    ptr +="<br>Humidit&eacute; relative : <b>\n";
    ptr +="<span id=\"getHmd\">\n";
    ptr += getHmd();
    ptr +="</span>\n";
    ptr +="&#37;</b></p><br>\n";
    ptr +="<h3>-- -- -- -- --</h3>\n";
    
    ptr +="Donn&eacute;es :<br><br>\n";
    ptr +="<a class=\"button button-off\" href=\"/dataSensorsHub\">Capteurs</a>\n";

    ptr +="<h3>-- -- -- -- --</h3> \n";
    
    ptr +="Configuration :<br><br>\n";
    ptr +="<a class=\"button button-off\" href=\"/configWIFI\">Wifi</a>\n";
    ptr +="<a class=\"button button-off\" href=\"/calibDateHeure\">Date / Heure</a>\n";
    ptr +="<a class=\"button button-off\" href=\"/configMESURES\">Mesures</a>\n";
    ptr +="<a class=\"button button-off\" href=\"/configCAPTEURS\">Capteurs</a>\n";
    ptr +="<a class=\"button button-off\" href=\"/configDisplay\">Affichage</a>\n";
    ptr +="<a class=\"button button-off\" href=\"/configHTTPS\">HTTPS</a>\n";

    //ptr +="<h3>-- -- -- -- --</h3> \n";
    //ptr +="Calibrations :<br><br>\n";
    //ptr +="<a class=\"button button-off\" href=\"/calibDateHeure\">Date / Heure</a>\n";
    //ptr +="<a class=\"button button-off\" href=\"/calibADC\">ADC</a>\n";
    //ptr +="<a class=\"button button-off\" href=\"/calibTempHmdR\">Temp. / Hmd.R.</a>\n";
    //ptr +="<a class=\"button button-off\" href=\"/calibFSR\">FSR-X-XXX</a>\n";
    
    ptr +="<h3>-- -- -- -- --</h3> \n";
    ptr +="<p></p><a class=\"button button-reset\" href=\"/reset\">DECONNEXION</a> \n";
    ptr +="<p>LMGC - Laboratoire de M&eacute;canique et G&eacute;nie Civil (Service COMPEX) | CNRS - Centre National de la Recherche Scientifique | UM - Universit&eacute de Montpellier<br>By S. DYCKE<br>&copy;Copyright 2023 </p>\n";

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
    ptr +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"getTmp\").innerHTML = this.responseText;}};\n";
    ptr +="    xhttp.open(\"GET\", \"getTmp\", true);\n"; 
    ptr +="    xhttp.send();\n";
    ptr +="  }\n";

    ptr +="setInterval(function(){getData3();}, 100);\n"; //100mSeconds update rate
    ptr +="function getData3() \n";
    ptr +="  {\n";
    ptr +="    var xhttp = new XMLHttpRequest();\n";
    ptr +="    xhttp.onreadystatechange = function(){if (this.readyState == 4 && this.status == 200){document.getElementById(\"getHmd\").innerHTML = this.responseText;}};\n";
    ptr +="    xhttp.open(\"GET\", \"getHmd\", true);\n"; 
    ptr +="    xhttp.send();\n";
    ptr +="  }\n";
    
    ptr +="</script>\n";
   
    ptr +="</body></html>\n";
    return ptr;
}



void configHTTPS(){
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
  msg +="<h1>ESP Acquisition Unit<br>Configuration HTTPS</h1> \n";
    
  msg +="<br>\n";
  msg +="<form action=\"/paramHTTPS\">\n";
 
  msg +="<label for=\"input1\">URL : <br><br></label>\n";
  msg +="<input list=\"list_ssid\" id=\"input1\" name=\"input1\" value=\"\n";
  msg +=readFile(SPIFFS, "/https_url.txt");
  msg +="\"/>\n";
    
  msg += "<br><br>Path :<br><br><input type=\"text\" name=\"input2\" value=\"\n";
  msg +=readFile(SPIFFS, "/https_path.txt");
  msg +="\"/>\n";

  msg += "<br><br><input class=\"button button-off\" type=\"submit\" value=\"Enregistrer\">\n";
  msg +="</form>\n";
  msg +="<p></p><a class=\"button button-reset\" href=\"/\"><- BACK</a> \n";
    
  msg +="</body></html>\n";
  server.send(200, "text/html", msg);
}


void paramHTTPS(){
  tempsExitWithDelay = 0;
  Serial.println("Paramètres HTTPS mis à jour");
  String message = "<html>";
  message +="<head>";
  message +="<title>Redirection ...</title>";
  message +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"\">";
  message +="</head>";
  message +="<body>";

  message += "<br><br><center><h1 style=\"color:#7FBB1B;\">Les saisies du formulaire ont bien &eacute;t&eacute; prises en compte</h1></center><br>\n";
  message += "<center><h4>Redirection ...</h4></center>\n";
  for (int i = 0; i < server.args(); i++) {
    Serial.print("Variable : ");Serial.print(server.argName(i));Serial.print(" ---> valeur : ");Serial.println(server.arg(i));
    if (i == 0){
      writeFile(SPIFFS, "/https_url.txt", server.arg(i).c_str());
    }else if (i == 1){
      writeFile(SPIFFS, "/https_path.txt", server.arg(i).c_str());
    }else{
    }
  } 
  server.send(200, "text/html", message);       //Response to the HTTP request
}








void handle_reset(){ // Si commande reset
  String message = "<html>";
  message +="<head>";
  message +="<title>Redirection ...</title>";
  message +="<meta http-equiv=\"refresh\" content=\"1; URL=http://"+local_ip_redirect+"\">";
  message +="</head>";
  message +="<body>";
  message +="</body></html>";
  server.send(200, "text/html", message);
  delay(1000);
  Serial.println("[RESET] AP-MODE exit");
  ESP.restart();
}
  

void exitWithDelay(){
  delay(1);
  tempsExitWithDelay++;
  //Serial.println(tempsExitWithDelay);
  //LEDTIMING(dureeExitWithDelay,tempsExitWithDelay);
  if (tempsExitWithDelay > dureeExitWithDelay){
    Serial.println("[RESET] AP-MODE exit");
    ESP.restart();
  }
}
