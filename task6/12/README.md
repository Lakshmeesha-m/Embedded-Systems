1️⃣ Objective of the Program

The objective of this program is to:

* Show how **error codes returned by sensor functions can be handled**
* Demonstrate how to **reconnect to the sensor if communication fails**
* Identify problems such as:

  * wrong I2C address
  * missing initialization
  * invalid configuration

In simple words:

> This program teaches how to detect and fix communication errors when using the BMA400 sensor.

---

# 2️⃣ Working Principle

Every function in the BMA400 library returns an **error code**.

Example error codes from the library:

| Error Code                | Meaning                |
| ------------------------- | ---------------------- |
| `BMA400_OK`               | No error               |
| `BMA400_E_NULL_PTR`       | Sensor not initialized |
| `BMA400_E_COM_FAIL`       | Communication failure  |
| `BMA400_E_DEV_NOT_FOUND`  | Wrong device detected  |
| `BMA400_E_INVALID_CONFIG` | Invalid configuration  |
| `BMA400_W_SELF_TEST_FAIL` | Self-test warning      |

The program checks these codes and takes appropriate actions such as:

* reconnecting to the sensor
* printing error messages
* freezing the program if a serious error occurs

---

# 3️⃣ Code Explanation

## 1. Including Libraries

```cpp
#include <Wire.h>
#include "SparkFun_BMA400_Arduino_Library.h"
```

* `Wire.h` enables I2C communication
* `SparkFun_BMA400_Arduino_Library.h` controls the BMA400 sensor

---

# 4️⃣ Creating Sensor Object

```cpp
BMA400 accelerometer;
```

Creates an object to communicate with the accelerometer.

---

# 5️⃣ I2C Address Selection

```cpp
uint8_t i2cAddress = BMA400_I2C_ADDRESS_SECONDARY;
```

This example intentionally uses the **secondary address (0x15)** to demonstrate errors.

Normally the default address is **0x14**.

---

# 6️⃣ Error Code Variable

```cpp
int8_t err = BMA400_OK;
```

Stores the error code returned by sensor functions.

---

# 7️⃣ Connection Retry Settings

```cpp
#define CONNECT_MAX_RETRIES 10
#define CONNECT_RETRY_INTERVAL 1000
```

If the connection fails:

* retry up to **10 times**
* wait **1 second between attempts**

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

Used to print messages to the Serial Monitor.

---

### Show Warning Message

The program prints a warning that **intentional errors exist in the code**.

---

### Give User Hints

```cpp
giveHints();
```

This function allows the user to request hints to fix the code.

---

### Start I2C

```cpp
Wire.begin();
```

Initializes I2C communication.

---

### Intentional Error

The sensor initialization function is commented out:

```cpp
// connectAndInit();
```

Because of this, the sensor **is never initialized**, which will cause errors.

---

# 9️⃣ Loop Function

```cpp
void loop()
```

Runs continuously.

---

### Read Sensor Data

```cpp
err = accelerometer.getSensorData();
```

Attempts to read acceleration values.

Since the sensor was not initialized, an error occurs.

---

### Handle Error

```cpp
handleError(err);
```

This function checks the error code and decides what to do.

---

### Print Acceleration Data

```cpp
Serial.print(accelerometer.data.accelX);
```

If no error occurs, the program prints:

* X acceleration
* Y acceleration
* Z acceleration

---

# 🔟 connectAndInit() Function

This function connects to the sensor and initializes it.

Steps:

1️⃣ Call `connectToBMA400()` to establish connection
2️⃣ Run the **self-test** feature of the sensor
3️⃣ Configure sensor parameters

---

### Intentional Configuration Error

```cpp
accelerometer.setODR(200);
```

This is incorrect.

Correct usage should be:

```cpp
accelerometer.setODR(BMA400_ODR_200HZ);
```

This causes the **BMA400_E_INVALID_CONFIG error**.

---

# 1️⃣1️⃣ connectToBMA400() Function

This function attempts to connect to the sensor.

Steps:

1. Increase connection attempt counter
2. Try connecting using `beginI2C()`
3. If successful → reset counter
4. If failed → retry until max attempts reached

If connection fails too many times, the program stops.

---

# 1️⃣2️⃣ handleError() Function

This function processes the error codes.

Examples:

### Null Pointer Error

```cpp
BMA400_E_NULL_PTR
```

Means the sensor is not initialized.

Solution:

Reconnect to the sensor.

---

### Communication Failure

```cpp
BMA400_E_COM_FAIL
```

Usually caused by:

* incorrect wiring
* wrong I2C address

The program retries connection.

---

### Device Not Found

```cpp
BMA400_E_DEV_NOT_FOUND
```

Means the device connected is not BMA400.

The program stops.

---

### Invalid Configuration

```cpp
BMA400_E_INVALID_CONFIG
```

Indicates a coding mistake.

The program freezes.

---

### Self Test Warning

```cpp
BMA400_W_SELF_TEST_FAIL
```

Sensor works but measurements may be unreliable.

---

# 1️⃣3️⃣ freeze() Function

```cpp
while(1);
```

Stops the program completely if a serious error occurs.

This prevents the system from continuing with incorrect data.

---

# 1️⃣4️⃣ giveHints() Function

This function helps users identify the intentional errors.

Hints include:

1️⃣ Wrong I2C address
2️⃣ Missing sensor initialization
3️⃣ Incorrect ODR configuration
4️⃣ Search for comments labeled **INTENTIONAL ERROR**

---

# 1️⃣5️⃣ Example Output

If errors occur, the Serial Monitor may show messages like:

```
Communication failure, check wiring and I2C address!
Null pointer! Reconnecting...
Invalid config!
Freezing program.
```

---


