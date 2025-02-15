#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
#include "BBTimer.hpp"

float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
float magX, magY, magZ;
bool newData = false;
int counter = 0;
const byte DEVICE_ADDRESS = 8;

#define ROWS 10 
#define COLS 3
float accBuffer[ROWS][COLS];
float gyroBuffer[ROWS][COLS];
float magBuffer[ROWS][COLS];
float buffer[ROWS][COLS];

//Create timer
BBTimer my_t3(BB_TIMER3);

//Action when timer runs out
void t3Callback() {
  newData = true; 
}


void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  my_t3.setupTimer(100000, t3Callback);
	my_t3.timerStart();
}

void loop() {
  if(newData){
    newData = false;
    Serial.println(counter);
    if(counter < 10){
      if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(accX, accY, accZ);
        accBuffer[counter][0] = accX;
        accBuffer[counter][1] = accY;
        accBuffer[counter][2] = accZ;
      }
      if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(gyroX, gyroY, gyroZ);
        gyroBuffer[counter][0] = gyroX;
        gyroBuffer[counter][1] = gyroY;
        gyroBuffer[counter][2] = gyroZ;
      }
      IMU.readMagneticField(magX, magY, magZ);
      magBuffer[counter][0] = magX;
      magBuffer[counter][1] = magY;
      magBuffer[counter][2] = magZ;
      counter++;

      if(counter ==10){
      Serial.println("Ha pasado el segundo");
      counter = 0;
      Serial.println("Data captured from accelerometer");
      for (int i = 0; i < 10; i++) {
          for (int j = 0; j < 3; j++) {
            Serial.print(accBuffer[i][j]);
            Serial.print("\t");  // Tab space for better formatting
          }
          Serial.println();  // Move to the next line after each row
      }
      Serial.println("Data captured from gyroscope");
      for (int i = 0; i < 10; i++) {
          for (int j = 0; j < 3; j++) {
            Serial.print(gyroBuffer[i][j]);
            Serial.print("\t");  // Tab space for better formatting
          }
          Serial.println();  // Move to the next line after each row
      }
      Serial.println("Data captured from magnetometer");
      for (int i = 0; i < 10; i++) {
          for (int j = 0; j < 3; j++) {
            Serial.print(magBuffer[i][j]);
            Serial.print("\t");  // Tab space for better formatting
          }
          Serial.println();  // Move to the next line after each row
      }      
    }
    }    
  }  
}
