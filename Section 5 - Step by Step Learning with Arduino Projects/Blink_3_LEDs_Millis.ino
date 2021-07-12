unsigned long timer[3];
bool state[3] = {true, true, true};
int frequency[3] = {250, 260, 270};

void setup()
{
    for (int index = 0; index < 3; index++)
    {
        pinMode(index + 2, OUTPUT);
        timer[index] = millis();
    }
}

void loop()
{
    for (int index = 0; index < 3; index++)
    {
        if (state[index] == true)
        {
            digitalWrite(index + 2, HIGH);
        }
        else
        {
            digitalWrite(index + 2, LOW);
        }

        if (millis() > (timer[index] + frequency[index]) )
        {
            state[index] = !state[index];
            timer[index] = millis();
        }
    }
}
