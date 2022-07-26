idf_component_register(SRCS "event_use_ut.c" "fdir_use.c"
  INCLUDE_DIRS "."
  REQUIRES cmock nominal-mode parameters
  PRIV_REQUIRES unity)
