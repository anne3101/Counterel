#include <LedControl.h>


#include "LedControl.h"
#include "Arduino.h"

LedControl lc = LedControl(12, 10, 11, 4); // Pins: DIN,CLK,CS, see Youtube tutorial for details, num displays connected

String no_number[] = 
{
  "00000",
  "00000",
  "00000",
  "00000",
  "00000",
  "00000",
  "00000",
  "00000"
};

String zero[] = //8x5
{
   "00100",  // digit 0
   "01010",
   "10001",
   "10001",
   "10001",
   "10001",
   "01010",
   "00100"
};

String one[] = //8x5
{
    "00010",  // digit 1
    "00110",
    "01010",
    "10010",
    "00010",
    "00010",
    "00010",
    "00010"
};

String two[] = //8x5
{
    "00100",  // digit 2
    "01010",
    "10001",
    "00001",
    "00010",
    "00100",
    "01000",
    "11111"
};

String three[] = //8x5
{
    "01110",  // digit 3
    "10001",
    "00001",
    "00110",
    "00001",
    "10001",
    "01010",
    "00100"
};

String four[] = //8x5
{
    "00010",  // digit 4
    "00110",
    "01010",
    "10010",
    "11111",
    "00010",
    "00010",
    "00010"
};


String five[] = //8x5
{
    "11111",  // 5
    "10000",
    "10000",
    "11110",
    "00011",
    "00001",
    "00011",
    "11110"
};

String six[] = //8x5
{
    "00110",  // 6
    "01001",
    "11000",
    "11110",
    "10011",
    "10001",
    "11011",
    "01110"
};

String seven[] = //8x5
{
    "11111",  // 7
    "00001",
    "00010",
    "11111",
    "01000",
    "01000",
    "10000",
    "10000"
};

String eight[] = //8x5
{
    "01110",  // 8
    "10001",
    "10001",
    "01110",
    "10011",
    "10001",
    "10001",
    "01110"
};

String nine[] = //8x5
{
    "01110",  // 9
    "10001",
    "10011",
    "01111",
    "00001",
    "00001",
    "10001",
    "01110"
};

String * getSegment(char character){
    switch(character) {
        case ' ': return no_number;  break;
        //case '0': return zero; break; 
        case '1': return one; break; 
        //case '2': return two; break; 
        //case '3': return three; break; 
        //case '4': return four; break; 
        //case '5': return five; break; 
        //case '6': return six; break; 
        //case '7': return seven; break; 
        //case '8': return eight; break; 
        //case '9': return nine; break; 
        default: return no_number; break;
  }
}

byte stringToByte(String number){
  byte result = 0;
  byte multiplier = 1;
  for (int i = 7; i>=0 ; i--){
    result += (number[i]-'0')  * multiplier;
    multiplier *= 2;
  }
  return result;
}

void showNumber(int mynum) {
    String s_num = String(mynum);
    //while(s_num.length() < 5) {
      //String converted_num;  
     // converted_num += ' ';
      //s_num = converted_num.concat(s_num);
    //}
    String combined_arr [8][5];
    for (int digit = 0; digit < 5; digit++){
      Serial.print("New digit\n");
        for (int i = 0; i < 8; i++){
            combined_arr[i][digit] = getSegment(s_num.charAt(digit))[i];
            Serial.print(combined_arr[i][digit]);
            Serial.print("\n");
        }
    }

    //segment 3: Ziffer1(1-5) leer(1) Ziffer2(1-2)
    String str_segment3 [8];
    for (int i = 0; i < 8; i++) {
        str_segment3[i] = combined_arr[i][1].charAt(0);
        str_segment3[i] += combined_arr[i][1].charAt(1);
        str_segment3[i] += combined_arr[i][1].charAt(2);
        str_segment3[i] += combined_arr[i][1].charAt(3);
        str_segment3[i] += combined_arr[i][1].charAt(4);
        str_segment3[i] += '0';
        str_segment3[i] += combined_arr[i][2].charAt(0);
        str_segment3[i] += combined_arr[i][2].charAt(1);
    }
    //segment 2: Ziffer2(3-5) leer(1) Punkt(1) leer(1) Ziffer3(1-2)
    String str_segment2 [8];
    for (int i = 0; i < 8; i++) {
        str_segment2[i] = combined_arr[i][2].charAt(2);
        str_segment2[i] += combined_arr[i][2].charAt(3);
        str_segment2[i] += combined_arr[i][2].charAt(4);
        str_segment2[i] += '0';
        str_segment2[i] += '0';
        str_segment2[i] += '0';
        str_segment2[i] += combined_arr[i][3].charAt(0);
        str_segment2[i] += combined_arr[i][3].charAt(1);
    }
    str_segment2[7][4] = '1';
    //segment 1: Ziffer3(3-5) leer(1) Ziffer 4(1-4)
    String str_segment1 [8];
    for (int i = 0; i < 8; i++) {
        str_segment1[i] = combined_arr[i][3].charAt(2);
        str_segment1[i] += combined_arr[i][3].charAt(3);
        str_segment1[i] += combined_arr[i][3].charAt(4);
        str_segment1[i] += '0';
        str_segment1[i] += combined_arr[i][4].charAt(0);
        str_segment1[i] += combined_arr[i][4].charAt(1);
        str_segment1[i] += combined_arr[i][4].charAt(2);
        str_segment1[i] += combined_arr[i][4].charAt(3);
    }
    //segment 0: Ziffer4(5) leer(1) Ziffer5(1-5) leer(1)
    String str_segment0 [8];
    for (int i = 0; i < 8; i++) {
        str_segment0[i] = combined_arr[i][4].charAt(4);
        str_segment0[i] += '0';
        str_segment0[i] += combined_arr[i][5].charAt(0);
        str_segment0[i] += combined_arr[i][5].charAt(1);
        str_segment0[i] += combined_arr[i][5].charAt(2);
        str_segment0[i] += combined_arr[i][5].charAt(3);
        str_segment0[i] += combined_arr[i][5].charAt(4);
        str_segment0[i] += '0';
        Serial.print(str_segment0[i]);
        Serial.print("\n");
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
  Serial.begin(9600);
  int test_num = 11111;
  showNumber(test_num);
  //for (int i = 0; i < 8; i++){
    //Serial.print(getSegment('1')[i]);
      //      Serial.print("\n");
        //}
}

void loop() {
    //lc.setLed(0, 1, 9, true);
  // put your main code here, to run repecharAtedly:
  //String test = "00001001";
  //lc.setRow(3,1, stringToByte(test));
}
