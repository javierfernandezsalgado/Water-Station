idf_component_register(SRCS "clean_water.c" "screen.c" "temperature.c"
  INCLUDE_DIRS "include"
  PRIV_INCLUDE_DIRS ""
  PRIV_REQUIRES main nvs_flash app_update)
