IR Sensor Interrupt Counter
Objective

To use an IR sensor connected to an external interrupt pin to count the number of object detection events. The counter is incremented only inside the interrupt service routine. An LED blinks every five detections. The main loop is used only for displaying or processing the count.

Output

Each object detection increases the counter value by one. The LED blinks once for every five detected objects. The main loop does not perform any sensor detection.

Result

This task demonstrates accurate event counting using interrupts, proper separation of ISR and main loop logic, and efficient real-time detection without missing fast events.
