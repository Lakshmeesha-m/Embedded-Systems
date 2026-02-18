
#include <TimerOne.h>
#define LED 13
#define BTN 12
volatile int count=0;

void isr()
{
  if(digitalRead(BTN)==HIGH)
  {
    count++;
    if(count>=300)
    {
      digitalWrite(LED,HIGH);
    }
  }
  else
  {
    count=0;
    digitalWrite(LED,LOW);
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  pinMode (BTN, INPUT);
  Timer1.initialize(10000);
  Timer1.attachInterrupt(isr);

}

void loop() {
  // put your main code here, to run repeatedly:

}
