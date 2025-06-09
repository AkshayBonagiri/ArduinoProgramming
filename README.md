# 🚗 ESP8266 WiFi Motor Control Web Server 🤖

This project implements a WiFi-controlled robot motor driver using an ESP8266 microcontroller. The ESP8266 runs a web server to receive motor control commands over WiFi and control two DC motors accordingly.

---

## ✨ Features

- 📶 Connects to a WiFi network or falls back to Access Point (AP) mode if connection fails
- 🌐 Web server listens on port 80 for control commands
- 🔧 Controls two DC motors (motor A and motor B) with speed and direction control
- ▶️ Supports commands to move forward, backward, turn left, turn right, and stop
- ⚡ Adjustable motor speed via commands (PWM speed control)
- 🔄 OTA (Over The Air) update support with ArduinoOTA library

---

## 🔌 Hardware Connections

| Motor Driver Pin | ESP8266 Pin | Description             |
|------------------|-------------|-------------------------|
| IN1              | D8 (GPIO15) | Motor A direction pin 1 |
| IN2              | D7 (GPIO13) | Motor A direction pin 2 |
| ENA              | D5 (GPIO14) | Motor A PWM enable pin  |
| IN3              | D4 (GPIO2)  | Motor B direction pin 1 |
| IN4              | D3 (GPIO0)  | Motor B direction pin 2 |
| ENB              | D6 (GPIO12) | Motor B PWM enable pin  |

> ⚠️ Note: Adjust pin mappings if you use a different ESP8266 board or motor driver.

---

## 💻 Software Setup

### 📚 Libraries Used

- ESP8266WiFi  
- ESP8266WebServer  
- ArduinoOTA  

### 🔑 WiFi Configuration

Set your WiFi credentials in the following variables:

```cpp
const String STA_SSID = "YourWiFiSSID";
const String STA_PASSWORD = "YourWiFiPassword";
