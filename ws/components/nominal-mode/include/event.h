#ifndef EVENT_H
#define EVENT_H



#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


/* It is in charge to handle the events. Read the configuration and set up the next the event to be handle. */
extern void task_event(void * pvParameters);

/*Handler */

extern void event_initilization(void);

extern uint32_t event_task_body(void);

#endif
