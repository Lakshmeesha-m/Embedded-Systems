1. Blink an LED every 1 second using a hardware timer interrupt. Do not use delay() function.
Change the blinking interval to 500 ms by modifying only the timer configuration.
2. Read the LDR sensor value every 200 ms using a timer interrupt. If the light intensity is below a
threshold, turn ON an LED. Otherwise, turn it OFF. Print the LDR values to the Serial Monitor.
3. Detect a long press of 3 seconds using a push button. Use a timer interrupt that triggers every 10
ms to measure the duration. If the button is pressed continuously for 3 seconds, turn ON an LED.
Reset when released.
4. Check the soil moisture sensor automatically every 5 seconds using a timer. If the soil is dry, turn
ON an LED. If the soil is wet, turn OFF the LED.
5. When rain is detected using the rain sensor, turn ON an LED immediately. Even if rain stops,
keep the LED ON for 10 seconds using timer-based counting, then turn it OFF
