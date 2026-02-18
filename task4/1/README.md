LED Blinking Using Hardware Timer Interrupt (Arduino)

This project demonstrates blinking an LED using a hardware timer interrupt on Arduino without using the delay() function. The implementation uses the TimerOne library to configure Timer1 and generate periodic interrupts. The LED blinks every 1 second, and the interval can be changed to 500 ms by modifying only the timer configuration value. This approach ensures accurate timing and non-blocking program execution, making it suitable for real-time embedded applications.
