#include <TimerOne.h>
#define LED 13
#define soil A0
volatile bool flag = false;
volatile int value=0;

void check()
{
  value=analogRead(soil);
  flag=true;
}
void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(soil, INPUT);
  Serial.begin(9600);
  Timer1.initialize(5000000);
  Timer1.attachInterrupt(check);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(flag)
  {
    Serial.print("Soil Moisture Value: ");
    Serial.println(value);
  }
  if(value>600)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }

}
