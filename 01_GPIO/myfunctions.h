/************************************************************
 * Project   : My Arduino Nano Functions
 * File      : myfunctions.h
 * Author    : Jitterbytes | Sarvesh 
 * Date      : 17.09.25
 * 
 * Description:
 *   This is the MAIN HEADER FILE for my custom implementations
 *   of Arduino-like functions for Nano.
 *   As I continue -> new functions will be added here
 *   and older ones may be improved.
 *
 * Note:
 *   Always refer to the DATE above to ensure you are using
 *   the latest version of this header file.
 ************************************************************/

#pragma once // using this instead of the traditional header guards

#ifdef __cplusplus
extern "C" {
#endif

/*Pin Definition*/
#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define D8 8
#define D9 9
#define D10 10
#define D11 11
#define D12 12
#define D13 13
#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define A4 18
#define A5 19
#define A6 20
#define A7 21

/*Macros Definition*/
#define input 0
#define output 1

#define high 22
#define low 23

void mypinMode(int pin, int mode);
void mydigitalWrite(int pin, int level);
int mydigitalRead(int pin);


















#ifdef __cplusplus
}
#endif
