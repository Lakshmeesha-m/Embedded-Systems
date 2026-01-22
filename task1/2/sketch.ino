//PULL UP RESISTOR
#define LED_1 13
#define BTN_1 8
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_1,OUTPUT);
  pinMode(BTN_1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(BTN_1)==HIGH)
  {
    digitalWrite(LED_1, LOW);
  }
  else
  {
    digitalWrite(LED_1, HIGH);
  }
}
