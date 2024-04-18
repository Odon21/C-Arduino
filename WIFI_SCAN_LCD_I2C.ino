#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // biblhoteca para definirmos pinos digitais para comnicacao I2C
#include <SPI.h>                // Tabem vamos pressar da SPI
#include <WiFi.h>               // Essa e a bilhoteca princimpal para o Scan de redes wifi

LiquidCrystal_I2C lcd(0x27, 20, 4);  // DEfinimos o endereco do nonso periferico na comunicacao I2C no Numero de colunas e o numero de linhas

void printEncryptionType();      // Aqui esta a inicializacao da funcao que se responsabiliza por ver i tipo ade criptogradi disponivel
void listNetworks();              // Funcao que lista as redes
void printMacAddress();           // Funcao que lista os enderecos MACs de cada rede
int x;

void setup() {
  //pinMode(4, OUTPUT);
  // put your setup code here, to run once:
  Wire.begin(14, 15);      // Aquie definimos os pinos para ligarmos o LCD liquidCrsytal SDA e SCL
  lcd.begin(20, 4);        // Inicializamos a comunicacao para lcd de 20 colunas em cada 4 linhas
  lcd.init();              // Inicializamos o lcd
  lcd.backlight();         // Ligamos a liz de fundo do LCD
  lcd.setCursor(0,0);      // Colocamos o cursor na linha 0 e coluna 0
  //analogWrite(4, 150);
  delay(1000);            
  //analogWrite(4, 1);

}

void loop() {
  // put your main code here, to run repeatedly:
  listNetworks();    // no loop vamos rodat o metodo que faz o sacn das redes...
}
void listNetworks() {
  // scan for nearby networks:
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    lcd.println("AP HIDEN");
    while (true);
  }
  if (numSsid<1){
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("WLAN unavailable");
    lcd.setCursor(10, 3);
    lcd.print("Scaning");
    delay(500);
    lcd.setCursor(17, 3);
    lcd.print(".");
    delay(500);
    lcd.setCursor(18, 3);
    lcd.print(".");
    delay(500);
    lcd.setCursor(19, 3);
    lcd.print(".");
    delay(500);

  }
  // Printar a lista de redes:
  //Serial.print("[*] Number of available networks:_");
  //Serial.print(numSsid);
  

  // Mostrar o numero das redes e os nomes das redes encontradas
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    x=thisNet;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(thisNet+1);

    lcd.setCursor(2,0);
    lcd.print(WiFi.SSID(thisNet));
    lcd.setCursor(0,1);
    lcd.print("Ecr ");
    lcd.setCursor(4,1);
    printEncryptionType();
    lcd.setCursor(0,2);
    lcd.print("CH ");
    lcd.setCursor(3, 2);
    lcd.print(WiFi.channel(thisNet));
    lcd.setCursor(6, 2);
    lcd.print("Sigl ");
    lcd.setCursor(11, 2);
    lcd.print(WiFi.RSSI(thisNet));
    lcd.setCursor(15, 2);
    lcd.println("dBm");
    lcd.setCursor(18, 2);
    lcd.print("..");
    
    lcd.setCursor(0, 3);
    lcd.print("MC ");
    lcd.setCursor(3, 3);
    lcd.print(WiFi.BSSIDstr(thisNet));
    delay(1000);
    //
    //printEncryptionType();
  }
  //Serial.println("\n\n");
}

void printEncryptionType() {
  // read the encryption type and print out the name:

  switch (WiFi.encryptionType(x)) {
    case 0:
      lcd.print("Open");
      break;
    case 1:
      lcd.print("WEP");
      break;
    case 2:
      lcd.print("WPA");
      break;
    case 3:
      lcd.print("WPA2-PSK");
      break;
    case 4:
      lcd.print("WPA|WPA2 Persnl");
      break;
    case 5:
      lcd.print("WPA|WPA2 Enterp");
      break;
    default:
      lcd.print("*******");
      break;
  }
}
