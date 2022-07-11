
#include <stdint.h>

/* TDS Sensor's PIN */
#define TdsSensorPin A0

/* Vref connected */
#define VREF 3.3              // analog reference voltage(Volt) of the ADC

/* Number of samples to have in consideration to make an average */
#define SCOUNT  30            // sum of sample point


static int32_t analogBuffer[SCOUNT];     // store the analog value in the array, read from ADC
static int32_t analogBufferTemp[SCOUNT];
/* Index of values save it */
static int32_t analogBufferIndex = 0;
/* Inde value temp */
static int32_t copyIndex = 0;

/* Get he median of the SCOUNT values */
/* @Param: bArray: list of values */
/* @Param: iFilterLen: Number of values */

static uint32_t getMedianNum(int32_t bArray[], int32_t iFilterLen);


static uint32_t getMedianNum(int bArray[], int iFilterLen){
  int bTab[iFilterLen];
  int i, j, bTemp;
  for (byte i = 0; i<iFilterLen; i++)
    {
      bTab[i] = bArray[i];
    }
  for (j = 0; j < iFilterLen - 1; j++)
    {
      for (i = 0; i < iFilterLen - j - 1; i++)
        {
          if (bTab[i] > bTab[i + 1])
            {
              bTemp = bTab[i];
              bTab[i] = bTab[i + 1];
              bTab[i + 1] = bTemp;
            }
        }
    }
  if ((iFilterLen & 1) > 0)
    {
      bTemp = bTab[(iFilterLen - 1) / 2];
    }
  else
    {
      bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
    }
  return bTemp;
}

/* Get hte values of the TDS in a median of 800 milliseconds */

extern float get_TDS_value(void)
{
  uint64_t analogSampleTimepoint = millis();
  unsigned long printTimepoint = millis();
  float averageVoltage = 0;
  float tdsValue = 0;
  float temperature = 23;       // current temperature for compensation
  float compensationCoefficient;
  float compensationVoltage;

  tdsSampleIsReady=false;


  while(!tdsSampleIsReady)
    {
      if(millis()-analogSampleTimepoint > 40U){     //every 40 milliseconds,read the analog value from the ADC
        analogSampleTimepoint = millis();
        analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
        analogBufferIndex++;
        if(analogBufferIndex == SCOUNT){
          analogBufferIndex = 0;
        }
      }

      if(millis()-analogSampleTimepoint > 800U)
        {
          for(copyIndex=0; copyIndex<SCOUNT; copyIndex++)
            {
              analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
            }
              // read the analog value more stable by the median filtering algorithm, and convert to voltage value
          averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF / 1024.0;

          //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
          compensationCoefficient = 1.0+0.02*(temperature-25.0);
          //temperature compensation
          compensationVoltage=averageVoltage/compensationCoefficient;

          //convert voltage value to tds value
          tdsValue=(133.42*compensationVoltage*compensationVoltage*compensationVoltage - 255.86*compensationVoltage*compensationVoltage + 857.39*compensationVoltage)*0.5;
          tdsSampleIsReady=true;
        }
    }
  return tdsValue;
}





extern void  clean_water_setup(void)
{
  pinMode(TdsSensorPin,INPUT);

}
