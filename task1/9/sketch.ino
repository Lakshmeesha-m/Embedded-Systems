#define LED 9
#define BTN 8
#define IRdata 7
void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT);
  pinMode(IRdata, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(BTN)==HIGH && digitalRead(IRdata)==LOW)
  {
    digitalWrite(LED, HIGH);
  }

}
