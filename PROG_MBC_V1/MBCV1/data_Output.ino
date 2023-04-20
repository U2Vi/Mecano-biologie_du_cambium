
/*******************************************************************************************************
 
A faire :
- crire la procedure de calib FSR
- Afficher dans config AP : IP et Mac
- Configue sur interface AP : hoste, webpage + hoste et webpage redondante
- Vérifier code couleur led R/V pour la wifi
- Modifier le nom de variable "WiFiConnectAttempt"
- Ajouter AP la possibilitée de changer le temps de sortie auto du mode AP.
- Dans ADC_ADS1113, ADC_to_VForWebCalib(int16_t ADC) -> FONCTION A REVOIRE /!\

Amélioration, carte SD :
- Ajouter parametrages carte SD dans l'interface ?
- Afficher taille fichier
- Carte SD presente ou non
- Renomer nom fichier
- Choix du format de sortie TXT, CSV, etc ..

*******************************************************************************************************/

void SDOutput()
  {
    String msg = ""; 
    msg += TimeForOutput();
    msg += ",";
    msg += Numero_systeme;
    msg += ",";
    msg += CodeERREUR;
    msg += ",";
    msg += ValuesTMPForOutput();
    msg += ",";
    msg += ValuesHRForOutput();
    msg += ",";
    msg += readFile(SPIFFS, "/nombreCapteurs.txt");
    for(int k = 1; k < 48; k ++)
      {
        msg += ",";
        delay(10);
        msg += ForceNForWeb(k);
      }
    msg += "\n";   
    if(debugESSENTIAL){Serial.print("Données à inscrire dans la carte SD :");Serial.println(msg);}
    appendFileInSD(SD, "/Data.txt", msg.c_str());
  }
  
void webOutput()
  {
    String device_data = ""; 
    device_data += TimeForOutput();
    device_data += "::";
    device_data += Numero_systeme;
    device_data += "::";
    device_data += CodeERREUR;
    device_data += "-::";
    device_data += ValuesTMPForOutput();
    device_data += "::";
    device_data += ValuesHRForOutput();
    device_data += "::";
    device_data += readFile(SPIFFS, "/nombreCapteurs.txt");
    for(int k = 1; k < 49; k ++)
      {
        device_data += "::";
        device_data += "J";
        device_data += String(k);
        device_data += ":";
        delay(10);
        device_data += ForceNForWeb(k);
      }
    if(debugESSENTIAL){Serial.print("Données à envoyer au cloud :");Serial.println(device_data);}
    SendToCloud(device_data);
  }

void serialOutput()
  {
    String msg = ""; 
    msg += TimeForOutput();
    msg += ",";
    msg += Numero_systeme;
    msg += ",";
    msg += CodeERREUR;
    msg += ",";
    msg += ValuesTMPForOutput();
    msg += ",";
    msg += ValuesHRForOutput();
    msg += ",";
    msg += readFile(SPIFFS, "/nombreCapteurs.txt");
    for(int k = 1; k < 48; k ++)
      {
        msg += ",J"+String(k)+",";
        delay(10);
        msg += ForceNForWeb(k);
      }
    msg += "\n";    
    Serial.println(msg);
  }


  
