// pin numbers
const int Switch_Pin = 2;
const int X_Axis_Pin = A0;
const int Y_Axis_Pin = A1;

void setup()
{
    Serial.begin(115200);
    pinMode(Switch_Pin, INPUT_PULLUP);
}

void loop()
{
    int x = analogRead(X_Axis_Pin);

    // X AXIS
    if (x < 250)
    {
        Serial.print("TOP");
    }
    else if (x > 750)
    {
        Serial.print("BOTTOM");
    }
    else
    {
        Serial.print("X MIDDLE");
    }
    Serial.print("\t");

    // Y AXIS
    int y = analogRead(Y_Axis_Pin);
    if (y < 250)
    {
        Serial.println("RIGHT");
    }
    else if (y > 750)
    {
        Serial.println("LEFT");
    }
    else
    {
        Serial.println("Y MIDDLE");
    }
}
