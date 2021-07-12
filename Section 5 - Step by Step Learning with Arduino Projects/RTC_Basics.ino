#include "DS3232RTC.h"

time_t TheTime;
TimeElements TimeStruct;

bool SQW_State;
bool Last_SQW_State = 0;
const int SQW_Pin = 2;

void setup()
{
    Serial.begin(115200);

    pinMode(SQW_Pin, INPUT_PULLUP);
    RTC.squareWave(SQWAVE_1_HZ);

    setSyncProvider(RTC.get);
    if (timeStatus() != timeSet)
    {
        Serial.println("SYNC FAIL!");
        while (1) { } ;
    }

}

void Print_Time(time_t TheTime)
{
    if (hour(TheTime) < 10) Serial.print('0');
    Serial.print(hour(TheTime));
    Serial.print(':');
    if (minute(TheTime) < 10) Serial.print('0');
    Serial.print(minute(TheTime));
    Serial.print(':');
    if (second(TheTime) < 10) Serial.print('0');
    Serial.print(second(TheTime));
}

void Print_Date(time_t TheTime)
{
    if (day(TheTime) < 10) Serial.print('0');
    Serial.print(day(TheTime));
    Serial.print('/');
    if (month(TheTime) < 10) Serial.print('0');
    Serial.print(month(TheTime));
    Serial.print('/');
    Serial.print(year(TheTime));
}

void Check_If_Input()
{
    // input format is YY,D,M,H,M,S
    if (Serial.available() >= 12)
    {
        int y = Serial.parseInt();
        if (y >= 100 && y < 1000  || y > 2100)
        {
            Serial.println("Error: Year must be two or four digits");
        }
        else
        {
            if (y >= 1000) TimeStruct.Year = CalendarYrToTm(y);
            else TimeStruct.Year = y2kYearToTm(y);
            TimeStruct.Month = Serial.parseInt();
            TimeStruct.Day = Serial.parseInt();
            TimeStruct.Hour = Serial.parseInt();
            TimeStruct.Minute = Serial.parseInt();
            TimeStruct.Second = Serial.parseInt();

            TheTime = makeTime(TimeStruct);

            RTC.set(TheTime);
            setTime(TheTime);

            Serial.print("RTC set to: ");
            Print_Time(TheTime);
            Serial.print("   ");
            Print_Date(TheTime);
            Serial.println();

            while (Serial.available() > 0) Serial.read();
        }
    }
}

void loop()
{
    Check_If_Input();

    SQW_State = digitalRead(SQW_Pin);

    if (SQW_State != Last_SQW_State)
    {
        Last_SQW_State = SQW_State;

        if (SQW_State == HIGH)
        {
            TheTime = now();
            Print_Time(TheTime);
            Serial.print("   ");
            Print_Date(TheTime);
            Serial.print("   ");
            Serial.print(monthStr(month(TheTime)));
            Serial.print("   ");
            Serial.print(dayStr(weekday(TheTime)));
            Serial.println();
        }
    }

}
