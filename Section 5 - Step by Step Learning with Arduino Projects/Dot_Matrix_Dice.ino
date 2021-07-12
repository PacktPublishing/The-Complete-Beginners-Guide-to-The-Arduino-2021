#include "LedControl.h"

int face;
int Last_Face = 10;

const int Data_Pin = 2;
const int CS_Pin = 3;
const int CLK_Pin = 4;
const int Button_Pin = 5;
const int Piezo_Pin = 6;

byte Dice_Faces[6][8] =
{
    {
        B00000000,
        B00000000,
        B00000000,
        B00011000,
        B00011000,
        B00000000,
        B00000000,
        B00000000,
    },
    {
        B00000000,
        B01100000,
        B01100000,
        B00000000,
        B00000000,
        B00000110,
        B00000110,
        B00000000,
    },
    {
        B11000000,
        B11000000,
        B00000000,
        B00011000,
        B00011000,
        B00000000,
        B00000011,
        B00000011,
    },
    {
        B00000000,
        B01100110,
        B01100110,
        B00000000,
        B00000000,
        B01100110,
        B01100110,
        B00000000,
    },
    {
        B11000011,
        B11000011,
        B00000000,
        B00011000,
        B00011000,
        B00000000,
        B11000011,
        B11000011,
    },
    {
        B11000011,
        B11000011,
        B00000000,
        B11000011,
        B11000011,
        B00000000,
        B11000011,
        B11000011,
    }
};

LedControl lc = LedControl(Data_Pin, CLK_Pin, CS_Pin, 1);


// #################################################################
// #################################################################
void setup()
{
    lc.shutdown(0, false);
    lc.setIntensity(0, 8);
    lc.clearDisplay(0);
    pinMode(Piezo_Pin, OUTPUT);
    pinMode(Button_Pin, INPUT_PULLUP);
    randomSeed(analogRead(A5));
}


// #################################################################
// #################################################################
void Throw_The_Dice()
{
    int Delay_ms = 1;

    while (Delay_ms < 200)
    {
        do
        {
            face = random(6);
        }
        while (face == Last_Face);
        Last_Face = face;

        for (int row = 0; row < 8; row++)
        {
            lc.setRow(0, row, Dice_Faces[face][row]);
        }

        tone(Piezo_Pin, 500, 10);
        delay(Delay_ms);
        Delay_ms += 5;
    }

    for (int freq = 0; freq < 3000; freq += 150)
    {
        tone(Piezo_Pin, freq);
        delay(50);
    }
    noTone(Piezo_Pin);
}


void loop()
{
    if (digitalRead(Button_Pin) == LOW)
    {
        Throw_The_Dice();
    }
}
