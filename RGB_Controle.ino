/*    AUTOR: RILDO FARIAS DEMES
      DATA: 13/11/2020
      LOCAL: BREVES-PA
*/

//========== inclue as bibliotecas, define as constantes e declara as variáveis ==========
#include <EEPROM.h>
#include <SoftwareSerial.h>

#define white 4                                  // define a cor branca no pino 4
#define red_blue 5                               // define as cores vermelha e azul no pino 5
#define green 6                                  // define a cor verde no pino 6

byte BTdata;                                     // define a variavel que recebe os dados do Bluetooth
byte serial;                                     // define a variavel que recebe os dados da Serial
boolean eeprom_white;
boolean eeprom_red_blue;
boolean eeprom_green;
SoftwareSerial Bluetooth(10, 11);                // RX, TX comunicacao serial com o bluetooth

//================== define e inicía os parametros e os pinos do arduino =================
void setup() {
 Serial.begin(9600);                             // comunicaçao serial padrao do arduino
 Bluetooth.begin(115200);                        // comunicaçao serial com o bluetooth
 boolean eeprom_white = EEPROM.read(0);          // memoria da cor branco
 boolean eeprom_red_blue = EEPROM.read(1);       // memoria da vermelho azul
 boolean eeprom_green = EEPROM.read(2);          // memoria da cor verde
 //---------------------------- printa a mensagem de inicio -------------------------------
Serial.println("Pronto!\nTudo certo. ;)");
Bluetooth.println("Pronto!\nTudo certo. ;)");
 //------------------- define os pinos dos ledes como saídas digitais ---------------------
 pinMode(white, OUTPUT);
 pinMode(red_blue, OUTPUT);
 pinMode(green, OUTPUT);
 //--------------------- recupera o utimo estado da memoria das luzes ---------------------
 digitalWrite(white, eeprom_white);
 digitalWrite(red_blue, eeprom_red_blue);
 digitalWrite(green, eeprom_green);
}
//================================== loop infinito do arduino =============================
void loop() {
  if (Bluetooth.available() || Serial.available() ){
    BTdata = Bluetooth.read();
    serial = Serial.read();
    }
  if (BTdata == 0x1 || serial == '1'){        // recebe o valor exadecimal "1" (um) e liga/desliga cor branco
    
    eeprom_white = !EEPROM.read(0);           // ler o locar 0 da memoria eeprom
    EEPROM.write(0,eeprom_white);             // escreve a negação no local 0 da memoria eeprom
    
    if (eeprom_white) {                       // bloco para desligar a luz branca
          //digitalWrite(13,LOW);
          digitalWrite(white,HIGH);
          Serial.println("Led branco OFF!");
          Bluetooth.println("Led branco OFF!");
        }
     else {                                   // bloco para ligar a luz branca
          //digitalWrite(13,HIGH);
          digitalWrite(white,LOW);
          Serial.println("Led branco ON!");
          Bluetooth.println("Led branco ON!");
        }
    
    BTdata = 0x0;
    serial = 0;
    }
  if (BTdata == 0x2 || serial == '2'){         // recebe o valor exadecimal "2" (dois) e liga/desliga cores vermelho e azul 
    
    eeprom_red_blue = !EEPROM.read(1);         // ler o locar 1 da memoria eeprom
    EEPROM.write(1, eeprom_red_blue);          // escreve a negação no local 2 da memoria eeprom

    if (eeprom_red_blue) {                     // bloco para desligar a luz vermelha e azul
          //digitalWrite(13,LOW);
          digitalWrite(red_blue,HIGH);
          Serial.println("Led RED e BLUE OFF!");
          Bluetooth.println("Led RED e BLUE OFF!");
        }
     else {                                    // bloco para ligar a luz vermelha e azul
          //digitalWrite(13,HIGH);
          digitalWrite(red_blue,LOW);
          Serial.println("Led RED e BLUE ON!");
          Bluetooth.println("Led RED e BLUE ON!");
        }
    
    BTdata = 0x0;
    serial = 0;
    }
  if (BTdata == 0x3 || serial == '3'){        // recebe o valor exadecimal "3" (tres) e liga/desliga cor verde
    
    eeprom_green = !EEPROM.read(2);           // ler o locar 2 da memoria eeprom 
    EEPROM.write(2, eeprom_green);            // escreve a negação no local 2 da memoria eeprom

    if (eeprom_green) {                       // bloco para desligar a luz verde
          //digitalWrite(13,LOW);
          digitalWrite(green,HIGH);
          Serial.println("Led VERDE OFF!");
          Bluetooth.println("Led VERDE OFF!");
        }
     else {                                   // bloco para ligar a luz verde
          //digitalWrite(13,HIGH);
          digitalWrite(green,LOW);
          Serial.println("Led VERDE ON!");
          Bluetooth.println("Led VERDE ON!");
        }
    
    BTdata = 0x0;                             
    serial = 0;
    }
}