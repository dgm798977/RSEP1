#include <Arduino.h>

int pinSensor = A0;
int value;
char buffer[40];

void setup() {
  Serial.begin(9600);


}

void loop() {
  value = analogRead(pinSensor);
  /*Simplest way
  Serial.print(value);
  Serial.println(" is the obtained value");
  */
  
  sprintf(buffer, "%d is the obtained value", value);
  Serial.println(buffer);
  delay(1000);

}
