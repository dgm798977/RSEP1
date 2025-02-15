#include "BBTimer.hpp"

#define PWM_PIN 5
#define INPUT_PIN A0

BBTimer myPWM(BB_TIMER3);

void setup() {
    pinMode(INPUT_PIN, INPUT);
    myPWM.setupPWM(2000000, PWM_PIN);  // Configurar PWM de 5 kHz en PIN 5
    myPWM.timerStart();
}

void loop() {
    int analogValue = analogRead(INPUT_PIN);
    int dutyCycle_us = map(analogValue, 0, 1023, 0, 200);
    myPWM.updateDutyCycle(dutyCycle_us);
}
