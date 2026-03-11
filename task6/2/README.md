1️⃣ Objective of the Program

The objective of this program is:

* To **connect the BMA400 accelerometer with Arduino using SPI communication**
* To **read acceleration values in X, Y, and Z directions**
* To **display the values on the serial monitor**

In simple words:

> The program measures motion or tilt using the BMA400 sensor and prints the acceleration values on the computer.

---

# 2️⃣ Working Principle

The **BMA400 accelerometer** is a **MEMS accelerometer**.

It measures motion in three directions:

* **X-axis → left / right**
* **Y-axis → forward / backward**
* **Z-axis → up / down**

The communication used here is **SPI**.

SPI uses four main pins:

| Pin  | Function            |
| ---- | ------------------- |
| MOSI | Master Out Slave In |
| MISO | Master In Slave Out |
| SCK  | Clock signal        |
| CS   | Chip Select         |

On the Arduino Uno:

| Arduino Pin | SPI Function     |
| ----------- | ---------------- |
| 11          | MOSI             |
| 12          | MISO             |
| 13          | SCK              |
| 10          | CS (Chip Select) |

The Arduino reads acceleration data through SPI and prints it to the **Arduino Serial Monitor**.

---

# 3️⃣ Code Explanation (Line by Line)

## Including Libraries

```cpp
#include <SPI.h>
#include "SparkFun_BMA400_Arduino_Library.h"
```

* `SPI.h` → Enables **SPI communication**.
* `SparkFun_BMA400_Arduino_Library.h` → Library used to control the BMA400 sensor.

---

## Creating Sensor Object

```cpp
BMA400 accelerometer;
```

Creates an object named **accelerometer** that allows the Arduino to interact with the BMA400 sensor.

---

## SPI Parameters

```cpp
uint8_t chipSelectPin = 10;
uint32_t clockFrequency = 100000;
```

### chipSelectPin

* Defines the **CS pin** used for SPI communication.
* Pin **10** is used to select the BMA400 sensor.

### clockFrequency

* Defines the **SPI communication speed**.
* Here it is **100000 Hz (100 kHz)**.

---

# 4️⃣ Setup Function

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

### Print Initial Message

```cpp
Serial.println("BMA400 Example 2 - Basic Readings SPI");
```

Displays a message indicating the program has started.

---

### Initialize SPI

```cpp
SPI.begin();
```

Starts the SPI communication.

---

### Check Sensor Connection

```cpp
while(accelerometer.beginSPI(chipSelectPin, clockFrequency) != BMA400_OK)
```

This line checks whether the sensor is connected properly.

* `beginSPI()` initializes SPI communication with the BMA400.
* If the sensor is not detected, the loop keeps running.

---

### Error Message

```cpp
Serial.println("Error: BMA400 not connected, check wiring and CS pin!");
```

Displays an error if the sensor is not connected properly.

---

### Delay

```cpp
delay(1000);
```

Waits **1 second** before checking the sensor again.

---

### Sensor Connected Message

```cpp
Serial.println("BMA400 connected!");
```

Printed once the sensor is successfully detected.

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

Without calling this function, the values will not update.

---

### Print Acceleration Heading

```cpp
Serial.print("Acceleration in g's");
```

Displays a heading in the serial monitor.

---

### Print X Axis

```cpp
Serial.print("X: ");
Serial.print(accelerometer.data.accelX, 3);
```

Prints the acceleration value in the **X direction**.

`3` means **3 decimal places**.

---

### Print Y Axis

```cpp
Serial.print("Y: ");
Serial.print(accelerometer.data.accelY, 3);
```

Displays acceleration in **Y direction**.

---

### Print Z Axis

```cpp
Serial.print("Z: ");
Serial.println(accelerometer.data.accelZ, 3);
```

Displays acceleration in **Z direction**.

---

# 6️⃣ Delay

```cpp
delay(20);
```

The program waits **20 milliseconds** before reading the sensor again.

This means the data is printed about **50 times per second**.

---

# 7️⃣ Example Output

Serial monitor output will look like:

```
Acceleration in g's   X: 0.003   Y: -0.012   Z: 1.001
Acceleration in g's   X: 0.005   Y: -0.010   Z: 0.999
```

---

# 8️⃣ Short Explanation (For PPT or Viva)

You can explain it like this:

> This program interfaces the BMA400 accelerometer with Arduino using SPI communication. The Arduino initializes the SPI bus, checks if the sensor is connected, reads acceleration data in X, Y, and Z directions, and displays the values on the serial monitor repeatedly.

---


