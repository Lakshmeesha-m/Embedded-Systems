1️⃣ Objective of the Program

The objective of this program is to:

* Interface the **BMA400 accelerometer with Arduino using I2C**
* Configure the sensor to **detect tap gestures**
* Trigger an **interrupt when a tap occurs**
* Display whether it is a **single tap or double tap** on the Serial Monitor

In simple words:

> When the sensor is tapped, it detects the sudden acceleration spike and sends a signal to the Arduino, which prints whether the tap was single or double.

---

# 2️⃣ Working Principle

The **BMA400 accelerometer** measures acceleration in **X, Y, and Z axes**.

When a tap occurs:

1. A **sudden acceleration spike** happens.
2. The sensor detects a **positive and negative peak pattern** typical of a tap.
3. The sensor checks timing conditions to distinguish between:

   * **Single tap**
   * **Double tap**
4. If the conditions match:

   * The sensor generates an **interrupt signal**.
5. The interrupt signal goes to **Arduino pin 2**.
6. Arduino checks the interrupt status and prints:

   * **Single tap**
   * **Double tap**

---

# 3️⃣ Code Explanation

## 1. Including Libraries

```cpp
#include <Wire.h>
#include "SparkFun_BMA400_Arduino_Library.h"
```

* `Wire.h` enables **I2C communication**
* `SparkFun_BMA400_Arduino_Library.h` provides functions to control the BMA400 sensor

---

# 4️⃣ Creating Sensor Object

```cpp
BMA400 accelerometer;
```

Creates an object named **accelerometer** used to interact with the sensor.

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

Checks whether the sensor is connected.

If not connected, the program prints an error message.

---

# 9️⃣ Sensor Configuration for Tap Detection

### Set Output Data Rate

```cpp
accelerometer.setODR(BMA400_ODR_200HZ);
```

ODR = **Output Data Rate**

Tap detection requires **200 Hz sampling** to capture fast taps.

---

### Increase Measurement Range

```cpp
accelerometer.setRange(BMA400_RANGE_16G);
```

Tap events create **large acceleration spikes**, so the range is increased to **16g**.

---

# 🔟 Tap Detection Configuration

```cpp
bma400_tap_conf config
```

This structure defines parameters for tap detection.

---

### Axis Selection

```cpp
.axes_sel = BMA400_TAP_Z_AXIS_EN
```

Tap detection is enabled on the **Z-axis**.

This is common because tapping the board produces strong motion along the vertical axis.

---

### Sensitivity

```cpp
.sensitivity = BMA400_TAP_SENSITIVITY_0
```

Defines how sensitive the tap detection is.

Lower value → **more sensitive**.

---

### Tap Duration Threshold

```cpp
.tics_th = BMA400_TICS_TH_18_DATA_SAMPLES
```

Maximum time allowed between **peak acceleration signals** for a tap.

---

### Quiet Time Between Taps

```cpp
.quiet = BMA400_QUIET_60_DATA_SAMPLES
```

Minimum delay between two taps.

Helps prevent noise from being detected as taps.

---

### Double Tap Timing

```cpp
.quiet_dt = BMA400_QUIET_DT_4_DATA_SAMPLES
```

Minimum time between taps to recognize **double taps**.

---

### Interrupt Channel

```cpp
.int_chan = BMA400_INT_CHANNEL_1
```

Uses **INT1 pin** of the sensor.

---

### Apply Tap Configuration

```cpp
accelerometer.setTapInterrupt(&config);
```

Applies the tap detection settings.

---

# 1️⃣1️⃣ Configure Interrupt Pin

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

# 1️⃣2️⃣ Enable Tap Interrupts

Enable **single tap detection**:

```cpp
accelerometer.enableInterrupt(BMA400_SINGLE_TAP_INT_EN, true);
```

Enable **double tap detection**:

```cpp
accelerometer.enableInterrupt(BMA400_DOUBLE_TAP_INT_EN, true);
```

---

# 1️⃣3️⃣ Attach Arduino Interrupt

```cpp
attachInterrupt(
digitalPinToInterrupt(interruptPin),
bma400InterruptHandler,
RISING
);
```

Arduino monitors **pin 2**.

When the signal goes **LOW → HIGH**, the interrupt handler runs.

---

# 1️⃣4️⃣ Loop Function

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

Determines what event triggered the interrupt.

---

### Detect Tap Type

Single tap detection:

```cpp
if(interruptStatus & BMA400_ASSERTED_S_TAP_INT)
```

Prints:

```
Single tap!
```

Double tap detection:

```cpp
else if(interruptStatus & BMA400_ASSERTED_D_TAP_INT)
```

Prints:

```
Double tap!
```

---

# 1️⃣5️⃣ Interrupt Handler

```cpp
void bma400InterruptHandler()
{
    interruptOccurred = true;
}
```

This function runs when the interrupt occurs.

It simply sets the flag **interruptOccurred = true**.

---

# 1️⃣6️⃣ Example Output

```
Interrupt occurred!   Single tap!
Interrupt occurred!   Double tap!
```

---
