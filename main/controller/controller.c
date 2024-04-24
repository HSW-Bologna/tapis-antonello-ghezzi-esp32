#include "controller.h"
#include "gatt_server.h"
#include "proximity.h"
#include "esp_log.h"

static const char *TAG = "controller";


void controller_init() {
    proximity_init();
    gatt_server_init();

    ESP_LOGI(TAG, "Controller initialized");
}

void controller_manage() {
    proximity_manage();
}
