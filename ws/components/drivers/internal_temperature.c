#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/temperature_sensor.h"
#include "internal_temperature.h"

static temperature_sensor_handle_t temp_handle = NULL;
static temperature_sensor_config_t temp_sensor = TEMPERAUTRE_SENSOR_CONFIG_DEFAULT(10, 80);


extern void internal_temperature_set_up(void)
{
    ESP_ERROR_CHECK(temperature_sensor_install(&temp_sensor, &temp_handle));
    ESP_ERROR_CHECK(temperature_sensor_enable(temp_handle));

}

extern float internal_temperature_get()
{
    float tsens_out;
    ESP_ERROR_CHECK(temperature_sensor_get_celsius(temp_handle, &tsens_out));
    return tsens_out;

}
