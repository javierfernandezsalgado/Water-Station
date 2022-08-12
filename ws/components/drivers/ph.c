
#include <stdint.h>
#include <stdbool.h>

#include <driver/adc.h>
#include "parameters.h"
#include "ph.h"
#include "esp_log.h"
//Reading voltage on ADC1 channel 0 (GPIO 36):

#define TAG "PH"

extern float get_ph (void)
{

    int voltage = adc1_get_raw(ADC1_CHANNEL_7);
    float ppm;

    ESP_LOGI(TAG,"Voltage of the PPM is %d",voltage);
    ppm = voltage  *(3.3/1024.0);



    return ppm;
}

extern void ph_setup(void)
{

    adc1_config_width(ADC_WIDTH_BIT_10);

/*TODO Calibration has not been performed*/
    adc1_config_channel_atten(ADC1_CHANNEL_7,ADC_ATTEN_DB_0);
}
