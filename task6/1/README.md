1️⃣ Objective of the Program

The objective of this program is:

* To **connect the BMA400 accelerometer with Arduino using I2C**
* To **read acceleration values in X, Y and Z directions**
* To **display those values on the serial monitor**

In simple words:

> The program measures how the sensor moves or tilts and prints the acceleration values on the computer.

---

# 2️⃣ Working Principle

The **BMA400 accelerometer** is a **MEMS accelerometer**.

It measures motion in **three axes**:

* **X-axis → left / right**
* **Y-axis → forward / backward**
* **Z-axis → up / down**

The **I2C** bus is used for communication.

I2C uses two lines:

* **SDA → Data**
* **SCL → Clock**

On the Arduino Uno:

* **A4 → SDA**
* **A5 → SCL**

The Arduino reads acceleration data from the sensor and prints it to the **Arduino Serial Monitor**.

---

# 3️⃣ Code Explanation (Line by Line)

## Library Inclusion

```cpp
#include <Wire.h>
#include "SparkFun_BMA400_Arduino_Library.h"
```

* `Wire.h` → Enables **I2C communication**.
* `SparkFun_BMA400_Arduino_Library.h` → Library used to control the BMA400 sensor.

---

## Creating Sensor Object

```cpp
BMA400 accelerometer;
```

This creates an **object named `accelerometer`** that allows us to use functions from the BMA400 library.

---

## I2C Address Selection

```cpp
uint8_t i2cAddress = BMA400_I2C_ADDRESS_DEFAULT; // 0x14
```

* `uint8_t` → 8-bit integer used to store the I2C address.
* `0x14` → Default address of the BMA400 sensor.

Alternative address:

```cpp
//uint8_t i2cAddress = BMA400_I2C_ADDRESS_SECONDARY; // 0x15
```

Used if the **SDO pin is connected to VCC**.

---

# 4️⃣ Setup Function

```cpp
void setup()
```

The **setup()** function runs **only once when the Arduino starts**.

---

### Start Serial Communication

```cpp
Serial.begin(115200);
```

Starts serial communication with **baud rate 115200** to send data to the computer.

---

### Print Initial Message

```cpp
Serial.println("BMA400 Example 1 - Basic Readings I2C");
```

Displays a message on the serial monitor.

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

This line checks whether the **sensor is connected properly**.

If the sensor is **not detected**, the loop continues.

---

### Error Message

```cpp
Serial.println("Error: BMA400 not connected, check wiring and I2C address!");
```

If the sensor is not connected, the Arduino prints an error message.

---

### Wait for 1 Second

```cpp
delay(1000);
```

Waits for **1 second before checking again**.

---

### Sensor Connected Message

```cpp
Serial.println("BMA400 connected!");
```

This message appears once the sensor is successfully connected.

---

# 5️⃣ Loop Function

```cpp
void loop()
```

The **loop() function runs continuously**.

---

### Read Sensor Data

```cpp
accelerometer.getSensorData();
```

This command reads the **latest acceleration values from the sensor**.

Without this line, the acceleration values will not update.

---

### Print Acceleration Label

```cpp
Serial.print("Acceleration in g's");
```

Displays the heading in the serial monitor.

---

### Print X Axis Value

```cpp
Serial.print("X: ");
Serial.print(accelerometer.data.accelX, 3);
```

Prints acceleration in the **X direction**.

`3` means **3 decimal places**.

Example output:

```
X: 0.012
```

---

### Print Y Axis Value

```cpp
Serial.print("Y: ");
Serial.print(accelerometer.data.accelY, 3);
```

Displays acceleration in **Y direction**.

---

### Print Z Axis Value

```cpp
Serial.print("Z: ");
Serial.println(accelerometer.data.accelZ, 3);
```

Displays acceleration in **Z direction**.

---

# 6️⃣ Delay

```cpp
delay(2000);
```

The program waits **2 seconds before reading the sensor again**.

So the values update **every 2 seconds**.

---

# 7️⃣ Example Output

Serial monitor will display something like:

```
Acceleration in g's   X: 0.002   Y: -0.015   Z: 1.001
Acceleration in g's   X: 0.005   Y: -0.010   Z: 0.998
```

---
