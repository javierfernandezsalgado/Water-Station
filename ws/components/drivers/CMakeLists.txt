idf_component_register(SRCS "clean_water.c"  "temperature.c" "ph.c"
  INCLUDE_DIRS "include"
  PRIV_INCLUDE_DIRS ""
  PRIV_REQUIRES main nvs_flash app_update ds18b20 parameters driver)
