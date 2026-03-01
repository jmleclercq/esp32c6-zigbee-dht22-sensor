# Wiring

## DHT22 (3-pin module) -> ESP32-C6-Zero

Use 3.3V logic.

| DHT22 Module Pin | ESP32-C6 |
|---|---|
| + (VCC) | 3V3 |
| - (GND) | GND |
| S / OUT / DATA | GPIO4 (default) |

## Strong Recommendation (Required in many cases)

### External pull-up resistor
Add a pull-up resistor between DATA and 3.3V:

- 4.7kΩ recommended (works best on breadboards / longer wires)
- 10kΩ can also work

Wiring:
- DATA (GPIO4) -> resistor -> 3.3V

### Decoupling capacitor
Add a 100nF ceramic capacitor close to the DHT module:
- VCC -> capacitor -> GND

This improves stability and noise immunity.

## Notes

- Keep wires short (preferably < 10 cm).
- Avoid noisy GPIOs (GPIO16/17 are used by console UART on this board).
