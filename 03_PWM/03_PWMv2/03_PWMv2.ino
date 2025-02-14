#include <Arduino.h>
#include "BBTimer.hpp"


int pinSensor = A0;
int pinPWM = 9;  
long frec = 5000;
int PMWvalue;
int value;

void setup() {
  Timer1.initialize(1000000 / frec);
}

void loop() {
  value = analogRead(pinSensor);
  PWMvalue = map(value, 0, 1023, 0, 255);
  Timer1.pwm(pinPWM, PWMvalue);
}