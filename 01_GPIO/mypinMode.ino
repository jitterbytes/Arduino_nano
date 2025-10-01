/* Register Level Programming (mypinMode Function) - Go through the README.md */
/* So normal pinMode() expects 2 args pin number and mode(input or output)
*  For pin number Digital Pins are 1 to 13 and Analog are A0 to A7 -> This will be the input to function
*  Step 1: Creating Macros list for all the pin number (digital + analog)
*        : Use If else to Map these pins to different Port 
*  Step 2: Use switch case to assign the ddr_ptr port according to the port + calculate the bit_index
*  Step 3: Based on the mode either set or clear that bit
*/

#include "myfunctions.h"

void setup() {
  // put your setup code here, to run once:
  mypinMode(2,output);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2,HIGH);
  delay(100);
  digitalWrite(2,LOW);
  delay(100);
}
