



//Fonction d'Init pour lecture/écriture dans carte SD
void init_SD_device() 
  {
    if (!SD.begin(broche_CS_SD)) 
      {
        Serial.println("[ERROR 709][SD] -> Carte SD manquante ou illisible");
        CodeERREUR += "709:";
        return;
      }
    else
      {
        Serial.println("[SD] -> Carte SD détectée et fonctionnelle");
      } 
  }

//Fonction pour l'ajout d'une ligne dans le ficier d'une carte SD
void appendFileInSD(fs::FS &fs, const char * path, const char * message) 
  {
    //Si le fichier n'existe pas encore, on le pre-formate pour export Exel 
    if(!SD.exists(path))
      {
        Serial.printf("[SD] -> Pré-formatage du fichier: %s\n", path);
        File file = fs.open(path, FILE_APPEND);
        file.print("Date,Numéro du Systéme,Code d'erreur,Température (°C),Humiditée Relative (%),Nombre de capteurs,J1.0,J1.1,J2.0,J2.1,J3.0,J3.1,J4.0,J4.1,J5.0,J5.1,J6.0,J6.1,J7.0,J7.1,J8.0,J8.1,J9.0,J9.1,J10.0,J10.1,J11.0,J11.1,J12.0,J12.1,J13.0,J13.1,J14.0,J14.1,J15.0,J15.1,J16.0,J16.1,J17.0,J17.1,J18.0,J18.1,J19.0,J19.1,J20.0,J20.1,J21.0,J21.1,J22.0,J22.1,J23.0,J23.1,J24.0,J24.1,J25.0,J25.1,J26.0,J26.1,J27.0,J27.1,J28.0,J28.1,J29.0,J29.1,J30.0,J30.1,J31.0,J31.1,J32.0,J32.1\n");
        file.close();
      }
    
    Serial.printf("Ecriture dans le fichier: %s\n", path);
    File file = fs.open(path, FILE_APPEND);
    if (!file) 
      {
        Serial.println("[ERROR 710][SD] -> Echec d'ouverture du fichier");
        CodeERREUR += "710:";
        return;
      }
    if (file.print(message)) 
      {
        Serial.println("[SD] -> Fichier modifié avec succes.");
      } 
    else 
      {
        Serial.println("[ERROR 711][SD] -> Echec de la modification du fichier");
        CodeERREUR += "711:";
      }
    file.close();
  }
