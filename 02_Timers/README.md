# 02_Timers
Now lets get into timers..wow the datasheet was overwhelming i got lost where to look at i want to replicate delay() -> mydelay()
but for that as much as i know uC uses timers behind the scenes

First i wanted to know how the timers actually works so its basically   
**Clock -> Tick -> Events  [Like this is the flow]**  
1. **Microcontroller Clock**  
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
3. **The Counter Register (TCNTx)**  
    This registers stores a number that is incremented after every tick by the counter. Timer0 is 8 but it can hold 0-255 
    Every tick (after prescaler), this counter increments by 1.
    So:
    - with prescaler 64, tick every 4us. In 256 ticks -> overflow after 1024us (256 x 4us)
    *That means Timer0 naturally overflows about 1000 times per seconds at prescale 64*
4. **What Happens at Overflow or Compare Match?**
     - Overflow -> when counter reaches max (255 for 8 bit , 65535 for 16 bit) it rolls back to 0 and sets a flag.
     - Compare Match ->If you load a value into OCRx, the timer will raise a flag (or toggle a pin) when counter == OCRx.  

5. **Interrupts** -> lets see if we can do this later

This is all the theory i got to know regarding the timers lets 

Atmega328p has three timers/counters 
Timer 0 | Timer 1 | Timer 2
Now which timer to use ? Well all three of them have some differentiating factor which makes it easy for us (this is basically from my understanding)
- Timer 0 : 8 bit -> used for short delays  with simple PWM
- Timer 1 : 16 bit -> used for long delays and very precise timings also PWM
- Timer 2 : 8 bit -> used for short delays , simple PWM and also it has async mode something

For now i will stick with Timer 0 to start with timers.  
directly not creating mydelay() -- I will go through the concepts which i mentioned earlier then recreate this function  
**I got more info about indiviaul Timer and its Register lets see one by one**  
> In the Register there is something like A,B,C well they do have meaning  
> A is for Compare and output stuffs  
> B is for Prescaler and some mode bits  
> C is for extra bits (used for Timer 1 as it is 16 bits)  

## Timer 0 (8 bit General Purpose)
> Used for: Simple delays, millis(), micros(), PWM(fast/phase connect)  
* **TCCR0A (Timer Counter Control Register A)**  
  - Purpose: Set PWM Mode, Toggle OC0A and OC0B pins   
  - Use Case: Want PWM Pin on D5/D6 or toggle pin on compare
* **TCCR0B (Timer Counter Control Register B)**  
  - Purpose: Select Prescaler and mode bits     
  - Use Case: To start timer clock    
* **TCNT0 (Timer Counter Register)**  
  - Purpose: Counter (0 - 255)     
  - Use Case: Read/Write when polling based overflow  
* **OCR0A/OCR0B (Output Compare Register)**  
  - Purpose: Compare Match Values   
  - Use Case: In CTC Mode (Clear timer on Match) or PWM
* **TIMSK0 (Timer Interrupt Mask Register)**  
  - Purpose: Enable Interrupts (Overflow Compare Match)   
  - Use Case: When you want timer interrupt instead of polling
* **TIFR0 (Timer Interrupt Flag Register)**  
  - Purpose: Flag bits (Check if event happened)     
  - Use Case: Use polling mode to see if overflow compare occcured

## Let's now first do Timer 0 overflow blink 
Plan 
1. Timer0 is 8 bit -> it counts 0 to 255.
2. When it overflows it goes from 255 to 0, overflow flag is set
3. We will poll this flag -> each overflow = like a know time delay.
4. Combine overflows until we reach 0.5s or 1s then toggle led

Now what registers we need for this 
1. TCCR0B - Prescaler selection (see the register mapping in the datasheet)  
   Bit 0 - 2 is what we are interested in CS00 - CS02 [Clock Select]
   | CS02 | CS01 | CS00 | Description          |
   |------|------|------|----------------------|
   |  0   |   0  |   0  |   No Clk             |
   |  0   |   0  |   1  | clk/(w/o prescaling) | 
   |  0   |   1  |   0  |   clk/8              |
   |  0   |   1  |   1  |   clk/64             |
   |  1   |   0  |   0  |   clk/256            |
   |  1   |   0  |   1  |   clk/1024           |
   |  1   |   1  |   0  | ext clk src(fall edg)| 
   |  1   |   1  |   1  | ext clk src(rise edg)|
   
    
