#include "sht31.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define TAG "sht31"

#define I2C_PORT 0
#define SDA_PIN 4
#define SCL_PIN 5
#define SHT31_ADDR 0x44

static i2c_master_bus_handle_t bus_handle = NULL;
static i2c_master_dev_handle_t dev_handle = NULL;

esp_err_t sht31_init(void)
{
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_PORT,
        .sda_io_num = SDA_PIN,
        .scl_io_num = SCL_PIN,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    esp_err_t err = i2c_new_master_bus(&bus_config, &bus_handle);
    if (err != ESP_OK) {
        return err;
    }

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = SHT31_ADDR,
        .scl_speed_hz = 100000,
    };

    err = i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle);
    if (err != ESP_OK) {
        return err;
    }

    ESP_LOGI(TAG, "SHT31 initialized on SDA=%d SCL=%d addr=0x%02X", SDA_PIN, SCL_PIN, SHT31_ADDR);

    // Soft reset command
    uint8_t reset_cmd[2] = {0x30, 0xA2};
    err = i2c_master_transmit(dev_handle, reset_cmd, sizeof(reset_cmd), 100);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Soft reset failed: %s", esp_err_to_name(err));
    } else {
        ESP_LOGI(TAG, "Soft reset OK");
    }

    vTaskDelay(pdMS_TO_TICKS(20));

    return ESP_OK;
}

esp_err_t sht31_read(float *temperature, float *humidity)
{
    // Single shot measurement, high repeatability, clock stretching enabled
    uint8_t cmd[2] = {0x2C, 0x06};
    uint8_t data[6] = {0};

    esp_err_t err;

    err = i2c_master_transmit(dev_handle, cmd, sizeof(cmd), 100);
    if (err != ESP_OK) {
        return err;
    }

    vTaskDelay(pdMS_TO_TICKS(20));

    err = i2c_master_receive(dev_handle, data, sizeof(data), 100);
    if (err != ESP_OK) {
        return err;
    }

    uint16_t raw_temp = ((uint16_t)data[0] << 8) | data[1];
    uint16_t raw_hum  = ((uint16_t)data[3] << 8) | data[4];

    *temperature = -45.0f + 175.0f * ((float)raw_temp / 65535.0f);
    *humidity    = 100.0f * ((float)raw_hum / 65535.0f);

    return ESP_OK;
}
