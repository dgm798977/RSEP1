int pinSensor = A0;
int value;

void setup() {
  Serial.begin(9600);


}

void loop() {
  value = AnalogRead(pinSensor);
  Serial.print(value);
  Serial.println("es el valor leído en el pin");
  delay(1000);

}
