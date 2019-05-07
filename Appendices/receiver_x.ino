/*
* SMART ERASER SENIOR DESIGN PROJECT
* Stepper Motor Receiver for X-axis              
* by Heather Libecki
* 
* with help from Dejan Nedelkovski
*/

/*receiver should be UNO*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Stepper.h>

// initialize the stepper library on pins 7 through 4
int stepsPerRev = 1600;
Stepper myStepper(stepsPerRev, 7, 6, 5, 4);

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);
  myStepper.setSpeed(120);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    int steps1;
    radio.read(&steps1, sizeof(steps1));
    myStepper.step(steps1);
//    Serial.println("clockwise");
    Serial.println(steps1);
    delay(500);
    myStepper.step(-steps1);
//    Serial.println("counterclockwise");
    Serial.println(steps1);
    delay(500);
  }
}
