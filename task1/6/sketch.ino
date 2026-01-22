#define LED 7
#define BTN 8

int Level = 0;  

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
}

void loop() {

  if (digitalRead(BTN)== LOW) {
    Level++;

    if (Level > 2) {
      Level = 0;
    }
    if (Level == 0) {
      analogWrite(LED, 85);  
    }
    else if (Level == 1) {
      analogWrite(LED, 170);  
    }
    else if (Level == 2) {
      analogWrite(LED, 255);  
    }
    delay(200); 
  }
}
