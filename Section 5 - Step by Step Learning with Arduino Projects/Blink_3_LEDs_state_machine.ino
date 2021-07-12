byte ledstates[3][20] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0}
};

byte counter = 0;

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop()
{
  for (byte led = 0; led < 3; led++)
  {
    if (ledstates[led][counter] == 1) digitalWrite(led + 2, HIGH);
    else digitalWrite(led + 2, LOW);
  }
  
  counter++;
  if (counter > 19) counter = 0;
  delay(100);
}
