# 02_Timers _(Still in Works)_
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
**_Plan_**
1. Timer0 is 8 bit -> it counts 0 to 255.
2. When it overflows it goes from 255 to 0, overflow flag is set
3. We will poll this flag -> each overflow = like a know time delay.
4. Combine overflows until we reach 0.5s or 1s then toggle led

**_Now what registers we need for this_** 
1. **TCCR0A** - Mode Selection Bit 0 - 1 since we want Normal Mode so Bit 0 and Bit 1 (WGM01 , WGM00 -> 0,0)  
2. **TCCR0B** - Prescaler selection (see the register mapping in the datasheet)  
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
3. **TCNT0** - Counter (0-255)
4. **TIFR0** - Bit 0 of this register that is TOV0 is set when an overflow occurs in Timer 0

**_Timming Calculation_**
* System Clock : 16MHz
* Prescaler Option: 1,8,64,256,1024.  
Let's pick **prescaler = 1024**
   * Timer Clk freq = 16MHz / 1024 = 15625 Hz -> each tick happens in = 64us (1 / 15625)
   * Overflow = `256 x 64us approx = 16.384ms` [1 overflow happens in 16.384ms]
   * So to reach `1 sec: 1s / 16.384ms approx 61 overflows`.
That means after **61 overflows** -> toggle LED

_**Rest in the code.. check out `overflow.c`**_
> Now with Overflow even after calculating based on the Overflow timming i am still not getting the accurate 1 seconds for me its more than 1s around 3-4 seconds. So now lets try do it with Compare Match.

## Let's now try to do Timer 0 Compare Match
**_Timming Calculation_**
* System Clock : 16MHz
* Prescaler = 1024
* Timer Clk freq = 16MHz / 1024 = 15625 Hz (15625 ticks happen in 1s)
* Time for 1 tick = 1 / 15625 = 64us
* No: of ticks for 1s = 1 / 64us = approx 15625
* Timer 0 is 8 bit max count is 255, in **CTC mode** timer resets when it reaches OCR0A.
* We cannot use 15625 directly as max is 255 -> need multiple compare match cycles
* So total compare counts needed to reach that delay  

```math
\text{Compare match count} = \frac{\text{Total no: of ticks needed}}{(\text{OCR0A} + 1)}
```
* Now here OCR0A is added with 1 coz OCR0A starts from 0.
* We can choose OCR0A value as 156 then The Compare match count = 15625 / 157 approx 100. -> So we toggle the led every 100 compare matches ~ 1 sec.

**_Registers_**
* TCCR0A -> CTC mode
* TCCR0B -> Prescale 1024
* OCR0A -> 156 (for 1 tick ~64us)
* TCNT0 -> Counter
* TIFR0 -> Poll the OCF0A bit 

**_Logic_**
* OCR0A = 156 → Timer TCNT0 counts: 0, 1, 2, …, 156 → total 157 ticks per cycle (OCR0A + 1).
* Each time the timer TCNT0 reaches 156, it triggers a compare match, and the counter TCNT0 resets to 0 automatically because you’re in CTC mode.
* You keep a separate compare match counter in your code.
* Once this counter reaches 100, you’ve accumulated roughly 1 second of timer time (100 × 157 ticks).

**_Flow of the Program_**
* **Setup**
   * TCCR0A -> CTC mode
   * TCCR0B -> 1024 Prescale
   * OCR0A -> Intialize 156
   * TCNT0 -> Initialize 0
* **Loop**
   * Poll compare match flag OCF0A in TIFR0
   * When flag is set
        * Clear the flag (Write 1 to clear)
        * Increment compare_match_count var
   * When compare_match_count == 100, toggle the led and reset counter

> Now with this the delay is atleast close enough like i am not getting exact 1 seconds i am getting 1.42 seconds which is better 
> In the above code we were continously polling that flag bit to check if its set well this continous check **_wastes CPU cycles_**

## So let's try to do Timer 0 Compare Match Interrupt

We will continue from the previous code. What we want to do is No Polling -> Interrupt  
It should automatically toggle the led when it hits the counter.  
* Timer 0 Interrupts are handled by -> TIMSK0
* Set the OCIE0A bit of TIMSK0 -> Enables Interrupt to Compare Match A
* This allows the timer to automatically trigger an interrupt when TCNT0 == OCR0A
**But here's the thing since OCR0A is 8bit and our led was toggling on the basis of compare_match_count and the timer will call the interrupt when TCNT0 == OCR0A**
* Everything goes in _**ISR (Interrupt Service Routine)**_ [**One thing we will have to keep it short, Its bad manners to have long ISR**]
* Inside ISR
   * Increment compare_match_count
   * When compare_match_count == 100, toggle led
   * reset compare_match_count
* The main loop can be empty as ISR will handle the logic
> Also have to enable global interrupt Enable bit in the **AVR status Register - SREG** if this is not enabled then the no interrupt enable in the control register will work 

**_Registers_**  
* Same as the Compare Match
* TIMSK0 -> Compar Match A interrupt enable bit
* SREG -> Global Interrupt Enable
 
**_Flow of the Program_**
* **Setup**
   * Same as prev
   * TIMSKO ->
   * SREG -> 1 << 7 (Set Global Interrupt Enable)
* **Loop**
   * Can do other tasks or leave empty
* **ISR**
   * increment compare_match_count
   * if compare_match_count == 100
      * toggle led
      * reset compare_match_count

> Well the code was working i was getting 1.71s of toggling but the printf statements even though it should have been 1s delay but it was > coming very late -> Then i read that **_Arduino delay() and millis() are dependent on Timer0 only_** i am not satisfied with this

_**So Im going to do with Timer 2 Compare Match Interrupt as Timer 2 is 8bit so it will be easy for me**_

Well the led and statements were printing properly visually simultanousley, But still the led was toggling at ~1.61 seconds i checked the Arduino delay function comes around 0.98-1s accurately this is not accurate.  
Lets list down the situations i am thinking
* If I stick with 15625 -> Timer clk frequency after 1024 prescaling. since this was not all dividing perfectly 

## Final try on Timer 1 Compare Match Interrupt - _Lets see if i get accuracy in this_
Wow this worked i am lil unsure why this did not work with Timer 0 and 2 i have few points that can point at this issue.
* **Timer width (Resolution)**
   * Timer 0 & 2 -> 8 bit so it can count from 0 to 255 in one go
   * Timer 1 -> 16 bit so it can count form 0 to 65535 in one go
   * So with Timer 1 i dont have to do much calculation like compare match counts and it can easily count to approx 65k without the need to frequent interrupts which i think might add some latency aka Interrupt Latency i will call it which was adding ~ 0.64 seconds
* **Interrupt Load**
   * Since Timer 0 is used by Arduino core for millis() delay() and micros(), so i think i was reusing those it was overloading it.
   * Same i feel for Timer 2 might be used for something else also
> Still if Arduino core is able to get accurate delay with 8 bit Timer, even i should have gotten it. So i will try to do this with true bare metal way where i will skip arduino headers so that they are not blocled or reserved or restrained under the hood. Lets see thats for later first i will get myself comfortable with this register level

_**ONE MORE THING I GOT TO KNOW**_  
Like i already know whatever i am doing here this is only for nano and is not at all portable and Arduino ide already understands those MACROS PORTD and DDRD and all so i cannot use my understanding of manually assigning address to those pointers and playing with them. Arduino Headers for avr/io those have Macros for the registers and like if i used those macros then i wont have to assign them address just i can play with those regsiter writing and reading those.But that code will be portable to multiple AVR based boards like UNO, NANO or MEGA etc.
Lets see when i will use this.  




