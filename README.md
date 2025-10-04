# Register Level Programming on Arduino nano
This repo is focused on programming the Arduino nano using Registers and not the Arduino functions.  

Get all the docs from the Arduino Website [Link](https://docs.arduino.cc/hardware/nano/)
Also download the Atmega328p Datasheet for Register Level Programming

Flow of this repo  
```
RegisterLevel_Arduino_Nano/
  1_Blink/
  2_Timers/
  3_Interrupts/
  4_ADC/
  5_UART/
  6_SPI/
  7_I2C/
  8_EEPROM/
  9_WDT_Sleep/
  10_Comparator/
  11_Assembly/
``` 

## **1_Blink/**
✅ *Goals: Learn GPIO registers, bitwise ops, LED patterns*

- [X] Blink LED on PD2 (DDRx, PORTx)  
- [X] Blink LED on PB5 (onboard LED)  
- [X] Multiple LEDs D2–D7 patterns (chaser, binary counter)  
- [ ] Create macros: `SET_BIT`, `CLEAR_BIT`, `TOGGLE_BIT`  
- [X] Implement your own `pinMode()`, `digitalWrite()`, `digitalRead()`  

🔗 **Arduino Core Mapping:** `pinMode()`, `digitalWrite()`, `digitalRead()`

## **2_Timers/**
✅ *Goals: Replace software delays with hardware timers*

- [X] Software delay loop  
- [X] Timer0 overflow polling → blink LED  
- [X] Timer1 compare match → 1s blink  
- [ ] Implement `delay_ms()` with timers  
- [X] Timer interrupt toggles LED (no polling)  
- [ ] Generate PWM (Fast PWM, Phase Correct PWM)  
- [ ] Input Capture Unit → measure frequency/duty cycle  

🔗 **Arduino Core Mapping:** `delay()`, `delayMicroseconds()`, `millis()`, `micros()`, `analogWrite()`

## **3_Interrupts/**
✅ *Goals: Event-driven programming*

- [ ] External interrupt INT0 → toggle LED  
- [ ] Pin Change interrupt → read button on multiple pins  
- [ ] Timer interrupt → periodic LED blink  
- [ ] Nested interrupt test (low vs high priority)  

🔗 **Arduino Core Mapping:** `attachInterrupt()`, `detachInterrupt()`

## **4_ADC/**
✅ *Goals: Read analog inputs*

- [ ] Read potentiometer value (ADC single conversion)  
- [ ] Multi-channel ADC (A0–A3)  
- [ ] ADC interrupt → continuous sampling  
- [ ] Map potentiometer value → LED blink speed  
- [ ] Map potentiometer value → PWM brightness  

🔗 **Arduino Core Mapping:** `analogRead()`, `analogReference()`

## **5_UART/**
✅ *Goals: Build serial communication driver*

- [ ] Initialize UART registers (baud rate, frame format)  
- [ ] Transmit single character  
- [ ] Receive single character  
- [ ] Transmit string  
- [ ] Echo received characters back  
- [ ] Command parser: `"ON" → LED ON`, `"OFF" → LED OFF`  

🔗 **Arduino Core Mapping:** `Serial.begin()`, `Serial.print() / Serial.println()`, `Serial.available()`, `Serial.read()`

## **6_SPI/**
✅ *Goals: Learn synchronous communication*

- [ ] Configure Nano as SPI master  
- [ ] Configure Nano as SPI slave  
- [ ] Send/receive byte to another Nano  
- [ ] Control 74HC595 shift register (LEDs)  
- [ ] Receive sensor data (if available)  

🔗 **Arduino Core Mapping:** `SPI.begin()`, `SPI.transfer()`

## **7_I2C/**
✅ *Goals: Master–slave communication via TWI*

- [ ] Configure Nano as I²C master  
- [ ] Write/read byte to EEPROM  
- [ ] Communicate with sensor (e.g., MPU6050, RTC)  
- [ ] Multi-byte transfers  

🔗 **Arduino Core Mapping:** `Wire.begin()`, `Wire.beginTransmission()`, `Wire.write()`, `Wire.endTransmission()`, `Wire.requestFrom()`

## **8_EEPROM/**
✅ *Goals: Use internal non-volatile memory*

- [ ] Write single byte to EEPROM  
- [ ] Read single byte back  
- [ ] Store multiple values (e.g., last LED state)  
- [ ] Simple data logger with EEPROM + UART  

🔗 **Arduino Core Mapping:** `EEPROM.read()`, `EEPROM.write()`, `EEPROM.update()`

## **9_WDT_Sleep/**
✅ *Goals: Reliability & low-power*

- [ ] Enable watchdog timer (reset if stuck)  
- [ ] Blink LED but reset on purpose (WDT demo)  
- [ ] Enter sleep mode (Idle)  
- [ ] Enter deep sleep (Power-down)  
- [ ] Wake up via external interrupt  

🔗 **Arduino Core Mapping:** *(Beyond API — not fully exposed in Arduino)*

## **10_Comparator/**
✅ *Goals: Learn built-in analog comparator*

- [ ] Configure comparator to compare AIN0 vs AIN1  
- [ ] Generate interrupt when threshold is crossed  
- [ ] Use comparator as simple voltage detector (e.g., battery monitor)  

🔗 **Arduino Core Mapping:** *(Beyond API — not exposed in Arduino)*

## **11_Assembly/**
✅ *Goals: Get closer to the hardware*

- [ ] Inline assembly: toggle pin  
- [ ] Simple loop in assembly  
- [ ] Mix C + assembly (critical delay sections)  
- [ ] Compare C vs ASM instruction cycles  

🔗 **Arduino Core Mapping:** *(Beyond API — pro-level assembly experimentss)*
