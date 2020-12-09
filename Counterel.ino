
#include "LedControl.h"

LedControl lc=LedControl(12,10,11,1);  // Pins: DIN,CLK,CS, see Youtube tutorial for details, num displays connected

// Put values in arrays
byte zero[] = //8x5
{
   B00011000,  // First frame of invader #1
   B00111100,
   B01111110,
   B11011011,
   B11111111,
   B00100100,
   B01011010,
   B10100101
};



void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0,false);  // Wake up displays
  lc.setIntensity(0,5);  // Set intensity levels
  lc.clearDisplay(0);  // Clear Display
}

void loop() {
  // put your main code here, to run repeatedly:

}
