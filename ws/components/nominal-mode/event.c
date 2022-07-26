
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include "esp_log.h"
#include "event.h"
#include "parameters.h"



#define TAG "EVENT_TASK"
/* MAx number of event */
#define MAX_EVENT_ELEMENTS 6u


/* It contains in seconds the events which are retrieved from the parameter module in nominal_mode  */
static fdir_event_entry  events [MAX_EVENT_ELEMENTS];

/* It contains the remaining seconds to be checked and event. */
static uint32_t events_seconds [MAX_EVENT_ELEMENTS];

static uint32_t elapse_seconds=0u;

extern void event_initilization(void)
{
    elapse_seconds=0u;
//EVENT
    event_configuration * event_conf = get_parameter(EVENT_GLOBAL);
    memcpy(events,&event_conf->temp_event,sizeof(event_conf->temp_event));
    memcpy(&events[2],&event_conf->ph_event,sizeof(event_conf->ph_event));
    memcpy(&events[4],&event_conf->ppm_event,sizeof(event_conf->ppm_event));

    //TODO find a better solution for this shit pointer to function is not working
    uint8_t i=0u;
    for(;i<MAX_EVENT_ELEMENTS;i++)
    {
        events_seconds[i]=events[i].period;
        switch (events[i].operator)
        {
        case LT:
        {
            events[i].eval = lt;
            break;
        }
        case GT:
        {
            events[i].eval = gt;
            break;
        }
        case EQ:
        {
            events[i].eval = eq;
            break;
        }
        default:
        {
            assert(false);
            break;
        }
        }

        switch(events[i].type_action)
        {
        case NONE_ACTION:
        {
            events[i].action = &none_action;
            break;
        }
        case INFO:
        {
            events[i].action = &info;
            break;
        }
        case RESET:
        {
            events[i].action = &reset;
            break;
        }
        case POWEROFF:
        {
            events[i].action = &poweroff;
            break;
        }
        default:
        {

            break;
        }
        }
    }


}

extern uint32_t event_task_body()
{


    uint32_t min_next_elapse_time=1000u;
    uint8_t i=0u;
    float adquisition;

    ESP_LOGI(TAG,"Checking the event list");
    for(;i<MAX_EVENT_ELEMENTS;i++)
    {
        if (events[i].isActived)
        {

            events_seconds[i]= events_seconds[i] - elapse_seconds;
            ESP_LOGI(TAG,"Event number %d is activated, remaining seconds: %d",i,events_seconds[i]);

            if (events_seconds[i]!=0 && events_seconds[i]<min_next_elapse_time)
            {
                min_next_elapse_time = events_seconds[i];
                ESP_LOGI(TAG,"Minimum Elapse time for events %d",min_next_elapse_time);
            }
            else
            {
                //empty else
            }
            if (events_seconds[i]==0u)
            {
                events_seconds[i]=events[i].period;
                bool (*eval)(float,float)=events[i].eval;
                adquisition=(float) (*(float *)get_adquisition(events[i].adquisition_id));
                ESP_LOGI(TAG,"Adquisition value of %d value: %.6f",events[i].adquisition_id,adquisition);
                ESP_LOGI(TAG,"Address of the eval function %x Function:gt: %x, lt:%x and eq:%x",*eval,gt,lt,eq);
                if ((*eval)(adquisition,events[i].value))
                {
                    ESP_LOGI(TAG,"Event is true");
                    events[i].action((const uint8_t *)"Event trigger");
                    ESP_LOGI(TAG,"Action performed");
                }
                else
                {
                    ESP_LOGI(TAG,"Eval funciton has been false");
                }
            }
            else
            {
                ESP_LOGI(TAG,"Non period of the event");
            }
        }
        else
        {
            ESP_LOGI(TAG,"Event is not activated");
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

extern void task_event(void * pvParameters)
{
    //DONE Initializate the fdir_event_entry table;
    ESP_LOGI(TAG,"task events_activated");
    uint32_t seconds_delay;
    while(true)
    {
        seconds_delay = event_task_body();
        vTaskDelay(seconds_delay*1000 / portTICK_PERIOD_MS);
    }

}
