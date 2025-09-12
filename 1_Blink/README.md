# 1_Blink
Led is connected at D2 pin of the Arduino Nano Board.
Very simple we used the digitalWrite() to turn on/off the led.

Lets do it in Register Level instead of using the Arduino Libraries we will try & create our own
Look into the pinout diagram of the Nano D2 is mapped to PD2 (which is Port D of the Atmega328p)
so we need to toggle the PD2 pin.

Now how to access it ??

For GPIO Control, three main registers matter in AVR
DDRx -> Data Direction Register (sets pin as input/output)
PORTx -> Output Register (writes HIGH/LOW when pin is output)
PINx -> Input Register (reads value when pin is input)

So, for PB5 we will use DDRB and PORTB

Now in normal Arduino coding  
void setup() -> pinMode() sets the direction of the pin output  
void loop() -> digitalWrite() toggles the pin high / low

Now in register level coding 
void setup() -> DDRB register (Need to set DDR5 as output) 
void loop() -> PORTB register (Need to set & clear PORTB5)

To set DDR5 as output we need to set that bit high (mentioned in the datasheet)
To turn on PORTB5 -> 1 and to turn off PORTB5 -> 0

To access these registers we need to use pointers
use the datasheet to know on which address are these registers sitting 

DDRB - Port D Direction Register 
There will be 2 addresses 0x0A and 0x2A we will use 0x2A as it is Memeory address of the DDRB , 0x0A is I/O address
D7 D6 D5 D4 D3 D2 D1 D0 ==> Set D5 as high | To set a bit we use OR operator 
