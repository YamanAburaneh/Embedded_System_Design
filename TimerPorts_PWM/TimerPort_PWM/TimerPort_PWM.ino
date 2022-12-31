unsigned char* DDRB=(unsigned char*) 0x2A;
unsigned char* ocr0b =(unsigned char*) 0x48;
unsigned char* tccr0a = (unsigned char*) 0x44;
unsigned char* tccr0b = (unsigned char*) 0x45;

void setup() {
  *DDRB= 1 << 5;
  *ocr0b =127;         //Duty Cycle of 50%
  *tccr0a =0b00100011; //Set fast PWM for Timer Counter 0
  *tccr0b =0b00000001; //Pre-scalar
}

void loop() {
  // put your main code here, to run repeatedly:

}
