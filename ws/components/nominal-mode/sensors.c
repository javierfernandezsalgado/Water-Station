
#include <stdint.h>
#include <string.h>

#include "esp_log.h"
#include "sensors.h"
#include "parameters.h"

#define TAG "SENSORS"

/* It is in charge to read the sensors every 1000 ms. The values are colleceted in the adquitions module. */
extern void task_read_sensors(void * pvParameters)
{

    //read temperature
    while(true)
    {
        ESP_LOGI(TAG,"Reading temperature");
        float temperature=0.0f;
        //getTemperature();
        set_aquition((void *)&temperature,TEMPERATURE_ACQ);

        //read ph
        ESP_LOGI(TAG,"Reading PH");
        float ph=0.0f;
        //get_ph(void);
        set_aquition((void *)&ph,PH_ACQ);

        ESP_LOGI(TAG,"Reading Power");
        float power=0.0f;
        //get_power();
        set_aquition((void *)&power,POWER_ACQ);


        //set_aquition((void *)&user_connections,USER_CONNECTIONS_ACQ);

        ESP_LOGI(TAG,"Reading TDS");
        float tds=0.0f;
        //=  get_TDS_value();
        set_aquition((void *)&tds,PPM_ACQ);

        //TODO the WIFI connection DB, the quality of the signal

        //Every second is measure the instrumentation
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
