void setup() {
  Serial.begin(9600);   // start the serial monitor at 9600 baud
}

void loop() {
 // check if there is data available in the serial monitor
    int angle = Serial.parseInt();  // read the data as an integer
    if (angle > 0){
    Serial.println(angle);
    delay(300);
    }
    else {
      
    }
}
