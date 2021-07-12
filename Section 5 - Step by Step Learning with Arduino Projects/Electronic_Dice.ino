int pin[7] = {2, 3, 4, 5, 6, 14, 15};
int face;
int Last_Face = 10;

int Dot_Pattern[6][7] =
{
    {0, 0, 0, 1, 0, 0, 0}, // Number 1
    {1, 0, 0, 0, 0, 0, 1}, // Number 2
    {1, 0, 0, 1, 0, 0, 1}, // Number 3
    {1, 1, 0, 0, 0, 1, 1}, // Number 4
    {1, 1, 0, 1, 0, 1, 1}, // Number 5
    {1, 1, 1, 0, 1, 1, 1}  // Number 6
};

void setup()
{
    pinMode(7, INPUT_PULLUP);
    pinMode(13, OUTPUT);

    for (int x = 0; x < 7; x++)
    {
        pinMode(pin[x], OUTPUT);
    }
    randomSeed(analogRead(A5));
}

void Throw_The_Dice()
{
    int Delay_ms = 1;

    while (Delay_ms < 200)
    {
        do
        {
            face = random(6);
        }
        while (face == Last_Face);
        Last_Face = face;

        for (int dot = 0; dot < 7; dot++)
        {
            if (Dot_Pattern[face][dot] == 1)
            {
                digitalWrite(pin[dot], HIGH);
            }
            else
            {
                digitalWrite(pin[dot], LOW);
            }
        }
        tone(13, 500, 10);
        delay(Delay_ms);
        Delay_ms += 5;
    }

    face = random(6);

    for (int dot = 0; dot < 7; dot++)
    {
        if (Dot_Pattern[face][dot] == 1)
        {
            digitalWrite(pin[dot], HIGH);
        }
        else
        {
            digitalWrite(pin[dot], LOW);
        }
    }
}

void loop()
{
    if (digitalRead(7) == LOW)
    {
        Throw_The_Dice();

        for (int freq = 0; freq < 3000; freq += 150)
        {
        	tone(13, freq);
        	delay(50);
        }
        noTone(13);
    }
}
