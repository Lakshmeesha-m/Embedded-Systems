Task 2: LED Blinking (With Timers)

This task blinks two LEDs using a hardware timer.

LED1 blinks every 2 seconds

LED2 blinks every 3 seconds

The TimerOne library is used to generate a 1-second timer interrupt.
Counters inside the interrupt track elapsed time, and each LED is toggled when its counter reaches the required interval.

Timing is handled by the hardware timer instead of software delays.
