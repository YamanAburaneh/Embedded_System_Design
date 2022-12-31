 // Library for DHT sensors 
 #include <dht.h>
 // EEPROM Library, NOT USED
 #include <EEPROM.h>
 // I2C library
 #include <Wire.h> 
 
 #define DHTPIN 2     // Digital pin where DHT is connected
 
 // Inicialize the sensor 
 dht DHT;
 
 int addr=0; //first address
 int maxB=32000; //~max EEPROM memory
 
 
 //functions for EEPROM
 void i2c_eeprom_write_byte( int deviceaddress, unsigned int eeaddress, byte data ) {
     int rdata = data;
     Wire.beginTransmission(deviceaddress);
     Wire.write((int)(eeaddress >> 8)); // MSB
     Wire.write((int)(eeaddress & 0xFF)); // LSB
     Wire.write(rdata);
     Wire.endTransmission();
 
     delay (500);
   }
 
   // address is a page address, 6-bit end will wrap around
   // also, data can be maximum of about 30 bytes, because the Wire library has a buffer of 32 bytes
   void i2c_eeprom_write_page( int deviceaddress, unsigned int eeaddresspage, byte* data, byte length ) {
     Wire.beginTransmission(deviceaddress);
     Wire.write((int)(eeaddresspage >> 8)); // MSB
     Wire.write((int)(eeaddresspage & 0xFF)); // LSB
     byte c;
     for ( c = 0; c < length; c++)
       Wire.write(data[c]);
     Wire.endTransmission();
   }
 
   byte i2c_eeprom_read_byte( int deviceaddress, unsigned int eeaddress ) {
     byte rdata = 0xFF;
     Wire.beginTransmission(deviceaddress);
     Wire.write((int)(eeaddress >> 8)); // MSB
     Wire.write((int)(eeaddress & 0xFF)); // LSB
     Wire.endTransmission();
     Wire.requestFrom(deviceaddress,1);
     if (Wire.available()) rdata = Wire.read();
     return rdata;
   }
 
   // not read more than 30 or 32 bytes at a time
   void i2c_eeprom_read_buffer( int deviceaddress, unsigned int eeaddress, byte *buffer, int length ) {
     Wire.beginTransmission(deviceaddress);
     Wire.write((int)(eeaddress >> 8)); // MSB
     Wire.write((int)(eeaddress & 0xFF)); // LSB
     Wire.endTransmission();
     Wire.requestFrom(deviceaddress,length);
     int c = 0;
     for ( c = 0; c < length; c++ )
       if (Wire.available()) buffer[c] = Wire.read();
   }
 
 // Configura Arduino 
 void setup() {
   Wire.begin(); // initialise the connections
   Serial.begin(9600); 
 }
 
 void loop() {
   int d = 2000; //pause in miliseconds 
  
   DHT.read11(DHTPIN);
   for (int i=addr;i<maxB;i=i+2){ //new loop to try to save every value in the EEPROM and then print them
     i2c_eeprom_write_byte(0x50, i, (byte)DHT.temperature);    //write each temperature reading
     i2c_eeprom_write_byte(0x50, i+1, (byte)DHT.humidity);     //write each humidity reading
     
     byte t = i2c_eeprom_read_byte(0x50, i); //read each temperature value
     int t2 = map(t, 0, 255, 0, 30);
     Serial.print("Temp: ");
     Serial.println(t2);                      //print through serial
     byte h = i2c_eeprom_read_byte(0x50, i+1); //read each humidity value
     int h2 = map(h, 0, 255, 0, 80);
     Serial.print("Humid: ");
     Serial.println(h2);                      //print through serial
     
     delay (d); //this delay will determine the interval between readings
   }
   
 }