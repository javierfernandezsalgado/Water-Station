#ifndef NOMINAL_MODE
#define NOMINAL_MODE


/** Nominal mode creates the full insfrastructure to the execute the nominal mode.
1. Retrieves the infomration from the parameter module. FDIR and Event. In addition, the configuration for the WIFI.
   2. Create the tasks needed to manage the nominal mode. FDIR, Events, Sensors, and Website. **/

extern void nominal_mode(void);



#endif
