# 01_GPIO   

LED is connected at **D2** pin of the Arduino Nano board.  
Normally, we can use `digitalWrite()` to turn it ON/OFF.  

But here, I’m doing it at **register level** instead of using Arduino libraries — basically creating _my own Arduino functions_ for the Nano.  

From the pinout diagram:  
- **D2 → PD2** (Port D of ATmega328p)  
- Our job: **toggle PD2, which is a bit of the Port D register**  



## 📑 Navigation  

- [How to access it?](#-how-to-access-it)  
- [LED Patterns](#-led-patterns)  
- [Custom Arduino-like Functions](#-custom-arduino-like-functions)  
- [Learnings](#-learnings)  



## 🔹 How to access it?  

For GPIO control in AVR, three main registers matter:  
- `DDRx` → Data Direction Register (sets pin as input/output)  
- `PORTx` → Output Register (writes HIGH/LOW when pin is output)  
- `PINx` → Input Register (reads value when pin is input)  

For `PD2`, we’ll use DDRD and PORTD.  

**Normal Arduino code:**  
- `setup()` → `pinMode()` sets direction  
- `loop()` → `digitalWrite()` toggles pin  

**Register level code:**  
- `setup()` → set `DDRD2` as output  
- `loop()` → set/clear `PORTD2`  

To do this:  
- `DDRD` (0x2A memory address) → set bit with OR operator  
- `PORTD` (0x2B memory address) → set/clear bit with OR, AND (or XOR)  

Since `DDRD` and `PORTD` are macros in Arduino IDE, I used:  
- `ddrd_ptr` → pointer for DDRD  
- `portd_ptr` → pointer for PORTD  

👉 Check out `blink.ino` for the implementation.  



## 🔹 LED Patterns  

Next, I connected multiple LEDs. To keep it simple, I chose pins on **PORTD**:  
- **D2 → D7** → mapped to **PORTD2 → PORTD7**  

### Interesting thing  
- ATmega328p is an **8-bit microcontroller** with 8-bit registers.  
- But not all bits are exposed as GPIO headers on Nano/UNO.  
  - `PORTD0` and `PORTD1` are reserved for **UART (RX/TX)**.  
- On Arduino Mega, you get more headers → closer to exposing all register bits.  

So with 6 LEDs (D2–D7):  
1. Declare pointer globally (if you put it in `setup()`, it won’t work in `loop()`).  
2. Turn ON/OFF all 6 LEDs at once.  
3. Try different patterns.  

👉 Check out `led_patterns.ino` for code.  



## 🔹 Custom Arduino-like Functions  

### `mypinMode()`  
Recreating Arduino’s `pinMode()` at register level.  
👉 Implementation in `myfunctions.c & myfunctions.h`  

### `mydigitalWrite()`  
Recreating `digitalWrite()`.  
👉 Implementation in `myfunctions.c & myfunctions.h`   

### `mydigitalRead()`  
Steps are similar → just read the bit level of the pin.  
👉 Implementation in `myfunctions.c & myfunctions.h`   

## 📝 Learnings  

- AVR GPIO control revolves around **3 registers**:  
  - **DDRx** → set direction (0 = input, 1 = output)  
  - **PORTx** → write data (0 = LOW, 1 = HIGH, when pin = output)  
  - **PINx** → read data (returns pin state, when pin = input)  
- To manipulate bits: use **OR, AND, XOR**.  
- Pointers are needed to access registers via memory addresses.  
- Pull-up/pull-down not covered yet → will do later.  
