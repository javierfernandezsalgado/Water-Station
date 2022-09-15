
#include <stdint.h>
#include <stdbool.h>

#include <driver/adc.h>
#include "parameters.h"
#include "ph.h"
//Reading voltage on ADC1 channel 0 (GPIO 36):



extern float get_ph (void)
{

    int voltage = adc1_get_raw(ADC1_CHANNEL_0);
    float ph;
    float calibration_ph=float tds_calibration=(*((calibration_datas *)get_parameter(CALIBRATION))->ph);

    ph = voltage  *(3.3/4095.0);
    return (ph*calibration_ph);
}

extern void ph_setup(void)
{

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_0);
}
