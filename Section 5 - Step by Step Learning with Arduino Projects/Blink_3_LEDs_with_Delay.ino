const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop()
{
  digitalWrite(LED1, HIGH);
  digitalWrite(LED3, HIGH);
  delay(250);
  digitalWrite(LED3, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(250);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  delay(250);
  digitalWrite(LED3, LOW);
  digitalWrite(LED2, HIGH);
  delay(250);
  digitalWrite(LED2, LOW);
}
