
//la lib vient d'ici : https://github.com/RobTillaart/ADS1X15

ADS1113 ADS(0x48);

//Fonction d'init de l'ADC
void init_ADC_ADS1113() 
  {
    if(debugESSENTIAL){Serial.println("------------------------- ADC_Lib_INFO ----------------------------");}
    if(debugESSENTIAL){Serial.println(__FILE__);}
    if(debugESSENTIAL){Serial.print("ADS1X15_LIB_VERSION: ");}
    if(debugESSENTIAL){Serial.println(ADS1X15_LIB_VERSION);}
    if(debugESSENTIAL){Serial.println("-------------------------------------------------------------------");}
    ADS.begin();
  }


//Retourne la valeure numérique lue par l'ADC
int16_t ADC() 
  {
    ADS.setGain(0);
    int16_t val = ADS.readADC(0);  
    return(val);
  }


//Retourne une tension (V) lue par l'ADC
float ADC_to_V(int16_t ADC) 
  {
    float valADC = ((ADC*(readFile(SPIFFS, "/offsetADCVolt.txt")).toFloat())/(readFile(SPIFFS, "/offsetADCNum.txt")).toFloat()); //Fait la mise à l'échelle pour donner une tention
    return(valADC);
  }


//Retourne, en string, une valeure numérique lue par l'ADC sur le canal "i"
String ADCNumOut(int i) 
  {
    selectInput(i);
    ADS.setGain(0);
    String val = String(ADS.readADC(0), DEC);  
    return(val);
  }


/*FONCTION A REVOIRE /!\*/
String ADC_to_VForWebCalib(int16_t ADC) 
  {
    String valADC = String(((ADC*(readFile(SPIFFS, "/offsetADCVolt.txt")).toFloat())/(readFile(SPIFFS, "/offsetADCNum.txt")).toFloat())); //Fait la mise à l'échelle pour donner une tention
    return(valADC);
  }

 
//Retourne, en string, la valeure analogique (en V) lue par l'ADC sur le canal "i"
String ADCVForOutput(int i) 
  {
    selectInput(i);
    delay(10);
    String valADC = String((((ADC()*(readFile(SPIFFS, "/offsetADCVolt.txt")).toFloat())/(readFile(SPIFFS, "/offsetADCNum.txt")).toFloat()))); //Fait la mise à l'échelle pour donner une tention
    return(valADC);
  }


//Fonction convertion tension numérique en force (N) lue sur le canal "i"
//MAJ : La fonction revoie uniquement les données bruts ...
String ForceNForWeb(int k) 
  {
    /*
    long int tensionCapt = ADCNumOut(i).toInt();  

    char * nomFichierCalibFSR;
    switch (i) 
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
    //Application à une courbe de tendance (polyno) d’ordre 5 :
    double force_newton = (CTP5_X5.toDouble())*pow(tensionCapt,5)+(CTP5_X4.toDouble())*pow(tensionCapt,4)+(CTP5_X3.toDouble())*pow(tensionCapt,3)+(CTP5_X2.toDouble())*pow(tensionCapt,2)+(CTP5_X.toDouble())*tensionCapt+(CTP5_Y.toDouble());
    return(String(force_newton));
    */

    long int Moy = 0;

    for (int i = 0; i < 16; i++) 
      {
        Moy += ADCNumOut(k).toInt();
        delay(10);
      }
      
    Moy = Moy/16;


    
    return(String(Moy));
  }
