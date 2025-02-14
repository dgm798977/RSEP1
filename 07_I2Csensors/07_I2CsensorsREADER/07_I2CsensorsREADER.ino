#include <Arduino.h>
#include <Wire.h>

const byte DEVICE_ADDRESS = 8;
byte row = 0;

#define ROWS 5 
#define COLS 3
float matrix[ROWS][COLS];
byte buffer[4];
int current_row;


void receiveEvent(int bytes) {
  row = Wire.read();  
  Wire.read();
  for (int b = 0; b < 4; b++) {
      if (Wire.available()) {
        buffer[b] = Wire.read();
      }
  }
  memcpy(&current_row, buffer, 4);
  for (int j = 0; j < 3; j++) {
    byte buffer[4];  
    for (int b = 0; b < 4; b++) {
      if (Wire.available()) {
        buffer[b] = Wire.read();
      }
    }
    memcpy(&matrix[current_row][j], buffer, 4);  
  }
  Serial.print("Row captured: ");
  Serial.println(current_row);
  for (int i = 0; i < 3; i++) {
    Serial.print(matrix[current_row][i]);  
    if (i < 2) {
      Serial.print(", "); 
    }
  }
  
  // Print a newline after the first row
  Serial.println();
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
