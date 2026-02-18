#include <TimerOne.h>
#define LED 13
bool ledstate=LOW;

void toggle()
{
  ledstate=!ledstate;
  digitalWrite(LED,ledstate);
  
}
void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(toggle);

}

void loop() {
  // put your main code here, to run repeatedly:


}
