// include the library code
#include <LiquidCrystal.h>

// define the LCD pins
const int RS = 12;
const int EN = 11;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;

// Create an LCD object
LiquidCrystal LCD(RS, EN, D4, D5, D6, D7);

void setup()
{

    // setup LCD and assign rows and columns
    LCD.begin(16, 2);
}

void loop()
{

    LCD.clear();
    LCD.setCursor(0, 0);


}
