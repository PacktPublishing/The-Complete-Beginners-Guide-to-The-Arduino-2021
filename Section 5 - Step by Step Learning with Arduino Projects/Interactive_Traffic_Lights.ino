const int CarRed = 2;
const int CarAmber = 3;
const int CarGreen = 4;
const int PedRed = 5;
const int PedGreen = 6;
const int ButtonPin = 7;

void setup()
{
    Serial.begin(115200);
    pinMode(CarRed, OUTPUT);
    pinMode(CarAmber, OUTPUT);
    pinMode(CarGreen, OUTPUT);
    pinMode(PedRed, OUTPUT);
    pinMode(PedGreen, OUTPUT);
    pinMode(ButtonPin, INPUT_PULLUP);

    // starting state = Vehicles GO - Pedestrians STOP
    digitalWrite(PedRed, HIGH);
    digitalWrite(CarGreen, HIGH);
    Serial.println("RESET");
}

void loop()
{
    // Car Green ON
    digitalWrite(CarGreen, HIGH);
    delay(10000);

    while(digitalRead(ButtonPin))
    {
    	
    }

    // Car Amber ON Green OFF
    digitalWrite(CarAmber, HIGH);
    digitalWrite(CarGreen, LOW);
    delay(2000);

    // Car Amber OFF Red ON
    digitalWrite(CarAmber, LOW);
    digitalWrite(CarRed, HIGH);
    delay(2000);

    // Pedestrian Red OFF Green ON
    digitalWrite(PedRed, LOW);
    digitalWrite(PedGreen, HIGH);
    delay(10000);

    // Flash pedestrian green
    for (int repeat = 0; repeat < 5; repeat++)
    {
        digitalWrite(PedGreen, LOW);
        delay(250);
        digitalWrite(PedGreen, HIGH);
        delay(250);
    }

    // Pedestrian Red ON Green OFF
    digitalWrite(PedRed, HIGH);
    digitalWrite(PedGreen, LOW);
    delay(2000);

    // Car Amber ON
    digitalWrite(CarAmber, HIGH);
    delay(2000);

    // Car Amber & Red OFF
    digitalWrite(CarAmber, LOW);
    digitalWrite(CarRed, LOW);
}
