# ESP32-C3 Super Mini PWM LED Controller

A compact, web-controlled LED dimmer built with **ESP32-C3 Super Mini**, featuring a custom 3D-printed enclosure with sliding lid.A compact web-controlled PWM LED dimmer designed specifically for **aquarium lighting**.


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
- **Female usb typeC and typeA port**
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

## ⚠️ Safety Disclaimer

**This project involves soldering, electronics, and power components.**

- The MOSFET may become hot during extended operation.
- Always verify polarity and connections before applying power.
- Use appropriate power supply ratings for your LED load.
- This is a hobby/educational project. Use at your own risk.
The author is not liable for any damage, injury, or loss resulting from following this guide.


## 📁 Project Contents

- `solo.ino` – Main firmware
- `README.md`
- `Images`
- `/3D_Enclosure/` – STL/f3d files for the case and sliding lid (updated for heatsink)

## 🚀 Setup Instructions

### 1. Libraries (Arduino IDE)
- ESPAsyncWebServer 
- AsyncTCP 

### 2. WiFi Configuration
Update SSID and password in the code by replacing ssid and password in

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

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


## 🔮 Future Updates (Planned)

- **Timer functionality** – Automatic on/off schedule
- **Multi-channel control** – Independent control for top lighting, bottom lighting, or RGB channels
- Additional smart aquarium features like temperature, water level
