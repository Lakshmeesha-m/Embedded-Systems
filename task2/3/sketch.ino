#define led 10
#define ir  2

volatile int count = 0;
volatile bool blink = false;

void INT0_ISR()
{
  count++;

  if (count%5==0) {
    blink = true;
  }
}

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(ir, INPUT);
  attachInterrupt(digitalPinToInterrupt(ir), INT0_ISR, RISING);
}

void loop()
{
  if (blink)
  {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);

    blink = false;  
  }
}
