#include <Arduino.h>
#include <Wire.h>
#include <Arduino_LSM9DS1.h>
#include "BBTimer.hpp"


float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
float magX, magY, magZ;
bool newData;
int counter = 0;
const byte DEVICE_ADDRESS = 8;
byte myBytes[4];
float myFloat;

#define ROWS 5 
#define COLS 3
float accBuffer[ROWS][COLS];
float gyroBuffer[ROWS][COLS];
float magBuffer[ROWS][COLS];

//Create timer
BBTimer my_t3(BB_TIMER3);

//Action when timer runs out
void t3Callback() {
  newData = true; 
}



void setup() {
  Wire.begin();
	my_t3.setupTimer(200000, t3Callback);
	my_t3.timerStart();
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}
void loop() {
  if(newData){
    newData= false;
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
      if(counter == 10){
        counter = 0;
        for (int i = 0; i < 5; i++) {
          Wire.beginTransmission(8);
          Wire.write(i);
          for (int j = 0; j < 3; j++) {
            myFloat = accBuffer[i][j];
            memcpy(myBytes, &myFloat, 4);
            Wire.write(myBytes, sizeof(myBytes));      
          }
          Wire.endTransmission();
          Serial.println();  
        }
        
        for (int i = 0; i < 5; i++) {
          Wire.beginTransmission(8);
          Wire.write(i);
          for (int j = 0; j < 3; j++) {
            myFloat = gyroBuffer[i][j];
            memcpy(myBytes, &myFloat, 4);
            Wire.write(myBytes, sizeof(myBytes));      
          }
          Wire.endTransmission();
          Serial.println();  
        }

        
        for (int i = 0; i < 5; i++) {
          Wire.beginTransmission(8);
          Wire.write(i);
          for (int j = 0; j < 3; j++) {
            myFloat = magBuffer[i][j];
            memcpy(myBytes, &myFloat, 4);
            Wire.write(myBytes, sizeof(myBytes));      
          }
          Wire.endTransmission();
          Serial.println();  
        }
      }
    }
  }
  
}
