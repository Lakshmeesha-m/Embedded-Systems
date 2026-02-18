#include <TimerOne.h>
#define LED 13
#define ldr A0
volatile int ldrvalue = 0;
volatile bool value;

void read()
{
  ldrvalue=analogRead(ldr);
  value=true;

}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  Timer1.initialize(200000);
  Timer1.attachInterrupt(read);


}

void loop() {
  // put your main code here, to run repeatedly:
  if(value)
    {
      Serial.print("LDR Value :");
      Serial.println(ldrvalue);
    }
  if((ldrvalue)<400)
    {
      digitalWrite(LED, HIGH);
    }
  else
    {
      digitalWrite(LED, LOW);
    }
  }
