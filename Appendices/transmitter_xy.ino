/*
* SMART ERASER SENIOR DESIGN PROJECT
* Stepper Motor Transmitter              
* by Heather Libecki
* 
* with help from Dejan Nedelkovski
*/

/*transmitter should be MRK1000*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Stepper.h>

RF24 radio(6, 7); // CE, CSN
const byte address[][6] = {"00001", "00002"};
void setup() {
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  int steps1 = 3200;  //revolutions specific to stepper motor
  radio.openWritingPipe(address[0]);
  radio.write(&steps1, sizeof(steps1));
  Serial.println(steps1);
  delay(500);
  int steps2 = 3600;
  radio.openWritingPipe(address[1]);
  radio.write(&steps2, sizeof(steps2));
  Serial.println(steps2);
  delay(500);
}
