#include <unity.h>
#include "internal_temperature.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include <stdint.h>
#include "temperature.h"
#include "parameters.h"


#define TAG "DRIVER"

TEST_CASE("temperature_get","[drivers]")
{

    float temp;
    uint8_t i=0u;
    initialization();
    reset_factory();



    temperature_setup();
    for (;i<50;i++)
    {
        temp =  getTemperature();
        ESP_LOGI(TAG,"Value of the temperature are: %0.2f",temp);
        //comTEST_ASSERT_EQUAL(true,20<temp && temp <50);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }



}
