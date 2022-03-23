#include <Arduino.h>
#include <Wire.h>
#include "mpu6050_basic.h"

static float milliOld_mpu = 0;
static float milliNew_mpu = 0;
static float dt = 0;

//=======Read and Write Functions.
void MPU_reg_write(uint8_t regAdr, uint8_t regData)
{
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(regAdr);
    Wire.write(regData);
    Wire.endTransmission();
}

uint8_t MPU_reg_read(uint8_t regAdr, int num)
{ // reads one or two registers (for If it's needed to read a register that is split into 2 banks)
    uint8_t reading = 0;
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(regAdr);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS, num, true);
    if (num == 2)
        reading = (Wire.read() << 8) | Wire.read();
    else if (num == 1)
        reading = Wire.read();

    return reading;
}
//=======MPU Initialization
void mpu_init()
{ // should be called after defining gyroMode and accelMode
    Wire.begin();
    MPU_reg_write(MPU_POWER, 0);
    MPU_reg_write(GYRO_CONFIG, gyroMode);
    MPU_reg_write(ACCEL_CONFIG, accelMode);
}
//=======Gyroscope Reading
inline float gyro_read_x()
{
    float reading = (float)MPU_reg_read(GYRO_XOUT_H, 2);
    return reading / gyroConverter;
}
inline float gyro_read_y()
{
    float reading = (float)MPU_reg_read(GYRO_YOUT_H, 2);
    return reading / gyroConverter;
}
inline float gyro_read_z()
{
    float reading = (float)MPU_reg_read(GYRO_ZOUT_H, 2);
    return reading / gyroConverter;
}
// * Added Functions to read the rotation relative to initial starting position
float readAngle(char axes, bool reset)
{
// TODO: Test this compiler error if it works
#if axes != 'x' || axex != 'y' || axes != 'z'
#error "Wrong axes input. Correct input should be either 'x', 'y' or 'z'."
#endif
    static float yaw = 0;
    yaw = (reset == true) ? 0 : yaw;
    milliOld_mpu = milliNew_mpu;
    milliNew_mpu = millis();
    dt_mpu = (milliOld_mpu - milliNew_mpu) / 1000;
    // TODO: Check if the below switch case is compilable using a string instead of a character
    switch (axes)
    {
    case 'z': // Yaw
        float reading = gyro_read_z();
        break;
    case 'y': // Pitch
        float reading = gyro_read_y();
        break;
    case 'x': // Roll
        float reading = gyro_read_x();
        break;
    }
    reading /= converter;
    yaw += reading * (dt_mpu);
    return yaw * 2; // For some reason The output here is correct if the case is pm1000.
}

//=======Accelerometer Reading.
inline float accel_read_x()
{
    float reading = (float)MPU_reg_read(GYRO_XOUT_H, 2);
    return reading / accelConverter;
}
inline float accel_read_y()
{
    float reading = (float)MPU_reg_read(GYRO_YOUT_H, 2);
    return reading / accelConverter;
}
inline float accel_read_z()
{
    float reading = (float)MPU_reg_read(GYRO_ZOUT_H, 2);
    return reading / accelConverter;
}

// TODO: add Functions to get the velocity and position.