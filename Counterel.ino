#include <LedControl.h>
#include <EEPROM.h>

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

LedControl lc = LedControl(12, 10, 11, 4); // Pins: DIN,CLK,CS, see Youtube tutorial for details, num displays connected

const int BUTTON_PIN = 7;

int counter = 0;
const int COUNTER_ADDRESS = 0;
const int FAST_ADD_TICK = 300;
const int TICK = 10;

void setup() {
  // Display setup
  for(int display_index=0; display_index<4; display_index++) {
     lc.shutdown(display_index, false); // Wake up displays
     lc.setIntensity(display_index, 5); // Set intensity levels
     lc.clearDisplay(display_index);  // Clear Display
  }

  // Initialize counter
  EEPROM.get(COUNTER_ADDRESS, counter);

  // Define pin #07 as input and activate the internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Define internal led as output
  pinMode(LED_BUILTIN, OUTPUT);

  // DEBUG, DELETE
  counter = 0;

  display_counter();
}

void display_counter() {
  lc.clearDisplay(0);
  lc.setLed(0, counter / 8, counter % 8, true);
  EEPROM.put(COUNTER_ADDRESS, counter);
}

void sum_to_counter(int delta) {
  counter+=delta;
  display_counter();
}

void fast_change(int delta){
  bool released = false;
  while (!released) {
    if(digitalRead(BUTTON_PIN) != LOW){
      released = true;
    }
    sum_to_counter(delta);
    delay(FAST_ADD_TICK);
  } 
}

void fast_increment() {
  fast_change(1);
}

void fast_decrease() {
  fast_change(-1);
}

void increase_counter(){
  sum_to_counter(1);
}

void decrease_counter(){
  sum_to_counter(-1);
}

void loop() {
    
  // Read the value of the input. It can either be 1 or 0
  int buttonValue = digitalRead(BUTTON_PIN);
  if (buttonValue == LOW) {
    

    bool released = false;
    int current_waiting_time = 0;
    const int MAX_WAITING_TIME = 3000;
    const int DOUBLE_CLICK_WAITING_TIME = 1000;

    while (!released && current_waiting_time < DOUBLE_CLICK_WAITING_TIME) {
      delay(TICK);
      current_waiting_time += TICK;
      released = digitalRead(BUTTON_PIN) != LOW;
    }
    // kept pressing through double click time
    if(!released){
      // increase once
      increase_counter();
      // wait for fast add
      while (!released && current_waiting_time < MAX_WAITING_TIME) {
        delay(TICK);
        current_waiting_time += TICK;
        released = digitalRead(BUTTON_PIN) != LOW;
      }
      if(!released){
        fast_increment();
      }
    }
    else {
    // released before double click time
      while (released && current_waiting_time < DOUBLE_CLICK_WAITING_TIME) {
        delay(TICK);
        current_waiting_time += TICK;
        released = digitalRead(BUTTON_PIN) != LOW;
      }
      // if didn't click again during double click time, just increase once
      if(released){
        increase_counter();
      } else {
      // if did double click, reset current_waiting_time and start substracting flow
        decrease_counter();
        current_waiting_time = 0;
        while (!released && current_waiting_time < MAX_WAITING_TIME) {
          delay(TICK);
          current_waiting_time += TICK;
          released = digitalRead(BUTTON_PIN) != LOW;
        }
        if(!released){
          fast_decrease();
        }
      }
    }    
  }

}
