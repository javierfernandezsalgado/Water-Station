#ifndef  HTTP_SEND_DATAS_H
#define HTTP_SEND_DATAS_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* It is charge yo handle the website with the needed information. It implements the methods get and post */
extern void task_website_monitoring(void * pvParameters);



#endif
