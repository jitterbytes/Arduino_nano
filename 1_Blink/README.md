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
void setup() -> DDRB register  
void loop() -> PORTB register

![Alt text](Arduino_nano/1_Blink/img/register.png)
