#include <stdio.h>
#include "parameters.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <string.h>

static const char* TAG = "FLASH PARAMETERS";

global_configuration parameters[2u];

static void load_init_factory_values()
{
    ESP_LOGI(TAG, "Preload parameter");


    ESP_LOGI(TAG, "Factory load");
    parameters[FACTORY_CONFIGURATION]= (global_configuration)
        {
            .is_configure_before=true,
            .sm=CONFIGURATION,
            .setup_delay=500u,
            .wifi_parameters={
                .http_port=80,
                .ssid_configuration="Fishery-station-1",
                .ssid_passwd_configuration="",
                .max_connection_configuration=3u,
                .wifi_channel_configuration=1u,
                .ssid_nominal="",
                .ssid_passwd_nominal="",
                .ip_address_configuration={192,168,1,1},
            },
            .ph_parameters =
            {
                .pin=0u,
            },
            .gns_parameters =
            {
                .pin=0u,
            },
            .power_parameters =
            {
                .pin=0u,
            },
            .temp_parameters =
            {
                .pin =4u,
            },
            .fdir_parameters =
            {
                .power_fdir=
                {
                    .power_max={
                        .type_action=INFO,
                        .action=&poweroff,
                        .value=4.0f,
                        .eval=lt,
                        .operator=LT,
                    },
                    .power_min=
                    {
                        .type_action=INFO,
                        .action=&poweroff,
                        .value=4.0f,
                        .eval=gt,
                        .operator=GT,
                    },
                },
                .wifi_fdir =
                {
                    .no_connection=
                    {
                        .type_action=INFO,
                        .action=NULL,
                        .value=true,
                        .eval=gt,
                        .operator=GT,
                        .period=0u,
                        .isActived=false,
                    },
                    .poor_connection =
                    {
                        .type_action=INFO,
                        .action=NULL,
                        .value=20u,
                        .eval=gt,
                        .operator=GT,
                        .period=0u,
                        .isActived=false,
                    },
                    .too_many_connections=
                    {
                        .type_action=INFO,
                        .action=NULL,
                        .value=10u,
                        .eval=gt,
                        .operator=GT,
                        .period=0u,
                        .isActived=false,
                    },
                },

            },
            .event_parameters=
            {
                .temp_event=
                {
                    .max_temp=
                    {
                        .type_action=INFO,
                        .action=NULL,
                        .value=25u,
                        .eval=gt,
                        .operator=GT,
                        .period=60u,
                        .isActived=true,

                    },
                    .min_temp=
                    {
                        .type_action=INFO,
                        .action=NULL,
                        .value=5u,
                        .eval=lt,
                        .operator=LT,
                        .period=60u,
                        .isActived=true,

                    },
                },
                .ph_event=
                {
                    .max_ph=
                    {
                        .type_action=INFO,
                        .action=NULL,
                        .value=8u,
                        .eval=gt,
                        .operator=GT,
                        .period=60u,
                        .isActived=false,

                    },
                    .min_ph=
                    {
                        .type_action=INFO,
                        .action=NULL,
                        .value=3u,
                        .eval=lt,
                        .operator=LT,
                        .period=60u,
                        .isActived=true,
                    },
                },
                .ppm_event=
                {
                    .max_ppm=
                    {
                        .type_action=INFO,
                        .action=NULL,
                        .value=8u,
                        .eval=gt,
                        .operator=GT,
                        .period=60u,
                        .isActived=false,

                    },
                    .min_ppm=
                    {
                        .type_action=INFO,
                        .action=NULL,
                        .value=3u,
                        .eval=lt,
                        .operator=LT,
                        .period=60u,
                        .isActived=true,
                    },
                },
            },
        };
    ESP_LOGI(TAG,"Copying a total of %d bytes from factory parameters to user configuration parameters ",sizeof(parameters[FACTORY_CONFIGURATION]));

    memcpy( &parameters[USER_CONFIGURATION],&parameters[FACTORY_CONFIGURATION],sizeof(global_configuration));

}


void app_main(void)

{
    ESP_LOGI(TAG,"Initilization of the flash values");

    load_init_factory_values();
    set_factory((void *)parameters);

    ESP_LOGI(TAG,"Flash done");
    while (true)
      {
        ESP_LOGI(TAG,"Flash done!");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
      }
}
