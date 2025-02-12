#include <Arduino.h>
#include "BBTimer.hpp"

int pinSensor = A0;
int valueNumber;
int pwmValue;
int adcValue;
int timerValue;
bool newData;
String command;

//Create timer
BBTimer my_t3(BB_TIMER3);

int obtainPMWValue(String command) {
  int startIdx = command.indexOf('(') + 1; 
  int endIdx = command.indexOf(')'); 
  String strValue = command.substring(startIdx, endIdx); 
  return strValue.toInt(); 
}

//Action when timer runs out
void t3Callback() {
  newData = true; 
}

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT); //Check which Pin for pwm on board
}

void loop() {
  if (newData) { 
    adcValue = analogRead(pinSensor); 
    Serial.println(adcValue);
    newData = false;
  }
  
  if (Serial.available() > 0) {
    command = Serial.readStringUntil('\n'); 
    command.trim(); 
    if (command == "ADC") {
      adcValue = analogRead(pinSensor);
      Serial.print("ADC value is: ");
      Serial.println(adcValue);
    }
    else if (command.startsWith("ADC(")) {
      valueNumber = obtainPMWValue(command);
      if (valueNumber > 0){
        timerValue = valueNumber * 1000000; 
        my_t3.setupTimer(timerValue, t3Callback);
	      my_t3.timerStart();
      }
      else{
        my_t3.timerStop();
      }
    }
    else if (command.startsWith("PWM(")) {
      valueNumber = obtainPMWValue(command);
      if (valueNumber >= 0 && valueNumber <= 9) {
        pwmValue = map(valueNumber, 0, 9, 0, 255);
        analogWrite(9, pwmValue);  // Establece el valor PWM en el pin 9
        Serial.print("PWM value set to: ");
        Serial.println(pwmValue);
      } else {
        Serial.println("Value not valid for PWM. It has to be between 0 and 9 (both included)");
      }
    }
    else {
      Serial.println("Comando no reconocido");
    }
  }
}