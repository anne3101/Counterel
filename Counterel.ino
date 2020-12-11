#include <LedControl.h>


#include "LedControl.h"
#include "Arduino.h"

#define unsigned char byte

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
};


byte five[] = //8x5
{
  B11111,  // First frame of invader #1
  B10000,
  B10000,
  B11110,
  B00011,
  B00001,
  B00011,
  B11110
};

byte six[] = //8x5
{
  B00110,  // First frame of invader #1
  B01001,
  B11000,
  B11110,
  B10011,
  B10001,
  B11011,
  B01110
};

byte seven[] = //8x5
{
  B11111,  // First frame of invader #1
  B00001,
  B00010,
  B11111,
  B01000,
  B01000,
  B10000,
  B10000
};

byte eight[] = //8x5
{
  B01110,  // First frame of invader #1
  B10001,
  B10001,
  B01110,
  B10011,
  B10001,
  B10001,
  B01110
};

byte nine[] = //8x5
{
  B01110,  // First frame of invader #1
  B10001,
  B10011,
  B01111,
  B00001,
  B00001,
  B10001,
  B01110
};

LedControl lc = LedControl(12, 10, 11, 1); // Pins: DIN,CLK,CS, see Youtube tutorial for details, num displays connected

// Put values in arrays


void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0, false); // Wake up displays
  lc.setIntensity(0, 5); // Set intensity levels
  lc.clearDisplay(0);  // Clear Display
  lc.setLed(0, 1, 1, true);
}

void loop() {
    lc.setLed(0, 1, 1, true);
  // put your main code here, to run repeatedly:

}
