#include <unity.h>
#include "internal_temperature.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include <stdint.h>
#include "internal_temperature.h"
#include "parameters.h"

#define TAG "DRIVER"

TEST_CASE("internal_temperature_get","[drivers]")
{

    initialization();
    reset_factory();
    internal_temperature_set_up();

    float temp ;
    uint8_t i=0u;

    for (;i<50;i++)
    {
        temp= internal_temperature_get();
        ESP_LOGI(TAG,"Value of the internal temperature are: %0.2f",temp);
        TEST_ASSERT_EQUAL(true,19<temp && temp<50);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

}
