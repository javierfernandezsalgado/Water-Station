#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "parameters.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "event.h"
#include "fdir.h"
#include "nominal-mode.h"
#include "http_send_datas.h"
#include "sensors.h"


#define TAG "Nominal-mode"

static TaskHandle_t xHandle_website=NULL;
static TaskHandle_t xHandle_event = NULL;
static TaskHandle_t xHandle_fdir = NULL;
static TaskHandle_t xHandle_read_sensor = NULL;

extern void  nominal_mode(void)
{
    fdir_initialization();
    event_initilization();

    //start the tasks
    //CORE 1
    xTaskCreatePinnedToCore(
        task_website_monitoring, /* Function to implement the task */
        "Website_monitoring", /* Name of the task */
        10000,  /* Stack size in words */
        NULL,  /* Task input parameter */
        1,  /* Priority of the task */
        &xHandle_website,  /* Task handle. */
        1); /* Core where the task should run */

    //CORE 0
    xTaskCreatePinnedToCore(
        task_fdir, /* Function to implement the task */
        "TaskFDIR", /* Name of the task */
        10000,  /* Stack size in words */
        NULL,  /* Task input parameter */
        5,  /* Priority of the task */
        &xHandle_fdir,  /* Task handle. */
        0); /* Core where the task should run */

    xTaskCreatePinnedToCore(
        task_event, /* Function to implement the task */
        "TaskEvent", /* Name of the task */
        10000,  /* Stack size in words */
        NULL,  /* Task input parameter */
        5,  /* Priority of the task */
        &xHandle_event,  /* Task handle. */
        0); /* Core where the task should run */

    xTaskCreatePinnedToCore(
        task_read_sensors, /* Function to implement the task */
        "TaskSensor", /* Name of the task */
        10000,  /* Stack size in words */
        NULL,  /* Task input parameter */
        1,  /* Priority of the task */
        &xHandle_read_sensor,  /* Task handle. */
        0); /* Core where the task should run */

}
