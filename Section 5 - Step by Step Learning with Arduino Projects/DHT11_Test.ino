//include DHT library
#include "DHT.h"
#define DHTTYPE DHT11

const int DHTPIN = 2;

DHT sensor(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(9600);
    sensor.begin();
}

void loop()
{
    delay(5000);

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
    Serial.println();
    Serial.println();
}
