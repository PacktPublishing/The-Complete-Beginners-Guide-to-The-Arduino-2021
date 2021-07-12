// Include our libraries
#include "Adafruit_GPS.h"
#include "SoftwareSerial.h"

// define the pins
const int TX = 4;
const int RX = 3;

// create a timer
unsigned long timer = millis();

// create instances of the library objects
SoftwareSerial mySerial(TX, RX);
Adafruit_GPS GPS(&mySerial);

// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=
void setup()
{
    // begin comms
    Serial.begin(115200);
    GPS.begin(9600);
}

// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=
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

    // every 3 seconds do this.....
    if (millis() - timer > 3000)
    {
        // store the timer value
        timer = millis();

        // print the time - add leading zeros if necessary
        // Print the hour ####################
        Serial.print("Time: ");
        if (GPS.hour < 10)
        {
            Serial.print('0');
        }
        Serial.print(GPS.hour);
        Serial.print(':');

        // print the minutes #################
        if (GPS.minute < 10)
        {
            Serial.print('0');
        }
        Serial.print(GPS.minute);
        Serial.print(':');

        // print the seconds #################
        if (GPS.seconds < 10)
        {
            Serial.print('0');
        }
        Serial.println(GPS.seconds);


        // print the date - add leading zeros if necessary
        // Print the day ####################
        Serial.print("Date: ");
        if (GPS.day < 10)
        {
            Serial.print('0');
        }
        Serial.print(GPS.day);
        Serial.print('/');

        // print the month #################
        if (GPS.month < 10)
        {
            Serial.print('0');
        }
        Serial.print(GPS.month);
        Serial.print("/20");

        // print the year #################
        if (GPS.year < 10)
        {
            Serial.print('0');
        }
        Serial.println(GPS.year);

        // print the GPS fix value and quality
        Serial.print("Fix: ");
        Serial.print(GPS.fix);
        Serial.print(" Quality: ");
        Serial.println(GPS.fixquality);

        // If we get a location fix display relevant data
        if (GPS.fix)
        {
            // display location
            Serial.print("Location: ");
            Serial.print(GPS.latitudeDegrees, 4);
            Serial.print(GPS.lat);
            Serial.print(", ");
            Serial.print(GPS.longitudeDegrees, 4);
            Serial.println(GPS.lon);

            // display speed   MPH 1.15078    KPH 1.852
            Serial.print("Speed (knots): ");
            Serial.println(GPS.speed);

            // display angle of motion
            Serial.print("Angle: ");
            Serial.println(GPS.angle);

            // display altitude
            Serial.print("Altitude: ");
            Serial.println(GPS.altitude);

            // display number of visible satellites
            Serial.print("Satellites: ");
            Serial.println(GPS.satellites);
        }

        Serial.println();
    }

}
