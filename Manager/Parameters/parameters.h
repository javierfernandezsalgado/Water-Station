#include <stdint.h>
#include <bool.h>


extern bool_t gt(float param);
extern bool_t lt(float param);
extern bool_t eq(float param);

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


/*FDIR entry*/
typedef struct
{
    action_fdir type_action;
    void (*action) (const uint8_t *);
    float value;
    bool_t (*eval)(float);
    uint32_t  period;
    bool_t    isActived;
}fdir_event_entry;

typedef struct
{
    temp_event_conf temp_event;
    ph_event_conf   ph_event;
    ppm_event_conf   ppm_event;

} event_configuration;



typedef struct
{
  bool_t is_configure_before;
  //mode the system is working.
  system_mode sm;
  //After setup device during on the initialization a delay of time is perfomed
  uint32_t setup_delay;
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

typedef struct
{
   //http_port_hi
  uint16_t http_port;
  uint8_t ssid_configuration[256u];
    uint8_t ssid_passwd_configuration[125u]=;
  uint8_t ssid_nominal[125u];
  uint8_t ssid_passwd_nominal[256u];
  uint8_t ip_address_configuration[17u];

}wifi_configuration;

typedef struct
{
  uint8_t pin=5u;
}temp_configuration;
typedef struct
{
  uint8_t pin=0u;
}ph_configuration;
typedef struct
{
  uint8_t pin=0u;
}gns_configuration;

typedef struct
{
  uint8_t pin=0u;
}power_configuration;



/*-----------------Configuration FDIR and Events---------------------------*/

/*Type of FDIR*/
typedef enum
{
  NONE_ACTION,
  INFO,
  RESET,
  POWEROFF
}action_fdir;



/*Power FDIR is hardcoded, users cannot configured*/
typedef struct
{
  fdir_event_entry power_max;
  fdir_event_entry power_min;

}power_fdir_conf;

/*PH FDIR ENTRY*/
typedef struct
{
  fdir_event_entry max_ph;
  fdir_event_entry min_ph;
}ph_event_conf;

/*Temperature fdir*/
typedef struct
{
  fdir_event_entry max_temp;
  fdir_event_entry min_temp;
}temp_event_conf;

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

typedef struct
{
    fdir_event_entry max_ppm;
    fdir_event_entry min_ppm;


}ppm_event;


typedef enum
{
    TEMPERATURE,
    PH,
    POWER,
    USER_CONNECTIONS,
    PPM,
    WIFI_CONECTION_DB

}aquisition_enum;

typedef struct{
    float temperature=0.0f;
    float ph=0.0f;
    float power=0.0f;
    uint8_t users_connections=0u;
    float ppm=0.0f;
    float wifi_connection_db=0.0f;
}adquisition_datas;

extern void initialization();
extern void * get_parameter(parameter_bank banck);
extern void  set_parameter(parameter_bank banck,void * configuration);

extern void * get_adquisition(aquisition_enum acq);
