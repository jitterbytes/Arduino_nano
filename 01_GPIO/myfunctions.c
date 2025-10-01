/************************************************************
 * File      : myfunctions.h
 * Purpose   : Adding mydigitalWrite() and mydigitalRead()
 * Author    : Jitterbytes | Sarvesh 
 * Date      : 17.09.25
 ************************************************************/
#include "myfunctions.h"
#include <stdint.h>

int mydigitalRead(int pin)
{
  int bit_index = 0;
  volatile uint8_t* pin_ptr;

  if(pin <= 7){
    bit_index = pin;
    pin_ptr = (volatile uint8_t*)0x29;
  }
  else if(pin > 7 && pin <= 13){
    bit_index = pin - 8;
    pin_ptr = (volatile uint8_t*)0x23;
  }
  else if(pin > 13 && pin <= 19){
    bit_index = pin - 14;
    pin_ptr = (volatile uint8_t*)0x26;
  }

  // Now here we are reading the bit of the register -> simply return the value at that bit
  if((*pin_ptr)&(1 << bit_index))
    return 1;
  else
    return 0;
}

void mydigitalWrite(int pin, int level)
{
 int bit_index = 0;
 volatile uint8_t* port_ptr;

  if(pin <= 7){
    bit_index = pin;
    port_ptr = (volatile uint8_t*)0x2B;
  }
  else if(pin > 7 && pin <= 13){
    bit_index = pin - 8;
    port_ptr = (volatile uint8_t*)0x25;
  }
  else if(pin > 13 && pin <= 19){
    bit_index = pin - 14;
    port_ptr = (volatile uint8_t*)0x28;
  }

  // Based on level, high -> set and low -> clear
  if(level == high)
    *port_ptr |= (1 << bit_index);
  else
    *port_ptr &= ~(1 << bit_index); 
}

void mypinMode(int pin, int mode)
{
  int bit_index = 0;
  volatile uint8_t* ddr_ptr;

  // Based on the Pin Number -> Got Port -> set the ddr_ptr to correct address  -> Calculated relative bit index 
  if(pin <= 7){
    bit_index = pin;
    ddr_ptr = (volatile uint8_t*)0x2A;
  }  
  else if(pin > 7 && pin <= 13){
    bit_index = pin - 8; 
    ddr_ptr = (volatile uint8_t*)0x24;
  }   
  else if(pin > 13 && pin <= 19){
    bit_index = pin - 14;
    ddr_ptr = (volatile uint8_t*)0x27;
  }

  // Based on the mode -> Either Set or Clear the bit
  if(mode == input)
    *ddr_ptr &= ~(1 << bit_index);
  else
    *ddr_ptr |= (1 << bit_index);
  
}
