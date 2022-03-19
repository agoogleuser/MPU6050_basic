#include <Wire.h>
#include "mpu6050_basic.h"

#define WAIT while(Wire.available())

static uint8_t gyro_mode =1;
static uint8_t accel_mode=1;

void regWrite(uint8_t regAdr, uint8_t regData)
{
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(regAdr);
    Wire.write(regData);
    Wire.endTransmission();
}
uint8_t regRead(uint8_t regAdr)
{
    static uint8_t reading;
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(regAdr);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS, 1, true);
    reading = Wire.read();
return reading;
}

//===Gyroscope Functions

void gyro_init(uint8_t mode)
{
    if (!(mode==pm250||mode==pm500||mode==pm1000||mode==pm2000)) return;
    regWrite(GYRO_CONFIG, mode);
    gyro_mode=mode;
}

uint16_t readSensor(uint8_t ADL,uint8_t ADH )
{
    //1. sends command to request lower  byte of the sensor's reading
    volatile uint8_t  lowByte = regRead(ADL);
    //2. sends command to request higher byte of the sensor's reading
    volatile uint8_t  highByte= regRead(ADH);
return (highByte<<8) | lowByte;
}

float convert_gyroData(uint16_t var)
{
    float converter=1;
    switch (gyro_mode){
        case pm250 :    converter=131;  break;
        case pm500 :    converter=65.5; break;
        case pm1000:    converter=32.8; break;
        case pm2000:    converter=16.4; break;
        default:        return 0;
    }
return ((float)var)/converter;
}

float gyro_read_x(){
    return convert_gyroData(readSensor(GYRO_XOUT_L, GYRO_XOUT_H));
}

float gyro_read_y(){
    return convert_gyroData(readSensor(GYRO_YOUT_L, GYRO_YOUT_H));
}

float gyro_read_z(){
    return convert_gyroData(readSensor(GYRO_ZOUT_L, GYRO_ZOUT_H));
}

//Accelerometer Functions
void accel_init(uint8_t mode)
{
    if (!(mode==pm2||mode==pm4||mode==pm8||mode==pm16)) return;
    regWrite(ACCEL_CONFIG, mode);
    accel_mode=mode;
}

float convert_accelData(uint16_t var){
    float converter=1;
    switch (gyro_mode){
        case pm16:      converter=2048;  break;
        case pm8:       converter=4096;  break;
        case pm4:       converter=8192;  break;
        case pm2:       converter=16384; break;
        default:        return 0;
    }
    
return ((float)var)/converter;
}

float accel_read_x(){
    return convert_accelData(readSensor(GYRO_XOUT_L, GYRO_XOUT_H));
}

float accel_read_y(){
    return convert_accelData(readSensor(GYRO_YOUT_L, GYRO_YOUT_H));
}

float accel_read_z(){
    return convert_accelData(readSensor(GYRO_ZOUT_L, GYRO_ZOUT_H));
}