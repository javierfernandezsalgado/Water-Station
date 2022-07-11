#include <stdint.h>
//#include <bool.h>
#include <Manager/Parameters/parameters.h>
#include <log.c/src/log.h>
//TODO include tasks free RTOS?

/* Max number of FDIR element */
#define MAX_FDIR_ELEMENTS 5u

/* MAx number of event */
#define MAX_EVENT_ELEMENTS 6u

/* Number of user connected to the website. */
static uint32_t user_connections=0u;

/* FDIR configuration elements. nominal_mode read the configuration from the parameters module. */
static fdir_event_entry * fdir [MAX_FDIR_ELEMENTS];

/* It contains the reamining seconds to be executed the verification of a FDIR mechanism. */
static uint32_t fdir_seconds [MAX_FDIR_ELEMENTS];

/* It contains in seconds the events which are retrieved from the parameter module in nominal_mode  */
static fdir_event_entry * events [MAX_EVENT_ELEMENTS];

/* It contains the remaining seconds to be checked and event. */
static uint32_t events_seconds [MAX_EVENT_ELEMENTS];


/* It is charge yo handle the website with the needed information. It implements the methods get and post */
static void task_website_monitoring(void);

/* It is in charge to handle the execution of the fdir mechanism. Reads the FDIR configuration and execute the methods configured as well. The minimun execution is 1000 ms and the meaximum execution ids the MCD of the FDIR mechanism. */
static void task_fdir(void);

/* It is in charge to handle the events. Read the configuration and set up the next the event to be handle. */
static void task_event(void);

/* It is in charge to read the sensors every 1000 ms. The values are colleceted in the adquitions module. */
static void task_read_sensors(void);


extern void  nominal_mode(void)
{
  //Configure some tables

  //FDIR
  fdir_configuration * fdir_conf = get_parameter(parameter_bank.FDIR_GLOBAL);
  memcpy(fdir,&fdir_conf->wifi_fdir,sizeof(fdir_conf->wifi_fdir));
  memcpy(fdir+sizeof(fdir_conf->wifi_fdir),&fdir_conf->power_fdir,sizeof(fdir_conf->power_fdir));

  //EVENT
  event_configuration * event_conf = get_parameter(parameter_bank.EVENT_GLOBAL);
  memcpy(events,&event_conf->temp_event_fdir,sizeof(event_conf->temp_event));
  memcpy(events+sizeof(event_conf->temp_event),&event_conf->ph_event_fdir,sizeof(event_conf->ph_event));
  memcpy(events+sizeof(event_conf->temp_event)+sizeof(event_conf->ph_event),&event_conf->ppm_event,sizeof(event_conf->ppm_event));


  //start the tasks
  //CORE 1
  xTaskCreatePinnedToCore(
                          task_website_monitoring, /* Function to implement the task */
                          "Website_monitoring", /* Name of the task */
                          10000,  /* Stack size in words */
                          NULL,  /* Task input parameter */
                          1,  /* Priority of the task */
                          &task_website_monitoring,  /* Task handle. */
                          1); /* Core where the task should run */

  //CORE 0
  xTaskCreatePinnedToCore(
                          task_fdir, /* Function to implement the task */
                          "TaskFDIR", /* Name of the task */
                          10000,  /* Stack size in words */
                          NULL,  /* Task input parameter */
                          5,  /* Priority of the task */
                          &task_fdir,  /* Task handle. */
                          0); /* Core where the task should run */

  xTaskCreatePinnedToCore(
                          task_event, /* Function to implement the task */
                          "TaskEvent", /* Name of the task */
                          10000,  /* Stack size in words */
                          NULL,  /* Task input parameter */
                          5,  /* Priority of the task */
                          &task_event,  /* Task handle. */
                          0); /* Core where the task should run */

  xTaskCreatePinnedToCore(
                          task_read_sensors, /* Function to implement the task */
                          "TaskSensor", /* Name of the task */
                          10000,  /* Stack size in words */
                          NULL,  /* Task input parameter */
                          1,  /* Priority of the task */
                          &task_read_sensors,  /* Task handle. */
                          0); /* Core where the task should run */

}


static void task_website_monitoring(void)
{

  while(true)
    {
      //http

      //catch the get and post methods.
    }
}

static void task_fdir(void)
{
  //DONE initilizate the fdir_event_entry table

  static uint32_t elapse_seconds;

  uint32_t min_next_elapse_time=1000u;
  uint8_t i;
  float adquisition;

  while (true)
    {
      log_info("Checking the fdir list");
      for(i=0u;i<MAX_FDIR_ELEMENTS;i++)
        {
          if (*fdirs[i].isActived)
            {
              fdir_seconds[i]= fdir_seconds[i] - elapse_seconds;

              if (fdir_seconds[i]<min_next_elapse_time)
                {
                  min_next_elapse_time = fdir_seconds[i];
                }
              else
                {
                  //empty else
                }
              if (fdir_seconds[i]==0u)
                {
                  adquisition==get_adquisition(NULL,*fdirs[i].adquisition_id);
                  if (*fdirs[i].eval(adquisition,*fdirs[i]).adquisition);
                  {
                    *fdirs[i].action("Fdir trigger");
                  }
                  else
                    {
                      log_info("Eval funciton has been false");
                    }
                }
              else
                {
                  log_info("Non period of the fdir");
                }
            }
          else
            {
              log_info("Fdir is not activated");
            }
        }

      //next task
      elapse_seconds=min_next_elapse_time;
      delay(elapse_seconds*1000);
    }

}

static void task_event(void)
{
  //DONE Initializate the fdir_event_entry table;
  log_info("task events_activated");

  static uint32_t elapse_seconds;

  uint32_t min_next_elapse_time=1000u;
  uint8_t i;
  float adquisition;
  while(true)
    {
      log_info("Checking the event list");
      for(i=0u;i<MAX_FDIR_ELEMENTS;i++)
        {
          if (*events[i].isActived)
            {
              events_seconds[i]= events_seconds[i] - elapse_seconds;

              if (event_seconds[i]<min_next_elapse_time)
                {
                  min_next_elapse_time = event_seconds[i];
                }
              else
                {
                  //empty else
                }
              if (events_seconds[i]==0u)
                {
                  adquisition==get_adquisition(NULL,*events[i].adquisition_id);
                  if (*events[i].eval(adquisition,*events[i]).adquisition);
                  {
                    *events[i].action("Event trigger");
                  }
                  else
                    {
                      log_info("Eval funciton has been false");
                    }
                }
              else
                {
                  log_info("Non period of the event");
                }
            }
          else
            {
              log_info("Event is not activated");
            }
        }

      //next task
      elapse_seconds=min_next_elapse_time;
      delay(elapse_seconds*1000);
    }

}

static void task_read_sensors(void)
{

  //read temperature
  while(true)
    {
      float temperature=getTemperature();
      set_aquition(&temperature,aquisition_enum.TEMPERATURE);

      //read ph

      float ph=get_ph(void);
      set_aquition(&ph,aquisition_enum.PH);

      float power=get_power();
      set_aquition(&power,aquisition_enum.POWER);


      set_aquition(&user_connections,aquisition_enum.USER_CONNECTIONS);


      float tds=  get_TDS_value();
      set_aquition(&tds,aquisition_enum.PPM);

      //TODO the WIFI connection DB, the quality of the signal

      delay(1000u);
    }
}
