const int Piezo_Pin = 3;

void setup()
{
    int Reading = analogRead(0);
    randomSeed(Reading);
}

void loop()
{
    int Random_Frequency = random(200, 2001);
    tone(Piezo_Pin, Random_Frequency);
}
