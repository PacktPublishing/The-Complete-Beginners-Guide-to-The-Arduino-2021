#include "LedControl.h"
#include "NewPing.h"

// Display Pins
const int Data_Pin = 2;
const int CS_Pin = 3;
const int CLK_Pin = 4;
// Ultrasonic Pins
const int Trigger_Pin = 5;
const int Echo_Pin = 6;

const int Max_Distance = 200;

int average[10];
int index = 0;

LedControl Seven_Seg_Display = LedControl(Data_Pin, CLK_Pin, CS_Pin, 1);
NewPing sonic(Trigger_Pin, Echo_Pin, Max_Distance);

void setup()
{
    Serial.begin(115200);
    Seven_Seg_Display.shutdown(0, false);
    Seven_Seg_Display.setIntensity(0, 8);
}

void Display_Distance(int d)
{
    Seven_Seg_Display.setDigit(0, 0, d % 10, false);
    d = d / 10;
    Seven_Seg_Display.setDigit(0, 1, d % 10, false);
    d = d / 10;
    Seven_Seg_Display.setDigit(0, 2, d % 10, false);
}

void Display_Average_Distance()
{
    int d = 0;
    int counter = 0;
    while (counter < 10)
    {
        d = d + average[counter];
        counter++;
    }
    d = d / 10;
    Serial.print(d);
    Serial.println("cm");
    Seven_Seg_Display.setDigit(0, 4, d % 10, false);
    d = d / 10;
    Seven_Seg_Display.setDigit(0, 5, d % 10, false);
    d = d / 10;
    Seven_Seg_Display.setDigit(0, 6, d % 10, false);
}

void loop()
{
    delay(33);
    int distance = sonic.ping_cm();
    Serial.print(distance);
    Serial.print("cm   ");
    Display_Distance(distance);

    average[index] = distance;
    index++;
    if (index == 10) index = 0;
    Display_Average_Distance();
}
