#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "dht22.h"

static const char *TAG = "zigbee_dht22";

/* Back to GPIO4 */
#define DHT_GPIO GPIO_NUM_4

void app_main(void)
{
    ESP_LOGI(TAG, "Boot OK. DHT22 on GPIO4. Debug mode.");

    /* Configure GPIO4 as input with pull-up to read idle level */
    gpio_config_t io = {
        .pin_bit_mask = (1ULL << DHT_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io);

    while (1) {

        int idle = gpio_get_level(DHT_GPIO);
        ESP_LOGI(TAG, "Idle level on GPIO4 = %d (expected 1)", idle);

        dht22_reading_t r;
        bool ok = dht22_read(DHT_GPIO, &r);

        if (ok) {
            ESP_LOGI(TAG, "DHT OK -> Temp: %.1f C | Hum: %.1f %%RH",
                     r.temperature_c, r.humidity_rh);
        } else {
            ESP_LOGW(TAG, "DHT read FAILED");
        }

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
