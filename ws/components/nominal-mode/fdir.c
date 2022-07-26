
#include <stdint.h>
#include <string.h>

#include "esp_log.h"
#include "fdir.h"
#include "parameters.h"


#define TAG "FDIR"
/* Max number of FDIR element */
#define MAX_FDIR_ELEMENTS 5u

static uint32_t elapse_seconds;

/* FDIR configuration elements. nominal_mode read the configuration from the parameters module. */
static fdir_event_entry  fdir [MAX_FDIR_ELEMENTS];

/* It contains the reamining seconds to be executed the verification of a FDIR mechanism. */
static uint32_t fdir_seconds [MAX_FDIR_ELEMENTS];



extern void  fdir_initialization()
{
    elapse_seconds=0u;
//Configure some tables
//TODO Change for pointers makes no sense duplciate and the waste memory
//FDIR
    fdir_configuration * fdir_conf = get_parameter(FDIR_GLOBAL);
    memcpy(fdir,&fdir_conf->wifi_fdir,sizeof(wifi_fdir_conf));
    memcpy(&fdir[3],&fdir_conf->power_fdir,sizeof(power_fdir_conf));




    uint8_t i=0u;
    for(;i<MAX_FDIR_ELEMENTS;i++)
    {
        fdir_seconds[i]=fdir[i].period;

        switch (fdir[i].operator)
        {
        case LT:
        {
            fdir[i].eval = lt;
            break;
        }
        case GT:
        {
            fdir[i].eval = gt;
            break;
        }
        case EQ:
        {
            fdir[i].eval = eq;
            break;
        }
        default:
        {
            assert(false);
            break;
        }
        }

        switch(fdir[i].type_action)
        {
        case INFO:
        {
            fdir[i].action = info;
            break;
        }
        case RESET:
        {
            fdir[i].action = reset;
            break;
        }
        case POWEROFF:
        {
            fdir[i].action = poweroff;
            break;
        }
        default:
        {

            break;
        }
        }
    }

}
extern void task_fdir(void * pvParameters)
{
    //DONE initilizate the fdir_event_entry table



    while(true)
    {
        //next task
        fdir_task_body();
        vTaskDelay(elapse_seconds*1000 / portTICK_PERIOD_MS);

    }

}

extern uint32_t fdir_task_body(void)
{
    uint32_t min_next_elapse_time=1000u;
    uint8_t i=0u;
    float adquisition;

    ESP_LOGI(TAG,"Checking the fdir list");
    for(;i<MAX_FDIR_ELEMENTS;i++)
    {
        if (fdir[i].isActived)
        {
            fdir_seconds[i]= fdir_seconds[i] - elapse_seconds;
            ESP_LOGI(TAG,"Fdir number %d is activated, remaining seconds: %d",i,fdir_seconds[i]);
            if (fdir_seconds[i]!=0 &&fdir_seconds[i]<min_next_elapse_time)
            {
                min_next_elapse_time = fdir_seconds[i];
            }
            else
            {
                //empty else
            }
            if (fdir_seconds[i]==0u)
            {
                fdir_seconds[i]=fdir[i].period;
                bool (*eval)(float,float)=fdir[i].eval;
                adquisition=(float) (*(float *)get_adquisition(fdir[i].adquisition_id));
                ESP_LOGI(TAG,"Adquisition value of %d value: %.6f",fdir[i].adquisition_id,adquisition);
                ESP_LOGI(TAG,"Address of the eval function %x Function:gt: %x, lt:%x and eq:%x",*eval,gt,lt,eq);
                if ((*eval)(adquisition,fdir[i].value))
                {
                    ESP_LOGI(TAG,"Event is true");
                    fdir[i].action((const uint8_t *)"Event trigger");
                    ESP_LOGI(TAG,"Action performed");
                }
                else
                {
                    ESP_LOGI(TAG,"Eval funciton has been false");
                }
            }
            else
            {
                ESP_LOGI(TAG,"Non period of the fdir");
            }
            }
            else
            {
                ESP_LOGI(TAG,"Fdir is not activated");
            }
        }
    //next task
    elapse_seconds=min_next_elapse_time;

    if (elapse_seconds == 0u)
    {
        elapse_seconds=1000u;
    }
    else
    {

    }
    return elapse_seconds;
}
