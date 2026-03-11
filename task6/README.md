1️⃣ What is BMA400?

**BMA400 is a 3-axis ultra-low power accelerometer.**

👉 In simple words:
It measures **acceleration / movement** in **X, Y, and Z directions**.

Typical uses:

* Step counter
* Activity detection (walking, running, still)
* Tap / double tap
* Wake-up from sleep (motion-based)
* Battery-powered devices (wearables, IoT)

This explanation is based on the official Bosch datasheet .

---

## 2️⃣ Key Features (Why BMA400 is special)

### ✅ 3-Axis Accelerometer

* Measures acceleration on **X, Y, Z axes**
* Output is **12-bit digital data**

### ✅ Ultra-Low Power

* **Sleep mode:** ~160 nA (extremely low)
* **Low power mode:** ~850 nA
* **Normal mode:** ~3.5 µA to 14.5 µA

👉 This is why it’s perfect for **coin-cell battery devices**

---

## 3️⃣ Measurement Range (g-range)

You can choose how much acceleration it can measure:

| Range | Meaning                         |
| ----- | ------------------------------- |
| ±2g   | Very sensitive (best for steps) |
| ±4g   | Normal motion                   |
| ±8g   | Faster motion                   |
| ±16g  | High shock / drops              |

Configured using:

```
ACC_CONFIG1.acc_range
```

---

## 4️⃣ Power Modes (Very Important)

BMA400 has **3 power modes** 👇

### 🔹 Sleep Mode

* No measurements
* Lowest power
* Registers can still be read/written

### 🔹 Low-Power Mode

* Fixed **25 Hz** sampling
* Used for **activity detection**
* Can **auto-wake** the sensor

### 🔹 Normal Mode

* Sampling from **12.5 Hz to 800 Hz**
* FIFO works here
* All interrupts available

👉 You switch modes using:

```
ACC_CONFIG0.power_mode
```

---

## 5️⃣ Output Data Rate (ODR)

This tells **how fast data is updated**.

Examples:

* 12.5 Hz → slow movement
* 100 Hz → normal motion
* 800 Hz → fast motion / vibration

Configured via:

```
ACC_CONFIG1.acc_odr
```

---

## 6️⃣ Acceleration Data Format

* Data is **12-bit signed (two’s complement)**
* Stored in registers:

```
ACC_X_LSB / MSB
ACC_Y_LSB / MSB
ACC_Z_LSB / MSB
```

To read data correctly:

* Always do a **burst read of all 6 bytes**
* Then convert to signed value

Example logic:

```c
if (X > 2047) X = X - 4096;
```

---

## 7️⃣ FIFO (First-In First-Out Buffer)

### What is FIFO?

It stores acceleration data **inside the sensor**, so MCU doesn’t need to read every sample.

### FIFO Details

* Size: **1024 bytes**
* Works only in **normal mode**
* Can store:

  * X, Y, Z data
  * 8-bit or 12-bit format
* Has **watermark interrupt** and **FIFO full interrupt**

👉 Very useful for **low-power systems**

---

## 8️⃣ Interrupts (Big Feature of BMA400)

BMA400 has **smart on-chip interrupts**, so MCU can sleep.

### Common interrupts:

* ✅ Data Ready
* ✅ Step Counter
* ✅ Activity / Inactivity
* ✅ Wake-up on motion
* ✅ Tap / Double tap
* ✅ Orientation change
* ✅ FIFO watermark / full

Interrupts can be:

* **Latched** (stay ON until read)
* **Non-latched** (auto clear)

Mapped to:

```
INT1 or INT2 pin
```

---

## 9️⃣ Step Counter & Activity Recognition

Built-in hardware features:

* Step counting (very low power ~4 µA)
* Activity recognition:

  * Walking
  * Running
  * Standing still

👉 No complex algorithm needed in MCU.

---

## 🔟 Communication Interface

BMA400 supports:

* **I²C**
* **SPI (3-wire / 4-wire)**

Voltage:

* VDD: 1.72 – 3.6 V
* VDDIO: 1.2 – 3.6 V

---

## 1️⃣1️⃣ Typical Applications

* Fitness bands
* Smart watches
* Motion-based wake-up systems
* Step counters
* Drop detection
* IoT battery devices


