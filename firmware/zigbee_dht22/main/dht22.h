#pragma once
#include <stdbool.h>
#include "driver/gpio.h"

typedef struct {
    float temperature_c;
    float humidity_rh;
} dht22_reading_t;

/**
 * Read a DHT22 sensor on the given GPIO.
 * Returns true on success, false on checksum/timing error.
 */
bool dht22_read(gpio_num_t gpio, dht22_reading_t *out);
