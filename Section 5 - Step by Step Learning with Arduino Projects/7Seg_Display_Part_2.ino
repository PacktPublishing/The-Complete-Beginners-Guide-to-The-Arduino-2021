#include "LedControl.h"

const int Data_Pin = 2;
const int CS_Pin = 3;
const int CLK_Pin = 4;

int Last_Amount_Of_Digits;

LedControl Seven_Seg_Display = LedControl(Data_Pin, CLK_Pin, CS_Pin, 1);

void setup()
{
  Seven_Seg_Display.shutdown(0, false);
  Seven_Seg_Display.setIntensity(0, 5);
}


void Display_Digits(long Number)
{
  // is the number within range?
  if (Number > 99999999 || Number < -9999999) return;

  // is the number to display positive or negative?
  bool negative = false;
  if (Number < 0) negative = true;

  // How many digits does the number have?
  int Amount_Of_Digits;
  if (Number == 0) Amount_Of_Digits = 1;
  else Amount_Of_Digits = floor(log10(abs(Number))) + 1;  
  if (Amount_Of_Digits < Last_Amount_Of_Digits)
  {
    Seven_Seg_Display.clearDisplay(0);
  }
  Last_Amount_Of_Digits = Amount_Of_Digits;

  // put the digits onto the display
  Number = abs(Number);
  for (int Segment = 0; Segment < Amount_Of_Digits; Segment++)
  {
    Seven_Seg_Display.setDigit(0, Segment, Number % 10, false);
    Number = Number / 10;
  }

  // put a negative symbol if negative number
  if (negative == true) Seven_Seg_Display.setChar(0, Amount_Of_Digits, '-', false);
  else Seven_Seg_Display.setChar(0, Amount_Of_Digits, ' ', false);
}


void loop()
{

  Display_Digits(123456);
  delay(1000);
  Display_Digits(-98765);
  delay(1000);

}
