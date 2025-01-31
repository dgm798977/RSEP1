#include <Arduino.h>

int pinSensor = A0;
int value;

void setup() {
  Serial.begin(9600);


}

void loop() {
  value = analogRead(pinSensor);
  Serial.print(value);
  Serial.println(" es el valor leído en el pin");
  delay(1000);

}
