#include "proximity.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include "gatt_server.h"

#define GPIO_PROXIMITY_PIN      2
#define GPIO_PROXIMITY_ON_LEVEL 0     // high-to-low

static uint32_t proximity_counter = 0;


static const char *TAG = "proximity";


void proximity_init() {
    gpio_config_t io_conf = {0};
    io_conf.pin_bit_mask  = BIT64(GPIO_PROXIMITY_PIN);
    io_conf.mode          = GPIO_MODE_INPUT;
    io_conf.pull_up_en    = 0;
    io_conf.pull_down_en  = 0;
    io_conf.intr_type     = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);

    ESP_LOGI(TAG, "Proximity initialized");
}

uint32_t proximity_get_counter() {
    return proximity_counter;
}

void proximity_manage() {
    static _Bool last_proximity_level = !GPIO_PROXIMITY_ON_LEVEL;
    static _Bool proximity_level      = !GPIO_PROXIMITY_ON_LEVEL;

    proximity_level = gpio_get_level(GPIO_PROXIMITY_PIN);

    if (last_proximity_level == GPIO_PROXIMITY_ON_LEVEL && proximity_level == !GPIO_PROXIMITY_ON_LEVEL) {
        // NOTE: first proximity signal is sent as 1
        ++proximity_counter;
        ESP_LOGI(TAG, "Notifying new value %u", proximity_counter);
        if (gatt_server_is_notify_enabled()) {
            gatt_server_send_notify((uint8_t *)&proximity_counter, sizeof proximity_counter);
        }
    }

    last_proximity_level = proximity_level;
}
