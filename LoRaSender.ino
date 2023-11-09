#include <SPI.h>
#include <LoRa.h>


/*#define SCK  13
#define MISO 12
#define MOSI 11*/
#define SS 10
#define RST 9
#define DIO0 2

int counter = 0;
int sf[] = {8,9,10,11,12};
void setup() {
  Serial.begin(9600);
  pinMode(4,OUTPUT);
  while (!Serial);
  LoRa.setPins(SS, RST, DIO0);
  Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  pinMode(5, INPUT_PULLUP);
  LoRa.setSpreadingFactor(8);
}


void executa(){
  counter = 1;
  
  for(int i = 0; i < 5; i++){
    digitalWrite(4, HIGH);
    LoRa.setSpreadingFactor(sf[i]);
    for(int j = 0; j < 200; j++){
      // Envia pacote
      Serial.print("Enviando pacote ");
      Serial.println(counter);
      LoRa.beginPacket();
      LoRa.print("pacote ");
      LoRa.print(counter);
      LoRa.print(" SF: ");
      LoRa.print(sf[i]);
      LoRa.endPacket();
      counter++;
    } 
    digitalWrite(4, LOW);
    int teste = 0;
    LoRa.setSpreadingFactor(sf[i+1]); //aumenta 1 spreading factor
    while(digitalRead(5)){
      teste=LoRa.parsePacket();
      if(teste) break;
    }

  }

}

void loop() {
  int Button = digitalRead(5);
  while(!Button){
    
    executa();
    Button = 0;
  //delay(1000);
  }
}
