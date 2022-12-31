#include <Servo.h>

Servo servoMotor;  // create a servo object
void setup() {
  servoMotor.attach(9);  // attach the servo to pin 9
  Serial.begin(9600);   // start the serial monitor at 9600 baud
}

void loop() {
  
  if (Serial.available()) {  // check if there is data available in the serial monitor

    String angletext = Serial.readStringUntil('\r\n');
    int angle =  angletext.toInt(); // read the data as an integer
    servoMotor.write(angle);  // move the servo to the specified angle
    Serial.println(angle);
    delay(1000);
    
  }
}
