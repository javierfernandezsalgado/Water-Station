extern void internal_temperature_setup(void)
{
  

}

extern float get_internal_temperature(void)
{
  //extern uint8_t temprature_sens_read(void);
  return (float)(temprature_sens_read()-32)/1.8;

}
