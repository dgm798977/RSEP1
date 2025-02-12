#include <Arduino.h>
#include "BBTimer.hpp"

int pinSensor = A0;
volatile int adcValue;
int valueNumber;
int pwmValue;


//Create timer
BBTimer my_t3(BB_TIMER3);

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
    adcvalue = analogRead(pinSensor); 
    Serial.println(value);
    newData = false;
  }
  
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); 
    command.trim(); 
    if (command == "ADC") {
      adcValue = analogRead(pinSensor);
      Serial.print("ACD value is: ");
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
    }
    else if (command.startsWith("PWM(")) {
      valueNumber = obtainPMWValue(command);
      if (valueNumber >= 0 && valueNumber <= 9) {
        pwmValue = map(valueNumber, 0, 9, 0, 255);
        analogWrite(9, pwmValue);  // Establece el valor PWM en el pin 9
        Serial.print("PWM value set to: ");
        Serial.println(pwmValue);
      } else {
        Serial.println("Valor no válido para PWM. Debe ser un número entre 0 y 9.");
      }
    }
    else {
      Serial.println("Comando no reconocido");
    }
  }
}


int obtainPMWValue(String command) {
  int startIdx = command.indexOf('(') + 1; 
  int endIdx = command.indexOf(')'); 
  String strValue = command.substring(startIdx, endIdx); 
  return strValue.toInt(); 
}
