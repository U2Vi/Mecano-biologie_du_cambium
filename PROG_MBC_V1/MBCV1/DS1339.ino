
#define DS1307_ADDRESS 0x68 //Adresse i2C

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


//Init le module RTC
void init_DS1339()
  {
    if (! rtc.begin()) 
      {
        if(debugESSENTIAL){Serial.println("[CRITICAL ERROR 802][RTC] -> Couldn't find RTC");}
        CodeERREUR += "802:";
      }
    if (! rtc.isrunning()) 
      {;
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        if(debugESSENTIAL){Serial.println("[INFO 101][RTC] -> RTC is NOT running, let's set the time!");}
        CodeERREUR += "101:";
      }
  }


//Met à jour la date
void timeAdjust(int newDay, int newMouth, int newYear, int newHour, int newMinute, int newSecond)
  {
    rtc.adjust(DateTime(newYear, newMouth, newDay, newHour, newMinute, newSecond));
    if(debugALL){Serial.println(" -> RTC adjust a new time");}
  }


//Retourne, en String, la date non standardisée (pour la lecture de l'utilisateur)
String TimeForWeb()
  {
    DateTime now = rtc.now();
    String date = "";
    
    int tok = now.day();
    if (tok < 10)
      {
        date += "0"+String(now.day(), DEC)+"/";
      }
    else
      {
        date += String(now.day(), DEC)+"/";
      }
    tok = now.month();
    if (tok < 10)
      {
        date += "0"+String(now.month(), DEC)+"/";
      }
    else
      {
        date += String(now.month(), DEC)+"/";
      } 
    date += String(now.year(), DEC)+" - ";
    tok = now.hour();
    if (tok < 10)
      {
        date += "0"+String(now.hour(), DEC)+":";
      }
    else
      {
        date += String(now.hour(), DEC)+":";
      }
    tok = now.minute();
    if (tok < 10)
      {
        date += "0"+String(now.minute(), DEC)+" et ";
      }
    else
      {
        date += String(now.minute(), DEC)+" et ";
      }
    tok = now.second();
    if (tok < 10)
      {
        date += "0"+String(now.second(), DEC)+"s";
      }
    else
      {
        date += String(now.second(), DEC)+"s";
      }
    return(date);
  }


//Retourne, en String, la date standardisée sous la forme : 2022-02-09T12:01:18  
String TimeForOutput()
  {
    DateTime now = rtc.now();
    String date = "";

    date += String(now.year(), DEC)+"-";
    int tok = now.day();
    tok = now.month();
    if (tok < 10)
      {
        date += "0"+String(now.month(), DEC)+"-";
      }
    else
      {
        date += String(now.month(), DEC)+"-";
      } 
      
    if (tok < 10)
      {
        date += "0"+String(now.day(), DEC)+"T";
      }
    else
      {
        date += String(now.day(), DEC)+"T";
      }
    tok = now.hour();
    if (tok < 10)
      {
        date += "0"+String(now.hour(), DEC)+":";
      }
    else
      {
        date += String(now.hour(), DEC)+":";
      }
    tok = now.minute();
    if (tok < 10)
      {
        date += "0"+String(now.minute(), DEC)+":";
      }
    else
      {
        date += String(now.minute(), DEC)+":";
      }
    tok = now.second();
    if (tok < 10)
      {
        date += "0"+String(now.second(), DEC)+"";
      }
    else
      {
        date += String(now.second(), DEC)+"";
      }
    return(date);
  }

//retourne le jour en String
String TimeDayForWeb()
  {
    DateTime now = rtc.now();
    String date = String(now.day(), DEC);
    return(date);
  }


//retourne le mois en String
String TimeMonthForWeb()
  {
    DateTime now = rtc.now();
    String date = String(now.month(), DEC);
    return(date);
  }


//retourne l'année en String
String TimeYearForWeb()
  {
    DateTime now = rtc.now();
    String date = String(now.year(), DEC);
    return(date);
  }


//retourne les heures en String
String TimeHourForWeb()
  {
    DateTime now = rtc.now();
    String date = String(now.hour(), DEC);
    return(date);
  }


//retourne les min. en String
String TimeMinuteForWeb()
  {
    DateTime now = rtc.now();
    String date = String(now.minute(), DEC);
    return(date);
  }


//retourne les sec. en String
String TimeSecondForWeb()
  {
    DateTime now = rtc.now();
    String date = String(now.second(), DEC);
    return(date);
  }


//retourne les sec. en int
int timeSecond()
  {
    DateTime now = rtc.now();
    return(now.second(), DEC);
  }


//Affiche la date sur le moniteur série
void Time()
  {
    DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  }



//Serial.print(" since midnight 1/1/1970 = ");
//Serial.print(now.unixtime());
//Serial.print("s = ");
//Serial.print(now.unixtime() / 86400L);
//Serial.println("d");

// calculate a date which is 7 days, 12 hours, 30 minutes, and 6 seconds into the future
//DateTime future (now + TimeSpan(7,12,30,6));
