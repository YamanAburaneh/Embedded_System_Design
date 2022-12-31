//MAX6675-K-Type-Thermocouple
#include "max6675.h"

//Temp. Sensor
int soPin = 4;      // SO=Serial Out
int csPin = 5;      // CS = chip select CS pin
int sckPin = 6;     // SCK = Serial Clock pin

//VFD
const int DI1 = 8;  //RUN
const int DI4 = 10; //RESET
const int AI1 = 9;  //Frequency Control

//LEDs
const int led_red = 30;
const int led_yellow = 31;
const int led_green = 32;

//Optical Sensor
const int opticalSensor = 2;
volatile long pulses; // number of pulses
unsigned long currentMillis;
unsigned long previousMillis;  
const int LOOPTIME = 10;

//Push button
const int PB = 3;   //PushButton


int speedOffset = 50;
int OnTemp = 50;
int MaxPWM = 255;


MAX6675 Module(sckPin, csPin, soPin); // Create instance object of MAX6675


void setup() {

  Serial.begin(9600);// initialize serial monitor with 9600 baud
  Serial.println("Ventix System ON."); 

  pinMode(DI1, OUTPUT);
  pinMode(DI4, OUTPUT);
  pinMode(AI1, OUTPUT);
  pinMode(PB, INPUT);

  pinMode(led_red, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_green, OUTPUT);

  pinMode(opticalSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(opticalSensor), counter, CHANGE);
}

void loop() {

  currentMillis = millis();
  if(currentMillis - previousMillis >= LOOPTIME){
    previousMillis = currentMillis;
      //Serial.print("Pulses: ");
      //Serial.println(pulses);
   }

   float C = Module.readCelsius();  //Degrees Celsius

   int fanSpeed = C + speedOffset;
   float PWM = (fanSpeed/255)*100;
   
   Serial.print("C = "); 
   Serial.print(Module.readCelsius());
   Serial.print("\t"); 
   Serial.print("FAN = %");
   Serial.println(PWM);  
   delay(1000);
   
   C = Module.readCelsius();
   
   
   if(C > OnTemp){
    Serial.println("Fan ON");
    digitalWrite(DI1, LOW);
    analogWrite(AI1, fanSpeed); //0-255
    blinkLED(led_green, 500);
   }
   else{
    Serial.println("Fan OFF");
    digitalWrite(DI1, HIGH);
    analogWrite(AI1, 0);
    blinkLED(led_red, 500);
   }

   int buttonState = digitalRead(PB);
   
   if(buttonState == HIGH){
    digitalWrite(DI4, HIGH);
    Serial.println("RESET");
    digitalWrite(DI1, HIGH);
    analogWrite(AI1, 0);
    blinkLED(led_yellow, 100);
   }
   else{
    digitalWrite(DI4, LOW);}

}

void counter()
{
   //Update count
   if(digitalRead(opticalSensor)==HIGH){
   pulses++;
   Serial.println("Smoke Detected! Fan On MAX");
   digitalWrite(DI1, LOW);
   analogWrite(AI1, MaxPWM); //0-255
   blinkLED(led_green, 500);
   }
 /* else if(digitalRead(opticalSensor)==LOW){
   Serial.println("Smoke Clear! Fan Back to Auto");
   digitalWrite(DI1, HIGH);
   analogWrite(AI1, 0); //0-255
   blinkLED(led_green, 500);
   }*/
}

void blinkLED(int LED, int leng){
  digitalWrite(LED, HIGH);
  delay(leng);
  digitalWrite(LED, LOW);
  delay(leng);
}
/*
int checkError(){
  
}*/