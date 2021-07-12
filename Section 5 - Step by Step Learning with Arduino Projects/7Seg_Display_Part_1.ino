#include "LedControl.h"

const int Data_Pin = 2;
const int CS_Pin = 3;
const int CLK_Pin = 4;

LedControl Seven_Seg_Display = LedControl(Data_Pin, CLK_Pin, CS_Pin, 1);

void setup()
{
  Seven_Seg_Display.shutdown(0, false);
  Seven_Seg_Display.setIntensity(0, 5);
}

void loop()
{

  Seven_Seg_Display.setChar(0, 6, 'A', false); // A
  Seven_Seg_Display.setRow(0, 5, B00000101);   // r
  Seven_Seg_Display.setChar(0, 4, 'd', false); // d
  Seven_Seg_Display.setRow(0, 3, B00011100);   // u
  Seven_Seg_Display.setRow(0, 2, B00010000);   // i
  Seven_Seg_Display.setRow(0, 1, B00010101);   // n
  Seven_Seg_Display.setRow(0, 0, B00011101);   // o
  delay(2000);
  Seven_Seg_Display.clearDisplay(0);
  delay(2000);
}
