
//List des fichiers (56 fichiers) :
// -> ssidBoxWifi.txt
// -> passwordBoxWifi.txt
// -> frequenceMesure.txt
// -> nombreCapteurs.txt
// -> offsetTmp.txt
// -> offsetHumR.txt
// -> offsetADCNum.txt  
// -> offsetADCVolt.txt
// -> ctp5_1.txt
//    ... to ...
// -> ctp5_48.txt


//Init de l'utilisation de la mémoire SPIFFS. Passer sur TRUE au premier televersement puis mettre sur False au second pour gagner du temps à chaque téléversement. 
#define FORMAT_SPIFFS_IF_FAILED true


//Valeurs par défaut des fichiers sur la mémoire flash SPIFFS :
char * ValUsine_ssidBoxWifi = "SSID";
char * ValUsine_passwordBoxWifi = "PASSWORD";
char * ValUsine_frequenceMesure = "24";
char * ValUsine_nombreCapteurs = "48";
char * ValUsine_offsetHumR = "0";
char * ValUsine_offsetTmp = "0";
char * ValUsine_offsetADCNum = "32768"; 
char * ValUsine_offsetADCVolt = "3.3";
char * ValUsine_CTP5_X = ":1:-1:1:-1:1:-1:";


//Init l'utilisation de la mémoire flash SPIFFS
void init_Flash_memory()
  {
    if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
      {
        if(debugESSENTIAL){Serial.println("[CRITICAL ERROR 801][SPIFFS] -> SPIFFS Mount Failed");}
        CodeERREUR += "801:";
        return;
      }
    if(debugALL){listDir(SPIFFS, "/", 0);}
  }


//Liste les fichiers disponibles à la racine "/"
void listDir(fs::FS &fs, const char * dirname, uint8_t levels)
  {
    if(debugALL){Serial.println("------------------------ Liste des fichiers -----------------------");}
    Serial.printf("Listing directory: %s\r\n", dirname);
    
    File root = fs.open(dirname);
    if(!root)
      {
        Serial.println("− failed to open directory");
        return;
      }
    if(!root.isDirectory())
      {
        Serial.println(" − not a directory");
        return;
      }

    File file = root.openNextFile();
    while(file)
      {
        if(file.isDirectory())
          {
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels)
              {
                listDir(fs, file.name(), levels -1);
              }
          } 
        else 
          {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
          }
        file = root.openNextFile(); 
      }
    if(debugALL){Serial.println("-------------------------------------------------------------------");}
  }

  
//Fonction qui lit le contenue des fichiers txt dans la mémoire Flash SPIFFS
String readFile(fs::FS &fs, const char * path)
  {
    if(debugALL){Serial.printf("Reading file: %s\r\n", path);}
    File file = fs.open(path);
    if(!file || file.isDirectory())
      {
        if(debugALL){Serial.println("− failed to open file for reading");}
        //Si fichier n'existe pas, on le créé avec une valeur d'usine
        if (path == "/ssidBoxWifi.txt")
          {
            writeFile(SPIFFS, "/ssidBoxWifi.txt", ValUsine_ssidBoxWifi);
            if(debugALL){Serial.println("Fichier '/ssidBoxWifi.txt' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/passwordBoxWifi.txt")
          { 
            writeFile(SPIFFS, path, ValUsine_passwordBoxWifi);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/frequenceMesure.txt")
          {
            writeFile(SPIFFS, path, ValUsine_frequenceMesure);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/nombreCapteurs.txt")
          {
            writeFile(SPIFFS, path, ValUsine_nombreCapteurs);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/offsetTmp.txt")
          {
            writeFile(SPIFFS, path, ValUsine_offsetTmp);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/offsetHumR.txt")
          {
            writeFile(SPIFFS, path, ValUsine_offsetHumR);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/offsetADCNum.txt")
          {
            writeFile(SPIFFS, path, ValUsine_offsetADCNum);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/offsetADCVolt.txt")
          {
            writeFile(SPIFFS, path, ValUsine_offsetADCVolt);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }  
       else if (path == "/ctp5_1.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }    
        else if (path == "/ctp5_2.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }    
        else if (path == "/ctp5_3.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_4.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_5.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }  
        else if (path == "/ctp5_6.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_7.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_8.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_9.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_10.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_11.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_12.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_13.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_14.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_15.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_16.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_17.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_18.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_19.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_20.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_21.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_22.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_23.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_24.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_25.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_26.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_27.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_28.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_29txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_30.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }        
        else if (path == "/ctp5_31.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_32.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_33.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_34.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_35.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_36.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_37.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_38.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_39.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_40.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_41.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_42.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_43.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_44.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_45.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }        else if (path == "/ctp5_.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_46.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_47.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else if (path == "/ctp5_48.txt")
          {
            writeFile(SPIFFS, path, ValUsine_CTP5_X);
            if(debugALL){Serial.print("Fichier '");Serial.print(path);Serial.println("' créé ! ");}
            File file = fs.open(path);
          }
        else
          {
            if(debugESSENTIAL){Serial.println("[ERROR 701][SPIFFS] -> Reading file failed");}
            CodeERREUR += "701:";
            return("-1");
          }
      }
    //Ouvre le fichier et retourne un String avec le contenue de celui-ci.
    String maData;
    while(file.available())
      {
        maData += file.readString();
      } 
    file.close();
    return(maData);
  }

//Fonction qui efface et écrit dans un fichier txt dans la flah SPIFFS
void writeFile(fs::FS &fs,const char * path,const char * message)
  {
    if(debugALL){Serial.printf("Writing file: %s\r\n", path);}
    File file = fs.open(path, FILE_WRITE);
    if(!file)
      {
        if(debugESSENTIAL){Serial.println("[ERROR 702][SPIFFS] -> Failed to open file for writing");}
        CodeERREUR += "702:";
        return;
      }
    if(file.print(message))
      {
        if(debugESSENTIAL){Serial.println(" −> file written");}
      }
    else 
      {
        if(debugESSENTIAL){Serial.println("[ERROR 703][SPIFFS] -> Written failed");}
        CodeERREUR += "703:";
      }
  }


//Fonction d'ajout de texte dans un fichier (ajout à la suite de l'existant)
void appendFile(fs::FS &fs, const char * path, const char * message)
  {
    if(debugALL){Serial.printf("Appending to file: %s\r\n", path);}
    File file = fs.open(path, FILE_APPEND);
    if(!file)
      {
        if(debugESSENTIAL){Serial.println("[ERROR 704][SPIFFS] -> Failed to open file for appending");}
        CodeERREUR += "704:";
        return;
      }
    if(file.print(message))
      {
        if(debugALL){Serial.println(" −> message appended");}
      } 
    else 
      {
        if(debugESSENTIAL){Serial.println("[ERROR 705][SPIFFS] -> Append failed");}
        CodeERREUR += "705:";
      }
  }


//Fonction pour renomer un fichier
void renameFile(fs::FS &fs, const char * path1, const char * path2)
  {
    if(debugALL){Serial.printf("Renaming file %s to %s\r\n", path1, path2);}
    if (fs.rename(path1, path2)) 
      {
        if(debugALL){Serial.println(" −> File renamed");}
      } 
    else 
      {
        if(debugESSENTIAL){Serial.println("[ERROR 706][SPIFFS] -> Rename failed");}
        CodeERREUR += "706:";
      }
  }

//Fonction de suppresion d'un fichier
void deleteFile(fs::FS &fs, const char * path)
  {
    if(debugALL){Serial.printf("Deleting file: %s\r\n", path);}
    if(fs.remove(path))
      {
        if(debugALL){Serial.println(" −> File deleted");}
      } 
    else 
      {
        if(debugESSENTIAL){Serial.println("[ERROR 707][SPIFFS] -> Delete failed");}
        CodeERREUR += "707:";
      }
  }
