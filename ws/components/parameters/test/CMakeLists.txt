idf_component_register(SRCS "parameters_nominal_use_ut.c" "acquistion_nominal_use.c"
  INCLUDE_DIRS "."
  REQUIRES cmock parameters
  PRIV_REQUIRES unity)
