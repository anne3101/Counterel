
#include "LedControl.h"

LedControl lc=LedControl(12,10,11,1);  // Pins: DIN,CLK,CS, see Youtube tutorial for details, num displays connected

// Put values in arrays
byte zero[] = //8x5
{
   B00100,  // digit 0
   B01010,
   B10001,
   B10001,
   B10001,
   B10001,
   B01010,
   B00100
};

byte one[] = //8x5
{
   B00010,  // digit 1
   B00110,
   B01010,
   B10010,
   B00001,
   B00001,
   B00001,
   B00001
};

byte two[] = //8x5
{
   B00100,  // digit 2
   B01010,
   B10001,
   B00001,
   B00010,
   B00100,
   B01000,
   B11111
};

byte three[] = //8x5
{
   B01110,  // digit 3
   B10001,
   B00001,
   B00110,
   B00001,
   B10001,
   B01010,
   B00100
};

byte four[] = //8x5
{
   B00010,  // digit 4
   B00110,
   B01010,
   B10010,
   B11111,
   B00010,
   B00010,
   B00010
};s

void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0,false);  // Wake up displays
  lc.setIntensity(0,5);  // Set intensity levels
  lc.clearDisplay(0);  // Clear Display
}

void loop() {
  // put your main code here, to run repeatedly:

}
