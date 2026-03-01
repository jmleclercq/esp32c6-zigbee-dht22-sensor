# ESP32-C6 Zigbee DHT22 Sensor (ZHA)
![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v6.x-blue)
![Zigbee](https://img.shields.io/badge/Zigbee-IEEE%20802.15.4-orange)
![Home%20Assistant](https://img.shields.io/badge/Home%20Assistant-ZHA-green)
![License](https://img.shields.io/badge/License-MIT-brightgreen)

# ESP32-C6 Zigbee DHT22 Sensor (ZHA)
## Overview

This project builds a DIY Zigbee temperature & humidity sensor based on:

- ESP32-C6 (Waveshare ESP32-C6-Zero)
- DHT22 / AM2302 sensor module
- ESP-IDF
- Future integration with ESP Zigbee SDK
- Home Assistant using ZHA

The goal is to learn Zigbee end-device development on ESP32-C6 and document everything properly.

---

## Project Status

Development phase:

- ESP-IDF environment validated
- Flash/monitor workflow working
- GPIO4 confirmed operational
- DHT debug firmware implemented
- DHT22 currently fails at protocol step 1 (no initial LOW response)

Likely cause:
Missing external pull-up resistor (recommended 4.7kΩ between DATA and 3.3V)

---

## Hardware

Main board:
- Waveshare ESP32-C6-Zero

Sensor:
- DHT22 / AM2302 (3-pin module)

Recommended additional components:
- 4.7kΩ resistor (DATA -> 3.3V)
- 100nF capacitor (VCC -> GND near sensor)

---

## Wiring

DHT22 (3-pin module) -> ESP32-C6-Zero

+ (VCC)  -> 3V3  
- (GND)  -> GND  
S / DATA -> GPIO4  

External pull-up:

DATA ---- 4.7kΩ ---- 3.3V

---

## Repository Structure

esp32c6-zigbee-dht22-sensor/
    README.md
    LICENSE
    .gitignore
    docs/
        wiring.md
        troubleshooting.md
        power-design.md
        enclosure.md
    firmware/
        zigbee_dht22/

---

## Flashing Firmware

Build + flash + monitor:

    idf.py -p /dev/ttyACM3 build flash monitor

Monitor only:

    idf.py -p /dev/ttyACM3 monitor

---

## Roadmap

Phase 1 – Reliable Sensor
- Add external pull-up resistor
- Confirm stable DHT22 readings
- Remove debug firmware

Phase 2 – Zigbee Integration
- Integrate ESP Zigbee SDK
- Implement Zigbee End Device
- Add Temperature cluster (0x0402)
- Add Humidity cluster (0x0405)
- Join ZHA network

Phase 3 – Power & Enclosure
- Evaluate power options
- Optimize low power
- Design enclosure

---

## License

MIT License
