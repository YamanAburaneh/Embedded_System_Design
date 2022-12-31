const int potpin = A0;
//char charRead;
char dataStr[100] = "";
char buffer[7];

void setup(){
  Serial.begin(9600);
  pinMode(potpin, INPUT);
}

void loop(void){
 dataStr[0] = 0; //clean out string

 int sensorValue = analogRead(potpin);
 //----------------------- using c-type ---------------------------
 //convert floats to string and assemble c-type char string for writing:
 ltoa( millis(),buffer,10); //convert long to charStr
 strcat(dataStr, buffer); //add it to the end
 strcat( dataStr, ", "); //append the delimiter

 dtostrf(sensorValue, 5, 1, buffer);  //5 is minimum width, 1 is precision; float value is copied onto buff
 strcat( dataStr, buffer); //append the converted float
 strcat( dataStr, 0); //terminate correctly 
 Serial.println(dataStr);
 delay(1000);  
} 