#include <unity.h>
#include "internal_temperature.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include <stdint.h>
#include "parameters.h"
#include "clean_water.h"

#define TAG "DRIVER"

TEST_CASE("/* ppm */_get","[drivers]")
{

    initialization();
    reset_factory();
    clean_water_setup();

    float ppm;
    uint8_t i=0u;

    for (;i<50;i++)
    {
        ppm = get_TDS_value();
        ESP_LOGI(TAG,"Value of the ppm are: %0.2f",ppm);
        TEST_ASSERT_EQUAL(true,0<ppm && ppm<5000);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

}
