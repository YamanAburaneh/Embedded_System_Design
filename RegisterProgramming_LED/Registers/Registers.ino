const uint8_t btn_pin = 2;
const uint8_t led_pin = 5;

// DDRD   = Direction Register (Input=0/Output=1) of Port D
// PORTD  = if Output --> Set Pin State (1=High/0=LOW)
//             Input  --> Set Pullup Resistor State (1=Enable/0=Disable)
// PIND   = Read the state of Port D pins (Bxxxxxxxx)
// _BV(x) = Bitwise Left Shift Operation from 1 (1 << x) [Macro]

void setup() {
  DDRD = B00100000;  //Set PIN 5 to output and PIN 2 to Input
  PORTD = B00000100; //Enable internal Pullup resistor for PIN 2 and Write LOW to PIN 5
}

void loop() {
  int btn = (PIND & (1 << btn_pin) >> btn_pin); //Read Input of PIN 2
  Serial.println(btn);
  if (btn == LOW){
    PORTD = (1 << led_pin) | PORTD; //ACtivate PIN 5 (Set to High)
    
  }
  else {
    PORTD = (1 << led_pin) & PORTD; //Clear PIN 5 (Set to Low)
  }

}
