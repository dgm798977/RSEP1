# 🧪 Laboratory Practices - Practice 1 - Redes de sensores electrónicos

This repository contains the first laboratory practice for the **Redes de sensores electrónicos** course. Each section is organized in its own folder and includes the necessary files along with a brief description.
In this practice, we will explore the basics of working with the Arduino Nano 33 sense BLE.

## 📖 Section Overview

### 📁 Section 1 - 01_sleep
📌 First working code to print on Serial Monitor the value captured on an Analog Pin.  
📄 Main files:  
- `01_sleep.ino`: Using sleep() to print every second the value obtained.

### 📁 Section 2 - 02_timers
📌 Same result as in the previous section, but a better approach by using interupt timers so as not to inutilize the board
📄 Main files:  
- `02_timers.ino`: main code used in order to print on screen the values obtained

### 📁 Section 3 - 03_PWM
📌 Working with PWM signals in order to obtain a 5kHz signal with varible duty  cycle
📄 Main files:  
- `03_PWM.ino`: creating PWM signal.  

### 📁 Section 4 - 04_UART
📌 Working with string commands sent through Serial Command on PC to configure board signals and obtain values back.
📄 Main files:  
- `04_UART.ino`: sending different string commands from PC in order to change PWM signal and obtain read values.

### 📁 Section 5 - 05_I2C
📌 Working with two boards in order to establish I2C communication between them.
📄 Main files:  
- `05_I2C.ino`: I2C communication between boards to turn on/off LED diode.

### 📁 Section 6 - 06_sensors
📌 Working with integrated sensors from the board to obtain the registered values.
📄 Main files:  
- `06_sensors.ino`: obtaining values from different integrated sensors.

### 📁 Section 7 - 07_I2Csensors
📌 Working with integrated sensors from the board to obtain the registered values and sending the captured info via I2C to another board.
📄 Main files:  
- `07_I2Csensors.ino`: obtaining values from different integrated sensors and using I2C to retrieve them on other board.