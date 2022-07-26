idf_component_register(SRCS "configuration-mode.c" "dns_server.c"
  INCLUDE_DIRS "include"
  PRIV_INCLUDE_DIRS ""
  PRIV_REQUIRES parameters esp_wifi esp_event esp_http_server
  EMBED_FILES root.html)
