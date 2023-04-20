/* [OK] */

/*************************************************************************
***************************[ Function  : ]********************************
**************************************************************************
***                                                                    ***
*** Void i2c_setChannel(ADDR, CHANNEL)                                 ***
***                                                                    ***
**************************************************************************
*************************************************************************/

#define SET_CHANNEL_0 0x04
#define SET_CHANNEL_1 0x05



// Select i2C channel ->  ADDR = Adresse du composant (0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77) | CHANNEL = Cannal i2C du composant (0 ou 1).

void i2c_setChannel(int ADDR, int CHANNEL){
  if (CHANNEL == 0x70 or 0x71 or 0x72 or 0x73 or 0x74 or 0x75 or 0x76 or 0x77){
    Wire.beginTransmission(ADDR);
    if (CHANNEL == 1){ //For channel 1
    Wire.write(SET_CHANNEL_1);
    Serial.print("[MUXI2C-PCA9542] -> Set channel 1 (Addr "); Serial.print(ADDR, HEX);Serial.println(")");
    }else if (CHANNEL == 0){ //For channel 0
      Wire.write(SET_CHANNEL_0);
      Serial.print("[MUXI2C-PCA9542] -> Set channel 0 (Addr "); Serial.print(ADDR, HEX);Serial.println(")");
    }else{
      Serial.print("[MUXI2C-PCA9542] -> ERROR on set channel, bad channel select ... (Addr "); Serial.print(ADDR, HEX);Serial.println(")");
    }
    Wire.endTransmission();
    delay(10);
  }else{
    Serial.print("[MUXI2C-PCA9542] -> ERROR on set channel, bad address select ... (Addr "); Serial.print(ADDR, HEX);Serial.println(")");
  }
}
