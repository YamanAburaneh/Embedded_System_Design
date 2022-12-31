// Pins
const uint8_t encoder_pin = 2;
volatile byte pulses;

//Global Variable
volatile uint8_t flag = 0;

// EICRA : External Interrupts Control Register
// EIMSK : External Interrupts Mask Register
// ISR   : Interrupt Service Routine
// ISC0n : Interrupt Sense Control of INT0 
// (00=Low Logic Level/10=falling edge/11=rising edge/01=Any Logical change) 

void setup(){
  Serial.begin(9600);
  //Set button pin to be input with pullup
  DDRD  &= ~(1 << encoder_pin); //b00000100
  PORTD |= (1 << encoder_pin);  //b00000100

  //Set LED pin to be Output
  DDRD |= (1 << led_pin)

  //Falling edge of INT0 to generate interrupt (b00000010)
  EICRA =  (1 << ISC01) | EICRA //Set bit 1
  EICRA = ~(1 << ISC00) & EICRA //clear bit 0

  //Enable interrupts for INT0
  EIMSK = (1 << INT0) | EIMSK 

  //Enable global interrupts
  sei();

  //Disable global interrupts
  // cli();
}

void loop(){
  if (flag){
    flag = 0;
  }
}

ISR(INT0_vect){
  flag = 1;
}