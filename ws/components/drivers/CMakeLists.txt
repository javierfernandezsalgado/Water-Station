idf_component_register(SRCS "clean_water.c"  "temperature.c" "ph.c" "internal_temperature.c"
  INCLUDE_DIRS "include"
  PRIV_INCLUDE_DIRS ""
  PRIV_REQUIRES main nvs_flash app_update ds18x20  parameters driver)
