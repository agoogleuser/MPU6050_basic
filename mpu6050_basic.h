#ifndef MPU6050_BASIC_H
#define MPU6050_BASIC_H

//====register addresses

//GYRO and ACCEL control registers
#define GYRO_CONFIG     0x1B
#define ACCEL_CONFIG    0x1A

//three 16-bit registers for reading the accelerometer data
#define ACCEL_XOUT_H    0x3B
#define ACCEL_XOUT_L    0x3C
#define ACCEL_YOUT_H    0x3D
#define ACCEL_YOUT_L    0X3E
#define ACCEL_ZOUT_H    0x3F
#define ACCEL_ZOUT_L    0X40

//three 16-bit registers for reading the accelerometer data
#define GYRO_XOUT_H     0x43
#define GYRO_XOUT_L     0x44
#define GYRO_YOUT_H     0x45
#define GYRO_YOUT_L     0x46
#define GYRO_ZOUT_H     0x47
#define GYRO_ZOUT_L     0x48

//Gyroscope modes
#define pm250           0b00000
#define pm500           0b01000
#define pm1000          0b10000
#define pm2000          0b11000

//Accelerometer modes
#define pm2             0b00000
#define pm4             0b01000
#define pm8             0b10000
#define pm16            0b11000

//====I2C (2-wire) interface
/*
 *IMPORTANT NOTE: the I2C must be manually initialized in the arduino code
 *as a slave device using 'MPU_ADDRESS' as the slave address.
*/ 
//max frequency is 400KHz
#define MPU_ADDRESS     0b1101000 
#define MPU_SENSOR_ID   0x652
//needs check: The LSB (A0) of the slave address is variable, can be 0 or 1 
//depending on the input of AD0 pin.

//====Functions
void gyro_init(uint8_t);
float gyro_read_x();
float gyro_read_y();
float gyro_read_z();

void accel_init(uint8_t);
float accel_read_x();
float accel_read_y();
float accel_read_z();

#endif