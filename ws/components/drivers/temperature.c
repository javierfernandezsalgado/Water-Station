#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"
#include "esp_system.h"
#include "nvs_flash.h"

#include "parameters.h"
#include <stdbool.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "ds18x20.h"
#include "driver/gpio.h"

#define TAG "TEMPERATURE"




ds18x20_addr_t  address_temperature_sensor;

 float getTemperature()
{
  float temperature;
  float temp_calibration=(((calibration_datas *)get_parameter(CALIBRATION))->temp);
  esp_err_t  status;

  status= ds18x20_measure(17, address_temperature_sensor, true);
  ds18x20_read_temperature(17, address_temperature_sensor, &temperature);
  ESP_LOGI(TAG,"Temperature %.2f°C.",temperature);
  ESP_LOGI(TAG,"status Temperature %d.",status);

  return temperature*temp_calibration;
}


 void temperature_setup(void)
{
  size_t found=0;
  gpio_set_pull_mode(17, GPIO_PULLUP_ONLY);
  while(found!=1)
    {
      ds18x20_scan_devices(17, &address_temperature_sensor, 1, &found);
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
  
  ESP_LOGI(TAG,"The ID of the temperature sensor are %llu number of devices: %d.",address_temperature_sensor,found);
}
