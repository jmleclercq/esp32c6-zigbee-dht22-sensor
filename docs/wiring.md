# Wiring

## SHT3x -> ESP32-C6-Zero

Current wiring:

- VIN  -> 3V3
- GND  -> GND
- SDA  -> GPIO4
- SCL  -> GPIO5

## Notes

- The sensor is detected at I2C address 0x44.
- Internal pull-ups are enabled in software.
- Wiring reliability matters: false contacts can break communication.
