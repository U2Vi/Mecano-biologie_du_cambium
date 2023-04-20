/* [~~~] */


//ADC
//int16_t value = 0;
//float voltage =0;

#define ADS1113_CONFIG_REGISTER_1 0x01
#define ADS1113_CONVER_REGISTER   0x00
#define ADS1113_MSB_LSB_REGISTER  0x83


//void init_ADC_device(){ 
//}

#define sampling 20

int ADC(){
  
  long int valueMoy = 0;
  for (int i = 0; i < sampling; i++) {
    //Select input channel 0 (AIN0 - GND)
    Wire.beginTransmission(ADS1113_ADDRESS);
    Wire.write(ADS1113_CONFIG_REGISTER_1); // Config register
    Wire.write(ADS1113_MSB_LSB_REGISTER); // MSB (0x83 for AIN0 single-ended mode)
    Wire.write(ADS1113_MSB_LSB_REGISTER); // LSB
    Wire.endTransmission();  
    delay(10);
    // Read ADC value
    Wire.beginTransmission(ADS1113_ADDRESS);
    Wire.write(ADS1113_CONVER_REGISTER); // Conversion register
    Wire.endTransmission();
    
    Wire.requestFrom(ADS1113_ADDRESS, 2);
    int value = (Wire.read() << 8) | Wire.read();
       
    valueMoy += value;
    delay(5);
    }
      
  valueMoy = (valueMoy/sampling);
  
  // Convert raw value to voltage
  float voltage = (float)valueMoy * 2.048 / 32768.0;
  
  Serial.print("ADC value: ");
  Serial.print(valueMoy);
  Serial.print("| Voltage: ");
  Serial.print(voltage, 6);
  Serial.println(" V");
  delay(5);

  //return(voltage); //Fonction à mettre en float
  return(valueMoy);

  //Valeure de mesure max pour 5V :  2,048V
}


//Fonction pour l'affichage web uniquement (soulage les calculs)
int ADCNoSampling(){
  
  long int valueMoy = 0;
  for (int i = 0; i < 1; i++) {
    //Select input channel 0 (AIN0 - GND)
    Wire.beginTransmission(ADS1113_ADDRESS);
    Wire.write(ADS1113_CONFIG_REGISTER_1); // Config register
    Wire.write(ADS1113_MSB_LSB_REGISTER); // MSB (0x83 for AIN0 single-ended mode)
    Wire.write(ADS1113_MSB_LSB_REGISTER); // LSB
    Wire.endTransmission();  
    delay(10);
    // Read ADC value
    Wire.beginTransmission(ADS1113_ADDRESS);
    Wire.write(ADS1113_CONVER_REGISTER); // Conversion register
    Wire.endTransmission();
    
    Wire.requestFrom(ADS1113_ADDRESS, 2);
    int value = (Wire.read() << 8) | Wire.read();
       
    valueMoy += value;
    delay(5);
    }
      
  valueMoy = (valueMoy/1);
  
  // Convert raw value to voltage
  float voltage = (float)valueMoy * 2.048 / 32768.0;
  
  Serial.print("ADC value: ");
  Serial.print(valueMoy);
  Serial.print("| Voltage: ");
  Serial.print(voltage, 6);
  Serial.println(" V");
  delay(5);

  //return(voltage); //Fonction à mettre en float
  return(valueMoy);

  //Valeure de mesure max pour 5V :  2,048V
}
