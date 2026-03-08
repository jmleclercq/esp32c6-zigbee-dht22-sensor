#pragma once
#include "esp_err.h"

esp_err_t sht31_init(void);
esp_err_t sht31_read(float *temperature, float *humidity);
