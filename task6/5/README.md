 1️⃣ Objective of the Program

The objective of this program is to:

* Connect the **BMA400 accelerometer with Arduino using I2C**
* Store multiple acceleration readings in the **FIFO buffer**
* Trigger an **interrupt when the buffer reaches a certain level**
* Read all stored acceleration samples at once
* Display them on the **Serial Monitor**

In simple words:

> The sensor collects several acceleration readings and stores them in memory. When enough samples are collected, it sends an interrupt to Arduino, and Arduino reads all the stored data together.

---

# 2️⃣ Working Principle

The **BMA400** contains an internal **FIFO buffer** that can store multiple acceleration measurements.

Program workflow:

1. The sensor measures acceleration continuously.
2. Each reading is stored inside the **FIFO buffer**.
3. When the buffer reaches a **watermark level (15 samples)**, an interrupt is generated.
4. Arduino receives the interrupt through **pin 2**.
5. Arduino reads all stored acceleration samples from the FIFO.
6. The data is printed to the Serial Monitor.

This method is useful when:

* Many samples must be collected quickly
* The microcontroller cannot read each sample immediately
* Power consumption needs to be reduced

---

# 3️⃣ Code Explanation

## Library Inclusion

```cpp
#include <Wire.h>
#include "SparkFun_BMA400_Arduino_Library.h"
```

* `Wire.h` enables **I2C communication**
* `SparkFun_BMA400_Arduino_Library.h` allows Arduino to control the BMA400 sensor

---

# 4️⃣ Creating Sensor Object

```cpp
BMA400 accelerometer;
```

Creates an object called **accelerometer** to access sensor functions.

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

Arduino **digital pin 2** receives interrupt signals from the sensor.

---

# 7️⃣ Interrupt Flag

```cpp
volatile bool interruptOccurred = false;
```

This flag becomes **true when an interrupt occurs**.

`volatile` is used because the variable is modified by an interrupt.

---

# 8️⃣ FIFO Data Buffer

```cpp
const uint16_t numSamples = 15;
BMA400_SensorData fifoData[numSamples];
```

* `numSamples = 15` → maximum number of samples stored before interrupt
* `fifoData[]` → array used to store acceleration readings from FIFO

---

# 9️⃣ FIFO Length Tracking

```cpp
uint8_t previousFIFOLength = 0;
```

Used to monitor how many samples are currently stored in the FIFO buffer.

---

# 🔟 Setup Function

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

Checks whether the sensor is connected.

If not connected, an error message appears.

---

### Reduce Output Data Rate

```cpp
accelerometer.setODR(BMA400_ODR_12_5HZ);
```

ODR = **Output Data Rate**

Sensor produces **12.5 samples per second**.

---

# 1️⃣1️⃣ FIFO Configuration

```cpp
bma400_fifo_conf config =
{
 .conf_regs = BMA400_FIFO_X_EN | BMA400_FIFO_Y_EN | BMA400_FIFO_Z_EN,
 .conf_status = BMA400_ENABLE,
 .fifo_watermark = numSamples,
 .fifo_full_channel = BMA400_UNMAP_INT_PIN,
 .fifo_wm_channel = BMA400_INT_CHANNEL_1
};
```

This configures the FIFO buffer:

* Store **X, Y, Z acceleration data**
* Enable FIFO
* Interrupt occurs when **15 samples are stored**
* Interrupt is sent to **INT1 pin**

---

### Apply FIFO Configuration

```cpp
accelerometer.setFIFOConfig(&config);
```

Applies the FIFO settings to the sensor.

---

# 1️⃣2️⃣ Interrupt Configuration

### Set Interrupt Pin Mode

```cpp
accelerometer.setInterruptPinMode(BMA400_INT_CHANNEL_1, BMA400_INT_PUSH_PULL_ACTIVE_1);
```

Interrupt pin works in **push-pull active high mode**.

---

### Enable FIFO Watermark Interrupt

```cpp
accelerometer.enableInterrupt(BMA400_FIFO_WM_INT_EN, true);
```

Interrupt occurs when the **FIFO buffer reaches the watermark level**.

---

### Attach Arduino Interrupt

```cpp
attachInterrupt(digitalPinToInterrupt(interruptPin), bma400InterruptHandler, RISING);
```

Arduino monitors **pin 2**.

When the signal goes **LOW → HIGH**, the interrupt handler runs.

---

# 1️⃣3️⃣ Loop Function

```cpp
void loop()
```

Runs continuously.

---

### Check FIFO Length

```cpp
accelerometer.getFIFOLength(&currentFIFOLength);
```

Reads the number of samples stored in the FIFO buffer.

---

### Print FIFO Status

Example output:

```
FIFO Length: 7/15
```

This shows how full the FIFO buffer is.

---

### Handle FIFO Overflow

```cpp
accelerometer.flushFIFO();
```

If too many samples are stored, the buffer is cleared.

---

# 1️⃣4️⃣ Interrupt Handling

When FIFO reaches **15 samples**, the interrupt occurs.

```cpp
if(interruptOccurred)
```

The program detects the interrupt.

---

### Check Interrupt Type

```cpp
accelerometer.getInterruptStatus(&interruptStatus);
```

Determines which interrupt occurred.

---

### Read FIFO Data

```cpp
accelerometer.getFIFOData(fifoData, &samplesRead);
```

Reads all stored acceleration samples from the FIFO.

---

### Print Acceleration Data

Each sample prints:

```
Acceleration in g's   X: 0.004   Y: -0.011   Z: 1.001
```

---

# 1️⃣5️⃣ Interrupt Handler

```cpp
void bma400InterruptHandler()
{
 interruptOccurred = true;
}
```

When interrupt occurs:

* This function runs automatically
* It sets the interrupt flag to **true**

---

# 1️⃣6️⃣ Example Output

```
FIFO Length: 5/15
FIFO Length: 10/15
FIFO Length: 15/15
Interrupt occurred!
Acceleration in g's   X: 0.004   Y: -0.010   Z: 1.002
Acceleration in g's   X: 0.003   Y: -0.011   Z: 1.001
...
```

---
