#ifndef SENSORS_H
#define SENSORS_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


extern void task_read_sensors(void * pvParameters);

#endif
