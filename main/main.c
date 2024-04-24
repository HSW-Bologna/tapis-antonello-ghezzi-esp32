#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "esp_log.h"

#include "controller/controller.h"


static const char *TAG = "Main";


void app_main(void) {
    controller_init();

    ESP_LOGI(TAG, "Begin main loop");
    for (;;) {
        controller_manage();
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}
