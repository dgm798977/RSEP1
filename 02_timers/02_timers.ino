#include <Arduino.h>
#include "BBTimer.hpp"

int pinSensor = A0;
volatile int value;
bool newData;

//Create timer
BBTimer my_t3(BB_TIMER3);

//Action when timer runs out
void t3Callback() {
  newData = true; 
}



void setup() {
  Serial.begin(9600);
	my_t3.setupTimer(10000000, t3Callback);
	my_t3.timerStart();

}

void loop() {
  if (newData) { 
    value = analogRead(pinSensor); 
    Serial.println(value);
    newData = false;
  }
}