const int LED_Pin = 7;

void setup()
{
    pinMode(LED_Pin, OUTPUT);
}

void loop()
{
    digitalWrite(LED_Pin, HIGH);
    delay(250);
    digitalWrite(LED_Pin, LOW);
    delay(1500);
}
