#include <Preferences.h>

static Preferences prefs;


static system_mode system_mode;
static global_configuration global_configuration;
static configuration_bancks select_banck;
static global_configuration parameters[2u];


extern void initialization()
{
  #ifdef preload_parameters
  prefs.begin("parameters");
  
  parameters[configuration_banck.FACTORY_CONFIGURATION]=
  {
    .is_configure_before=true;
    .sm=system_mode.CONFIGURATION;
    .setup_delay=500u;
    .wifi_parameters={
      .http_port=80;
      .ssid_configuration="Fishery-station-1";
      .ssid_passwd_configuration="123456789";
      .ssid_nominal="";
      .ssid_passwd_nominal="";
      .ip_address_configuration=="192.168.1.1";
    };
    .ph_parameters
    {
      .pin=0u;
    };
    .gns_parameters
    {
      .pin=0u;
    };
    .power_parameters
    {
      .pin=0u;
    };
    .temp_parameters
    {
      .pin =0u;
    };
    .fdir_parameters
    {
      .wifi_fdir=
      {
        
      };
      .temp_fdir=
      {
      
      };
      .ph_fdir=
      {
      
      };
      .power_fdir=
      {
          .power_max={
            .type_action=POWEROFF;
            .action=&poweroff;
            .value=4.0f;
            .eval=&lt;
      };
          .power_min=
            {
              .type_action=POWEROFF;
              .action=&poweroff;
              .value=4.0f;
              .eval=&gt;
            };
      };
    };
    
  
  };
  prefs.putBytes("parameters", parameters, sizeof(parameters));
  
  #else
  
  #endif
  prefs.begin("isFirstTime");
  prefs.begin("parameters");
  uint8_t isFirtsTime = prefs.getBytes("isFirstTime");
  
  prefs.begin("isFirstTime");
  
  
  prefs.putBytes("schedule", content, sizeof(content));
  
  EEPROM.get(configuration_banck.FACTORY_CONFIGURATION, parameters[configuration_banck.FACTORY_CONFIGURATION]);
  EEPROM.get(configuration_banck.USER_CONFIGURATION, parameters[configuration_banck.FACTORY_CONFIGURATION]);
}
}

extern bool_t gt(float param1,float param2)
{
return param1>param2;
}
extern bool_t lt(float param1,float param2)
{
return param1<param2;
}
extern bool_t eq(float param1,float param2)
{
return param1==param2;
}

extern void poweroff(const uint8_t * message)
{

}
extern void info(const uint8_t * message)
{

}  

extern void none_action(const uint8_t * message)
{

}

extern get_parameter(uint8_t)
{

  
}

