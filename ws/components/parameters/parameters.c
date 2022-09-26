
#include "parameters.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

#include "driver/gpio.h"
#include "esp_log.h"


#define STORAGE_NAMESPACE "FLASH"
//static system_mode system_m;
static configuration_banck select_banck=USER_CONFIGURATION;
static global_configuration parameters[2u];
static adquisition_datas acq_datas;


static nvs_handle_t nvs_handle_parameter;
static const char* TAG = "Parameter Module";


SemaphoreHandle_t mutex_acq;





extern void initialization()
{
    esp_err_t err;
    size_t required_size = 0;
    int32_t init_flash=1;

    mutex_acq = xSemaphoreCreateMutex();

    ESP_ERROR_CHECK(nvs_flash_init());

    err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &nvs_handle_parameter);


    if (err != ESP_OK)
    {
        assert(false);
    }



    err = nvs_get_i32(nvs_handle_parameter, "init_flash", &init_flash);



    if (err == ESP_ERR_NVS_NOT_FOUND)
    {

        /* load_init_factory_values(); */
        /* err = nvs_set_blob(nvs_handle_parameter, "parameters", parameters, sizeof(global_configuration)*2); */
        /* err = nvs_set_i32(nvs_handle_parameter, "init_flash", init_flash); */
        /*Non flash values*/

        ESP_LOGI(TAG, "WARNING: There are not flash values loaded!!!!");

    }

    else
    {
        required_size=sizeof(global_configuration)*2;
        err = nvs_get_blob(nvs_handle_parameter, "parameters", parameters, &required_size);

        if(required_size!=sizeof(global_configuration)*2)
        {
            assert(false);
            //It must be updated the flash values / rese
            /* ESP_LOGI(TAG,"Reseting the user values in flash memory "); */
            /* load_init_factory_values(); */
            /* err = nvs_set_blob(nvs_handle_parameter, "parameters", parameters, sizeof(global_configuration)*2); */

            /* err = nvs_set_i32(nvs_handle_parameter, "init_flash", init_flash); */

        }
        //vTaskDelay(2000/ portTICK_PERIOD_MS);
        ESP_LOGI(TAG,"Copying a total of %d bytes from flash memory to RAM ",required_size);
        if (err != ESP_OK )
        {
            ESP_LOGI(TAG,"Error: %d ",err);
            assert(false);
        }

    }


    ESP_LOGI(TAG, "Retrieved the values from the flash");
}

extern bool gt(float param1,float param2)
{
    return param1>param2;
}
extern bool lt(float param1,float param2)
{
    return param1<param2;
}
extern bool eq(float param1,float param2)
{
    return param1==param2;
}
//see this info https://www.techtonions.com/esp32-sending-alert-message-to-whatsapp/
extern void poweroff(const uint8_t * message)
{
    esp_restart();
}

extern void reset(const uint8_t * message)
{
    esp_restart();
}
extern void info(const uint8_t * message)
{
    //Send whatsapp;
}

extern void none_action(const uint8_t * message)
{
    (void) message;
}

extern void * get_parameter(parameter_bank banck)
{
    switch (banck) {
    case GLOBAL:
    {
        return (void *) &parameters[select_banck];
    }
    case TEMPERATURE:
    {
        return (void *) &parameters[select_banck].temp_parameters;
    }
    case PH:
    {
        return  (void *) &parameters[select_banck].ph_parameters;
    }
    case PPM:
    {
        return  (void *) &parameters[select_banck].ppm_parameters;
    }
    case GNS:
    {
        return (void *) &parameters[select_banck].gns_parameters;
    }
    case POWER:
    {
        return (void *) &parameters[select_banck].power_parameters;
    }
    case WIFI:
    {
        return (void *) &parameters[select_banck].wifi_parameters;
    }
    case FDIR_GLOBAL:
    {
        return  (void *) &parameters[select_banck].fdir_parameters;
    }
    case FDIR_POWER:
    {
        return (void *) &parameters[select_banck].fdir_parameters.power_fdir;
    }
    case FDIR_WIFI:
    {
        return (void *) &parameters[select_banck].fdir_parameters.wifi_fdir;
    }
    case EVENT_GLOBAL:
    {
        return  (void *)&parameters[select_banck].event_parameters;
    }
    case EVENT_PH:
    {
        return  (void *) &parameters[select_banck].event_parameters.ph_event;
    }
    case EVENT_TEMPERATURE:
    {
        return  (void *) &parameters[select_banck].event_parameters.temp_event;
    }
    case EVENT_PPM:
    {
        return (void *) &parameters[select_banck].event_parameters.ppm_event;
    }
    case CALIBRATION:
      {
        return (void *) &parameters[select_banck].event_parameters.calibration;
      }
    default:
    {
        assert(false);
        return NULL;
    }


    }
    assert (false);
    return NULL;
}

extern void  set_parameter(parameter_bank banck,void * configuration)
{
    esp_err_t err;


    switch (banck) {
    case GLOBAL:
    {

        memcpy(&parameters[select_banck],configuration,sizeof (global_configuration));
        break;
    }
    case TEMPERATURE:
    {
        memcpy(&parameters[select_banck].temp_parameters,configuration,sizeof(parameters[select_banck].temp_parameters));
        break;
    }
    case PH:
    {
        memcpy(&parameters[select_banck].ph_parameters,configuration,sizeof (parameters[select_banck].ph_parameters));
        break;
    }
    case PPM:
    {
        memcpy(&parameters[select_banck].ppm_parameters,configuration,sizeof (parameters[select_banck].ppm_parameters));
        break;
    }

    case GNS:
    {
        memcpy(&parameters[select_banck].gns_parameters,configuration,sizeof(parameters[select_banck].gns_parameters) );
        break;
    }
    case POWER:
    {
        memcpy(&parameters[select_banck].power_parameters,configuration,sizeof (parameters[select_banck].power_parameters));
        break;
    }
    case WIFI:
    {
        memcpy(&parameters[select_banck].wifi_parameters,configuration,sizeof (parameters[select_banck].wifi_parameters));
        break;
    }
    case FDIR_GLOBAL:
    {
        memcpy(&parameters[select_banck].fdir_parameters,configuration,sizeof (parameters[select_banck].fdir_parameters));
        break;
    }
    case FDIR_POWER:
    {
        memcpy(&parameters[select_banck].fdir_parameters.power_fdir,configuration,sizeof (parameters[select_banck].fdir_parameters.power_fdir));
        break;
    }
    case FDIR_WIFI:
    {
        memcpy(&parameters[select_banck].fdir_parameters.wifi_fdir,configuration,sizeof (parameters[select_banck].fdir_parameters.wifi_fdir));
        break;
    }
    case EVENT_GLOBAL:
    {
        memcpy(&parameters[select_banck].event_parameters,configuration,sizeof (parameters[select_banck].event_parameters));
        break;
    }
    case EVENT_PH:
    {
        memcpy(&parameters[select_banck].event_parameters.ph_event,configuration,sizeof (parameters[select_banck].event_parameters.ph_event));
        break;
    }
    case EVENT_TEMPERATURE:
    {
        memcpy(&parameters[select_banck].event_parameters.temp_event,configuration,sizeof (parameters[select_banck].event_parameters.temp_event));
        break;
    }
    case EVENT_PPM:
    {
        memcpy(&parameters[select_banck].event_parameters.ppm_event,configuration,sizeof (parameters[select_banck].event_parameters.ppm_event));
        break;
    }
    case CALIBRATION:
      {
        memcpy(&parameters[select_banck].calibration,configuration,sizeof (parameters[select_banck].calibration));
        break;
      }

    default:
    {
        assert(false);
        break;
    }
    }
    //Copying the paramters in the flash memory

    err = nvs_set_blob(nvs_handle_parameter, "parameters", parameters, sizeof(global_configuration)*2);


    if (err!=ESP_OK)
    {
        ESP_LOGI(TAG,"Parameter has been set in the flash memory");
        assert(false);
    }
    ESP_LOGI(TAG,"Parameter has been set in the flash memory");

}

extern void * get_adquisition(aquisition_enum acq_type)
{
    void * aux;
    if( xSemaphoreTake( mutex_acq, ( TickType_t ) 10000 ) == pdTRUE )
    {
        switch (acq_type) {
        case PPM_ACQ:
            aux= (void *)  &acq_datas.ppm;
            break;
        case USER_CONNECTIONS_ACQ:
            aux= (void *) &acq_datas.users_connections;
            break;
        case WIFI_CONECTION_DB_ACQ:
            aux= (void *) &acq_datas.wifi_connection_db;
            break;
        case TEMPERATURE_ACQ:
            aux= (void *) &acq_datas.temperature;
            break;
        case PH_ACQ:
            aux= (void *) &acq_datas.ph;
            break;
        case POWER_ACQ:
            aux= (void *) &acq_datas.power;
            break;
        default:
            assert(false);
            break;
        }
    }
    else{
        /*Too much time block*/
        assert(false);
    }
    xSemaphoreGive( mutex_acq );
    return aux;
}

extern void set_aquition(void * data,aquisition_enum acq_type)
{
    if( xSemaphoreTake( mutex_acq, ( TickType_t ) 10000 ) == pdTRUE )
    {

        switch (acq_type) {
        case PPM_ACQ:
            acq_datas.ppm=*((float *)data);
            break;
        case USER_CONNECTIONS_ACQ:
            acq_datas.users_connections=*((uint8_t *)data);
            break;
        case WIFI_CONECTION_DB_ACQ:
            acq_datas.wifi_connection_db=*((float *)data);
            break;
        case TEMPERATURE_ACQ:
            acq_datas.temperature=*((float *)data);
            break;
        case PH_ACQ:
            acq_datas.ph=*((float *) data);
            break;
        case POWER_ACQ:
            acq_datas.power=*((float *) data);
            break;
        default:
            assert(false);
            break;
        }
    }
    else{
        /*Too much time block*/
        assert(false);
    }
    xSemaphoreGive( mutex_acq );
}

extern void   reset_factory(void)
{
    memcpy(&parameters[USER_CONFIGURATION],&parameters[FACTORY_CONFIGURATION],sizeof(global_configuration));

}

extern void set_factory(void * factory_memory)
{

    int32_t init_flash=1;
    esp_err_t err;

    assert(factory_memory==NULL);
    memcpy(parameters,factory_memory,sizeof(global_configuration)*2);

    err = nvs_set_blob(nvs_handle_parameter, "parameters", parameters, sizeof(global_configuration)*2);
    err = nvs_set_i32(nvs_handle_parameter, "init_flash", init_flash);
    assert(err==ESP_OK);

}
