#include <Servo.h>

Servo myServo;

int position;

void setup()
{
    myServo.attach(9);
}

void loop()
{
    int voltage = analogRead(A0);
    position = map(voltage, 0, 1023, 0, 180);
    myServo.write(position);
}
