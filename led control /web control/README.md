# ESP32-C3 Super Mini PWM LED Controller

A compact, web-controlled LED dimmer built with **ESP32-C3 Super Mini**, featuring a custom 3D-printed enclosure with sliding lid.


## ✨ Features

- **Ultra-compact design** using ESP32-C3 Super Mini
- **Smooth PWM brightness control** (0–100%) via web interface
- **Custom Domain** – Accessible at `http://led.local`
- **Real-time WebSocket** communication for low latency
- **Responsive modern UI** with percentage display
- **Quick Full ON / OFF** buttons
- **Stable & crash-resilient** operation

## 🛠️ Hardware

- **Microcontroller**: ESP32-C3 Super Mini (chosen for its small size)
- **Power Switch**: N-channel MOSFET
- **Protection**:
  - 1kΩ resistor between GPIO and MOSFET Gate (limits inrush current)
  - 10kΩ pull-down resistor between Gate and GND (ensures default OFF state and prevents floating)
- **Cooling**: Small heatsink added to MOSFET due to heating observed during prolonged PWM operation
- **Enclosure**: Custom 3D-printed case with sliding lid (files included)

**Connections:**
- MOSFET Gate → GPIO 02 (via 1kΩ resistor)
- MOSFET Source → GND
- MOSFET Drain → LED negative
- 10kΩ pull-down between Gate and GND

## 📁 Project Contents

- `ESP32_LED_Controller.ino` – Main firmware
- `README.md`
- `/3D_Enclosure/` – STL files for the case and sliding lid (updated for heatsink)

## 🚀 Setup Instructions

### 1. Libraries (Arduino IDE)
- ESPAsyncWebServer (me-no-dev)
- AsyncTCP (me-no-dev)

### 2. WiFi Configuration
Update SSID and password in the code.

### 3. Upload & Access
1. Flash the code to the ESP32-C3 Super Mini
2. Open Serial Monitor (115200 baud)
3. Navigate to `http://led.local` (or the shown IP)

## 📝 Technical Notes

- PWM generated using ESP32 LEDC peripheral
- WebSocket + client-side throttling ensures smooth slider performance
- MOSFET heating mitigated with heatsink (common with high-frequency PWM on cheaper/smaller boards)
- Pull-down resistor ensures safe default state during boot

## 🎯 Purpose

This project demonstrates:
- Compact embedded system design using ESP32-C3 Super Mini
- Proper MOSFET driving techniques (gate protection & pull-down)
- Real-time web control with AsyncWebServer + WebSocket
- 3D-printed enclosure design for practical use



