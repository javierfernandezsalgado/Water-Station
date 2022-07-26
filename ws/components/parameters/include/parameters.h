#ifndef PARAMETER_H
#define PARAMETER_H



#include <stdint.h>
#include <stdbool.h>
#include <stdbool.h>

extern bool gt(float param1,float param2);
extern bool lt(float param1,float param2);
extern bool eq(float param,float param2);

extern void poweroff(const uint8_t * message);
extern void info(const uint8_t * message);
extern void reset(const uint8_t * message);
extern void none_action(const uint8_t * message);


/*List of configuration parameters*/
typedef enum {
  GLOBAL,
  TEMPERATURE,
  PH,
  GNS,
  POWER,
  WIFI,
  FDIR_GLOBAL,
  EVENT_TEMPERATURE,
  FDIR_POWER,
  FDIR_WIFI,
  EVENT_PH,
  EVENT_GLOBAL,
  EVENT_PPM
} parameter_bank;

/*Global configuration */

typedef enum
{
    CONFIGURATION,
    NOMINAL,
    STANDBY
}system_mode;

typedef enum
{
  FACTORY_CONFIGURATION,
  USER_CONFIGURATION
}configuration_banck;

typedef enum
{
    TEMPERATURE_ACQ,
    PH_ACQ,
    POWER_ACQ,
    USER_CONNECTIONS_ACQ,
    PPM_ACQ,
    WIFI_CONECTION_DB_ACQ

}aquisition_enum;


/*Type of FDIR*/
typedef enum
{
    NONE_ACTION,
    INFO,
    RESET,
    POWEROFF
}action_fdir;

typedef enum
{
    LT,
    GT,
    EQ
}operator_compare;
/*FDIR entry*/
typedef struct
{
    action_fdir type_action;
    void (*action) (const uint8_t *);

    float value;

    operator_compare operator;
    bool (*eval)(float,float);

    aquisition_enum adquisition_id;
    uint32_t  period;
    bool    isActived;
}fdir_event_entry;


/*Power FDIR is hardcoded, users cannot configured*/
typedef struct
{
  fdir_event_entry power_max;
  fdir_event_entry power_min;

}power_fdir_conf;


typedef struct
{
    //http_port_hi
    uint16_t http_port;
    uint8_t ssid_configuration[256u];
    uint8_t ssid_passwd_configuration[125u];
    uint32_t max_connection_configuration;
    uint32_t wifi_channel_configuration;
    uint8_t ssid_nominal[256u];
    uint8_t ssid_passwd_nominal[125u];
    uint8_t ip_address_configuration[4u];


}wifi_configuration;


typedef struct
{
    uint8_t pin;

}temp_configuration;
typedef struct
{
    uint8_t pin;
}ph_configuration;
typedef struct
{
    uint8_t pin;
}gns_configuration;

typedef struct
{
    uint8_t pin;
}power_configuration;

/*Temperature wifi*/
typedef struct
{
  fdir_event_entry no_connection;
  fdir_event_entry poor_connection;
  fdir_event_entry too_many_connections;
}wifi_fdir_conf;


/*FDIR Configuration*/
typedef struct
{
    wifi_fdir_conf wifi_fdir;
    power_fdir_conf power_fdir;
}fdir_configuration;


/*Temperature fdir*/
typedef struct
{
  fdir_event_entry max_temp;
  fdir_event_entry min_temp;
}temp_event_conf;



typedef struct
{
    fdir_event_entry max_ppm;
    fdir_event_entry min_ppm;


}ppm_event;

/*PH FDIR ENTRY*/
typedef struct
{
  fdir_event_entry max_ph;
  fdir_event_entry min_ph;
}ph_event_conf;


/*PPM FDIR ENTRY*/
typedef struct
{
    fdir_event_entry max_ppm;
    fdir_event_entry min_ppm;
}ppm_event_conf;


typedef struct
{
    temp_event_conf temp_event;
    ph_event_conf   ph_event;
    ppm_event_conf   ppm_event;

} event_configuration;




typedef struct
{
    bool is_configure_before;
    //mode the system is working.
  system_mode sm;
  //After setup device during on the initialization a delay of time is perfomed
    uint32_t setup_delay; // never used
    //configuration_bank   select_configuration;
  wifi_configuration   wifi_parameters;
  ph_configuration     ph_parameters;
  gns_configuration    gns_parameters;
    power_configuration  power_parameters;
  fdir_configuration   fdir_parameters;
    event_configuration  event_parameters;
    temp_configuration   temp_parameters;
    uint16_t crc;
  }global_configuration;



/*-----------------Configuration FDIR and Events---------------------------*/







typedef struct{
    float temperature;
    float ph;
    float power;
    uint8_t users_connections;
    float ppm;
    float wifi_connection_db;
}adquisition_datas;

extern void   initialization();
extern void * get_parameter(parameter_bank banck);
extern void   set_parameter(parameter_bank banck,void * configuration);
extern void   reset_factory(void);

extern void * get_adquisition(aquisition_enum acq_type);
extern void   set_aquition(void * data,aquisition_enum acq_type);
extern void   reset_adquistion(void);
#endif
