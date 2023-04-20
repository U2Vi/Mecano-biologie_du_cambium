/* [~~~] */

/*************************************************************************
***************************[ Functions : ]********************************
**************************************************************************
***                                                                    ***

***                                                                    ***
**************************************************************************
*************************************************************************/


//List des fichiers (56 fichiers) :
// -> SSIDBoxWifi.txt
// -> passwordBoxWifi.txt
// -> measurementFrequency.txt
// -> numberOfSensors.txt
// -> offsetTmp.txt
// -> offsetHumR.txt
// -> offsetADCNum.txt  
// -> offsetADCVolt.txt


//Init de l'utilisation de la mémoire SPIFFS. Passer sur TRUE au premier televersement puis mettre sur False au second pour gagner du temps à chaque téléversement. 
#define FORMAT_SPIFFS_IF_FAILED true


//Valeurs par défaut des fichiers sur la mémoire flash SPIFFS :
char * ValUsine_SSIDBoxWifi = "SSID";
char * ValUsine_passwordBoxWifi = "PASSWORD";
char * ValUsine_measurementFrequency = "24";
char * ValUsine_numberOfSensors = "32";
char * ValUsine_offsetHumR = "0";
char * ValUsine_offsetTmp = "0";
char * ValUsine_offsetADCNum = "32768"; 
char * ValUsine_offsetADCVolt = "3.3";
char * ValUsine_paramPrintFloat = "2";
char * ValUsine_calibConvBar = "0";
char * ValUsine_https_url = "sd-radio.fr";
char * ValUsine_https_path = "test.php";



//Init l'utilisation de la mémoire flash SPIFFS
void init_Flash_memory(){
  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
    Serial.println("[ERROR 801][SPIFFS] -> SPIFFS Mount Failed");
    CodeERREUR += "801:";
    return;
  }
  listDir(SPIFFS, "/", 0);
}


//Liste les fichiers disponibles à la racine "/"
void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
  Serial.printf("[SPIFFS] -> Listing directory of internal memory ... %s\r\n", dirname);
    
  File root = fs.open(dirname);
  if(!root){
    Serial.println("− failed to open directory");
    return;
  }
  if(!root.isDirectory()){
    Serial.println(" − not a directory");
    return;
  }
  File file = root.openNextFile();
  while(file){
    if(file.isDirectory()){
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if(levels){
        listDir(fs, file.name(), levels -1);
      }
    }else{
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("\tSIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile(); 
  }
  Serial.println("[SPIFFS] ... end");
}

  
//Fonction qui lit le contenue des fichiers txt dans la mémoire Flash SPIFFS
String readFile(fs::FS &fs, const char * path){
  Serial.printf("[SPIFFS] -> Reading file: %s\r\n", path);
  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("− failed to open file for reading");
    //Si fichier n'existe pas, on le créé avec une valeur d'usine
    if (path == "/SSIDBoxWifi.txt"){
      writeFile(SPIFFS, "/SSIDBoxWifi.txt", ValUsine_SSIDBoxWifi);
      Serial.print("[SPIFFS] -> File '");Serial.print(path);Serial.println("' created ! ");
      File file = fs.open(path);
    }else if (path == "/paramPrintFloat.txt"){ 
      writeFile(SPIFFS, path, ValUsine_paramPrintFloat);
      Serial.print("[SPIFFS] -> File '");Serial.print(path);Serial.println("' created ! ");
      File file = fs.open(path);
    }else if (path == "/passwordBoxWifi.txt"){ 
      writeFile(SPIFFS, path, ValUsine_passwordBoxWifi);
      Serial.print("[SPIFFS] -> File '");Serial.print(path);Serial.println("' created ! ");
      File file = fs.open(path);
    }else if (path == "/measurementFrequency.txt"){
      writeFile(SPIFFS, path, ValUsine_measurementFrequency);
      Serial.print("[SPIFFS] -> File '");Serial.print(path);Serial.println("' created ! ");
      File file = fs.open(path);
    }else if (path == "/numberOfSensors.txt"){
      writeFile(SPIFFS, path, ValUsine_numberOfSensors);
      Serial.print("[SPIFFS] -> File '");Serial.print(path);Serial.println("' created ! ");
      File file = fs.open(path);
    }else if (path == "/offsetTmp.txt"){
      writeFile(SPIFFS, path, ValUsine_offsetTmp);
      Serial.print("[SPIFFS] -> File '");Serial.print(path);Serial.println("' created ! ");
      File file = fs.open(path);
    }else if (path == "/offsetHumR.txt"){
      writeFile(SPIFFS, path, ValUsine_offsetHumR);
      Serial.print("[SPIFFS] -> File '");Serial.print(path);Serial.println("' created ! ");
      File file = fs.open(path);
    }else if (path == "/offsetADCNum.txt"){
      writeFile(SPIFFS, path, ValUsine_offsetADCNum);
      Serial.print("[SPIFFS] -> File '");Serial.print(path);Serial.println("' created ! ");
      File file = fs.open(path);
    }else if (path == "/offsetADCVolt.txt"){
      writeFile(SPIFFS, path, ValUsine_offsetADCVolt);
      Serial.print("[SPIFFS] -> File '");Serial.print(path);Serial.println("' created ! ");
      File file = fs.open(path);
    }else if (path == "/calibConvBar.txt"){
      writeFile(SPIFFS, path, ValUsine_calibConvBar);
      Serial.print("[SPIFFS] -> File '");Serial.print(path);Serial.println("' created ! ");
      File file = fs.open(path);
    }else if (path == "/https_url.txt"){
      writeFile(SPIFFS, path, ValUsine_https_url);
      Serial.print("[SPIFFS] -> File '");Serial.print(path);Serial.println("' created ! ");
      File file = fs.open(path);
    }else if (path == "/https_path.txt"){
      writeFile(SPIFFS, path, ValUsine_https_path);
      Serial.print("[SPIFFS] -> File '");Serial.print(path);Serial.println("' created ! ");
      File file = fs.open(path);
    }else{
      Serial.println("[ERROR 701][SPIFFS] -> Reading file failed");
      CodeERREUR += "701:";
      return("-1");
    }
  }



  
  //Ouvre le fichier et retourne un String avec le contenue de celui-ci.
  String maData;
  while(file.available()){
    maData += file.readString();
  } 
  file.close();
  return(maData);
}


//Fonction qui efface et écrit dans un fichier txt dans la flah SPIFFS
void writeFile(fs::FS &fs,const char * path,const char * message){
  Serial.printf("[SPIFFS] -> Writing file: %s\r\n", path);
  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("[ERROR 702][SPIFFS] -> Failed to open file for writing");
    CodeERREUR += "702:";
    return;
  }
  if(file.print(message)){
    Serial.println(" −> file written");
  }else{
    Serial.println("[ERROR 703][SPIFFS] -> Written failed");
    CodeERREUR += "703:";
  }
}


//Fonction d'ajout de texte dans un fichier (ajout à la suite de l'existant)
void appendFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("[SPIFFS] -> Appending to file: %s\r\n", path);
  File file = fs.open(path, FILE_APPEND);
  if(!file){
    Serial.println("[ERROR 704][SPIFFS] -> Failed to open file for appending");
    CodeERREUR += "704:";
    return;
  }
  if(file.print(message)){
    Serial.println(" −> message appended");
  }else{
    Serial.println("[ERROR 705][SPIFFS] -> Append failed");
    CodeERREUR += "705:";
  }
}


//Fonction pour renomer un fichier
void renameFile(fs::FS &fs, const char * path1, const char * path2){
  Serial.printf("[SPIFFS] -> Renaming file %s to %s\r\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println(" −> File renamed");
  }else{
    Serial.println("[ERROR 706][SPIFFS] -> Rename failed");
    CodeERREUR += "706:";
  }
}


//Fonction de suppresion d'un fichier
void deleteFile(fs::FS &fs, const char * path){
  Serial.printf("[SPIFFS] -> Deleting file: %s\r\n", path);
  if(fs.remove(path)){
    Serial.println(" −> File deleted");
  }else{
    Serial.println("[ERROR 707][SPIFFS] -> Delete failed");
    CodeERREUR += "707:";
  }
}
