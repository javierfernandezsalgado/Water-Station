idf_component_register(SRCS "nominal-mode.c" "event.c" "fdir.c" "http_send_datas.c" "sensors.c"
  INCLUDE_DIRS "include"
  PRIV_INCLUDE_DIRS ""
  PRIV_REQUIRES parameters esp_wifi esp_http_client
  )
