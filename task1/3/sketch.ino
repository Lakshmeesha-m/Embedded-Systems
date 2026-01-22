// Toggle LED on each button press
// Arduino UNO

#define LED_PIN 13
#define BUTTON_PIN 2

int ledState = LOW;
int lastButtonState = HIGH;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);  // Internal pull-up
}

void loop()
{
    int currentButtonState = digitalRead(BUTTON_PIN);

    // Detect button press (HIGH → LOW transition)
    if (lastButtonState == HIGH && currentButtonState == LOW)
    {
        ledState = !ledState;                 // Toggle LED state
        digitalWrite(LED_PIN, ledState);
        delay(200);                           // Debounce delay
    }

    lastButtonState = currentButtonState;
}
