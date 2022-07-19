#include <stdio.h>
#include "parameters.h"
#include "esp_log.h"

static const char* TAG = "Main module";




void app_main(void)

{
    ESP_LOGI(TAG, "Parameter iniitialization");
    initialization();

}
