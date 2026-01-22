#define led 7
#define irsensor 6
#define btn 5
bool startalarm=false;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(irsensor, INPUT);
  pinMode(btn, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(irsensor)==LOW)
  {
    startalarm=true;
  }

  if(digitalRead(btn)==LOW)
  {
    startalarm=false;
    digitalWrite(led, LOW);
    delay(200);
  }
  if(startalarm)
  {
    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(led, LOW);
    delay(200);
  }
}
