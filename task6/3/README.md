1️⃣ Objective of the Program

The objective of this program is:

* To **connect the BMA400 accelerometer with Arduino using I2C**
* To **use an interrupt signal when new sensor data is ready**
* To **read and print acceleration values (X, Y, Z) on the serial monitor**

In simple words:

> Instead of repeatedly checking the sensor, the Arduino waits for a signal (interrupt) from the BMA400 indicating that new acceleration data is ready.

---

# 2️⃣ Working Principle

Normally, Arduino programs continuously check sensors in the loop.

But in this program the **BMA400 sends an interrupt signal** when new data is available.

Steps of operation:

1. The BMA400 measures acceleration.
2. When new data is ready, it sends a signal through the **INT1 pin**.
3. This signal goes to **Arduino digital pin 2**.
4. Arduino detects this signal using an interrupt.
5. The interrupt handler sets a flag.
6. The loop function reads the sensor data and prints it.

This method is **more efficient** because the Arduino reads data **only when needed**.

---

# 3️⃣ Code Explanation

## Including Libraries

```cpp
#include <Wire.h>
#include "SparkFun_BMA400_Arduino_Library.h"
```

* `Wire.h` enables I2C communication.
* `SparkFun_BMA400_Arduino_Library.h` allows Arduino to control the BMA400 sensor.

---

## Creating Sensor Object

```cpp
BMA400 accelerometer;
```

Creates an object named **accelerometer** to access sensor functions.

---

## I2C Address Selection

```cpp
uint8_t i2cAddress = BMA400_I2C_ADDRESS_DEFAULT;
```

Stores the I2C address of the sensor.

Default address = **0x14**.

---

## Interrupt Pin Definition

```cpp
int interruptPin = 2;
```

Arduino **digital pin 2** is used to receive the interrupt signal from the sensor.

---

## Interrupt Flag

```cpp
volatile bool interruptOccurred = false;
```

This variable tells the program whether an interrupt happened.

`volatile` is used because the value may change during an interrupt.

---

# 4️⃣ Setup Function

```cpp
void setup()
```

Runs once when Arduino starts.

---

### Start Serial Communication

```cpp
Serial.begin(115200);
```

Starts communication with the computer.

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

Checks whether the BMA400 is connected.

If not connected, an error message is printed.

---

### Reduce Output Data Rate

```cpp
accelerometer.setODR(BMA400_ODR_12_5HZ);
```

ODR = **Output Data Rate**.

Default is **200 Hz**, which is very fast.

This program reduces it to **12.5 Hz** so data arrives slower and is easier to read.

---

### Select Interrupt Channel

```cpp
accelerometer.setDRDYInterruptChannel(BMA400_INT_CHANNEL_1);
```

The BMA400 has **two interrupt pins (INT1 and INT2)**.

Here we use **INT1**.

---

### Configure Interrupt Mode

```cpp
accelerometer.setInterruptPinMode(BMA400_INT_CHANNEL_1, BMA400_INT_PUSH_PULL_ACTIVE_1);
```

This sets the interrupt pin to:

* **Push-pull mode**
* **Active HIGH signal**

This means the interrupt pin goes **HIGH when triggered**.

---

### Enable Interrupt

```cpp
accelerometer.enableInterrupt(BMA400_DRDY_INT_EN, true);
```

Enables the **Data Ready interrupt**.

This means the sensor sends an interrupt whenever **new data is available**.

---

### Attach Arduino Interrupt

```cpp
attachInterrupt(digitalPinToInterrupt(interruptPin), bma400InterruptHandler, RISING);
```

This tells Arduino:

* Watch **pin 2**
* When the signal **rises from LOW to HIGH**
* Run the function **bma400InterruptHandler()**

---

# 5️⃣ Loop Function

```cpp
void loop()
```

Runs continuously.

---

### Check Interrupt Flag

```cpp
if(interruptOccurred)
```

Checks if the interrupt happened.

---

### Reset Flag

```cpp
interruptOccurred = false;
```

Resets the flag for the next interrupt.

---

### Read Interrupt Status

```cpp
uint16_t interruptStatus = 0;
accelerometer.getInterruptStatus(&interruptStatus);
```

Checks **which interrupt caused the signal**.

---

### Check Data Ready Condition

```cpp
if(interruptStatus & BMA400_ASSERTED_DRDY_INT)
```

Checks if the interrupt was due to **new sensor data**.

---

### Read Sensor Data

```cpp
accelerometer.getSensorData();
```

Reads acceleration values from the sensor.

---

### Print Acceleration Values

```cpp
Serial.print("X: ");
Serial.print(accelerometer.data.accelX, 3);
```

Prints acceleration values in **X, Y, Z axes**.

`3` means **3 decimal places**.

---

# 6️⃣ Interrupt Handler Function

```cpp
void bma400InterruptHandler()
{
    interruptOccurred = true;
}
```

This function runs **when the interrupt occurs**.

It simply sets the flag **interruptOccurred = true**.

Then the loop reads the sensor data.

---

# 7️⃣ Example Output

Serial Monitor may show:

```
Interrupt occurred!  Acceleration in g's  X: 0.003  Y: -0.011  Z: 1.001
Interrupt occurred!  Acceleration in g's  X: 0.004  Y: -0.010  Z: 0.998
```

---



