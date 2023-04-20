/* [~~~] */

// Serial monitor
// I2C
// Power 


void init_peripheral_devices(){

  /* Serial monitor */
  Serial.begin(115200); 

  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println("[INIT-Monitor] -> Serial Monitor set");

  /* Wire (i2C) */
  Wire.begin(I2C_SDA,I2C_SCL);
  //Wire.setClock(1000000);    //Set clk for I2C
  Serial.print("[INIT-I2C] -> I2C set (SDA : GPIO");Serial.print(I2C_SDA);Serial.print("| SCL : GPIO");Serial.print(I2C_SCL);Serial.println(")");

  /* Power */
  pinMode(PWR_AUX_3V3, OUTPUT);
  pinMode(PWR_AUX_5V, OUTPUT);
  Serial.print("[INIT-I/O] -> Input and Output set (GPIO");Serial.print(PWR_AUX_3V3);Serial.print(", GPIO");Serial.print(PWR_AUX_5V);Serial.println(")");

  /* BP */
  pinMode(BP_WIFI, INPUT);
}


//Power supply 3V3
void power_3V3(bool switch_){

  if (switch_ == 1){
    digitalWrite(PWR_AUX_3V3, HIGH);
    Serial.println("[POWER MANAGEMENT] -> Power supply 3.3V : ON");
  }else{
    digitalWrite(PWR_AUX_3V3, LOW);
    Serial.println("[POWER MANAGEMENT] -> Power supply 3.3V : OFF");
  }
}


//Power supply 5V
void power_5V(bool switch_){
  if (switch_ == 1){
    digitalWrite(PWR_AUX_5V, HIGH);
    Serial.println("[POWER MANAGEMENT] -> Power supply 5V : ON");
  }else{
    digitalWrite(PWR_AUX_5V, LOW);
    Serial.println("[POWER MANAGEMENT] -> Power supply 5V : OFF");
  }
}


void testing_i2C(){
  Serial.println();
  Serial.println("[I2C] -> Scanning for I2C devices ...");
  if (DYBoard_Collector){
    i2c_setChannel(PCA9542_ADDRESS, 0);
    scanning_i2C();
    delay(10);
    i2c_setChannel(PCA9542_ADDRESS, 1);
    scanning_i2C();
    delay(10);
  }else{
    scanning_i2C();
    delay(10);
  }
}


void scanning_i2C(){
  byte error, address;
  int nDevices = 0;
  for(address = 0x01; address < 0x7f; address++){
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0){
      Serial.printf("[I2C] -> I2C device found at address 0x%02X\n", address);
      nDevices++;
    } else if(error != 2){
      Serial.printf("[I2C] -> Error %d at address 0x%02X\n", error, address);
    }
  }
  if (nDevices == 0){
    Serial.println("[I2C] -> No I2C devices found");
  }
}


//Fonction de mise en mode AP si action sur bp
void App_Bp_WIFI(){
  if(digitalRead(BP_WIFI) == 0){
    //LED_BiColor_R_ON();
    Serial.println("[BP WIFI] -> 1");
    while(digitalRead(BP_WIFI) == 0){delay(10);} //Fonction bloquante pour attendre le relachement du bp 
    for (uint8_t i = 0; i < 50; i++){  //Attente d'un deuxieme app pendant 10s
      if(digitalRead(BP_WIFI) == 0){ // Si deuxieme app pendant les 10s
        Serial.println("[BP WIFI] -> 2");
        StartInit_WIFI_AP();
        while(1){
          //LED_BiColor_V_ON();
          WIFI_Mode_AP(); //(fonction blocante, reset obligatoire pour sortir du mode AP)
        }
        return; //Sécuritée si on sort de la boucle
      }
      //LED_BiColor_R(100);
      Serial.println("[BP WIFI] -> 0");
      delay(500);
    }
  }
}
