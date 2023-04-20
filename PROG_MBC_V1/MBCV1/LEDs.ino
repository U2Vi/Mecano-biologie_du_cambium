
#define LedB_Mux1 2
#define LedB_Mux2 4
#define LedB_Mux3 12
#define LedB_Mux4 13
#define LedB_Mux5 14
#define LedB_Mux6 16


void init_LEDs() 
  {   
    pinMode(LedB_Mux1, OUTPUT);
    pinMode(LedB_Mux2, OUTPUT);
    pinMode(LedB_Mux3, OUTPUT);
    pinMode(LedB_Mux4, OUTPUT);
    pinMode(LedB_Mux5, OUTPUT);
    pinMode(LedB_Mux6, OUTPUT);
  }



void ledInitMode(bool etat)
  {
    if (etat == 1)
      {
        digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, HIGH);
        digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, HIGH);
        delay(500);
      }
    else
      {
        digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, LOW);
        digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, LOW);
      }
  }




void LEDM0_U11(int time_) 
  {
    digitalWrite(LedB_Mux1, HIGH);
    delay(time_);
    digitalWrite(LedB_Mux1, LOW);
  }

  
void LEDM1_U10(int time_) 
  {
    digitalWrite(LedB_Mux6, HIGH);
    delay(time_);
    digitalWrite(LedB_Mux6, LOW);
  }

  
void LEDM2_U9(int time_) 
  {
    digitalWrite(LedB_Mux2, HIGH);
    delay(time_);
    digitalWrite(LedB_Mux2, LOW);
  }

  
void LEDM3_U7(int time_) 
  {
    digitalWrite(LedB_Mux5, HIGH);
    delay(time_);
    digitalWrite(LedB_Mux5, LOW);
  }

  
void LEDM4_U6(int time_) 
  {
    digitalWrite(LedB_Mux3, HIGH);
    delay(time_);
    digitalWrite(LedB_Mux3, LOW);
  }

  
void LEDM5_U4(int time_) 
  {
    digitalWrite(LedB_Mux4, HIGH);
    delay(time_);
    digitalWrite(LedB_Mux4, LOW);
  }

//Fonction barre de temps avec les Leds pour le temps restant en mode AP
void LEDTIMING(long int timeMax,long int timeAcctu) 
  {
    if (timeAcctu < timeMax/8*2)
      {
        digitalWrite(LedB_Mux1, HIGH);
        digitalWrite(LedB_Mux2, HIGH);
        digitalWrite(LedB_Mux3, HIGH);
        digitalWrite(LedB_Mux4, HIGH);
        digitalWrite(LedB_Mux5, HIGH);
        digitalWrite(LedB_Mux6, HIGH);
      }
    else if (timeAcctu < timeMax/8*3)
      {
        digitalWrite(LedB_Mux1, LOW);
        digitalWrite(LedB_Mux2, HIGH);
        digitalWrite(LedB_Mux3, HIGH);
        digitalWrite(LedB_Mux4, HIGH);
        digitalWrite(LedB_Mux5, HIGH);
        digitalWrite(LedB_Mux6, HIGH);
      }
    else if (timeAcctu < timeMax/8*4)
      {
        digitalWrite(LedB_Mux1, LOW);
        digitalWrite(LedB_Mux2, LOW);
        digitalWrite(LedB_Mux3, HIGH);
        digitalWrite(LedB_Mux4, HIGH);
        digitalWrite(LedB_Mux5, HIGH);
        digitalWrite(LedB_Mux6, HIGH);
      }
    else if (timeAcctu < timeMax/8*5)
      {
        digitalWrite(LedB_Mux1, LOW);
        digitalWrite(LedB_Mux2, LOW);
        digitalWrite(LedB_Mux3, LOW);
        digitalWrite(LedB_Mux4, HIGH);
        digitalWrite(LedB_Mux5, HIGH);
        digitalWrite(LedB_Mux6, HIGH);
      }
    else if (timeAcctu < timeMax/8*6)
      {
        digitalWrite(LedB_Mux1, LOW);
        digitalWrite(LedB_Mux2, LOW);
        digitalWrite(LedB_Mux3, LOW);
        digitalWrite(LedB_Mux4, LOW);
        digitalWrite(LedB_Mux5, HIGH);
        digitalWrite(LedB_Mux6, HIGH);
      }
    else if (timeAcctu < timeMax/8*7)
      {
        digitalWrite(LedB_Mux1, LOW);
        digitalWrite(LedB_Mux2, LOW);
        digitalWrite(LedB_Mux3, LOW);
        digitalWrite(LedB_Mux4, LOW);
        digitalWrite(LedB_Mux5, LOW);
        digitalWrite(LedB_Mux6, HIGH);
      }
    else if (timeAcctu < timeMax/8*8)
      {
        digitalWrite(LedB_Mux1, LOW);
        digitalWrite(LedB_Mux2, LOW);
        digitalWrite(LedB_Mux3, LOW);
        digitalWrite(LedB_Mux4, LOW);
        digitalWrite(LedB_Mux5, LOW);
        if (timeAcctu%200 >= 100)
          {
            digitalWrite(LedB_Mux6, LOW); 
          }
        else if (timeAcctu%200 <= 100)
          {
            digitalWrite(LedB_Mux6, HIGH); 
          }
        else
          {
            digitalWrite(LedB_Mux6, LOW); 
          }
      }
  }


void LEDALL(int time_) 
  {
    digitalWrite(LedB_Mux1, HIGH);
    delay(time_);
    digitalWrite(LedB_Mux1, LOW);
    digitalWrite(LedB_Mux6, HIGH);
    delay(time_);
    digitalWrite(LedB_Mux6, LOW);
    digitalWrite(LedB_Mux2, HIGH);
    delay(time_);
    digitalWrite(LedB_Mux2, LOW);
    digitalWrite(LedB_Mux5, HIGH);
    delay(time_);
    digitalWrite(LedB_Mux5, LOW);
    digitalWrite(LedB_Mux3, HIGH);
    delay(time_);
    digitalWrite(LedB_Mux3, LOW);
    digitalWrite(LedB_Mux4, HIGH);
    delay(time_);
    digitalWrite(LedB_Mux4, LOW);
  }


void LED_BiColor_V(int time_) 
  {
    digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, HIGH);
    delay(time_);
    digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, LOW);
    delay(time_);
  }
void LED_BiColor_R(int time_) 
  {
    digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, HIGH);
    delay(time_);
    digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, LOW);
    delay(time_);
  }
void LED_BiColor_R_ON() 
  {
    digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, HIGH);
  }
void LED_BiColor_V_ON() 
  {
    digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, HIGH);
  }
void LED_BiColor_R_OFF() 
  {
    digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, LOW);
  }
void LED_BiColor_V_OFF() 
  {
    digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, LOW);
  }
void LED_BiColor_V_ConnectOK() 
  {
    digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, HIGH);
    delay(500);
    digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, LOW);
    delay(500);
    digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, HIGH);
    delay(500);
    digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, LOW);
    delay(500);
  }
