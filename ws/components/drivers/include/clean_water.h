#ifndef CLEAN_WATER_H
#define CLEAN_WATER_H
/* Setup the device and the turn on  */
extern void  clean_water_setup(void);

/* Get a sample of TDS, it takes 800 milliseconds */
extern float get_TDS_value(void);
#endif
