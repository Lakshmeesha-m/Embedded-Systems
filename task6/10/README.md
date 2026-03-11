1️⃣ Objective of the Program

The objective of this program is to:

* Connect the **BMA400 accelerometer with Arduino using I2C**
* Use the **built-in step counter feature**
* Trigger an **interrupt whenever a step is detected**
* Display:

  * **Total step count**
  * **Activity type (walking, running, or still)**

In simple words:

> The accelerometer detects walking or running movements, counts the steps internally, and informs the Arduino whenever a new step is detected.

---

# 2️⃣ Working Principle

The **BMA400 accelerometer** measures acceleration in three axes:

| Axis | Movement           |
| ---- | ------------------ |
| X    | Left / Right       |
| Y    | Forward / Backward |
| Z    | Up / Down          |

When a person walks:

1. The body produces a **periodic acceleration pattern**.
2. The BMA400 analyzes this pattern internally.
3. The sensor determines whether the motion corresponds to:

   * **Walking**
   * **Running**
   * **Standing still**
4. Every time a step is detected:

   * The **step counter increases**.
   * An **interrupt signal is generated**.
5. The interrupt goes to **Arduino pin 2**.
6. Arduino reads the **total step count** and **activity type**.
7. The results are printed on the **Serial Monitor**.

This feature is used in devices like:

* Fitness trackers
* Smart watches
* Activity monitors

---

# 3️⃣ Code Explanation

## 1. Including Libraries

```cpp
#include <Wire.h>
#include "SparkFun_BMA400_Arduino_Library.h"
```

* `Wire.h` enables **I2C communication**.
* `SparkFun_BMA400_Arduino_Library.h` provides functions to control the sensor.

---

# 4️⃣ Creating Sensor Object

```cpp
BMA400 accelerometer;
```

Creates an object named **accelerometer** used to communicate with the sensor.

---

# 5️⃣ I2C Address Selection

```cpp
uint8_t i2cAddress = BMA400_I2C_ADDRESS_DEFAULT;
```

Stores the **I2C address of the sensor**.

Default address = **0x14**.

---

# 6️⃣ Interrupt Pin

```cpp
int interruptPin = 2;
```

Arduino **digital pin 2** receives interrupt signals from the sensor.

---

# 7️⃣ Interrupt Flag

```cpp
volatile bool interruptOccurred = false;
```

This variable becomes **true when an interrupt occurs**.

`volatile` is used because interrupts modify the variable.

---

# 8️⃣ Setup Function

```cpp
void setup()
```

Runs once when the Arduino starts.

---

### Start Serial Communication

```cpp
Serial.begin(115200);
```

Starts communication between Arduino and the computer.

---

### Initialize I2C

```cpp
Wire.begin();
```

Starts I2C communication.

---

### Check Sensor Connection

```cpp
while(accelerometer.beginI2C(i2cAddress) != BMA400_OK)
```

Checks if the sensor is connected.

If not connected, an error message is printed.

---

# 9️⃣ Configure Step Counter

```cpp
bma400_step_int_conf config =
{
    .int_chan = BMA400_INT_CHANNEL_1
};
```

This structure configures the **step counter interrupt**.

It tells the sensor to send step interrupts through **INT1 pin**.

---

### Apply Step Counter Configuration

```cpp
accelerometer.setStepCounterInterrupt(&config);
```

Activates the step counter feature in the sensor.

---

# 🔟 Configure Interrupt Pin

```cpp
accelerometer.setInterruptPinMode(
BMA400_INT_CHANNEL_1,
BMA400_INT_PUSH_PULL_ACTIVE_1
);
```

Sets interrupt pin mode to:

* **Push-pull**
* **Active HIGH**

---

# 1️⃣1️⃣ Enable Step Counter Interrupt

```cpp
accelerometer.enableInterrupt(BMA400_STEP_COUNTER_INT_EN, true);
```

This enables **step counting and step interrupts**.

Without this line, the step counter will not work.

---

# 1️⃣2️⃣ Attach Arduino Interrupt

```cpp
attachInterrupt(
digitalPinToInterrupt(interruptPin),
bma400InterruptHandler,
RISING
);
```

Arduino monitors **pin 2**.

When the signal changes from **LOW → HIGH**, the interrupt handler runs.

---

# 1️⃣3️⃣ Loop Function

```cpp
void loop()
```

Runs continuously.

---

### Check if Interrupt Occurred

```cpp
if(interruptOccurred)
```

Checks whether the sensor triggered an interrupt.

---

### Reset Interrupt Flag

```cpp
interruptOccurred = false;
```

Resets the flag for the next interrupt.

---

### Get Interrupt Status

```cpp
accelerometer.getInterruptStatus(&interruptStatus);
```

Determines which event caused the interrupt.

---

### Detect Step Event

```cpp
if(interruptStatus & BMA400_ASSERTED_STEP_INT)
```

Confirms that the interrupt occurred because a **step was detected**.

---

# 1️⃣4️⃣ Read Step Count

```cpp
accelerometer.getStepCount(&stepCount, &activityType);
```

This function reads:

* **Total number of steps**
* **Type of activity**

The step count is stored as a **24-bit integer inside the sensor**.

---

# 1️⃣5️⃣ Print Step Count

```cpp
Serial.print("Step detected! Step count: ");
```

Displays the total steps detected so far.

---

# 1️⃣6️⃣ Detect Activity Type

The sensor also identifies whether the person is:

| Activity Code      | Meaning        |
| ------------------ | -------------- |
| `BMA400_RUN_ACT`   | Running        |
| `BMA400_WALK_ACT`  | Walking        |
| `BMA400_STILL_ACT` | Standing still |

The code prints the activity using a **switch statement**.

Example output:

```cpp
case BMA400_RUN_ACT:
Serial.println("Running");
```

---

# 1️⃣7️⃣ Interrupt Handler

```cpp
void bma400InterruptHandler()
{
    interruptOccurred = true;
}
```

When a step is detected:

* The sensor sends an interrupt
* Arduino runs this function
* The flag **interruptOccurred** becomes **true**

Then the loop processes the event.

---

# 1️⃣8️⃣ Example Output

```
Interrupt occurred! Step detected! Step count: 15   Detected activity type: Walking
Interrupt occurred! Step detected! Step count: 16   Detected activity type: Walking
Interrupt occurred! Step detected! Step count: 17   Detected activity type: Running
```

---
