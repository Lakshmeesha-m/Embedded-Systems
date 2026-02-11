#define LED1 9
#define LED2 8

int count1 = 0;
int count2 = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  delay(1000); 

  count1++;
  count2++;

  if (count1 == 2) {
    digitalWrite(LED1, !digitalRead(LED1));
    count1 = 0;
  }

  if (count2 == 3) {
    digitalWrite(LED2, !digitalRead(LED2));
    count2 = 0;
  }
}
