/*
  Debounce

  Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
  press), the output pin is toggled from LOW to HIGH or HIGH to LOW. There's a
  minimum delay between toggles to debounce the circuit (i.e. to ignore noise).*/
#include <Servo.h>

Servo servo1;


const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 12;      // the number of the LED pin
const int ServoPin = 11;

// Variables
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int ButtonPressCount = 0;

const int MaxSpeed = 6;
int val = 90;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 100;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  servo1.attach(ServoPin);
  Serial.begin(9600); 
}

void loop() {

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      Serial.println(ButtonPressCount);

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ButtonPressCount++;
        val = (ButtonPressCount * 15) +90;
        ledState = !ledState; }
    }
  }


  if (ButtonPressCount == MaxSpeed){
    ButtonPressCount = 0; 
    Serial.println("MAX Speed");}
  else{
    Serial.print("Speed ");
    Serial.println(ButtonPressCount);
  }
  
  // set the LED:
  servo1.write(val);
  digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
