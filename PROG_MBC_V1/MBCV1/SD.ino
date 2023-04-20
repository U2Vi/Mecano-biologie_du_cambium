
#define broche_CS_SD 5


//Fonction d'Init pour lecture/écriture dans carte SD
void init_SD() 
  {
    if (!SD.begin(broche_CS_SD)) 
      {
        if(debugESSENTIAL){Serial.println("[ERROR 709][SD] -> Carte SD manquante ou illisible");}
        CodeERREUR += "709:";
        return;
      }
    else
      {
        if(debugESSENTIAL){Serial.println("[SD] -> Carte SD détectée et fonctionnelle");}
      } 
  }


//Fonction pour l'ajout d'une ligne dans le ficier d'une carte SD
void appendFileInSD(fs::FS &fs, const char * path, const char * message) 
  {
    //Si le fichier n'existe pas encore, on le pre-formate pour export Exel 
    if(!SD.exists(path))
      {
        if(debugESSENTIAL){Serial.printf("[SD] -> Pré-formatage du fichier: %s\n", path);}
        File file = fs.open(path, FILE_APPEND);
        file.print("Date,Numéro du Systéme,Code d'erreur,Température (°C),Humiditée Relative (%),Nombre de capteurs,J1,J2,J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,J13,J14,J15,J16,J17,J18,J19,J20,J21,J22,J23,J24,J25,J26,J27,J28,J29,J30,J31,J32,J33,J34,J35,J36,J37,J38,J39,J40,J41,J42,J43,J44,J46,J47,J48\n");
        file.close();
      }
    
    if(debugESSENTIAL){Serial.printf("Ecriture dans le fichier: %s\n", path);}
    File file = fs.open(path, FILE_APPEND);
    if (!file) 
      {
        if(debugESSENTIAL){Serial.println("[ERROR 710][SD] -> Echec d'ouverture du fichier");}
        CodeERREUR += "710:";
        return;
      }
    if (file.print(message)) 
      {
        if(debugESSENTIAL){Serial.println("[SD] -> Fichier modifié avec succes.");}
      } 
    else 
      {
        if(debugESSENTIAL){Serial.println("[ERROR 711][SD] -> Echec de la modification du fichier");}
        CodeERREUR += "711:";
      }
    file.close();
  }
