#include <WiFi.h>
#include <log.c/src/log.h>
#include <Drivers/Screen/screen.h>
#include <stdbool.h>

extern config_mode(void)
{
  configure_wifi();
  // Configure Wifi in access point https://randomnerdtutorials.com/esp32-access-point-ap-web-server/


  //Create the website for configuration  mode

  while(true)
    {
      website_configure();
    }

}

static void website_configure()
{
  WiFiClient client = server.available();

  uint8_t ssid_nominal = get_parameter(SSID_NOMINAL);
  uint8_t ssid_nominal_passwd = get_parameter(SSID_PASSW_NOMINAL);

  if (client)

    {
      //see as example https://randomnerdtutorials.com/esp32-access-point-ap-web-server/


      // In case that the user ends software restart
      ESP.restart();
    }
}

static void configure_wifi()
{
  uint16_t http_port = get_parameter(HTTP_PORT_CONFIGURE);

  WiFiServer server(http_port);
  const char* ssid     = get_parameter(SSID_CONFIGURATION);
  const char* password = get_parameter(SSID_PASWD_CONFIGURATION);

  IPAddress ip;
  set_parameter(IP_ADDRESS,ip);
  print_screen(ip);

  log_info("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);
  IP=WiFi.softAPIP();
  server.begin();
}
