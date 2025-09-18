# 1_GPIO
Let's begin then, Led is connected at D2 pin of the Arduino Nano Board.  
Normally when can use `digitalWrite()` to turn ON | OFF.

But I want to do it in Register Level instead of using the Arduino Libraries we will try & create _my arduino functions_ for the Nano.  
For this we need to look into the pinout diagram of the Nano   
D2 is mapped to PD2 (which is Port D of the Atmega328p)  
**our job is to toggle PD2 which is a bit of the Port D Register**.  

### Now how to access it ??  
For GPIO Control, three main registers matter in AVR  
`DDRx` -> Data Direction Register (sets pin as input/output)  
`PORTx` -> Output Register (writes HIGH/LOW when pin is output)  
`PINx` -> Input Register (reads value when pin is input)  

So, for `PD2` we will use DDRB and PORTB

Now in normal Arduino coding  
`void setup()` -> `pinMode()` sets the direction of the pin output    
`void loop()` -> `digitalWrite()` toggles the pin high / low  

Now in register level coding   
`void setup()` -> `DDRD` register (Need to set `DDRD2` as output)   
`void loop()` -> `PORTD` register (Need to set & clear `PORTB5`)  

To set `DDRD2` as output we need to set that bit high _(mentioned in the datasheet)_  
To turn ON `PORTD2` -> 1 and to turn OFF `PORTD2` -> 0  

To access these registers we need to use pointers  
use the datasheet to know on which address are these registers sitting on   

* **DDRD - Port D Direction Register**   
There will be 2 addresses **0x0A** and **0x2A** we will use **0x2A** as it is **Memeory address of the DDRB** , _0x0A is I/O address_  
> **Set DDRD2 -> To set a bit use OR operator** 

* **PORTD - Port D Data Register**  
Again same here _0x0B -> I/O address_ and **0x2B we will use -> Memory address**  
> **Set and Clear PORTD2 -> To set and clear an bit use OR and AND (or better XOR) but since its my first time lets first Set and then clear**  

So we will create 2 pointers one will be in `void setup()` to set the direction and other will be in `void loop()`
i wanted to use **DDRD** and **PORTD** as my variable but in Arduino IDE ig they are special Macros 
> **DDRD -> ddrd_ptr & PORTD -> portd_ptr**

_**Rest in the Code.. Check out `first.c`**_  

------
### Led Patterns  
So after i did the led blink i am going to connect _few more leds_   
for not making it complex for me we will choose the pins that are connected to the PORT D  
**D2 to D7 are connected to PORTD2 to PORTD7**

**Intersting THing**
- Atmega328p its a **8 bit microcontroller** -> **8 bit wide registers** so logically all the 8 bits should have been _**exposed as GPIO headers**_, but its not on the boards like Nano or UNO. Coz here some pins are internally reserved for other functions
  > **Like PORTD0 and PORTD1 -> They are researved for UART Communication RX and TX.**
- Similarly you see this thing on Arduino UNO Board too, I feel only **Arduino Mega** does the justice with more GPIO Header Pins on the board so that it can expose almost **_every bit of the internal registers to header_**.

> **So if you have Mega with you then you can toggle the whole 8 bits port without missing the bits**

I connected 6 leds D2 to D7 lets play with this make some kind of pattern. Setup is same as the `first.c`  
1. Globally declare the pointer (coz if you just declare it in setup then in loop it wont recognize it -_- i tried that lol)
2. Try to turn and turn off all the 6 leds at the same time
3. Then lets try some patterns 

_**Rest in the Code.. Check out `second.c`**_ 

------
### mypinMode()
Making my own version of the arduino nano function   
`pinMode` **->** `mypinMode()`  

Lets see how to do it...
_**Rest in the Code.. Check out `mypinMode.c`**_

-----------------------------------------------------------------------------------------
### mydigitalWrite()
`digitalWrite` **->** `mydigitalWrite()`  

Again in the code like its mostly written in the header file T-T (like why i am ece)
_**Check out `mypinMode.c`**_

------------------------------------------------------------------------------------------
Now lets get to digitalRead() Function 
it seems like steps are similar
in digital Read we are reading the pin. 

----------------------------------------------------------------------------------------
Well with this GPIO ends.. onto next. 
What i learnt: In AVR to manipulate the registers we have 3 addresses to deal with, Port Direction register | Port Data Register | Port Input Register. with pinmode to make a pin/bit of register as input make it 0 for output make it 1 , with digitalwrite first after the pin is output to make it high we make the bit 1, to make it low  we make the bit 0, with digitalread we simply read the bit return the pin level. Until now i have not gone it pull up and pull down we do that later.
