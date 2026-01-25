Task 1: Button Interrupt Toggle
Use a push button connected to an external interrupt pin to toggle an LED ON and OFF.
The LED must change state only when the interrupt occurs, not by polling the button in loop().
Ensure one toggle per press (handle button bounce without using delay()).


Task 2: IR Sensor Interrupt Counter
Use an IR sensor connected to an external interrupt pin to count how many times an object is detected.
Increment a counter on every interrupt event and blink an LED every 5 detections.
The main loop must only display or use the count, not detect the event.


Task 3: Emergency Stop Interrupt
Blink an LED continuously during normal operation.
Use a push button interrupt as an emergency stop that immediately turns OFF all LEDs and halts system operation until reset, regardless of what the main loop is doing.
