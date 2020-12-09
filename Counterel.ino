
#include "LedControl.h"

LedControl lc = LedControl(12, 10, 11, 1); // Pins: DIN,CLK,CS, see Youtube tutorial for details, num displays connected

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


void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0, false); // Wake up displays
  lc.setIntensity(0, 5); // Set intensity levels
  lc.clearDisplay(0);  // Clear Display
}

void loop() {
  // put your main code here, to run repeatedly:

}
