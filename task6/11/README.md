1️⃣ Objective of the Program

The objective of this program is to:

* Connect the BMA400 accelerometer with Arduino using I2C
* Keep the sensor in **low-power mode to save energy**
* Automatically switch to **normal mode when motion is detected**
* Log acceleration values while motion continues
* Return to **low-power mode when motion stops**

In simple words:

> The sensor sleeps in low-power mode. When motion is detected, it wakes up, records acceleration data, and then goes back to low power when the motion stops.

---

# 2️⃣ Working Principle

The **BMA400** continuously measures acceleration even in **low-power mode**.

The program works like this:

1. The sensor starts in **low-power mode** to save energy.
2. The **wake-up interrupt** monitors acceleration changes.
3. If motion exceeds a **threshold**, the sensor:

   * switches to **normal mode**
   * generates an **interrupt signal**.
4. The interrupt is sent to **Arduino pin 2**.
5. Arduino reads and prints acceleration data continuously.
6. If motion stops for a certain time:

   * the sensor automatically returns to **low-power mode**.

This technique is widely used in **battery-powered devices** such as:

* wearable devices
* motion trackers
* IoT sensors

---

# 3️⃣ Code Explanation

## 1. Including Libraries

```cpp
#include <Wire.h>
#include "SparkFun_BMA400_Arduino_Library.h"
```

* `Wire.h` → enables **I2C communication**
* `SparkFun_BMA400_Arduino_Library.h` → library to control the sensor

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

`volatile` ensures the value can be modified by an interrupt.

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

Starts communication between Arduino and computer.

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

Checks whether the sensor is connected.

If not connected, the program repeatedly prints an error.

---

# 9️⃣ Set Sensor to Low Power Mode

```cpp
accelerometer.setMode(BMA400_MODE_LOW_POWER);
```

The sensor starts in **low-power mode** to save energy.

Important:

Low-power mode **still measures acceleration**, but at reduced power.

---

# 🔟 Configure Wake-Up Detection

```cpp
bma400_wakeup_conf wakeupConfig
```

This structure defines how the sensor wakes up.

Key parameters:

### Wake-up Threshold

```cpp
.int_wkup_threshold = 4
```

Motion must exceed this acceleration threshold to wake the sensor.

---

### Axis Selection

```cpp
.wakeup_axes_en = BMA400_AXIS_XYZ_EN
```

Motion is detected on **all three axes**.

---

### Interrupt Channel

```cpp
.int_chan = BMA400_INT_CHANNEL_1
```

Wake-up interrupt is sent through **INT1 pin**.

---

### Apply Wake-Up Configuration

```cpp
accelerometer.setWakeupInterrupt(&wakeupConfig);
```

Activates wake-up detection.

---

# 1️⃣1️⃣ Configure Automatic Low Power Mode

```cpp
bma400_auto_lp_conf autoLPConfig
```

This defines when the sensor returns to **low power**.

### Timeout Threshold

```cpp
.auto_lp_timeout_threshold = 400
```

Each unit = **2.5 ms**

Example:

```
400 × 2.5 ms = 1 second
```

If no motion occurs for **1 second**, the sensor returns to low power.

---

### Apply Auto Low Power Configuration

```cpp
accelerometer.setAutoLowPower(&autoLPConfig);
```

---

# 1️⃣2️⃣ Configure Motion Detection

```cpp
bma400_gen_int_conf config
```

This interrupt keeps resetting the timer while motion continues.

Key parameters:

| Parameter       | Meaning                 |
| --------------- | ----------------------- |
| `gen_int_thres` | Motion threshold        |
| `gen_int_dur`   | Duration of motion      |
| `axes_sel`      | Axes used for detection |
| `hysteresis`    | Reduces noise           |

---

### Apply Motion Configuration

```cpp
accelerometer.setGeneric2Interrupt(&config);
```

---

# 1️⃣3️⃣ Configure Interrupt Pin

```cpp
accelerometer.setInterruptPinMode(
BMA400_INT_CHANNEL_1,
BMA400_INT_PUSH_PULL_ACTIVE_1
);
```

Sets interrupt pin to:

* push-pull output
* active HIGH signal

---

# 1️⃣4️⃣ Enable Interrupts

Enable **wake-up interrupt**:

```cpp
accelerometer.enableInterrupt(BMA400_AUTO_WAKEUP_EN, true);
```

Enable **motion interrupt**:

```cpp
accelerometer.enableInterrupt(BMA400_GEN2_INT_EN, true);
```

---

# 1️⃣5️⃣ Attach Arduino Interrupt

```cpp
attachInterrupt(
digitalPinToInterrupt(interruptPin),
bma400InterruptHandler,
RISING
);
```

Arduino monitors **pin 2**.

When signal goes **LOW → HIGH**, the interrupt function runs.

---

# 1️⃣6️⃣ Loop Function

```cpp
void loop()
```

Runs continuously.

---

### Check if Interrupt Occurred

```cpp
if(interruptOccurred)
```

If motion triggered an interrupt:

1. reset flag
2. check interrupt type

---

### Check Wake-Up Condition

```cpp
if(interruptStatus & BMA400_ASSERTED_WAKEUP_INT)
```

If motion caused wake-up:

```
Motion detected!
```

Then acceleration data is logged.

---

# 1️⃣7️⃣ Log Acceleration Data

Function:

```cpp
logAccelData();
```

This function prints acceleration values until the sensor returns to **low power mode**.

Example output:

```
Acceleration in g's   X: 0.012   Y: -0.004   Z: 1.001
```

---

### Check Sensor Power Mode

```cpp
accelerometer.getMode(&powerMode);
```

The loop continues while the sensor is in **normal mode**.

When motion stops, it returns to **low power mode**.

---

# 1️⃣8️⃣ Interrupt Handler

```cpp
void bma400InterruptHandler()
{
    interruptOccurred = true;
}
```

When the sensor detects motion:

* interrupt is triggered
* this function sets the flag to **true**

The main loop then processes the event.

---

# 1️⃣9️⃣ Example Output

```
Interrupt occurred! Motion detected!
Acceleration in g's   X: 0.003   Y: -0.011   Z: 1.002
Acceleration in g's   X: 0.004   Y: -0.012   Z: 1.000
Returning to low power mode
```

---
