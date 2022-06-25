


#define SYSTEM_MODE_PARAM 0u
#define SET_UP_DELAY 500u
#define HTTP_PORT_CONFIGURE 80u
#define SSID_CONFIGURATION "Fishery-station-1"
#define SSID_PASWD_CONFIGURATION "123456789"
#define IP_ADDRESS "0.0.0.0"

#define SSID_NOMINAL ""
#define SSID_PASSW_NOMINAL ""

/*List of configuration parameters*/
typedef enum {
  GLOBAL,
  TEMPERATURE,
  PH,
  GNS,
  POWER
} parameter_bank;

/*Global configuration */

typedef enum
{
  CONFIGURATION,
  NOMINAL,
  STANDBY
}system_mode;

typedef struct
{
  //mode the system is working.
  system_mode sm;
  //After setup device during on the initialization a delay of time is perfomed
  uint32_t setup_delay;
  
  
  }global_configuration;

typedef struct
{
   //http_port_hi
  uint16_t http_port;
  uint8_t ssid_configuration[]="Fishery-station-1";
  uint8_t ssid_passwd_configuration[]="123456789";
  uint8_t ssid_nominal[125u];
  uint8_t ssid_passwd_nominal[256u];
  uint8_t ip_address_configuration[]="192.168.1.1";

}wifi_configuration;
  

typedef struct
{

}ph_configuration;
typedef struct
{

}gns_configuration;

typedef 
{

}power_configuration;

typedef
{

}fdir_configuration;


extern get_parameter(uint8_t);
extern set_parameter(uint8_t);








