1️⃣ Objective of the Program

The objective of this program is to:

* Interface the **BMA400 accelerometer with Arduino using I2C**
* Configure the sensor to **detect motion**
* Generate an **interrupt signal when motion is detected**
* Print **“Motion detected!”** on the Serial Monitor

In simple words:

> The sensor monitors movement, and when acceleration exceeds a set threshold, it triggers an interrupt to notify the Arduino that motion has occurred.

---

# 2️⃣ Working Principle

The **BMA400 accelerometer** continuously measures acceleration in **three axes**:

| Axis | Motion             |
| ---- | ------------------ |
| X    | Left / Right       |
| Y    | Forward / Backward |
| Z    | Up / Down          |

In this program:

1. The sensor continuously measures acceleration.
2. A **motion threshold** is set.
3. If acceleration exceeds that threshold for a certain duration:

   * The sensor generates an **interrupt signal**.
4. The interrupt signal goes to **Arduino pin 2**.
5. Arduino runs the interrupt handler.
6. The program prints **“Motion detected!”**.

This method is efficient because the Arduino **does not need to constantly check the sensor**.

---

# 3️⃣ Code Explanation

## Library Inclusion

```cpp
#include <Wire.h>
#include "SparkFun_BMA400_Arduino_Library.h"
```

* `Wire.h` enables **I2C communication**
* `SparkFun_BMA400_Arduino_Library.h` provides functions to control the BMA400 sensor.

---

# 4️⃣ Creating Sensor Object

```cpp
BMA400 accelerometer;
```

Creates an object named **accelerometer** to communicate with the sensor.

---

# 5️⃣ I2C Address Selection

```cpp
uint8_t i2cAddress = BMA400_I2C_ADDRESS_DEFAULT;
```

Stores the **I2C address of the BMA400 sensor**.

Default address = **0x14**.

---

# 6️⃣ Interrupt Pin Definition

```cpp
int interruptPin = 2;
```

Arduino **digital pin 2** receives interrupt signals from the sensor.

---

# 7️⃣ Interrupt Flag

```cpp
volatile bool interruptOccurred = false;
```

This flag indicates whether an interrupt occurred.

`volatile` is used because the variable may change during an interrupt.

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

### Start I2C Communication

```cpp
Wire.begin();
```

Initializes the I2C bus.

---

### Check Sensor Connection

```cpp
while(accelerometer.beginI2C(i2cAddress) != BMA400_OK)
```

Checks whether the BMA400 sensor is connected.

If not connected, it prints an error message.

---

# 9️⃣ Motion Detection Configuration

The following structure defines the **motion detection parameters**:

```cpp
bma400_gen_int_conf config =
```

This configuration determines when an interrupt will occur.

---

### Threshold

```cpp
.gen_int_thres = 5
```

Acceleration threshold.

Each step = **8 mg**

Example:

```
5 × 8 mg = 40 mg
```

So motion above **40 mg** triggers detection.

---

### Duration

```cpp
.gen_int_dur = 5
```

Time duration for motion detection.

Each step = **10 ms**

```
5 × 10 ms = 50 ms
```

So motion must last **50 ms** before triggering.

---

### Axes Selection

```cpp
.axes_sel = BMA400_AXIS_XYZ_EN
```

Motion detection is enabled for **all three axes**.

---

### Data Source

```cpp
.data_src = BMA400_DATA_SRC_ACCEL_FILT_2
```

Uses **Filter 2** acceleration data for motion detection.

---

### Activity Condition

```cpp
.criterion_sel = BMA400_ACTIVITY_INT
```

Triggers interrupt when **movement occurs**.

---

### Axis Evaluation

```cpp
.evaluate_axes = BMA400_ANY_AXES_INT
```

Interrupt occurs if **any axis detects motion**.

---

### Reference Update

```cpp
.ref_update = BMA400_UPDATE_EVERY_TIME
```

The reference acceleration value updates automatically.

---

### Hysteresis

```cpp
.hysteresis = BMA400_HYST_96_MG
```

Helps remove noise by ignoring very small fluctuations.

---

### Reference Values

```cpp
.int_thres_ref_z = 512
```

Defines the reference acceleration.

Here **512 corresponds to 1g** (gravity).

---

### Interrupt Channel

```cpp
.int_chan = BMA400_INT_CHANNEL_1
```

Uses **INT1 pin** of the sensor.

---

### Apply Motion Configuration

```cpp
accelerometer.setGeneric1Interrupt(&config);
```

Applies the motion detection settings to the sensor.

---

# 🔟 Configure Interrupt Pin

```cpp
accelerometer.setInterruptPinMode(
BMA400_INT_CHANNEL_1,
BMA400_INT_PUSH_PULL_ACTIVE_1
);
```

Sets interrupt pin to:

* Push-pull mode
* Active HIGH signal

---

# 1️⃣1️⃣ Enable Interrupt

```cpp
accelerometer.enableInterrupt(BMA400_GEN1_INT_EN, true);
```

Enables **Generic Interrupt 1**, which detects motion.

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

If motion triggered the interrupt:

1. Reset the flag
2. Check interrupt status
3. Print the message.

---

### Check Interrupt Type

```cpp
if(interruptStatus & BMA400_ASSERTED_GEN1_INT)
```

Confirms that the interrupt occurred due to **motion detection**.

---

### Print Motion Message

```cpp
Serial.println("Motion detected!");
```

Displays the message in the Serial Monitor.

---

# 1️⃣4️⃣ Interrupt Handler

```cpp
void bma400InterruptHandler()
{
 interruptOccurred = true;
}
```

When motion occurs:

* The sensor sends an interrupt signal
* Arduino runs this function
* The flag becomes **true**

Then the loop processes the event.

---

# 1️⃣5️⃣ Example Output

```
Interrupt occurred!   Motion detected!
Interrupt occurred!   Motion detected!
```

---

