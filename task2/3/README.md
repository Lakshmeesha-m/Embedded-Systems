Emergency Stop Interrupt
Objective

To implement an emergency stop system using a push button connected to an external interrupt pin. During normal operation, an LED blinks continuously. When the emergency button is pressed, all LEDs turn OFF immediately and the system halts execution until a reset is performed.

Output

The LED blinks continuously during normal operation. Pressing the emergency stop button instantly turns OFF all LEDs and stops the system completely. The system remains halted until reset.

Result

This task demonstrates the use of high-priority interrupts for safety-critical applications, immediate system response, and reliable system shutdown independent of the main loop execution.
