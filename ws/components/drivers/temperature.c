#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "ds18b20.h" //Include library
#include "parameters.h"
#include <stdbool.h>
#include "esp_log.h"
#include "driver/gpio.h"
#define TAG "TEMPERATURE"
DeviceAddress tempSensor;



extern float getTemperature(void) {
    //sensors.requestTemperatures();
    //return sensors.getTempCByIndex(0);


    ds18b20_requestTemperatures();

    return ds18b20_getTempC((DeviceAddress *)&tempSensor);

}


extern void temperature_setup(void)
{//((temp_configuration *)get_parameter(TEMPERATURE))->pin
    ds18b20_init(GPIO_NUM_13);

    search(tempSensor,false);
    ESP_LOGI(TAG,"The ID of the temperature sensor are %c.",*tempSensor);
    ds18b20_setResolution(&tempSensor,1,10);

}
