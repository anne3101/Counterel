#include <LedControl.h>


#include "LedControl.h"
#include "Arduino.h"

LedControl lc = LedControl(12, 10, 11, 4); // Pins: DIN,CLK,CS, see Youtube tutorial for details, num displays connected

int no_number[] = 
{
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

int zero[] = //8x5
{
  0B00100,  // digit 0
   0B01010,
   0B10001,
   0B10001,
   0B10001,
   0B10001,
   0B01010,
   0B00100
};

int one[] = //8x5
{
   0B00010,  // digit 1
   0B00110,
    0B01010,
    0B10010,
    0B00001,
    0B00001,
    0B00001,
    0B00001
};

int two[] = //8x5
{
    0B00100,  // digit 2
    0B01010,
    0B10001,
    0B00001,
    0B00010,
    0B00100,
    0B01000,
    0B11111
};

int three[] = //8x5
{
    0B01110,  // digit 3
    0B10001,
    0B00001,
    0B00110,
    0B00001,
    0B10001,
    0B01010,
    0B00100
};

int four[] = //8x5
{
    0B00010,  // digit 4
    0B00110,
    0B01010,
    0B10010,
    0B11111,
    0B00010,
    0B00010,
    0B00010
};


int five[] = //8x5
{
    0B11111,  // 5
    0B10000,
    0B10000,
    0B11110,
    0B00011,
    0B00001,
    0B00011,
    0B11110
};

int six[] = //8x5
{
    0B00110,  // 6
    0B01001,
    0B11000,
    0B11110,
    0B10011,
    0B10001,
    0B11011,
    0B01110
};

int seven[] = //8x5
{
    0B11111,  // 7
    0B00001,
    0B00010,
    0B11111,
    0B01000,
    0B01000,
    0B10000,
    0B10000
};

int eight[] = //8x5
{
    0B01110,  // 8
    0B10001,
    0B10001,
    0B01110,
    0B10011,
    0B10001,
    0B10001,
    0B01110
};

int nine[] = //8x5
{
    0B01110,  // 9
    0B10001,
    0B10011,
    0B01111,
    0B00001,
    0B00001,
    0B10001,
    0B01110
};

int * getSegment(char character){
    switch(character) {
        case ' ': return no_number;  break;
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

byte stringToByte(String number){
  byte result = 0;
  byte multiplier = 1;
  for (int i = 0; i < 8; i++){
    result += number[i] * multiplier;
    multiplier *= 2;
  }
  return result;
}

void showNumber(int mynum) {
    String s_num = String(mynum);
    while(s_num.length() < 5) {
      String converted_num;  
      converted_num += ' ';
      s_num = converted_num.concat(s_num);
    }
    int combined_arr [8][5];
    for (int digit = 0; digit < 5; digit++){
        for (int i = 0; i < 8; i++){
            combined_arr[i][digit] = getSegment(s_num.charAt(digit))[i];
        }
    }

    String str_digit1 [8]; 
    String str_digit2 [8]; 
    String str_digit3 [8]; 
    String str_digit4 [8]; 
    String str_digit5 [8]; 
    for(int i = 0; i < 8; i++){
        str_digit1[i] = String(byte (combined_arr[i][0]));
        str_digit2[i] = String(byte (combined_arr[i][1]));
        str_digit3[i] = String(byte (combined_arr[i][2]));
        str_digit4[i] = String(byte (combined_arr[i][3]));
        str_digit5[i] = String(byte (combined_arr[i][4]));
    }  

    //segment 3: Ziffer1(1-5) leer(1) Ziffer2(1-2)
    String str_segment3 [8];
    for (int i = 0; i < 8; i++) {
        str_segment3[i] = str_digit1[i].charAt(3);
        str_segment3[i] += str_digit1[i].charAt(4);
        str_segment3[i] += str_digit1[i].charAt(5);
        str_segment3[i] += str_digit1[i].charAt(6);
        str_segment3[i] += str_digit1[i].charAt(7);
        str_segment3[i] += '0';
        str_segment3[i] += str_digit2[i].charAt(3);
        str_segment3[i] += str_digit2[i].charAt(4);
    }
    //segment 2: Ziffer2(3-5) leer(1) Punkt(1) leer(1) Ziffer3(1-2)
    String str_segment2 [8];
    for (int i = 0; i < 8; i++) {
        str_segment2[i] = str_digit2[i].charAt(5);
        str_segment2[i] += str_digit2[i].charAt(6);
        str_segment2[i] += str_digit2[i].charAt(7);
        str_segment2[i] += '0';
        str_segment2[i] += '0';
        str_segment2[i] += '0';
        str_segment2[i] += str_digit3[i].charAt(3);
        str_segment2[i] += str_digit3[i].charAt(4);
    }
    str_segment2[7][4] = '1';
    //segment 1: Ziffer3(3-5) leer(1) Ziffer 4(1-4)
    String str_segment1 [8];
    for (int i = 0; i < 8; i++) {
        str_segment1[i] = str_digit3[i].charAt(5);
        str_segment1[i] += str_digit3[i].charAt(6);
        str_segment1[i] += str_digit3[i].charAt(7);
        str_segment1[i] += '0';
        str_segment1[i] += str_digit4[i].charAt(3);
        str_segment1[i] += str_digit4[i].charAt(4);
        str_segment1[i] += str_digit4[i].charAt(5);
        str_segment1[i] += str_digit4[i].charAt(6);
    }
    //segment 0: Ziffer4(5) leer(1) Ziffer5(1-5) leer(1)
    String str_segment0 [8];
    for (int i = 0; i < 8; i++) {
        str_segment0[i] = str_digit4[i].charAt(7);
        str_segment0[i] += '0';
        str_segment0[i] += str_digit5[i].charAt(3);
        str_segment0[i] += str_digit5[i].charAt(4);
        str_segment0[i] += str_digit5[i].charAt(5);
        str_segment0[i] += str_digit5[i].charAt(6);
        str_segment0[i] += str_digit5[i].charAt(7);
        str_segment0[i] += '0';
    }

  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i, stringToByte(str_segment0[i]));
    lc.setRow(1,i, stringToByte(str_segment1[i]));
    lc.setRow(2,i, stringToByte(str_segment2[i]));
    lc.setRow(3,i, stringToByte(str_segment3[i]));
  }
}


// Put values in arrays


void setup() {
  // put your setup code here, to run once:
  for(int display_index=0; display_index<4; display_index++) {
     lc.shutdown(display_index, false); // Wake up displays
     lc.setIntensity(display_index, 5); // Set intensity levels
     lc.clearDisplay(display_index);  // Clear Display
  }
}

void loop() {
    //lc.setLed(0, 1, 9, true);
  // put your main code here, to run repecharAtedly:
  int test_num = 4;
  showNumber(test_num);
}
