#include <LedControl.h>
#include <EEPROM.h>

#include "LedControl.h"
#include "Arduino.h"

LedControl lc = LedControl(12, 10, 11, 4); // Pins: DIN,CLK,CS, see Youtube tutorial for details, num displays connected

int no_number[] = 
{
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000
};

int zero[] = //8x5
{
    B01110,  // digit 0
    B10001,
    B10001,
    B10001,
    B10001,
    B10001,
    B10001,
    B01110
};

int one[] = //8x5
{
    B00010,  // digit 1
    B00110,
    B01010,
    B10010,
    B00010,
    B00010,
    B00010,
    B00010
};

int two[] = //8x5
{
    B01110,  // digit 2
    B10001,
    B10001,
    B00001,
    B00010,
    B00100,
    B01000,
    B11111
};

int three[] = //8x5
{
    B01110,  // digit 3
    B10001,
    B00001,
    B00110,
    B00001,
    B00001,
    B10001,
    B01110
};

int four[] = //8x5
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


int five[] = //8x5
{
    B11111,  // 5
    B10000,
    B10000,
    B11110,
    B00011,
    B00001,
    B00011,
    B11110
};

int six[] = //8x5
{
    B00110,  // 6
    B01001,
    B10000,
    B11110,
    B10011,
    B10001,
    B11011,
    B01110
};

int seven[] = //8x5
{
    B11111,  // 7
    B00001,
    B00010,
    B11111,
    B01000,
    B01000,
    B10000,
    B10000
};

int eight[] = //8x5
{
    B01110,  // 8
    B10001,
    B10001,
    B01110,
    B10001,
    B10001,
    B10001,
    B01110
};

int nine[] = //8x5
{
    B01110,  // 9
    B10001,
    B10001,
    B01111,
    B00001,
    B00001,
    B10001,
    B01110
};

int * getSegment(char character){
    switch(character) {
        case '.': return no_number;  break;
        case '0': return zero; break; 
        case '1': return one; break; 
        case '2': return two; break; 
        case '3': return three; break; 
        case '4': return four; break; 
        case '5': return five; break; 
        case '6': return six; break; 
        case '7': return seven; break; 
        case '8': return eight; break; 
        case '9': return nine; break; 
        default: return no_number; break;
  }
}

void showNumber(int mynum) {
    char num_str[5];
    itoa(mynum, num_str, 10);
    int divide = 10000;
    while(mynum < divide && divide > 1) {  
        num_str[4] = num_str[3];
        num_str[3] = num_str[2];
        num_str[2] = num_str[1];
        num_str[1] = num_str[0];
        num_str[0] =  '.';
        divide = divide / 10;
    }
    int combined_arr [8][5];
    for (int digit = 0; digit < 5; digit++){
        for (int i = 0; i < 8; i++){
            combined_arr[i][digit] = getSegment(num_str[digit])[i];
        }
    }

    int segment3 [8];
    for (int i = 0; i < 8; i++) {
        segment3[i] = combined_arr[i][0] << 3; //digit 1 + one empty line
        segment3[i] += combined_arr[i][1] >> 3; //shifted to the right
     }

    int segment2 [8];
    for (int i = 0; i < 8; i++) {
        segment2[i] = (combined_arr[i][1] & B00111) << 5; //last three digits of digit 2  + 3 empty lines 
        segment2[i] += (combined_arr[i][2] >> 3); //two digits of digit three 
    }
    if (mynum >= 1000){
      segment2[7] += 8; //add point
    }

    int segment1 [8];
    for (int i = 0; i < 8; i++) {
        segment1[i] = (combined_arr[i][2] & B00111) << 5; //three digits of three + empty line 
        segment1[i] += (combined_arr[i][3] >> 1); //4 digits of four
    }

    int segment0 [8];
    for (int i = 0; i < 8; i++) {
        segment0[i] = (combined_arr[i][3] & B00001) << 7; //last digit of four + empty line
        segment0[i] += combined_arr[i][4] << 1;
    }

  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i, segment0[i]);
    lc.setRow(1,i, segment1[i]);
    lc.setRow(2,i, segment2[i]);
    lc.setRow(3,i, segment3[i]);
  }
}

const int BUTTON_PIN = 7;

int counter = 0;
const int COUNTER_ADDRESS = 0;
const int FAST_ADD_TICK = 300;
const int TICK = 10;

void display_counter() {
  // lc.clearDisplay(0);
  // lc.setLed(0, counter / 8, counter % 8, true);
  showNumber(counter);
  EEPROM.put(COUNTER_ADDRESS, counter);
}

void setup() {
  // Display setup
  for(int display_index=0; display_index<4; display_index++) {
     lc.shutdown(display_index, false); // Wake up displays
     lc.setIntensity(display_index, 5); // Set intensity levels
     lc.clearDisplay(display_index);  // Clear Display
  }

  // Initialize counter
  EEPROM.get(COUNTER_ADDRESS, counter);
  if(counter < 0){
    counter = 0;
  }

  // Define pin #07 as input and activate the internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Define internal led as output
  pinMode(LED_BUILTIN, OUTPUT);

  // DEBUG, DELETE
  // counter = 0;

  display_counter();
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
    const int MAX_WAITING_TIME = 1000;
    const int DOUBLE_CLICK_WAITING_TIME = 350;

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
