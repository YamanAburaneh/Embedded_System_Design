// Convert Potentiometer analog input to color Hue, Saturation, and Luminance (HSL) values 
// and then output the converted RGB PWM values to their respective LEDs.

#include "math.h"
#define DEG_TO_RAD(X) (M_PI*(X)/180)

// Pin initialization
const int ledRed = 9;
const int ledGreen = 10;
const int ledBlue = 11;
const int potPin = A0; 

// Hue, Saturation, and Luminance
float H = 0;
const float S = 255;
const float L = 255;

// RGB colorspace
int rgbColour[3];

void setup() {
 // Start off with the LEDs off.
  setColourRgb(0,0,0);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(potPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);
  int mode = map(potValue, 0, 1023, 0, 360);
  H = mode;
  hsi2rgb(H, S, L, rgbColour);
  setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
  Serial.print("Hue: "); Serial.print(H);
  Serial.print(" Saturation: "); Serial.print(S);
  Serial.print(" Luminance: "); Serial.print(L);
  Serial.print(" Red: "); Serial.print(rgbColour[0]);
  Serial.print(" Green: "); Serial.print(rgbColour[1]);
  Serial.print(" Blue: "); Serial.println(rgbColour[2]);
}

// Function to set the colors of LEDs
void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(ledRed, red);
  analogWrite(ledGreen, green);
  analogWrite(ledBlue, blue);
}

// Function takes H, S, I, and a pointer to the returned RGB colorspace converted vector. 
// the vector rgb will contain red, green, and blue calculated values.
void hsi2rgb(float H, float S, float I, int* rgb) {
  int r, g, b;
  H = fmod(H,360); // cycle H around to 0-360 degrees
  H = 3.14159*H/(float)180; // Convert to radians.
  S = S>0?(S<1?S:1):0; // clamp S and I to interval [0,1]
  I = I>0?(I<1?I:1):0;
    
  if(H < 2.09439) {
    r = 255*I/3*(1+S*cos(H)/cos(1.047196667-H));
    g = 255*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
    b = 255*I/3*(1-S);
  } else if(H < 4.188787) {
    H = H - 2.09439;
    g = 255*I/3*(1+S*cos(H)/cos(1.047196667-H));
    b = 255*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
    r = 255*I/3*(1-S);
  } else {
    H = H - 4.188787;
    b = 255*I/3*(1+S*cos(H)/cos(1.047196667-H));
    r = 255*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
    g = 255*I/3*(1-S);
  }
  rgb[0]=r;
  rgb[1]=g;
  rgb[2]=b;
}
