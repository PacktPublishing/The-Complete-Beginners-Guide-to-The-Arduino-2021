void setup()
{
    for (int PINS = 2; PINS <= 4; PINS++)
    {
        pinMode(PINS, OUTPUT);
    }
}

void loop()
{
    for (int PINS = 2; PINS <= 4; PINS++)
    {
        digitalWrite(PINS, HIGH);
        delay(1000);
        digitalWrite(PINS, LOW);
    }
}
