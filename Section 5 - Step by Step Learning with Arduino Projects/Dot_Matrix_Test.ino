#include "LedControl.h"

const int Data_Pin = 2;
const int CS_Pin = 3;
const int CLK_Pin = 4;

LedControl lc = LedControl(Data_Pin, CLK_Pin, CS_Pin, 1);

byte smiley[8] =
{
    B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100
};

byte sad[8] =
{
    B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100
};

void setup()
{
    lc.shutdown(0, false);
    lc.setIntensity(0, 6);
    lc.clearDisplay(0);
    randomSeed( analogRead(A0));
}

void loop()
{
    for (int rows = 0; rows < 8; rows++)
    {
        lc.setRow(0, rows, smiley[rows]);
    }
    delay(1000);

    for (int rows = 0; rows < 8; rows++)
    {
        lc.setRow(0, rows, sad[rows]);
    }
    delay(1000);
}
