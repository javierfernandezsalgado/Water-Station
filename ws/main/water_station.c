#include <stdio.h>
#include "parameters.h"
#include "esp_log.h"
#include "configuration-mode.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nominal-mode.h"

static const char* TAG = "Main module";

static void driver_initilization()
{
    //Driver configuration
    ESP_LOGI(TAG,"Setup Init ");

    ESP_LOGI(TAG,"Screen set up ");
    //screen_setup();

    ESP_LOGI(TAG,"ph set up ");
    //ph_setup();

    ESP_LOGI(TAG,"temperature set up ");
    //temperature_setup();

    ESP_LOGI(TAG,"clean water set up ");
    //clean_water_setup();

    ESP_LOGI(TAG,"Internal temperature set up ");
    //internal_temperature_setup();

    ESP_LOGI(TAG,"Setup finish ");

}


void app_main(void)

{

    //system_mode sm = global_conf->sm;

    ESP_LOGI(TAG, "Parameter initialization");
    initialization();

    global_configuration * global_conf= get_parameter(GLOBAL);

    ESP_LOGI(TAG, "Drivers initialization");
    driver_initilization();

    ESP_LOGI(TAG, "Mode is in %d",global_conf->sm);

    switch(global_conf->sm)
    {

    case CONFIGURATION:
    {
        ESP_LOGI(TAG,"config mode ");
        config_mode();
        break;

    }
    case NOMINAL:
    {
        ESP_LOGI(TAG,"Nominal mode");
        //nominal_mode();

        ESP_LOGI(TAG,"We are in nominal");
        nominal_mode();
        ESP_LOGI(TAG,"Nominal mode functional");
        break;
    }
    default:
    {
        ESP_LOGE(TAG,"Mode non defined ");
        assert(false);
        break;
    }
    }




}
