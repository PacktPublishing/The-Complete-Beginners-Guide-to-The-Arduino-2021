void setup()
{
    Serial.begin(9600);
}

void loop()
{
    int LDR_Reading = analogRead(A0);

    float voltage = LDR_Reading * (5.0 / 1023.0);

    Serial.println(voltage);
}
