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

So, for PD2 we will use DDRB and PORTB

Now in normal Arduino coding  
void setup() -> pinMode() sets the direction of the pin output  
void loop() -> digitalWrite() toggles the pin high / low

Now in register level coding 
void setup() -> DDRD register (Need to set DDRD2 as output) 
void loop() -> PORTD register (Need to set & clear PORTB5)

To set DDRD2 as output we need to set that bit high (mentioned in the datasheet)
To turn on PORTD2 -> 1 and to turn off PORTD2 -> 0

To access these registers we need to use pointers
use the datasheet to know on which address are these registers sitting 

DDRD - Port D Direction Register 
There will be 2 addresses 0x0A and 0x2A we will use 0x2A as it is Memeory address of the DDRB , 0x0A is I/O address
Set DDRD2 as high | To set a bit we use OR operator 

PORTD - Port D Data Register
Again same here 0x0B -> I/O address and 0x2B we will use -> Memory address
Set and Clear PORTD2 | To set and clear an bit use OR and AND (or better XOR) but since its my first time lets first Set and then clear

So we will create 2 pointers one will be in setup() to set the direction and other will be in loop()
