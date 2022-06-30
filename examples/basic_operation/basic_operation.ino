
/**
 * @file basic_operation.ino
 * @author Armia Khairy Fahmy (you@domain.com)
 * @brief This example code demonestrates How to read data from the gyroscope and accelerometer
 * @version 0.2
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <mpu6050_basic.h>
#define gyroMode pm1000
#define accelMode pm4

float readings[15];
void setup()
{
  mpu_init();
  Serial.begin(9600);
}

void loop()
{
  int i=0;
  readings[0]  = gyro_read_x();  
  readings[1]  = gyro_read_y();  
  readings[2]  = gyro_read_z();  
  readings[3]  = accel_read_x();  
  readings[4]  = accel_read_y();  
  readings[5]  = accel_read_z();
  readings[6] += readAngle('x', true);
  readings[7] += readAngle('y', true);
  readings[8] += readAngle('z', true);
  readings[9] += readVelocity('x', true);
  readings[10] += readVelocity('y', true);
  readings[11] += readVelocity('z', true);
  readings[12] += readPosition('x', true);
  readings[13] += readPosition('y', true);
  readings[14] += readPosition('z', true);

 
  Serial.print("Gyroscope Raw Data:\t");
  //Gyroscope Raw Datas
  for (i=0; i<3; i++)
  {
    Serial.print(readings[i]);
    Serial.print("    ");
  }
  Serial.println(" ");

  Serial.print("Accelerometer Raw Data:\t");
  //Accelerometer Raw datas
  for (; i<6; i++)
  {
    Serial.print(readings[i]);
    Serial.print("    ");
  }
  Serial.println(" ");

  Serial.print("Angle Data (deg):\t");
  //Angle
  for (; i<9; i++)
  {
    Serial.print(readings[i]);
    Serial.print("    ");
  }
  Serial.println(" ");

  //velocity
  Serial.print("Velocity Data (meter/sec):\t");
  for (; i<12; i++)
  {
    Serial.print(readings[i]);
    Serial.print("    ");
  }
  Serial.println(" ");
 
  //Position
  Serial.print("Position Data (meter):\t");
  for (; i<15; i++)
  {
    Serial.print(readings[i]);
    Serial.print("    ");
  }

  Serial.println(" "); 
  Serial.println(" "); 
  Serial.println(" "); 
}