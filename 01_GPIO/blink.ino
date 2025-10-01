/* Register Level Programming (LED Blinking) - Go through the README.md */

// using pointer to access the memory address of DDR D
volatile uint8_t* ddrd_ptr = (volatile uint8_t*)0x02A; // using volatile here instructs the compiler not to optimize this & the value at the memory address can change at any time (due to hardware)

//using pointer to access the memory address of Port D
volatile uint8_t* portd_ptr = (volatile uint8_t*)0x2B; 
  
void setup()
{
  *ddrd_ptr = *ddrd_ptr | (1 << 2); // Making the PD2 as Output (1 << 2) -> 0000 0100 and we used OR on the Exisiting value on that memory address
  // or better written as *ddrd_ptr |= (1 << 2) -----> pinMode(2, OUTPUT);

  // Turning Off led in the setup (can be skipped but keep it -> better)
  *portd_ptr = *portd_ptr & ~(1 << 2); // Making PD2 value as 0 ~(1 << 2) -> 1111 1011 [inverted the orginal mask] and used AND on the Existing value on that memory address
  // or *portd_ptr &= ~(1 << 2)
}

void loop()
{
  //Turning ON the led 
  *portd_ptr |= (1 << 2); // -----> digitalWrite(2, HIGH);
  delay(100);
  //Turning OFF the led
  *portd_ptr &= ~(1 << 2); // -----> digitalWrite(2, LOW);
  delay(100);
}
