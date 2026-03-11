1️⃣ Objective of the Program

The objective of this program is:

* To connect the **BMA400 accelerometer with Arduino using I2C**
* To **apply filtering to sensor data to reduce noise**
* To **improve measurement accuracy**
* To **display the filtered acceleration values (X, Y, Z) on the Serial Monitor**

In simple words:

> The program reads acceleration from the sensor and uses built-in filters to make the data smoother and more accurate before printing it.

---

# 2️⃣ Working Principle

The **BMA400 accelerometer** measures motion in **three axes**:

| Axis | Motion             |
| ---- | ------------------ |
| X    | Left / Right       |
| Y    | Forward / Backward |
| Z    | Up / Down          |

However, raw sensor data usually contains **noise** (small unwanted variations).

To reduce this noise, the program:

1. **Increases oversampling** → improves accuracy
2. **Reduces measurement range** → increases resolution
3. **Uses built-in filters** → smooths the data
4. **Reduces output data rate** → reduces noise and improves stability

After filtering, the Arduino reads the acceleration values and prints them on the serial monitor.

---

# 3️⃣ Code Explanation

## Including Libraries

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

Creates an object called **accelerometer** which allows the program to interact with the sensor.

---

# 5️⃣ I2C Address Selection

```cpp
uint8_t i2cAddress = BMA400_I2C_ADDRESS_DEFAULT;
```

This stores the **I2C address of the BMA400**.

Default address = **0x14**.

---

# 6️⃣ Setup Function

```cpp
void setup()
```

The **setup() function runs once when the Arduino starts**.

---

### Start Serial Communication

```cpp
Serial.begin(115200);
```

Starts communication between Arduino and computer.

Baud rate = **115200**.

---

### Print Start Message

```cpp
Serial.println("BMA400 Example 4 - Filtering");
```

Displays the program name in the Serial Monitor.

---

### Start I2C Communication

```cpp
Wire.begin();
```

Initializes the I2C communication between Arduino and the sensor.

---

### Check Sensor Connection

```cpp
while(accelerometer.beginI2C(i2cAddress) != BMA400_OK)
```

This checks if the sensor is connected properly.

If not connected, it prints an error message and keeps trying.

---

### Sensor Connected Message

```cpp
Serial.println("BMA400 connected!");
```

Printed when the sensor is detected successfully.

---

# 7️⃣ Sensor Configuration for Filtering

### Oversampling Setting

```cpp
accelerometer.setOSR(BMA400_ACCEL_OSR_SETTING_3);
```

OSR = **Oversampling Rate**

Higher oversampling:

* improves accuracy
* reduces noise
* increases power consumption

---

### Measurement Range

```cpp
accelerometer.setRange(BMA400_RANGE_2G);
```

The sensor can measure different ranges:

| Range | Meaning        |
| ----- | -------------- |
| 2g    | very sensitive |
| 4g    | default        |
| 8g    | medium         |
| 16g   | large motion   |

Setting **2g** improves **measurement resolution**.

---

### Select Data Source Filter

```cpp
accelerometer.setDataSource(BMA400_DATA_SRC_ACCEL_FILT_1);
```

The BMA400 has **two internal filters**.

This program selects **Filter 1** to smooth the acceleration data.

---

### Set Filter Bandwidth

```cpp
accelerometer.setFilter1Bandwidth(BMA400_ACCEL_FILT1_BW_1);
```

Bandwidth determines how much noise is removed.

Lower bandwidth:

* smoother data
* slower response

---

### Set Output Data Rate (ODR)

```cpp
accelerometer.setODR(BMA400_ODR_50HZ);
```

ODR = **Output Data Rate**

This controls how often the sensor sends data.

Here it is set to **50 Hz (50 readings per second)**.

Lower ODR reduces noise.

---

# 8️⃣ Loop Function

```cpp
void loop()
```

The **loop() function runs continuously**.

---

### Read Sensor Data

```cpp
accelerometer.getSensorData();
```

Reads the latest acceleration values from the sensor.

---

### Print Acceleration Heading

```cpp
Serial.print("Acceleration in g's");
```

Displays a label in the Serial Monitor.

---

### Print X Axis Value

```cpp
Serial.print("X: ");
Serial.print(accelerometer.data.accelX, 3);
```

Prints acceleration in the **X direction**.

`3` means **3 decimal places**.

---

### Print Y Axis Value

```cpp
Serial.print("Y: ");
Serial.print(accelerometer.data.accelY, 3);
```

Displays acceleration in the **Y direction**.

---

### Print Z Axis Value

```cpp
Serial.print("Z: ");
Serial.println(accelerometer.data.accelZ, 3);
```

Displays acceleration in the **Z direction**.

---

# 9️⃣ Delay

```cpp
delay(20);
```

Waits **20 milliseconds** before reading the sensor again.

This means the program prints data about **50 times per second**.

---

# 🔟 Example Output

Serial Monitor output may look like:

```
Acceleration in g's   X: 0.004   Y: -0.010   Z: 1.002
Acceleration in g's   X: 0.005   Y: -0.011   Z: 0.999
```

The values will be **smoother because filtering is applied**.

---


