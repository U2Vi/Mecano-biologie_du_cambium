/* [~~~] */



void init_gpio_exp_device(){

  //Select i2C channel
  i2c_setChannel(PCA9542_ADDRESS,1);
  
  //Config peripheriques i2C GPIO EXP
  Wire.beginTransmission(PCAL6416_ADDRESS);
  Wire.write(0x06); // Configure le registre de direction pour mettre les pins en sortie
  Wire.write(0x00); // Configure les pins 0 à 7 en sortie
  Wire.endTransmission();
  Serial.println("[GPIOEXP-PCAL6416] -> Set 0 to 7 as OUTPUT");

  Wire.beginTransmission(PCAL6416_ADDRESS);
  Wire.write(0x07); // Configure le registre de direction pour mettre les pins en sortie
  Wire.write(0x00); // Configure les pins 8 à 15 en sortie
  Wire.endTransmission();
  Serial.println("[GPIOEXP-PCAL6416] -> Set 8 to 15 as OUTPUT");
}




void blue_lights(int led){
  int timeDelay = 10;
  byte ledBits[] = {0b00000001, 0b00000010, 0b00000100, 0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000};

  if(led >= 3 && led <= 10){
    Wire.beginTransmission(PCAL6416_ADDRESS);
    Wire.write(0x02);
    Wire.write(ledBits[led-3]);
    Wire.endTransmission();
    delay(timeDelay);
  }
}



void sensorSelect(int connector, int channel) {
  const int delayTime = 10;
  const int address = PCAL6416_ADDRESS;
  const int channels[2][33] = {
    {0b00000000, 0b10101110, 0b10101010, 0b10100110, 0b10100010, 0b11101110, 0b11101010, 0b11100110, 0b11100010, 0b11001110, 0b11001010, 0b11000110, 0b11000010, 0b10001110, 0b10001010, 0b10000110, 0b10000010, 0b01001110, 0b01001010, 0b01000110, 0b01000010, 0b00101110, 0b00101010, 0b00100110, 0b00100010, 0b00001110, 0b00001010, 0b00000110, 0b00000010, 0b01101110, 0b01101010, 0b01100110, 0b01100010},
    {0b00000000, 0b10101100, 0b10101000, 0b10100100, 0b10100000, 0b11101100, 0b11101000, 0b11100100, 0b11100000, 0b11001100, 0b11001000, 0b11000100, 0b11000000, 0b10001100, 0b10001000, 0b10000100, 0b10000000, 0b01001100, 0b01001000, 0b01000100, 0b01000000, 0b00101100, 0b00101000, 0b00100100, 0b00100000, 0b00001100, 0b00001000, 0b00000100, 0b00000000, 0b01101100, 0b01101000, 0b01100100, 0b01100000}
  };

  const int index = (connector * 2) + channel;
  const int pinMask = channels[channel][connector];

  blue_lights((connector - 1) / 4 + 3); //Turn on the LED corresponding to the selected connector row

  Wire.beginTransmission(address);
  Wire.write(0x03);
  Wire.write(pinMask);
  Wire.endTransmission();

  delay(delayTime);
}






/*
 void sensorSelect_1(int connector, int channel){

  i2c_setChannel(PCA9542_ADDRESS,1);

  int timeDelay = 10;

  if((channel < 0) || (channel >=2)){
    Serial.println("[GPIOEXP-PCAL6416] -> Wrong channel selected");
    return;
  }
  if((connector < 0) || (connector >=33)){
    Serial.println("[GPIOEXP-PCAL6416] -> Wrong connector selected");
    return;
  }

  if ((connector >= 1) && (connector <= 4)){
    //U6
    blue_lights(3);
    Wire.beginTransmission(PCAL6416_ADDRESS);
    Wire.write(0x03);
    if(connector == 1){
      if(channel == 0){
        Wire.write(0b10101110);
      }else{
        Wire.write(0b10101100);
      }
    }else if(connector == 2){
      if(channel == 0){
        Wire.write(0b10101010);
      }else{
        Wire.write(0b10101000);
      }
    }else if(connector == 3){
      if(channel == 0){
        Wire.write(0b10100110);
      }else{
        Wire.write(0b10100100);
      }
    }else if(connector == 4){
      if(channel == 0){
        Wire.write(0b10100010);
      }else{
        Wire.write(0b10100000);
      }
    }
    Wire.endTransmission();
    delay(timeDelay);
  }else if  ((connector >= 5) && (connector <= 8)){
    blue_lights(4);
    Wire.beginTransmission(PCAL6416_ADDRESS);
    Wire.write(0x03);
    if(connector == 5){
      if(channel == 0){
        Wire.write(0b11101110);
      }else{
        Wire.write(0b11101100);
      }
    }else if(connector == 6){
      if(channel == 0){
        Wire.write(0b11101010);
      }else{
        Wire.write(0b11101000);
      }
    }else if(connector == 7){
      if(channel == 0){
        Wire.write(0b11100110);
      }else{
        Wire.write(0b11100100);
      }
    }else if(connector == 8){
      if(channel == 0){
        Wire.write(0b11100010);
      }else{
        Wire.write(0b11100000);
      }
    }
    Wire.endTransmission();
    delay(timeDelay);
  }else if  ((connector >= 9) && (connector <= 12)){
    blue_lights(5);
    Wire.beginTransmission(PCAL6416_ADDRESS);
    Wire.write(0x03);
    if(connector == 9){
      if(channel == 0){
        Wire.write(0b11001110);
      }else{
        Wire.write(0b11001100);
      }
    }else if(connector == 10){
      if(channel == 0){
        Wire.write(0b11001010);
      }else{
        Wire.write(0b11001000);
      }
    }else if(connector == 11){
      if(channel == 0){
        Wire.write(0b11000110);
      }else{
        Wire.write(0b11000100);
      }
    }else if(connector == 12){
      if(channel == 0){
        Wire.write(0b11000010);
      }else{
        Wire.write(0b11000000);
      }
    }
    Wire.endTransmission();
    delay(timeDelay);
  }else if  ((connector >= 13) && (connector <= 16)){
    blue_lights(6);
    Wire.beginTransmission(PCAL6416_ADDRESS);
    Wire.write(0x03);
    if(connector == 13){
      if(channel == 0){
        Wire.write(0b10001110);
      }else{
        Wire.write(0b10001100);
      }
    }else if(connector == 14){
      if(channel == 0){
        Wire.write(0b10001010);
      }else{
        Wire.write(0b10001000);
      }
    }else if(connector == 15){
      if(channel == 0){
        Wire.write(0b10000110);
      }else{
        Wire.write(0b10000100);
      }
    }else if(connector == 16){
      if(channel == 0){
        Wire.write(0b10000010);
      }else{
        Wire.write(0b10000000);
      }
    }
    Wire.endTransmission();
    delay(timeDelay);
  }else if  ((connector >= 17) && (connector <= 20)){
    blue_lights(7);
    Wire.beginTransmission(PCAL6416_ADDRESS);
    Wire.write(0x03);
    if(connector == 17){
      if(channel == 0){
        Wire.write(0b01001110);
      }else{
        Wire.write(0b01001100);
      }
    }else if(connector == 18){
      if(channel == 0){
        Wire.write(0b01001010);
      }else{
        Wire.write(0b01001000);
      }
    }else if(connector == 19){
      if(channel == 0){
        Wire.write(0b01000110);
      }else{
        Wire.write(0b01000100);
      }
    }else if(connector == 20){
      if(channel == 0){
        Wire.write(0b01000010);
      }else{
        Wire.write(0b01000000);
      }
    }
    Wire.endTransmission();
    delay(timeDelay);
  }else if  ((connector >= 21) && (connector <= 24)){
    blue_lights(8);
    Wire.beginTransmission(PCAL6416_ADDRESS);
    Wire.write(0x03);
    if(connector == 21){
      if(channel == 0){
        Wire.write(0b00101110);
      }else{
        Wire.write(0b00101100);
      }
    }else if(connector == 22){
      if(channel == 0){
        Wire.write(0b00101010);
      }else{
        Wire.write(0b00101000);
      }
    }else if(connector == 23){
      if(channel == 0){
        Wire.write(0b00100110);
      }else{
        Wire.write(0b00100100);
      }
    }else if(connector == 24){
      if(channel == 0){
        Wire.write(0b00100010);
      }else{
        Wire.write(0b00100000);
      }
    }
    Wire.endTransmission();
    delay(timeDelay);
  }else if  ((connector >= 25) && (connector <= 28)){
    blue_lights(9);
    Wire.beginTransmission(PCAL6416_ADDRESS);
    Wire.write(0x03);
    if(connector == 25){
      if(channel == 0){
        Wire.write(0b00001110);
      }else{
        Wire.write(0b00001100);
      }
    }else if(connector == 26){
      if(channel == 0){
        Wire.write(0b00001010);
      }else{
        Wire.write(0b00001000);
      }
    }else if(connector == 27){
      if(channel == 0){
        Wire.write(0b00000110);
      }else{
        Wire.write(0b00000100);
      }
    }else if(connector == 28){
      if(channel == 0){
        Wire.write(0b00000010);
      }else{
        Wire.write(0b00000000);
      }
    }
    Wire.endTransmission();
    delay(timeDelay);
  }else if  ((connector >= 29) && (connector <= 32)){
    blue_lights(10);
    Wire.beginTransmission(PCAL6416_ADDRESS);
    Wire.write(0x03);
    if(connector == 29){
      if(channel == 0){
        Wire.write(0b01101110);
      }else{
        Wire.write(0b01101100);
      }
    }else if(connector == 30){
      if(channel == 0){
        Wire.write(0b01101010);
      }else{
        Wire.write(0b01101000);
      }
    }else if(connector == 31){
      if(channel == 0){
        Wire.write(0b01100110);
      }else{
        Wire.write(0b01100100);
      }
    }else if(connector == 32){
      if(channel == 0){
        Wire.write(0b01100010);
      }else{
        Wire.write(0b01100000);
      }
    }
    Wire.endTransmission();
    delay(timeDelay);  
  }
}*/




/*
      // Channel 0
      0b00000000, // Connector 0
      0b10101110, // Connector 1
      0b10101010, // Connector 2
      0b10100110, // Connector 3
      0b10100010, // Connector 4
      0b11101110, // Connector 5
      0b11101010, // Connector 6
      0b11100110, // Connector 7
      0b11100010, // Connector 8
      0b11001110, // Connector 9
      0b11001010, // Connector 10
      0b11000110, // Connector 11
      0b11000010, // Connector 12
      0b10001110, // Connector 13
      0b10001010, // Connector 14
      0b10000110, // Connector 15
      0b10000010, // Connector 16
      0b01001110, // Connector 17
      0b01001010, // Connector 18
      0b01000110, // Connector 19
      0b01000010, // Connector 20
      0b00101110, // Connector 21
      0b00101010, // Connector 22
      0b00100110, // Connector 23
      0b00100010, // Connector 24
      0b00001110, // Connector 25
      0b00001010, // Connector 26
      0b00000110, // Connector 27
      0b00000010, // Connector 28
      0b01101110, // Connector 29
      0b01101010, // Connector 30
      0b01100110, // Connector 31
      0b01100010  // Connector 32

      // Channel 1
      0b00000000, // Connector 0
      0b10101100, // Connector 1
      0b10101000, // Connector 2
      0b10100100, // Connector 3
      0b10100000, // Connector 4
      0b11101100, // Connector 5
      0b11101000, // Connector 6
      0b11100100, // Connector 7
      0b11100000, // Connector 8
      0b11001100, // Connector 9
      0b11001000, // Connector 10
      0b11000100, // Connector 11
      0b11000000, // Connector 12
      0b10001100, // Connector 13
      0b10001000, // Connector 14
      0b10000100, // Connector 15
      0b10000000, // Connector 16
      0b01001100, // Connector 17
      0b01001000, // Connector 18
      0b01000100, // Connector 19
      0b01000000, // Connector 20
      0b00101100, // Connector 21
      0b00101000, // Connector 22
      0b00100100, // Connector 23
      0b00100000, // Connector 24
      0b00001100, // Connector 25
      0b00001000, // Connector 26
      0b00000100, // Connector 27
      0b00000000, // Connector 28
      0b01101100, // Connector 29
      0b01101000, // Connector 30
      0b01100100, // Connector 31
      0b01100000  // Connector 32











//S2 S1 S0 E1 S5 S4 S3 E2


/*
Wire.write(0b00010000); //E1 - 1
Wire.write(0b00000001); //E2 - 2
Wire.write(0b00100000); //S0 - 3
Wire.write(0b01000000); //S1 - 4
Wire.write(0b10000000); //S2 - 5
Wire.write(0b00000010); //S3 - 6
Wire.write(0b00000100); //S4 - 7
Wire.write(0b00001000); //S5 - 8

Wire.write(0b01101000); //U06Y5
Wire.write(0b01111000); //U08Y7
Wire.write(0b01011000); //U10Y6
Wire.write(0b01001000); //U05Y4
Wire.write(0b01010000); //U07Y2
Wire.write(0b01100000); //U09Y1
Wire.write(0b01000000); //U11Y0
Wire.write(0b01110000); //U04Y3

  1-4
  5-8
  9-12
  13-16
  17-20
  21-24
  25-28
  29-32
  
  //0x02
  Wire.write(0b00000000);
  Wire.write(0b00010000); //E1 - 1
  Wire.write(0b00010001); //E2 - 2
  Wire.write(0b00110001); //S0 - 3
  Wire.write(0b01110001); //S1 - 4
  Wire.write(0b11110001); //S2 - 5
  Wire.write(0b11110011); //S3 - 6
  Wire.write(0b11110111); //S4 - 7
  Wire.write(0b11111111); //S5 - 8

  --> Ya -->
U06 = Y5
U08 = Y7
U10 = Y6
U05 = Y4
U07 = Y2
U09 = Y1
U11 = Y0
U04 = Y3

--> Yb -->
J1.0 = Y7
J1.1 = Y6
J2.0 = Y5
J2.1 = Y4
J3.0 = Y3
J3.1 = Y2
J4.0 = Y1
J4.1 = Y0

//AV
Wire.write(0b00000001); //D3
Wire.write(0b00000010); //D4
Wire.write(0b00000100); //D5
Wire.write(0b10000000); //D6 
Wire.write(0b01000000); //D7
Wire.write(0b00100000); //D8
Wire.write(0b00010000); //D9
Wire.write(0b00001000); //D10
//AR
Wire.write(0b00010000); //D10
Wire.write(0b00100000); //D9
Wire.write(0b01000000); //D8
Wire.write(0b10000000); //D7
Wire.write(0b00000100); //D6
Wire.write(0b00000010); //D5
Wire.write(0b00000001); //D4










      
*/
