#include <Arduino.h>
#include <Wire.h>

const byte DEVICE_ADDRESS = 8;
byte row = 0;

void receiveEvent(int bytes) {
  row = Wire.read();  

  for (int j = 0; j < 3; j++) {
    byte buffer[4];  
    for (int b = 0; b < 4; b++) {
      if (Wire.available()) {
        buffer[b] = Wire.read();
      }
    }
    memcpy(&matriz[fila_actual][j], buffer, 4);  
  }
  Serial.print("Fila recibida: ");
  Serial.println(fila_actual);
}

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");
}
void loop() {
  
}
