/* Register Level Programming (LED Patterns) - Go through the README.md */

volatile uint8_t* ddrd_ptr = (volatile uint8_t*)0x2A; // Data Direction Register D
volatile uint8_t* portd_ptr = (volatile uint8_t*)0x2B; // Data Register D


void setup() {
  // put your setup code here, to run once:
  *ddrd_ptr = 0xFF; // Setting all bits of Port D as Output
  *portd_ptr = 0x00; // Making all the bits of Port D as LOW
}

void loop() {
  // put your main code here, to run repeatedly:
  // Port D is D7  D6  D5  D4  D3  D2  D1  D0  

  // Lets turn all the leds from D0 to D7 ON one by one so 0000 0001 -> 0000 0011 -> 0000 0111 -> 0000 1111 -> 0001 1111 -> like this in the end all the led on 1111 1111
  for(uint8_t i=2; i<=7; i++) // for just D2 to D7 start i from 2
  {
    *portd_ptr = *portd_ptr | (1 << i); // better *portd_ptr |= (1 << i);
    delay(200);
  }

  /***********************************************/
  delay(500);
  *portd_ptr = 0x00; //Clearing all the bits 
  delay(500);
  /***********************************************/
  
  // from D7 to D2 -> 1000 0000 -> 1100 0000 -> 1110 0000 -> 1111 0000 -> like this 
  for(uint8_t j=7; j>=2; j--) // from D7 to D2
  {
    *portd_ptr |= (1 << j);
    delay(200);
  }

  /***********************************************/
  delay(500);
  *portd_ptr = 0x00; //Clearing all the bits 
  delay(500);
  /***********************************************/

  // Running Light (Chaser) one dot moving from D2 to D7 and from D7 to D2
  // 0000 0100 -> 0000 1000 -> 0001 0000 -> 0010 0000 -> 0100 0000 -> 1000 0000 -> 0100 0000 -> like this (ahh its tricky lets split it from D2 to D7 and then from D7 to D2)
  
  for(uint8_t i=2; i<=7; i++)
  {
    *portd_ptr = (1 << i);
    delay(100);
  }
  for(int8_t j=7; j>=2; j--) // changing from unsigned to signed chances of overflow
  {
    *portd_ptr = (1 << j);
    delay(100);
  }

  /***********************************************/
  delay(500);
  *portd_ptr = 0x00; //Clearing all the bits 
  delay(500);
  /***********************************************/

  // Wave pattern [cool]
  // 0000 1100 -> 0001 1000 -> 0011 0000 -> 0110 0000 -> 1100 0000 -> 0110 0000 -> 0011 0000 -> 0001 1000 -> 0000 1100
  // adjacent bit manipulation using 2 bit mask with operator i found it very interesting
  for(uint8_t i=2; i<=6; i++)
  {
    *portd_ptr = ((1 << i) | (1 << (i+1))); 
    delay(100);
  }
  for(int8_t j=7; j>=3; j--)
  {
    *portd_ptr = ((1 << j) | (1 << (j-1)));
    delay(100);
  }

  /***********************************************/
  delay(500);
  *portd_ptr = 0x00; //Clearing all the bits 
  delay(500);
  /***********************************************/
}
