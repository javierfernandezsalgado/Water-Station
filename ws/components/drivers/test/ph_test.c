#include <unity.h>
#include "internal_temperature.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include <stdint.h>
#include "ph.h"
#include "parameters.h"



#define TAG "DRIVER"

TEST_CASE("ph_get","[drivers]")
{

    initialization();
    reset_factory();
    ph_setup();

    float ph;
    uint8_t i=0u;

    for (;i<50;i++)
    {
        ph = internal_temperature_get();
        ESP_LOGI(TAG,"Value of the ph are: %0.2f",ph);
        TEST_ASSERT_EQUAL(true,1<ph && ph<10);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

}
