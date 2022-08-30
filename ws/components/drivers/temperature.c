#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "ds18b20.h" //Include library
#include "parameters.h"
#include <stdbool.h>



DeviceAddress tempSensor;



extern float getTemperature(void) {
    //sensors.requestTemperatures();
    //return sensors.getTempCByIndex(0);
  float temp_calibration=(*((calibration_datas *)get_parameter(CALIBRATION))->temp);

    ds18b20_requestTemperatures();

    return ds18b20_getTempC((DeviceAddress *)&tempSensor)*temp_calibration;

}


extern void temperature_setup(void)
{
    ds18b20_init(((temp_configuration *)get_parameter(TEMPERATURE))->pin);
    search(tempSensor,false);
    ds18b20_setResolution(&tempSensor,1,10);

}
