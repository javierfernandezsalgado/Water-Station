
#include <stdint.h>
#include <stdbool.h>

#include <driver/adc.h>
#include "parameters.h"
#include "ph.h"
#include "esp_log.h"
#include "driver/gpio.h"

//Reading voltage on ADC1 channel 0 (GPIO 34):

#define TAG "PH"

extern float get_ph (void)
{
  int voltage = adc1_get_raw(ADC1_CHANNEL_6);
  float ph;
  float calibration_ph=(((calibration_datas *) get_parameter(CALIBRATION))->ph);
  calibration_ph=20.24 - 12.7;
  ph = ((voltage*(3.3/4096.0))*-5.70)+(calibration_ph);

  ESP_LOGI(TAG,"PH %.2f.",ph);
  return (ph*calibration_ph);

}

extern void ph_setup(void)
{
  gpio_set_direction(GPIO_NUM_34, GPIO_MODE_INPUT);
  adc1_config_width(ADC_WIDTH_BIT_12);

  /*TODO Calibration has not been performed*/
  adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_11);
}
