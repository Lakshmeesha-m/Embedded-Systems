#include <TimerOne.h>
#define LED 12
#define RAIN 10
volatile bool rain = false;
volatile int norain = 0;
void isr()
{
  if(digitalRead(RAIN)==LOW)
  {
    rain=true;
    norain=0;
    digitalWrite(LED,HIGH);
  }
  else
  {
    if(rain)
    {
      norain++;

      if(norain>=1000)
      {
        digitalWrite(LED, LOW);
        rain = false;
        norain = 0;
      }
    }
    
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(RAIN,INPUT);
  Timer1.initialize(10000);
  Timer1.attachInterrupt(isr);

}

void loop() {
  // put your main code here, to run repeatedly:

}
