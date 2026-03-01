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
