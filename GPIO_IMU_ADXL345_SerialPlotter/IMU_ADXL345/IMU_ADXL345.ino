#include <Wire.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

void setup(void) 
{
   Serial.begin(9600);  
   if(!accel.begin())
   {
      Serial.println("No ADXL345 sensor detected.");
      while(1);
   }
}
void loop(void) 
{
   sensors_event_t event; 
   accel.getEvent(&event);

   int x= event.acceleration.x;
   int y= event.acceleration.y;
   int z= event.acceleration.z;

  //  Serial.print("X: "); Serial.print(x); Serial.print("  ");
  //  Serial.print("Y: "); Serial.print(y); Serial.print("  ");
  //  Serial.print("Z: "); Serial.print(z); Serial.print("  ");
  //  Serial.println("m/s^2 ");

Serial.print(x);
Serial.print(",");
Serial.print(y);
Serial.print(",");
Serial.println(z);

   delay(100);
}