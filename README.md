# MPU6050_basic
## About:
A MPU6050 driver I wrote that only reads sensor data from the MPU, for arduino nano , used for a Line Follower. My team only needed Gyroscope and Accelerometer Readings for the project, and most libraries were too big to fit all the project, So I wrote this library myself.

**IMPORTANT: I Haven't tested this Library yet and the example needs to be re-written as of now**

In this file, I will explain how to get started to use this library for your projects.

## Functions summary:

This is a quick summary for the functions that can be used in this Library for quick refrencing. Details are explained later below.

```cpp
#define gyroMode pm1000
//modes --> {pm250, pm500, pm1000, pm2000}
#define accelMode pm4
//modes --> {pm2, pm4, pm8, pm16}
void mpu_init();    //Reset the MPU and reconfigure Accelerometer and Gyroscope Ranges. Must be used after the two lines above.

//Getting Reading from Gyroscope in [deg/sec]
float gyro_read_x();
float gyro_read_y();
float gyro_read_z();
//Getting Angle Reading from gyroscope by integration over time.
float readAngle(char axes,bool reset);

//Getting Accelerometer readings.
float accel_read_x();
float accel_read_y();
float accel_read_z();
```

## MPU Initialization.
The MPU6050 communicates using the IIC protocol, It has a 7-bit address = `0x68` or `0x69` depending on the input on `A0` pin in the IC, which is considered the first bit in the MPU adress.

The function `mpu_init()` automatically sets the Arduino as a master, resets the MPU and configure the gyroscope and accelerometer ranges.

To properly initialize your MPU6050, you should write your code something like this:
```cpp
#include <MPU6050_basic.h>
//-----other libraties and stuff-----
#define gyroMode    pm1000 //or any other value, will explain later.
#define accelMode   pm8

void setup()
{
    mpu_init();
 //-----------------------rest of the code------------------------
```
As seen above, `gyroMode` and `accelMode` should be defined before calling the function `mpu_init()`

### Gyroscope Ranges:
The Gyroscope in MPU6050 has four ranges shown in the below table:

|Range(deg/sec)|#define parameter|
|:-----:|:-----:|
|±250|`pm250`|
|±500|`pm500`|
|±1000|`pm1000`|
|±2000|`pm2000`|

These mode refer to the highest and lowest change they can sense.

In my experience, The higher the range, the lower the error in `readAngle()` function. You should choose the higher possible value, depending on the accuracy you need in your project.
### Accelerometer Ranges:

The Accelerometer also have four ranges you can choose from, As shown in the table below:

|Range(m/s^2)|#define parameter|
|:-----:|:-----:|
|±2|`pm2`|
|±4|`pm4`|
|±8|`pm8`|
|±16|`pm16`|

## Taking Readings
### Gyroscope
To get Reading from the MPU6050, you must initialise it as shown above. 
After initialization, The following Functions return a floating point value in Deg/sec
```cpp
gyro_read_x();
gyro_read_y();
gyro_read_z();
```
To get the Angle reading, Normally you will integrate the returned values from the previous three functions to get roll(`'x'`), pitch(`'y'`) and yaw (`'z'`) respectively, but I added a function that basically does that
```cpp
readAngle('x',false);
```
The first run of this function should return a zero. Then the output will change depending on your angle and the noise and inaccuracies in time measurements (which its significance largely dependent in `gyroMode`).

It's preferred to run this function in a `loop` to get accurate readings. and If you want to reset the reading, you should changing `false` to `true`, but it's recomennded to be outside of an infinite loop or the value will be nearly always equal to zero.

### Accelerometer

Its reading is the same as the gyroscope. and the functions are the following: The returned values are in meters/second^2
```cpp
accel_read_x();
accel_read_y();
accel_read_z();
```
You can Get the Velocity by integrating the values from these functions, and you can get the distance by integrating the velocity, for each axis. The function to automatically do this is not implement yet and will be in the near future, unless you want to implement it yourself before me :)
