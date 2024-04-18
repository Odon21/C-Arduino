#include <SoftwareSerial.h>

SoftwareSerial mySerial(22, 23); //rx tx

void setup() {
  Serial.begin(115200);
  delay(1000); // Pequeno atraso para estabilizar a comunicação serial
  Serial.println("Teste de comunicação serial em diferentes baud rates:");
}

void loop() {
  // Lista de baud rates a serem testados
  long baudRates[] = {50, 75, 110, 134.5, 150, 200, 300, 600, 1200, 1800, 2400, 3600, 4800, 7200, 9600, 14400, 19200, 28800, 38400, 57600, 76800, 115200, 230400, 250000, 460800, 500000, 921600, 1000000, 1500000, 2000000, 2500000, 3000000, 3500000, 4000000};


  int numBaudRates = sizeof(baudRates) / sizeof(baudRates[0]);

  for (int i = 0; i < numBaudRates; i++) {
    long baudRate = baudRates[i];
    Serial.print("Tentando iniciar a comunicação serial em ");
    Serial.print(baudRate);
    Serial.println(" ...");

    mySerial.begin(baudRate); // Inicializa a comunicação serial com o baud rate atual

    // Verifica se a comunicação serial foi iniciada com sucesso
    if (mySerial.available()) {
      Serial.println("Comunicação serial iniciada com sucesso!");
      Serial.println("este de comunicação serial bem-sucedido!-------------------------------------");
      // Envie uma mensagem de teste
      mySerial.println("Teste de comunicação serial bem-sucedido!-------------------------------------");
      Serial.write(mySerial.read());
      delay(1000); // Aguarda um breve período
    } else {
      Serial.println("Falha ao iniciar a comunicação serial!");
    }
  }

  // Após testar todos os baud rates, aguarda 5 segundos antes de reiniciar o loop
  delay(5000);
  Serial.println("_______RESTARTING_____");
}