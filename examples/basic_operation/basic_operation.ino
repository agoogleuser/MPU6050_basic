<<<<<<< HEAD
#include <mpu6050_basic.h>
#include <Wire.h>

float gyro[3],accel[3];

void setup() {
  Wire.begin();       //Initialise the Arduino board as a master
  Serial.begin(9600); //Initializing USB connection to PC for outputs.
  gyro_init(pm2);
  accel_init(pm250);
}

void loop()
{
  gyro[0] = gyro_read_x();
  gyro[1] = gyro_read_y();
  gyro[2] = gyro_read_z();

  accel[0] = accel_read_x();
  accel[1]= accel_read_y();
  accel[2] = accel_read_z();

  for (int i=0; i<3; i++)
  {
    Serial.print(gyro[i]);
    Serial.print("    ");
    Serial.println(accel[i]);
  }
=======
#include <mpu6050_basic.h>
#include <Wire.h>

float gyro[3],accel[3];

void setup() {
  Wire.begin();       //Initialise the Arduino board as a master
  Serial.begin(9600); //Initializing USB connection to PC for outputs.
  gyro_init(pm2);
  accel_init(pm250);
}

void loop()
{
  gyro[0] = gyro_read_x();
  gyro[1] = gyro_read_y();
  gyro[2] = gyro_read_z();

  accel[0] = accel_read_x();
  accel[1]= accel_read_y();
  accel[2] = accel_read_z();

  for (int i=0; i<3; i++)
  {
    Serial.print(gyro[i]);
    Serial.print("    ");
    Serial.println(accel[i]);
  }
>>>>>>> 0426e32d10b5c2fc4fec789be19a95eda52d48d0
}