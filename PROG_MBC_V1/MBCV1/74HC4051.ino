
//Config des broches de contrôle du MuxADC
#define IO_5_MatriceMux 27
#define IO_6_MatriceMux 26
#define IO_7_MatriceMux 32

//Config des broches de contrôle des MuxIN (et LEDs R/V)
//#define IO_2_MuxADC_et_LedRV_RWifi 17
//#define IO_3_MuxADC_et_LedRV_VWifi 25
#define IO_4_MuxADC 33


//Mux in "Z" pin
int Z_pin = 0;

int numChannel = 0;
int numMuxADC = 5;


//Fonction d'init des MUX
void init_74HC4051()
  {
    pinMode(IO_5_MatriceMux, OUTPUT);
    pinMode(IO_6_MatriceMux, OUTPUT);
    pinMode(IO_7_MatriceMux, OUTPUT);
    pinMode(IO_2_MuxADC_et_LedRV_RWifi, OUTPUT);
    pinMode(IO_3_MuxADC_et_LedRV_VWifi, OUTPUT);
    pinMode(IO_4_MuxADC, OUTPUT);

    digitalWrite(IO_5_MatriceMux, LOW);
    digitalWrite(IO_6_MatriceMux, LOW);
    digitalWrite(IO_7_MatriceMux, LOW);
    digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, LOW);
    digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, LOW);
    digitalWrite(IO_4_MuxADC, LOW);  
  }


//Selectionne le canal, si Num = 1 on selectionne J1, etc ... 
void selectInput(int Num)
  {
    if (Num>=1&&Num<=8) // PASSED
      {
        //MUX en tete pour selcetion sur MUX U4
        digitalWrite(IO_5_MatriceMux, 0);
        digitalWrite(IO_6_MatriceMux, 1);
        digitalWrite(IO_7_MatriceMux, 1);
        selectMatMuxInput(Num);
      }
    else if (Num>=9&&Num<=16) //PASSED
      {
        //MUX en tete pour selcetion sur MUX U6
        digitalWrite(IO_5_MatriceMux, 0);
        digitalWrite(IO_6_MatriceMux, 1);
        digitalWrite(IO_7_MatriceMux, 0);
        selectMatMuxInput(Num);
      }
    else if (Num>=17&&Num<=24) //PASSED
      {
        //MUX en tete pour selcetion sur MUX U7
        digitalWrite(IO_5_MatriceMux, 1);
        digitalWrite(IO_6_MatriceMux, 0);
        digitalWrite(IO_7_MatriceMux, 1);
        selectMatMuxInput(Num);
      }
    else if (Num>=25&&Num<=32) //PASSED
      {
        //MUX en tete pour selcetion sur MUX U9 (Noté U10)
        digitalWrite(IO_5_MatriceMux, 1);
        digitalWrite(IO_6_MatriceMux, 0);
        digitalWrite(IO_7_MatriceMux, 0);
        selectMatMuxInput(Num);
      }
    else if (Num>=33&&Num<=40) //PASSED
      {
        //MUX en tete pour selcetion sur MUX U10 (Noté U9)
        digitalWrite(IO_5_MatriceMux, 0);
        digitalWrite(IO_6_MatriceMux, 0);
        digitalWrite(IO_7_MatriceMux, 1);
        selectMatMuxInput(Num);
      }
    else if (Num>=41&&Num<=48) //PASSED
      {
        //MUX en tete pour selcetion sur MUX U11
        digitalWrite(IO_5_MatriceMux, 0);
        digitalWrite(IO_6_MatriceMux, 0);
        digitalWrite(IO_7_MatriceMux, 0);
        selectMatMuxInput(Num);
      }
    else
      {
           
      }
    delay(1);
  }


//Fonction de service pour la fonction selectInput()
void selectMatMuxInput(int Num)
  {
    if (Num==1||Num==9||Num==17||Num==25||Num==33||Num==41)
      {
        //selectionne les broches "7" des MUXs en //
        digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, 1);
        digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, 1);
        digitalWrite(IO_4_MuxADC, 1);
        if(debugALL){Serial.print("Channel MatMux set : ");Serial.println(Num);}
      }
    else if (Num==2||Num==10||Num==18||Num==26||Num==34||Num==42)
      {
        //selectionne les broches "6" des MUXs en //
        digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, 0);
        digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, 1);
        digitalWrite(IO_4_MuxADC, 1);
        if(debugALL){Serial.print("Channel MatMux set : ");Serial.println(Num);}
      }
    else if (Num==3||Num==11||Num==19||Num==27||Num==35||Num==43)
      {
        //selectionne les broches "5" des MUXs en //
        digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, 1);
        digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, 0);
        digitalWrite(IO_4_MuxADC, 1);
        if(debugALL){Serial.print("Channel MatMux set : ");Serial.println(Num);}
      }
    else if (Num==4||Num==12||Num==20||Num==28||Num==36||Num==44)
      {
        //selectionne les broches "4" des MUXs en //
        digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, 0);
        digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, 0);
        digitalWrite(IO_4_MuxADC, 1);
        if(debugALL){Serial.print("Channel MatMux set : ");Serial.println(Num);}
      }
    else if (Num==5||Num==13||Num==21||Num==29||Num==37||Num==45)
      {
        //selectionne les broches "3" des MUXs en //
        digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, 1);
        digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, 1);
        digitalWrite(IO_4_MuxADC, 0);
        if(debugALL){Serial.print("Channel MatMux set : ");Serial.println(Num);}
      }
    else if (Num==6||Num==14||Num==22||Num==30||Num==38||Num==46)
      {
        //selectionne les broches "2" des MUXs en //
        digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, 0);
        digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, 1);
        digitalWrite(IO_4_MuxADC, 0);
        if(debugALL){Serial.print("Channel MatMux set : ");Serial.println(Num);}
      }
    else if (Num==7||Num==15||Num==23||Num==31||Num==39||Num==47)
      {
        //selectionne les broches "1" des MUXs en //
        digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, 1);
        digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, 0);
        digitalWrite(IO_4_MuxADC, 0);
        if(debugALL){Serial.print("Channel MatMux set : ");Serial.println(Num);}
      }
    else if (Num==8||Num==16||Num==24||Num==32||Num==40||Num==48)
      {
        //selectionne les broches "0" des MUXs en //
        digitalWrite(IO_2_MuxADC_et_LedRV_RWifi, 0);
        digitalWrite(IO_3_MuxADC_et_LedRV_VWifi, 0);
        digitalWrite(IO_4_MuxADC, 0);
        if(debugALL){Serial.print("Channel MatMux set : ");Serial.println(Num);}
      }
    else
      {
           
      }
  }
