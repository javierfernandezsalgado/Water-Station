idf_component_register(SRCS "external_temperature_test.c" "internal_temperature_test.c" "ph_test.c" "ppm_test.c"
  INCLUDE_DIRS "."
  REQUIRES cmock driver drivers parameters
  PRIV_REQUIRES unity)
