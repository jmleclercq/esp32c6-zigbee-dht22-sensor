#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "sht31.h"

static const char *TAG = "sht31_test";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting SHT31 test");

    if (sht31_init() != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize SHT31");
        while (1) {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }

    while (1) {
        float temperature = 0.0f;
        float humidity = 0.0f;

        esp_err_t err = sht31_read(&temperature, &humidity);
        if (err == ESP_OK) {
            ESP_LOGI(TAG, "Temperature: %.2f C", temperature);
            ESP_LOGI(TAG, "Humidity: %.2f %%", humidity);
        } else {
            ESP_LOGE(TAG, "Failed to read SHT31: %s", esp_err_to_name(err));
        }

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
