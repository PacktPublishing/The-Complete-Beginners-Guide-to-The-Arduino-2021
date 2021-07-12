// include the library code
#include <LiquidCrystal.h>
#include "Adafruit_BME280.h"

// define the LCD pins
const int RS = 12;
const int EN = 11;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;
const float Sea_Level_Pressure = 1016.5;

// Create an LCD object
LiquidCrystal LCD(RS, EN, D4, D5, D6, D7);
Adafruit_BME280 BME280;

void setup()
{
    // setup LCD and assign rows and clumns
    LCD.begin(16, 2);

    Serial.begin(9600);

    bool status = BME280.begin(0x76);
    Serial.println(BME280.sensorID(), HEX);

    if (!status)
    {
        Serial.println("Sensor error!");
        Serial.println(BME280.sensorID(), HEX);
        while (1)
        {
            delay(1000);
        }
    }
    else
    {
        Serial.println("BME280 Sensor Detected");
        Serial.println();
    }
}

void loop()
{
    // BME280 code
    float temp = BME280.readTemperature();
    Serial.print("    Temp: ");
    Serial.print(temp);
    Serial.println("°C");

    Serial.print("    Temp: ");
    Serial.print(1.8 * temp + 32);
    Serial.println("°F");

    Serial.print("Pressure: ");
    Serial.print(BME280.readPressure() / 100);
    Serial.println(" hPa");

    Serial.print("Altitude: ");
    Serial.print(BME280.readAltitude(Sea_Level_Pressure));
    Serial.println(" m");

    Serial.print("Humidity: ");
    Serial.print(BME280.readHumidity());
    Serial.println("%");

    Serial.println();

    // LCD code
    // TEMPERATURE
    LCD.clear();
    // first line
    LCD.setCursor(0, 0);
    LCD.print("Temperature: ");
    // second line - Celsius
    LCD.setCursor(0, 1);
    LCD.print(temp);
    LCD.write((char)223);
    LCD.print("C  ");
    // fahrenheit
    LCD.print(1.8 * temp + 32);
    LCD.write((char)223);
    LCD.print("F");
    delay(3000);

    // HUMIDITY
    LCD.clear();
    // first line
    LCD.setCursor(0, 0);
    LCD.print("Humidity: ");
    LCD.setCursor(0, 1);
    LCD.print(BME280.readHumidity());
    LCD.print("%");
    delay(3000);

    // PRESSURE hPa
    LCD.clear();
    // first line
    LCD.setCursor(0, 0);
    LCD.print("Pressure: ");
    LCD.setCursor(0, 1);
    LCD.print(BME280.readPressure() / 100);
    LCD.print(" hPa");
    delay(3000);

    // ALTITUDE
    LCD.clear();
    // first line
    LCD.setCursor(0, 0);
    LCD.print("Altitude: ");
    LCD.setCursor(0, 1);
    LCD.print(BME280.readAltitude(Sea_Level_Pressure));
    LCD.print(" m");
    delay(3000);
}
