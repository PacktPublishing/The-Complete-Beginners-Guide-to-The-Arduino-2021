#include "Adafruit_BME280.h"

const float Sea_Level_Pressure = 1016.5;

Adafruit_BME280 BME280;

void setup()
{
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

    delay(5000);
}
