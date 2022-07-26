idf_component_register(SRCS "nominal-mode.c" "event.c" "fdir.c" "webservice.c" "sensors.c"
  INCLUDE_DIRS "include"
  PRIV_INCLUDE_DIRS ""
  PRIV_REQUIRES parameters esp_wifi esp_event esp_http_server file-system
  )
spiffs_create_partition_image(storage ../../website FLASH_IN_PROJECT)
