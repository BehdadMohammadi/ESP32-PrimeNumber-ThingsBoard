# ESP32 Prime Number ThingsBoard Project

This project demonstrates how to use **FreeRTOS tasks** on an **ESP32** to generate prime numbers and send them to **ThingsBoard Cloud** via HTTP.  
It includes two concurrent tasks:
1. **Prime Number Generator Task** – continuously finds prime numbers.
2. **HTTP Sender Task** – sends prime numbers to the ThingsBoard telemetry API.

---

## 🚀 Features
- ESP32 with **FreeRTOS multitasking**
- **WiFi connectivity** with automatic reconnection
- **Queue-based task communication**
- **HTTP telemetry posting** to ThingsBoard Cloud
- Modular and efficient design

---

## 🧰 Requirements
- **Hardware:** ESP32 Development Board  
- **Software:**
  - [Arduino IDE](https://www.arduino.cc/en/software)  
  - [ESP32 board support](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)
  - Active **ThingsBoard Cloud account** (or local ThingsBoard instance)

---

## ⚙️ Setup

1. **Clone the repository:**
   ```bash
   git clone https://github.com/<your-username>/ESP32-PrimeNumber-ThingsBoard.git
   cd ESP32-PrimeNumber-ThingsBoard
