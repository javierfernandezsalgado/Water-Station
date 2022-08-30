
#include <stdint.h>
#include <stdbool.h>

#include <driver/adc.h>
#include "parameters.h"
//Reading voltage on ADC1 channel 0 (GPIO 36):




/* Vref connected */
#define VREF 3.3              // analog reference voltage(Volt) of the ADC


/* Get he median of the SCOUNT values */
/* @Param: bArray: list of values */
/* @Param: iFilterLen: Number of values */


extern float get_TDS_value(void)
{

    float averageVoltage = 0;
    float tdsValue = 0;
    float temperature = (*(float *)get_adquisition(TEMPERATURE_ACQ));       // current temperature for compensation
    float compensationCoefficient;
    float compensationVoltage;
    float tds_calibration=(*((calibration_datas *)get_parameter(CALIBRATION))->ppm);


    int ppm = adc1_get_raw(ADC1_CHANNEL_0);

    averageVoltage = ppm * (float)VREF / 1024.0;


    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
    compensationCoefficient = 1.0+0.02*(temperature-25.0);
    //temperature compensation
    compensationVoltage=averageVoltage/compensationCoefficient;

    //convert voltage value to tds value
    tdsValue=(133.42*compensationVoltage*compensationVoltage*compensationVoltaged
              - 255.86*compensationVoltage*compensationVoltage + 857.39*compensationVoltage)*0.5;
    return tdsValue*tds_calibration;
}

extern void  clean_water_setup(void)
{

    adc1_config_width(ADC_WIDTH_BIT_10);
    adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_0);
}
