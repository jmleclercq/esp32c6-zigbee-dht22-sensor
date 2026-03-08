#include "dht22.h"
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/portmacro.h"
#include "esp_rom_sys.h"
#include "esp_log.h"
#include "driver/gpio.h"

static const char *TAG = "dht22";
static portMUX_TYPE dht_mux = portMUX_INITIALIZER_UNLOCKED;

static inline void delay_us(uint32_t us) { esp_rom_delay_us(us); }

static int wait_level(gpio_num_t gpio, int level, uint32_t timeout_us)
{
    uint32_t t = 0;
    while (gpio_get_level(gpio) != level) {
        if (t++ >= timeout_us) return -1;
        delay_us(1);
    }
    return (int)t;
}

bool dht22_read(gpio_num_t gpio, dht22_reading_t *out)
{
    if (!out) return false;

    gpio_config_t io = {
        .pin_bit_mask = (1ULL << gpio),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io);

    // Start signal
    gpio_set_level(gpio, 0);
    vTaskDelay(pdMS_TO_TICKS(5));   // 5 ms LOW
    gpio_set_level(gpio, 1);
    delay_us(80);

    io.mode = GPIO_MODE_INPUT;
    io.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io);

    uint8_t data[5] = {0};
    int fail_step = 0;

    portENTER_CRITICAL(&dht_mux);

    // Sensor response: LOW -> HIGH -> LOW
    if (wait_level(gpio, 0, 3000) < 0) { fail_step = 1; goto fail; }
    if (wait_level(gpio, 1, 3000) < 0) { fail_step = 2; goto fail; }
    if (wait_level(gpio, 0, 3000) < 0) { fail_step = 3; goto fail; }

    for (int i = 0; i < 40; i++) {
        // Wait for bit HIGH
        if (wait_level(gpio, 1, 1000) < 0) { fail_step = 10; goto fail; }

        // Measure HIGH duration
        int high_us = wait_level(gpio, 0, 2000);
        if (high_us < 0) { fail_step = 11; goto fail; }

        // More tolerant threshold
        int bit = (high_us > 40) ? 1 : 0;

        data[i / 8] <<= 1;
        data[i / 8] |= (uint8_t)bit;
    }

    portEXIT_CRITICAL(&dht_mux);

    uint8_t sum = (uint8_t)(data[0] + data[1] + data[2] + data[3]);
    if (sum != data[4]) {
        ESP_LOGW(TAG, "Checksum error: got 0x%02X expected 0x%02X", data[4], sum);
        return false;
    }

    uint16_t raw_h = (uint16_t)((data[0] << 8) | data[1]);
    uint16_t raw_t = (uint16_t)((data[2] << 8) | data[3]);

    out->humidity_rh = raw_h / 10.0f;

    bool neg = (raw_t & 0x8000) != 0;
    raw_t &= 0x7FFF;
    out->temperature_c = raw_t / 10.0f;
    if (neg) out->temperature_c = -out->temperature_c;

    return true;

fail:
    portEXIT_CRITICAL(&dht_mux);
    ESP_LOGW(TAG, "Failed at step %d, line level=%d", fail_step, gpio_get_level(gpio));
    return false;
}
