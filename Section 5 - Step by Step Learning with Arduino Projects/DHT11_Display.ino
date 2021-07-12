// include the library code
#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTTYPE DHT11

const int DHTPIN = 6;
DHT sensor(DHTPIN, DHTTYPE);

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
    Serial.begin(9600);
    sensor.begin();
    // setup LCD and assign rows and clumns
    LCD.begin(16, 2);
}

void loop()
{
    float Humidity = sensor.readHumidity();
    float Celsius = sensor.readTemperature();
    float Fahrenheit = sensor.readTemperature(true);

    if (isnan(Humidity) || isnan(Celsius) || isnan(Fahrenheit))
    {
        Serial.println("Error reading from the sensor!");
        return;
    }

    float Heat_Index_Celsius = sensor.computeHeatIndex(Celsius, Humidity, false);
    float Heat_Index_Fahrenheit = sensor.computeHeatIndex(Fahrenheit, Humidity);

    Serial.print("Humidity:    ");
    Serial.print(Humidity);
    Serial.println("%");

    Serial.print("Temperature: ");
    Serial.print(Celsius);
    Serial.print("°C     ");
    Serial.print(Fahrenheit);
    Serial.println("°F");

    Serial.print("Heat Index:  ");
    Serial.print(Heat_Index_Celsius);
    Serial.print("°C     ");
    Serial.print(Heat_Index_Fahrenheit);
    Serial.println("°F");


    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Temperature:");
    LCD.setCursor(0, 1);
    LCD.print(Celsius, 1);
    LCD.write((char)223);
    LCD.print("C  ");
    LCD.print(Fahrenheit, 1);
    LCD.write((char)223);
    LCD.print("F");
    delay(2000);

    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Humidity:    ");
    LCD.setCursor(0, 1);
    LCD.print(Humidity);
    LCD.print("%");
    delay(2000);

    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Heat Index:  ");
    LCD.setCursor(0, 1);
    LCD.print(Heat_Index_Celsius, 1);
    LCD.write((char)223);
    LCD.print("C  ");
    LCD.print(Heat_Index_Fahrenheit, 1);
    LCD.write((char)223);
    LCD.print("F");
    delay(2000);
}
