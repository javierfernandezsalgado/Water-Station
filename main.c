#include <Manager/Nominal-mode/nominal-mode.h>
#include <Manager/Parameters/parameters.h>
#include <Manager/Configuration-mode/configuration-mode.h>

//DRIVERS

#include <Drivers/Screen/screen.h>
#include <Drivers/PH/ph.h>
#include <Drivers/Temperature/temperature.h>
#include <Drivers/Clean_water/clean_water.h>
#include <Drivers/Internal_temperature/internal_temperature.h>
#include <log.c/src/log.h>




mode system_mode=CONFIG_MODE;


setup ()
{
  //Driver configuration
  log_info("Setup Init ");

  log_info("Screen set up ");
  screen_setup();

  log_info("ph set up ");
  ph_setup();

  log_info("temperature set up ");
  temperature_setup();

  log_info("clean water set up ");
  clean_water_setup();

  log_info("Internal temperature set up ");
  internal_temperature_setup();

  log_info("Setup finish ");


  delay(get_paramter(SET_UP_DELAY));
}



main ()
{

  switch(get_parameter(SYSTEM_MODE_PARAM))
    {

    case CONFIG:
      {
        log_info("config mode ");
        print_screen("Mode CONFIG ");
        config_mode();
        break;

      }
    case NOMINAL:
      {
        log_info("Nominal mode");
        print_screen("Mode NOMINAL ");
        nominal_mode();
        break;
      }
    default:
      {
        log_error("Mode non defined ");
        print_screen(ERROR_MODE_INCORRECT);
        assert(1u);
        break;
      }
    }
}
