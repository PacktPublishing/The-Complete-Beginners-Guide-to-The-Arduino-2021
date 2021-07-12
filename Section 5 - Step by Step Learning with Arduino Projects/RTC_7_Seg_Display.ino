#include "DS3232RTC.h"
#include "LedControl.h"
#include "Wire.h"
#define DS3232_I2C_ADDRESS 0x68

time_t TheTime;
TimeElements TimeStruct;

bool SQW_State;
bool Last_SQW_State = 0;
const int SQW_Pin = 2;

const int Data_Pin = 3;
const int CS_Pin = 4;
const int CLK_Pin = 5;

LedControl Seven_Seg_Display = LedControl(Data_Pin, CLK_Pin, CS_Pin, 1);

// =#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#
void setup()
{
    Wire.begin();
    //setControlRegisters();
    Serial.begin(115200);

    Seven_Seg_Display.shutdown(0, false);
    Seven_Seg_Display.setIntensity(0, 5);
    delay(2000);

    //setAgingOffset(-60);
    //forceConversion();

    delay(100);

    pinMode(SQW_Pin, INPUT_PULLUP);
    RTC.squareWave(SQWAVE_1_HZ);

    // sync the time library with the RTC
    setSyncProvider(RTC.get);
    setSyncInterval(300);

    // check if the sync was successful
    if (timeStatus() != timeSet)
    {
        Serial.println("SYNC FAIL!");
        while (1) { };
    }
}


void setControlRegisters()
{
    Wire.beginTransmission(DS3232_I2C_ADDRESS);
    Wire.write(0x0E);

    Wire.write(B00011100);
    Wire.write(B11001000);
    Wire.endTransmission();
}

void setAgingOffset(int offset)
{
    if (offset < 0) offset += 256;

    Wire.beginTransmission(DS3232_I2C_ADDRESS);
    Wire.write(0x10);
    Wire.write(offset);
    Wire.endTransmission();
}

void forceConversion()
{
    Wire.beginTransmission(DS3232_I2C_ADDRESS);
    Wire.write(0x0E);

    Wire.write(B00111100);
    Wire.endTransmission();
}

// =#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#
void Print_Time(time_t TheTime)
{
    if (hour(TheTime) < 10) Serial.print('0');
    Serial.print(hour(TheTime));
    Serial.print(':');
    if (minute(TheTime) < 10) Serial.print('0');
    Serial.print(minute(TheTime));
    Serial.print(':');
    if (second(TheTime) < 10) Serial.print('0');
    Serial.println(second(TheTime));
}

void Display_Time(time_t TheTime)
{
    int h = hour(TheTime);
    Seven_Seg_Display.setDigit(0, 4, h % 10, SQW_State);
    h = h / 10;
    Seven_Seg_Display.setDigit(0, 5, h % 10, false);

    int m = minute(TheTime);
    Seven_Seg_Display.setDigit(0, 2, m % 10, SQW_State);
    m = m / 10;
    Seven_Seg_Display.setDigit(0, 3, m % 10, false);

    int s = second(TheTime);
    Seven_Seg_Display.setDigit(0, 0, s % 10, false);
    s = s / 10;
    Seven_Seg_Display.setDigit(0, 1, s % 10, false);
}

// =#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#
void Check_If_Input()
{
    // input format is YY,M,D,H,M,S
    if (Serial.available() >= 12)
    {
        int y = Serial.parseInt();
        if (y >= 100 && y < 1000)
            Serial.println("Error: Year must be two or four digits");
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
            Serial.println();
            // get rid of any extra characters from the serial buffer
            while (Serial.available() > 0) Serial.read();
        }
    }
}

// =#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#
void loop()
{
    Check_If_Input();

    SQW_State = digitalRead(SQW_Pin);

    if (SQW_State != Last_SQW_State)
    {
    	
        Last_SQW_State = SQW_State;
        TheTime = now();
        Display_Time(TheTime);
    }
}
