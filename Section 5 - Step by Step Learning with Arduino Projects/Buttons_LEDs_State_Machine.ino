// Pin Numbers
const int Button1_Pin = 5;
const int Button2_Pin = 6;
const int LED1_Pin = 2;
const int LED2_Pin = 3;
const int LED3_Pin = 4;

bool On_Off_state = HIGH; // starting state of the LEDs
bool LED_Activation_States[3] = {true, false, false};

int Flash_Frequency = 1500; // starting flash rate of LEDS in ms
int Selected_Pattern = 1; // start with combination 1

// Timers for the button presses and LED flashes
unsigned long Last_Time_Button1_Pressed = 0;
unsigned long Last_Time_Button2_Pressed = 0;
unsigned long Flash_Timer = 0;
int Debounce_Delay = 50;

void setup()
{
    // set up the pins
    pinMode(Button1_Pin, INPUT);
    pinMode(BUtton2_Pin, INPUT);
    pinMode(LED1_Pin, OUTPUT);
    pinMode(LED2_Pin, OUTPUT);
    pinMode(LED3_Pin, OUTPUT);
}

void Flash_LEDs()
{
    // change the flash state once the flash rate time has passed
    if (millis() > (Flash_Timer + Flash_Frequency))
    {
        // toggle LED state
        On_Off_State = !On_Off_State;
        // then store the time of the change
        Flash_Timer = millis();
    }

    if (LED_Activation_States[0] == true)
    {
        digitalWrite(LED1_Pin, On_Off_State);
    }
    else
    {
        digitalWrite(LED1_Pin, LOW);
    }


    if (LED_Activation_States[1] == true)
    {
        digitalWrite(LED2_Pin, On_Off_State);
    }
    else
    {
        digitalWrite(LED2_Pin, LOW);
    }


    if (LED_Activation_States[2] == true)
    {
        digitalWrite(LED3_Pin, On_Off_State);
    }
    else
    {
        digitalWrite(LED3_Pin, LOW);
    }
}

void loop()
{
    bool Button1_Read = digitalRead(Button1_Pin);
    bool Button2_Read = digitalRead(Button2_Pin);

    // check if button 1 is pressed
    if (Button1_Read == HIGH)
    {
        if ((millis() - Last_Time_Button1_Pressed) > Debounce_Delay)
        {
            // divide flash frequency in half
            Flash_Frequency = Flash_Frequency / 2;

            // if smaller than 40ms reset back to 1500ms
            if (Flash_Frequency < 40)
            {
                Flash_Frequency = 1500;
            }

            Last_Time_Button1_Pressed = millis();
        }
    }

    if (Button2_Read == HIGH)
    {
        if ((millis() - Last_Time_Button2_Pressed) > Debounce_Delay)
        {
            // increase pattern number every time button is pressed
            Selected_Pattern++;

            // set back to zero if greater than 7
            if (Selected_Pattern > 7) Selected_Pattern = 0;

            switch (Selected_Pattern)
            {
                case 0:
                    LED_Activation_States[0] = false;
                    LED_Activation_States[1] = false;
                    LED_Activation_States[2] = false;
                    break;
                case 1:
                    LED_Activation_States[0] = true;
                    LED_Activation_States[1] = false;
                    LED_Activation_States[2] = false;
                    break;
                case 2:
                    LED_Activation_States[0] = false;
                    LED_Activation_States[1] = true;
                    LED_Activation_States[2] = false;
                    break;
                case 3:
                    LED_Activation_States[0] = false;
                    LED_Activation_States[1] = false;
                    LED_Activation_States[2] = true;
                    break;
                case 4:
                    LED_Activation_States[0] = true;
                    LED_Activation_States[1] = true;
                    LED_Activation_States[2] = false;
                    break;
                case 5:
                    LED_Activation_States[0] = false;
                    LED_Activation_States[1] = true;
                    LED_Activation_States[2] = true;
                    break;
                case 6:
                    LED_Activation_States[0] = true;
                    LED_Activation_States[1] = false;
                    LED_Activation_States[2] = true;
                    break;
                case 7:
                    LED_Activation_States[0] = true;
                    LED_Activation_States[1] = true;
                    LED_Activation_States[2] = true;
                    break;
            }
            Last_Time_Button2_Pressed = millis();
        }
    }

    Flash_LEDs();
}
