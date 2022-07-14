#include <Preferences.h>
#include <Manager/Parameters/parameters.h>
#include <log.c/src/log.h>


static Preferences prefs;

static system_mode system_mode;
static configuration_banck select_banck=configuration_banck.USER_CONFIGURATION;
static global_configuration parameters[2u];
static adquisition_datas acq_datas;

extern void initialization()
{
  #ifdef PRELOAD_PARAMETERS
  log_info("Preload parameter");

  prefs.begin("parameters");

  log_info("Factory load");
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
          .wifi_fdir
          {
            .no_connection=
                    {
                    .type_action=INFO;
                    .action=NULL;
                    .value=true;
                    .eval=&gt;
                    .period=0u;
                    .isActived=false;
                    };
            .poor_connection =
                    {
                    .type_action=INFO;
                    .action=NULL;
                    .value=20u;
                    .eval=&gt;
                    .period=0u;
                    .isActived=false;
                    };
            .too_many_connections=
                    {
                    .type_action=INFO;
                    .action=NULL;
                    .value=10u;
                    .eval=&gt;
                    .period=0u;
                    .isActived=false;
                    };
          };

    };
    .event_parameters=
    {
        .temp_event=
                {
                .max_temp=
                        {
               .type_action=INFO;
                    .action=NULL;
                    .value=25u;
                    .eval=&gt;
                    .period=60u;
                    .isActived=true;

                        };
                .min_temp=
                        {
               .type_action=INFO;
                    .action=NULL;
                    .value=5u;
                    .eval=&lt;
                    .period=60u;
                    .isActived=true;

                        };
                };
        .ph_event=
                {
                    .max_ph=
                            {
                    .type_action=INFO;
                    .action=NULL;
                    .value=8u;
                    .eval=&gt;
                    .period=60u;
                    .isActived=false;

                            };
                    .min_ph=
                            {
                    .type_action=INFO;
                    .action=NULL;
                    .value=3u;
                    .eval=&lt;
                    .period=60u;
                    .isActived=true;
                            };
                };

    };

  };
 memcpy( parameters[configuration_banck.USER_CONFIGURATION],parameters[configuration_banck.FACTORY_CONFIGURATION],sizeof(parameters[configuration_banck.FACTORY_CONFIGURATION])];
 prefs.putBytes("parameters", parameters, sizeof(parameters));

  #else
    log_info("Retriving the values from the flash");
    prefs.getBytes("parameters", parameters, sizeof (parameters));
  #endif
  //Parameters initialized.

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
//see this info https://www.techtonions.com/esp32-sending-alert-message-to-whatsapp/
extern void poweroff(const uint8_t * message)
{
    ESP.restart();
}
extern void info(const uint8_t * message)
{
 //Send whatsapp;
}

extern void none_action(const uint8_t * message)
{
    (void) message;
}

extern void * get_parameter(parameter_bank banck)
{
    switch (banck) {
        case GLOBAL:
        {
            return (void *) &parameters[select_banck];
        }
        case TEMPERATURE:
        {
            return (void *) &parameters[select_banck].temp_parameters;
        }
        case PH:
        {
            return  (void *) &parameters[select_banck].ph_parameters;
        }
        case GNS:
        {
            return (void *) &parameters[select_banck].gns_parameters;
        }
        case POWER:
        {
            return (void *) &parameters[select_banck].power_parameters;
        }
        case WIFI:
        {
            return (void *) &parameters[select_banck].wifi_parameters;
        }
        case FDIR_GLOBAL:
        {
            return  (void *) &parameters[select_banck].fdir_parameters;
        }
        case FDIR_POWER:
        {
            return (void *) &parameters[select_banck].fdir_parameters.power_fdir;
        }
        case FDIR_WIFI:
        {
            return (void *) &parameters[select_banck].fdir_parameters.wifi_fdir;
        }
        case EVENT_GLOBAL:
        {
            return  (void *)&parameters[select_banck].event_parameters;
        }
        case EVENT_PH:
        {
            return  (void *) &parameters[select_banck].event_parameters.ph_event;
        }
        case EVENT_TEMPERATURE:
        {
            return  (void *) &parameters[select_banck].event_parameters.temp_event;
        }
        case EVENT_PPM:
        {
            return (void *) &parameters[select_banck].event_parameters.ppm_event;
        }
        default:
        {
            assert(false);
            return NULL;
        }


    }
    assert (false);
    return NULL;
}

extern void  set_parameter(parameter_bank banck,void * configuration)
{
    switch (banck) {
        case GLOBAL:
            memcpy(parameters[select_banck],configuration,sizeof (parameters[select_banck]));
            {
                break;
            }
    case TEMPERATURE:
    {
        memcpy(parameters[select_banck].temp_parameters,configuration,sizeof(parameters[select_banck].temp_parameters));
        break
            }
case PH:
        {
            memcpy(parameters[select_banck].ph_parameters,configuration,sizeof (parameters[select_banck].ph_parameters));
        }
        case GNS:
        {
            memcpy(parameters[select_banck].gns_parameters,configuration,sizeof(parameters[select_banck].gns_parameters) );
        }
        case POWER:
        {
            memcpy(parameters[select_banck].power_parameters,configuration,sizeof (parameters[select_banck].power_parameters));
        }
        case WIFI:
        {
            memcpy(parameters[select_banck].wifi_parameters,configuration,sizeof (parameters[select_banck].wifi_parameters));
        }
        case FDIR_GLOBAL:
        {
            memcpy(parameters[select_banck].fdir_parameters,configuration,sizeof (parameters[select_banck].fdir_parameters))
        }
        case FDIR_POWER:
        {
            memcpy(parameters[select_banck].fdir_parameters.power_fdir,configuration,sizeof (parameters[select_banck].fdir_parameters.power_fdir));
        }
        case FDIR_WIFI:
        {
            memcpy(parameters[select_banck].fdir_parameters.wifi_fdir,configuration,sizeof (parameters[select_banck].fdir_parameters.wifi_fdir));
        }
        case EVENT_GLOBAL:
        {
            memcpy(parameters[select_banck].event_parameters,configuration,sizeof (parameters[select_banck].event_parameters));
        }
        case EVENT_PH:
        {
            memcpy(parameters[select_banck].event_parameters.ph_event,configuration,sizeof (parameters[select_banck].event_parameters.ph_event));
        }
        case EVENT_TEMPERATURE:
        {
            memcpy(parameters[select_banck].event_parameters.temp_event,configuration,sizeof (parameters[select_banck].event_parameters.temp_event));
        }
        case EVENT_PPM:
        {
            memcpy(parameters[select_banck].event_parameters.ppm_event,configuration,sizeof (parameters[select_banck].event_parameters.ppm_event));
        }
        default:
        {
            assert(false);
            return NULL;
        }
    }
    //Copying the paramters in the flash memory
    prefs.putBytes("parameters", parameters, sizeof(parameters));

}

extern void * get_adquisition(void * data,aquisition_enum acq_type)
{
    switch (acq_type) {
        case PPM:
            return &acq_datas.ppm;
        case USER_CONNECTIONS:
            return &acq_datas.users_connections;
        case WIFI_CONECTION_DB:
            return &acq_datas.wifi_connection_db;
        case TEMPERATURE:
            return &acq_datas.temperature;
        case PH:
            return &acq_datas.ph;
            break;
        case POWER:
            return &acq_datas.power=(float);
        default:
            assert(false);
            return NULL;
    }
    assert(false);
    return NULL;
}

extern void set_aquition(void * data,aquisition_enum acq_type)
{
    switch (acq_type) {
        case PPM:
            acq_datas.ppm=(float)*data;
            break;
        case USER_CONNECTIONS:
            acq_datas.users_connections=(uint8_t)*data;
            break;
        case WIFI_CONECTION_DB:
            acq_datas.wifi_connection_db=(float)*data;
            break;
        case TEMPERATURE:
            acq_datas.temperature=(float )*data;
            break;
        case PH:
            acq_datas.ph=(float)*data;
            break;
        case POWER:
            acq_datas.power=(float) *data;
            break;
        default:
            assert(false);
    }
}
