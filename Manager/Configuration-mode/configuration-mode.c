#include <WiFi.h>
#include <log.c/src/log.h>
#include <Drivers/Screen/screen.h>
#include <stdbool.h>


static WiFiServer server;
static String header;
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
    uint8_t c;
  uint8_t ssid_nominal = get_parameter(SSID_NOMINAL);
  uint8_t ssid_nominal_passwd = get_parameter(SSID_PASSW_NOMINAL);

  if (client)
//see as example https://randomnerdtutorials.com/esp32-access-point-ap-web-server/
    {
    log_info("New client");

        while (client.connected()) {
            if (client.available())
            {
                c = client.read();
                header +=c;
                log_info(c);
                if (c == '\n') {


                }
                }


                }




                // In case that the user ends software restart
      ESP.restart();
    }
}

static void configure_wifi()
{
    wifi_configuration * wifi_conf = (wifi_configuration * )get_parameter( parameter_bank.WIFI);
    IPAddress ip;
    uint16_t http_port = get_parameter(HTTP_PORT_CONFIGURE);

    server = WiFiServer(wifi_conf->http_port);

    set_parameter(IP_ADDRESS,ip);
    print_screen(ip);

    log_info("Setting AP (Access Point)…");
    WiFi.softAP(wifi_conf->ssid_configuration, wifi_conf->ssid_passwd_configuration);
    IP=WiFi.softAPIP();
    server.begin();

}
