#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = 5;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

extern float getTemperature(void) {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}


extern void temperature_setup(void)
{
  sensors.begin();

}
