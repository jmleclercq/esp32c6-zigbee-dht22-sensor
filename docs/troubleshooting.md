# Troubleshooting

## DHT22 - Failed at step 1

### Symptoms

- Idle level on DATA = 1
- Read fails at step 1
- Sensor never pulls DATA line LOW after start signal

### Most Likely Cause

Missing external pull-up resistor.

The internal GPIO pull-up is usually too weak for reliable DHT22 communication.

### Recommended Fix

Add a 4.7kΩ resistor between:

DATA ---- 4.7kΩ ---- 3.3V

Also recommended:
- Add 100nF capacitor between VCC and GND
- Keep wires short
- Avoid noisy breadboards

---

## Serial Port Not Detected

Check available ports:

    ls /dev/ttyACM*

If not detected:
- Verify USB data cable
- Check dmesg
- Try another USB port

---

## Flash Fails

Try:

    idf.py fullclean
    idf.py -p /dev/ttyACM3 build flash monitor

## Current blocker (DHT22)

With the following setup:

- ESP32-C6 GPIO4 confirmed working
- External 4.7kΩ pull-up resistor between DATA and 3.3V
- 100nF decoupling capacitor between VCC and GND
- Multiple DHT modules tested

The sensor still fails during the DHT protocol initialization:

Typical log:

    Idle level on GPIO4 = 1
    Failed at step 1 or step 11

Possible causes:

- Incompatible DHT clone module
- Breadboard wiring instability
- Sensor requiring slightly different timing

Next recommended tests:

1. Direct wiring without breadboard
2. Verify exact sensor model (DHT11 / AM2301 / AM2302)
3. Test with a known good DHT22 sensor

Fallback option:

Use a more robust sensor such as:

- SHT31
- BME280

These sensors provide much more reliable readings and easier integration.
