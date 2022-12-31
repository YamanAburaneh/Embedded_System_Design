//MAX6675-K-Type-Thermocouple

#include "max6675.h"

int soPin = 4;// SO=Serial Out
int csPin = 5;// CS = chip select CS pin
int sckPin = 6;// SCK = Serial Clock pin
MAX6675 Module(sckPin, csPin, soPin);// create instance object of MAX6675

void setup() {
  
  Serial.begin(9600);// initialize serial monitor with 9600 baud
  Serial.println("MAX6675"); 
  
}

void loop() {
  // basic readout test, just print the current temp
   Serial.print("C = "); 
   Serial.println(Module.readCelsius());
   delay(1000);
}
