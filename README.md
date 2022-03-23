# MPU6050_basic
## About:
A MPU6050 driver I wrote that only reads sensor data from the MPU, for arduino nano , used for a Line Follower. My team only needed Gyroscope and Accelerometer Readings for the project, and most libraries were too big to fit all the project, So I wrote this library myself.

In this file, I will explain how to get started to use this library for your projects.

## Functions used:

### MPU Initialization.
The MPU6050 communicates using the IIC protocol, It has a 7-bit address = `0x68` or `0x69` depending on the input on `A0` Pin in the IC, which is considered the first bit in the MPU adress.

To begin operating the MPU, It must be reset after poweering up in order to work and return correct values.

```cpp
#include <wire.h>
#define gyroMode pm1000
void setup()
{

}
```
### Gyroscope
#### Configuration
```c
gyro_init(uint8_t mode);
```
This Functions must be used in the setup of the microcontroller to specify the range of the readings, The higher the range, the Lower the error and precision.

There are Four modes in the Gyroscope:

* ±250  Deg/sec
* ±500  Deg/sec
* ±100  Deg/sec
* ±2000 Deg/sec

```c
gyro_read_x();
gyro_read_y();
gyro_read_z();
```