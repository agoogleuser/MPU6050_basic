#ifndef MPU6050_BASIC_H
#define MPU6050_BASIC_H

//====register addresses

//GYRO and ACCEL control registers
#define MPU_POWER       0x6B
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


#ifndef gyroMode
//Setting a default value for gyroMode.
    #define gyroMode pm1000
#endif

#if gyroMode == pm2000
    #define gyroConverter 131
#elif gyroMode == pm1000
    #define gyroConverter 65.5
#elif gyroMode == pm500
    #define gyroConverter 32.8
#else
    #define gyroConverter 16.4
#endif

//Accelerometer modes
#define pm2             0b00000
#define pm4             0b01000
#define pm8             0b10000
#define pm16            0b11000

#ifndef accelMode
//Setting a default value for gyroMode.
    #define accelMode pm4
#endif

#if accelMode == pm16
    #define accelConverter 2048
#elif accelMode == pm8
    #define accelConverter 4096
#elif accelMode == pm4
    #define accelConverter 8192
#else
    #define accelConverter 16384
#endif

//max frequency is 400KHz
#define MPU_ADDRESS     0b1101000 
#define MPU_SENSOR_ID   0x652

//====Functions
void mpu_init();

float gyro_read_x();
float gyro_read_y();
float gyro_read_z();
float readAngle(char axes,bool reset);

float accel_read_x();
float accel_read_y();
float accel_read_z();
float readVelocity(char axes, bool reset);
float readPosition(char axes, bool reset);
#endif
