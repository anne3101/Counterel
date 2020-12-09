
#include "LedControl.h"
#include "digits.cpp"

LedControl lc = LedControl(12, 10, 11, 1); // Pins: DIN,CLK,CS, see Youtube tutorial for details, num displays connected

// Put values in arrays


void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0, false); // Wake up displays
  lc.setIntensity(0, 5); // Set intensity levels
  lc.clearDisplay(0);  // Clear Display
}

void loop() {
  // put your main code here, to run repeatedly:

}
