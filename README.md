# ESP32-C6 Zigbee SHT3x Sensor (ZHA)

![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v6.x-blue)
![Zigbee](https://img.shields.io/badge/Zigbee-IEEE%20802.15.4-orange)
![Home%20Assistant](https://img.shields.io/badge/Home%20Assistant-ZHA-green)
![License](https://img.shields.io/badge/License-MIT-brightgreen)

## Overview

This project builds a DIY Zigbee temperature & humidity sensor based on:

- ESP32-C6 (Waveshare ESP32-C6-Zero)
- SHT3x temperature & humidity sensor
- ESP-IDF
- Future integration with ESP Zigbee SDK
- Home Assistant using ZHA

The goal is to learn Zigbee end-device development on ESP32-C6 and document everything properly.

---

## Project Status

Development phase:

- ESP-IDF environment validated
- Flash/monitor workflow working
- I2C scan working
- SHT3x detected at address 0x44
- SHT3x read path validated after fixing wiring issues
- Next step: implement Zigbee end device support

---

## Hardware

Main board:
- Waveshare ESP32-C6-Zero

Sensor:
- SHT3x module

Current wiring:
- VIN  -> 3V3
- GND  -> GND
- SDA  -> GPIO4
- SCL  -> GPIO5

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

    source ~/esp-idf/export.sh
    cd ~/Git/esp32c6-zigbee-dht22-sensor/firmware/zigbee_dht22
    idf.py -p /dev/ttyACM3 build flash monitor

Monitor only:

    idf.py -p /dev/ttyACM3 monitor

---

## Roadmap

Phase 1 – Stable Sensor
- [x] Validate I2C communication
- [x] Detect SHT3x on the bus
- [x] Get stable sensor readings

Phase 2 – Zigbee Integration
- [ ] Integrate ESP Zigbee SDK
- [ ] Implement Zigbee End Device
- [ ] Add Temperature cluster
- [ ] Add Humidity cluster
- [ ] Join ZHA network

Phase 3 – Power & Enclosure
- [ ] Evaluate power options
- [ ] Optimize low power
- [ ] Design enclosure

---

## License

MIT License
