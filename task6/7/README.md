1️⃣ Objective of the Program

The objective of this program is to:

* Interface the **BMA400 accelerometer with Arduino using I2C**
* Configure the sensor to **detect orientation change**
* Generate an **interrupt when the device orientation changes**
* Print **“Orientation changed!”** on the Serial Monitor

In simple words:

> The sensor monitors the direction of gravity. When the device is tilted or rotated significantly, it sends a signal to Arduino indicating that the orientation has changed.

---

# 2️⃣ Working Principle

The **BMA400 accelerometer** measures acceleration in three axes:

| Axis  | Motion                  |
| ----- | ----------------------- |
| **X** | Left / Right tilt       |
| **Y** | Forward / Backward tilt |
| **Z** | Up / Down direction     |

When the board orientation changes:

1. The direction of **gravity (1g)** relative to the sensor axes changes.
2. The sensor checks whether this change **exceeds a threshold**.
3. It also waits until the readings become **stable**.
4. If the change persists for a certain **duration**, the sensor triggers an **interrupt**.
5. The interrupt signal goes to **Arduino pin 2**.
6. Arduino detects the interrupt and prints **“Orientation changed!”**.

This type of feature is used in devices like **smartphones where the screen rotates automatically**.

---

# 3️⃣ Code Explanation

## 1. Including Libraries

```cpp
#include <Wire.h>
#include "SparkFun_BMA400_Arduino_Library.h"
```

* `Wire.h` enables **I2C communication**.
* `SparkFun_BMA400_Arduino_Library.h` provides functions to control the BMA400 sensor.

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

Stores the I2C address of the sensor.

Default address = **0x14**.

---

# 6️⃣ Interrupt Pin

```cpp
int interruptPin = 2;
```

Arduino **digital pin 2** receives the interrupt signal from the sensor.

---

# 7️⃣ Interrupt Flag

```cpp
volatile bool interruptOccurred = false;
```

This variable becomes **true when an interrupt occurs**.

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

Checks whether the sensor is connected correctly.

If not connected, the program prints an error message.

---

# 9️⃣ Orientation Change Configuration

This structure sets the parameters for detecting orientation changes.

```cpp
bma400_orient_int_conf config
```

---

### Axes Selection

```cpp
.axes_sel = BMA400_AXIS_XYZ_EN
```

Orientation change detection is enabled for **all three axes (X, Y, Z)**.

---

### Data Source

```cpp
.data_src = BMA400_DATA_SRC_ACCEL_FILT_LP
```

Uses **low-pass filtered acceleration data** to remove noise.

---

### Reference Update

```cpp
.ref_update = BMA400_UPDATE_LP_EVERY_TIME
```

Updates the reference acceleration value automatically.

---

### Orientation Threshold

```cpp
.orient_thres = 50
```

Threshold value for orientation change.

Each step = **8 mg**

Example:

```
50 × 8 mg = 400 mg
```

So orientation change must exceed **400 mg**.

---

### Stability Threshold

```cpp
.stability_thres = 10
```

Ensures the sensor readings are stable before triggering an interrupt.

---

### Duration

```cpp
.orient_int_dur = 50
```

Time duration required for orientation change.

Each step = **10 ms**

```
50 × 10 ms = 500 ms
```

So the new orientation must remain stable for **0.5 seconds**.

---

### Reference Values

```cpp
.orient_ref_z = 512
```

Defines the reference gravity value.

At **4g range**, value **512 represents 1g**.

---

### Interrupt Channel

```cpp
.int_chan = BMA400_INT_CHANNEL_1
```

Uses the **INT1 pin** of the sensor to send interrupts.

---

### Apply Orientation Configuration

```cpp
accelerometer.setOrientationChangeInterrupt(&config);
```

Applies the orientation detection settings.

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

# 1️⃣1️⃣ Enable Interrupt

```cpp
accelerometer.enableInterrupt(BMA400_ORIENT_CHANGE_INT_EN, true);
```

Enables **orientation change interrupt detection**.

---

# 1️⃣2️⃣ Attach Arduino Interrupt

```cpp
attachInterrupt(digitalPinToInterrupt(interruptPin),
                bma400InterruptHandler,
                RISING);
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

### Check Interrupt Flag

```cpp
if(interruptOccurred)
```

Checks whether an interrupt occurred.

---

### Reset Interrupt Flag

```cpp
interruptOccurred = false;
```

Resets the flag for the next interrupt.

---

### Check Interrupt Status

```cpp
accelerometer.getInterruptStatus(&interruptStatus);
```

Determines which interrupt occurred.

---

### Detect Orientation Change

```cpp
if(interruptStatus & BMA400_ASSERTED_ORIENT_CH)
```

Confirms that the interrupt was caused by **orientation change**.

---

### Print Message

```cpp
Serial.println("Orientation changed!");
```

Displays the message on the Serial Monitor.

---

# 1️⃣4️⃣ Interrupt Handler

```cpp
void bma400InterruptHandler()
{
    interruptOccurred = true;
}
```

This function runs when the interrupt occurs.

It sets the flag **interruptOccurred = true**.

The main loop then processes the event.

---

# 1️⃣5️⃣ Example Output

```
Interrupt occurred!   Orientation changed!
Interrupt occurred!   Orientation changed!
```

This message appears whenever the device orientation changes.

---


