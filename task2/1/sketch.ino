#define led 10
#define btn 2
volatile byte state=LOW;

void INT0_ISR(){
  state=!state;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT);
  attachInterrupt(digitalPinToInterrupt(2),INT0_ISR,FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led,state);

}
