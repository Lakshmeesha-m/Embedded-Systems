#include <TimerOne.h>>
#define LED1 13
#define LED2 12
int count1=0;
int count2=0;

void isr()
{
  count1++;
  count2++;
  if(count==2)
  {
    digitalWrite(LED1,!digitalRead(LED1));
    count1=0;
  }
  if(count==3)
  {
    digitalWrite(LED2,!digitalRead(LED2));
    count2=0;
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2,OUTPUT);
  Timer1.initialze(1000000);
  Timer1.attachInterrupt(isr);
}

void loop() {

}
