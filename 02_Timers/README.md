# 02_Timers
Now lets get into timers..wow the datasheet was overwhelming i got lost where to look at i want to replicate delay() -> mydelay()
but for that as much as i know uC uses timers behind the scenes

Damn i got a lot info of how the timers works so its basically 
Clock -> Tick -> Events 
1. Microcontroller Clock
   Atmega328p runs at 16MHz (Nano's Crystal) -> Means 16 Million cycles per second
   So Each cycle happen at 62.5ns i.e ( 1 / 16M )
   So if we directly feed this clock to timer/counter then it increments its counter at every 62.5ns
2. The **Prescaler (Divider)**
   Now the problem is -> counting every 62.5ns is wayy too fast to human scale delays
   Sol: insert a prescaler - a divider circuit.
   Available prescaler (for Timer0) : 1,8,64,256,1024
   Now how this helps the timer say for eg prescaler = 64:
   - Timer tick = 16MHz / 64 = 250Hz 
   - Tick period = 1 / 250MHz = 4us
   - So we won't give 16MHz to clock after prescaling we are now givng 250MHz to the Timer/Counter -> So now counter increments after every 4us and not 62.5ns which is manageable.
3. The Counter Register (TCNTx)
    This registers stores a number that is incremented after every tick by the counter. Timer0 is 8 but it can hold 0-255 
    Every tick (after prescaler), this counter increments by 1.
    So:
    - with prescaler 64, tick every 4us. In 256 ticks -> overflow after 1024us (256 x 4us)
    *That means Timer0 naturally overflows about 1000 times per seconds at prescale 64*
4. What Happens at Overflow or Compare Match?
  - Overflow -> when counter reaches max (255 for 8 bit , 65535 for 16 bit) it rolls back to 0 and sets a flag.
  - Compare Match ->If you load a value into OCRx, the timer will raise a flag (or toggle a pin) when counter == OCRx.  

5. Interrupts -> lets see if we can do this later

This is all the theory i got to know regarding the timers lets 
Atmega328p has three timers
