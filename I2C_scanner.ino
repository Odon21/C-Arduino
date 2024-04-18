#include <Wire.h> // Importas a pibilhoteca para configuracao de pinos na cominocacao I2C

void setup() {
  //Wire.setClock(400000); // Define a velocidade de comunicação I2C para 400 kHz
  Wire.begin();
  Serial.begin(9600);
  Wire.setClock(400000); // Define a velocidade de comunicação I2C para 400 kHz

  while (!Serial);
  
  Serial.println("\nI2C Scanner");
}

void loop() {
  byte error, address;
  int devices = 0;

  Serial.println("Scanning...");

  for(address = 1; address < 127; address++ ) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
      devices++;
    }
    else if (error==4) {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (devices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(2000);           // wait 5 seconds for next scan
}
