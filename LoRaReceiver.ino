#include <SPI.h>
#include <LoRa.h>

/*#define SCK  13
#define MISO 12
#define MOSI 11*/
#define SS 10
#define RST 9
#define DIO0 2

int sf[] = {8,9,10,11,12};
int i = 0;
void setup() {
  Serial.begin(9600);
  while (!Serial);
  LoRa.setPins(SS, RST, DIO0);
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  pinMode(5, INPUT_PULLUP);
  LoRa.setSpreadingFactor(8);
  //attachInterrupt(digitalPinToInterrupt(2), mudaSf, CHANGE);
}

void mudaSf(){
    Serial.print("O sf está em: '");
    i++;
    Serial.println(sf[i]);
    LoRa.setSpreadingFactor(sf[i%5]);
    delay(2000);
    LoRa.beginPacket();
    LoRa.print("cont");
    LoRa.endPacket();
}
void loop() {
  // try to parse packet
  int Button = digitalRead(5);
  if(!Button){
    mudaSf();
  }
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' RSSI: ");
    Serial.print(LoRa.packetRssi());
    // print RSSI of packet
    Serial.print(" SNR: ");
    Serial.println(LoRa.packetSnr());
  }
}
