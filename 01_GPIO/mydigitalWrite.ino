/* Register Level Programming (mydigitalWrite Function) */
/* So normal mydigitalWrite() expects 2 args pin number and level (high or low)
*  Since we already created mypinMode function i think it will exactly the same ohh yess it will be XD lol
*  Coz all the steps will be same
*  Based on Pin number -> get Port -> get relative bit index -> Based on the level either set or clear the that bit of the register
*/

#include "myfunctions.h"

void setup() {
  // put your setup code here, to run once:
  mypinMode(2, output);

}

void loop() {
  // put your main code here, to run repeatedly:
  mydigitalWrite(2, high);
  delay(500);
  mydigitalWrite(2, low);
  delay(500);

}
