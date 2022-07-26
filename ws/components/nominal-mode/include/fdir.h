#ifndef FDIR_H
#define FDIR_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


/* It is in charge to handle the execution of the fdir mechanism. Reads the FDIR configuration and execute the methods configured as well. The minimun execution is 1000 ms and the meaximum execution ids the MCD of the FDIR mechanism. */

extern void task_fdir(void * pvParameters);

extern void  fdir_initialization();

extern uint32_t fdir_task_body(void);

#endif
