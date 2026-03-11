1️⃣ Objective of the Program

The objective of this program is to:

* Connect the **BMA400 accelerometer with Arduino using I2C**
* Configure the sensor to **detect activity changes**
* Trigger an **interrupt when motion behavior changes**
* Display which **axis experienced the activity change**

In simple words:

> The sensor compares the current motion with the previous motion. If the motion pattern changes significantly, it notifies the Arduino using an interrupt.

---

# 2️⃣ Working Principle

The **BMA400 accelerometer** measures acceleration along three axes:

| Axis | Movement           |
| ---- | ------------------ |
| X    | Left / Right       |
| Y    | Forward / Backward |
| Z    | Up / Down          |

The activity-change feature works like this:

1. The sensor collects acceleration data for a certain **time period**.
2. It calculates the **average activity level** during that period.
3. It compares this activity level with the **previous period**.
4. If the difference is larger than a **threshold**, an **interrupt is triggered**.
5. The interrupt signal is sent to **Arduino pin 2**.
6. Arduino prints **which axis experienced the activity change**.

Example situations where this is useful:

* Detecting when a **device starts moving**
* Detecting **sudden motion changes**
* Activity monitoring in wearable devices

---

# 3️⃣ Code Explanation

## 1. Including Libraries

```cpp
#include <Wire.h>
#include "SparkFun_BMA400_Arduino_Library.h"
```

* `Wire.h` enables **I2C communication**
* `SparkFun_BMA400_Arduino_Library.h` provides functions to control the sensor

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

This flag becomes **true when an interrupt occurs**.

`volatile` is used because interrupts modify this variable.

---

# 8️⃣ Setup Function

```cpp
void setup()
```

Runs once when Arduino starts.

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

Checks whether the BMA400 sensor is connected.

If not connected, the program repeatedly prints an error message.

---

# 9️⃣ Activity Change Configuration

This structure defines how the sensor detects activity changes.

```cpp
bma400_act_ch_conf config
```

---

### Activity Change Threshold

```cpp
.act_ch_thres = 10
```

Defines the sensitivity of activity detection.

Each step = **8 mg**

Example:

```
10 × 8 mg = 80 mg
```

So activity must change by **80 mg** to trigger detection.

---

### Axis Selection

```cpp
.axes_sel = BMA400_AXIS_XYZ_EN
```

Activity change detection is enabled for **all axes (X, Y, Z)**.

---

### Data Source

```cpp
.data_source = BMA400_DATA_SRC_ACC_FILT1
```

Uses **filtered acceleration data** to reduce noise.

---

### Measurement Period

```cpp
.act_ch_ntps = BMA400_ACT_CH_SAMPLE_CNT_64
```

Defines how many samples are collected before comparing activity levels.

Here **64 samples** are used.

---

### Interrupt Channel

```cpp
.int_chan = BMA400_INT_CHANNEL_1
```

Uses the **INT1 pin** of the sensor.

---

### Apply Activity Configuration

```cpp
accelerometer.setActivityChangeInterrupt(&config);
```

Applies the activity change settings.

---

# 🔟 Configure Interrupt Pin

```cpp
accelerometer.setInterruptPinMode(
BMA400_INT_CHANNEL_1,
BMA400_INT_PUSH_PULL_ACTIVE_1
);
```

Sets the interrupt pin to:

* Push-pull mode
* Active HIGH signal

---

# 1️⃣1️⃣ Enable Activity Change Interrupt

```cpp
accelerometer.enableInterrupt(BMA400_ACTIVITY_CHANGE_INT_EN, true);
```

Enables the **activity change detection feature**.

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

When the signal goes from **LOW → HIGH**, the interrupt function runs.

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

Checks which event caused the interrupt.

---

### Identify Axis with Activity Change

```cpp
if(interruptStatus & BMA400_ASSERTED_ACT_CH_X)
```

Prints activity change detected in **X-axis**.

```cpp
else if(interruptStatus & BMA400_ASSERTED_ACT_CH_Y)
```

Prints activity change detected in **Y-axis**.

```cpp
else if(interruptStatus & BMA400_ASSERTED_ACT_CH_Z)
```

Prints activity change detected in **Z-axis**.

---

# 1️⃣4️⃣ Interrupt Handler

```cpp
void bma400InterruptHandler()
{
    interruptOccurred = true;
}
```

When the interrupt occurs:

* This function runs automatically
* The flag **interruptOccurred** becomes **true**

The main loop then processes the event.

---

# 1️⃣5️⃣ Example Output

```
Interrupt occurred! Activity changed! (x-axis)
Interrupt occurred! Activity changed! (y-axis)
Interrupt occurred! Activity changed! (z-axis)
```

---
