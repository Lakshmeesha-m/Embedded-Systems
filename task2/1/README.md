Button Interrupt Toggle
Objective

To toggle an LED ON and OFF using a push button connected to an external interrupt pin. The LED changes state only when an interrupt occurs. Button polling inside the loop function is completely avoided. Button debounce is handled inside the interrupt service routine without using delay, ensuring only one toggle per button press.

Output

Each time the push button is pressed, the LED toggles between ON and OFF. The LED does not change state on button release or due to signal noise.

Result

This task successfully demonstrates edge-triggered external interrupts, software debouncing using timing logic, and reliable state control without continuous polling.
