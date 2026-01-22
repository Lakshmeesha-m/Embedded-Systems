#define IRdata 9
#define LED 2
void setup() {
  // put your setup code here, to run once:
  pinMode(IRdata, INPUT);
  pinMode(LED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(IRdata)==LOW)
  {
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
    
  }
  
}