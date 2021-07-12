const int Button_Pin = 2;
const int LED_Pin = 13;

bool LED_State = LOW;
bool Button_State = LOW;

unsigned long Last_Change_Time = 0;
int Debounce_Delay = 50;

void setup()
{
    Serial.begin(9600);
    pinMode(Button_Pin, INPUT);
    pinMode(LED_Pin, OUTPUT);
    digitalWrite(LED_Pin, LED_State);
}

void loop()
{
    bool Button_Read = digitalRead(Button_Pin);
    
    if (Button_Read == HIGH)
    {
    	if((millis() - Last_Change_Time) > Debounce_Delay)
    	{
    		LED_State = !LED_State;
    		digitalWrite(LED_Pin, LED_State);
    	}
    	Last_Change_Time = millis();
    }
}
