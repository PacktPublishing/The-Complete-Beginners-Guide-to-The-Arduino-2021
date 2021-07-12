// Include our libraries
#include "Adafruit_GPS.h"
#include "SoftwareSerial.h"
#include "LedControl.h"

// define the pins used
const int TX = 4;
const int RX = 3;
const int Data_Pin = 5;
const int CS_Pin = 6;
const int CLK_Pin = 7;

// timer for tick dots
unsigned long Tick_Timer;

// tick status
bool tick = false;

// timezone offset
int Hour_Offset = 1;

// create instances of our library objects
SoftwareSerial mySerial(TX, RX);
Adafruit_GPS GPS(&mySerial);
LedControl Seven_Seg_Display = LedControl(Data_Pin, CLK_Pin, CS_Pin, 1);


// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=
// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=
void setup()
{
    // begin comms
    Serial.begin(115200);
    GPS.begin(9600);

    // initialise display
    Seven_Seg_Display.shutdown(0, false);
    Seven_Seg_Display.setIntensity(0, 5);

    // initialise tick timer
    Tick_Timer = millis();
}


// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=
// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=
void Display_Time()
{
    // display the seconds
    if (GPS.seconds < 10)
    {
        Seven_Seg_Display.setDigit(0, 0, GPS.seconds, false);
        Seven_Seg_Display.setDigit(0, 1, 0, false);
    }
    else
    {
        int Current_Seconds = GPS.seconds;
        Seven_Seg_Display.setDigit(0, 0, Current_Seconds % 10, false);
        Current_Seconds = Current_Seconds / 10;
        Seven_Seg_Display.setDigit(0, 1, Current_Seconds, false);
    }

    // display the minutes
    if (GPS.minute < 10)
    {
        Seven_Seg_Display.setDigit(0, 2, GPS.minute, tick);
        Seven_Seg_Display.setDigit(0, 3, 0, false);
    }
    else
    {
        int Current_Minutes = GPS.minute;
        Seven_Seg_Display.setDigit(0, 2, Current_Minutes % 10, tick);
        Current_Minutes = Current_Minutes / 10;
        Seven_Seg_Display.setDigit(0, 3, Current_Minutes, false);
    }

    // Add hour offset to convert from UTC to local time
    int hours = GPS.hour + Hour_Offset;
    // Handle when UTC + offset is a negative or > 23 value.
    if (hours < 0)
    {
        hours = 24 + hours;
    }
    if (hours > 23)
    {
        hours = 24 - hours;
    }
    // display the hours
    if (GPS.hour < 10)
    {
        Seven_Seg_Display.setDigit(0, 4, GPS.hour, tick);
        Seven_Seg_Display.setDigit(0, 5, 0, false);
    }
    else
    {
        int Current_Hours = GPS.hour;
        Seven_Seg_Display.setDigit(0, 4, Current_Hours % 10, tick);
        Current_Hours = Current_Hours / 10;
        Seven_Seg_Display.setDigit(0, 5, Current_Hours, false);
    }
    Seven_Seg_Display.setChar(0, 6, ' ', false);
    Seven_Seg_Display.setChar(0, 7, ' ', false);
}


// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=
// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=
void Display_Date()
{
    // display the year
    if (GPS.year < 10)
    {
        Seven_Seg_Display.setDigit(0, 0, GPS.year, false);
        Seven_Seg_Display.setDigit(0, 1, 0, false);
    }
    else
    {
        int Current_Year = GPS.year;
        Seven_Seg_Display.setDigit(0, 0, Current_Year % 10, false);
        Current_Year = Current_Year / 10;
        Seven_Seg_Display.setDigit(0, 1, Current_Year, false);
    }
    // print leading '20' of year
    Seven_Seg_Display.setDigit(0, 2, 0, false);
    Seven_Seg_Display.setDigit(0, 3, 2, false);

    // display the month
    if (GPS.month < 10)
    {
        Seven_Seg_Display.setDigit(0, 4, GPS.month, true);
        Seven_Seg_Display.setDigit(0, 5, 0, false);
    }
    else
    {
        int Current_Month = GPS.month;
        Seven_Seg_Display.setDigit(0, 5, Current_Month % 10, true);
        Current_Month = Current_Month / 10;
        Seven_Seg_Display.setDigit(0, 5, Current_Month, false);
    }

    // display the day
    if (GPS.day < 10)
    {
        Seven_Seg_Display.setDigit(0, 6, GPS.day, true);
        Seven_Seg_Display.setDigit(0, 7, 0, false);
    }
    else
    {
        int Current_Day = GPS.day;
        Seven_Seg_Display.setDigit(0, 6, Current_Day % 10, true);
        Current_Day = Current_Day / 10;
        Seven_Seg_Display.setDigit(0, 7, Current_Day, false);
    }
}


// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=
// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=
void Update_Display()
{
    // boolean - time or date to be shown?
    bool Time_Or_Date = GPS.seconds % 30;

    // show time or date
    switch (Time_Or_Date)
    {
        case 0:
            Display_Date();
            break;
        case 1:
            Display_Time();
            break;
    }
}


// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=
// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=
void loop()
{
    // tell the GPS to get some data
    GPS.read();

    // Check if anything received
    if (GPS.newNMEAreceived())
    {

        // parse the NMEA sentences and return if not valid
        if (!GPS.parse(GPS.lastNMEA()))
            return;
    }

    // every half a second....
    if (millis() - Tick_Timer > 500)
    {
        // store the current millis value
        Tick_Timer = millis();
        // toggle the tick status
        tick = !tick;
        // update the display
        Update_Display();
    }

}
