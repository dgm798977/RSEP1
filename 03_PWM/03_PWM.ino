#include <Arduino.h>
#include <TimerOne.h>

int pinSensor = A0;
int pinPWM = 9;  
long frec = 5000;
int PMWvalue;

void setup() {
  Timer1.initialize(1000000 / frec);
}

void loop() {
  value = analogRead(pinSensor);
  Timer1.pwm(pinPWM, value);
}