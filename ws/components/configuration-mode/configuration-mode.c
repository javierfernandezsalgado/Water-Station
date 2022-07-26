#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_http_server.h"

#include "lwip/err.h"
#include "lwip/sys.h"
#include "parameters.h"
#include "dns_server.h"

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1
#define UNUSED(x) (void)(x)

static const char *TAG = "Configuration manager";
extern const char root_start[] asm("_binary_root_html_start");
extern const char root_end[] asm("_binary_root_html_end");

static void configure_wifi();

static httpd_handle_t start_webserver(void);
static esp_err_t root_get_handler(httpd_req_t *req);
static httpd_handle_t start_webserver(void);
static esp_err_t wifi_registration_get_handler(httpd_req_t *req);

static const httpd_uri_t root = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = root_get_handler
};

static const httpd_uri_t wifi_registration = {
    .uri = "/wifi_registration",
    .method = HTTP_POST,
    .handler = wifi_registration_get_handler
};



static esp_err_t wifi_registration_get_handler(httpd_req_t *req)
{

    uint8_t   buf[512u];
    size_t off = 0;
    int    ret;

        /* Search for Custom header field */
    uint8_t wifissid_hdr[250u];
    uint8_t passwd_hdr[250u];
    size_t wifissid_len = httpd_req_get_hdr_value_len(req, "wifissid");
    size_t passwd_len = httpd_req_get_hdr_value_len(req, "passwd");

    wifi_configuration * wifi_conf;
    global_configuration * global_conf;

    ESP_LOGI(TAG, "Server wifi post handler");
    ESP_LOGI(TAG, "/Request WIFI post with the info %d", req->content_len);



    while (off < req->content_len) {
        /* Read data received in the request */
        ret = httpd_req_recv(req,(char *) buf + off, req->content_len - off);
        if (ret <= 0) {
            if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
                httpd_resp_send_408(req);
            }

            return ESP_FAIL;
        }
        off += ret;
        ESP_LOGI(TAG, "/Request WIFI handler recv length %d", ret);
    }
    buf[off] = '\0';



    if (wifissid_len) {
        /* Read Custom header value */
        httpd_req_get_hdr_value_str(req, "wifissid", (char *) wifissid_hdr, wifissid_len + 1);

        /* Set as additional header for response packet */
        //        httpd_resp_set_hdr(req, "wifissid", (char *)wifissid_hdr);
    }
    if (passwd_len) {
        /* Read Custom header value */
        httpd_req_get_hdr_value_str(req, "passwd", (char *) passwd_hdr, passwd_len + 1);

        /* Set as additional header for response packet */
        //httpd_resp_set_hdr(req, "passwd", (char *)passwd_hdr);
    }

    ESP_LOGI(TAG, "SSID %s and PASSWD %s",(char *)wifissid_hdr,(char *)passwd_hdr);
    char * message_registered = "The SSID and the passwd has been properly registered. System rebooting";
    httpd_resp_send(req,message_registered, strlen(message_registered));

    wifi_conf = get_parameter(WIFI);

    memcpy(wifi_conf->ssid_nominal,wifissid_hdr,wifissid_len);
    memcpy(wifi_conf->ssid_passwd_nominal,passwd_hdr,passwd_len);

    set_parameter(WIFI,wifi_conf);

    global_conf = get_parameter (GLOBAL);
    ESP_LOGI(TAG, "Mode is in  %d",global_conf->sm);

    global_conf->sm=NOMINAL;
    ESP_LOGI(TAG, "Transition to nominal %d",global_conf->sm);
    set_parameter(GLOBAL,global_conf);

    ESP_LOGI(TAG, "Restarting");
    vTaskDelay(10000 / portTICK_PERIOD_MS);
    fflush(stdout);
    esp_restart();

    return ESP_OK;

}

// HTTP GET Handler
static esp_err_t root_get_handler(httpd_req_t *req)
{
    const uint32_t root_len = root_end - root_start;

    ESP_LOGI(TAG, "Serve root");
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, root_start, root_len);

    return ESP_OK;
}


// HTTP Error (404) Handler - Redirects all requests to the root page
esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err)
{
    // Set status
    httpd_resp_set_status(req, "302 Temporary Redirect");
    // Redirect to the "/" root directory
    httpd_resp_set_hdr(req, "Location", "/");
    // iOS requires content in the response to detect a captive portal, simply redirecting is not sufficient.
    httpd_resp_send(req, "Configuration WIFI", HTTPD_RESP_USE_STRLEN);

    ESP_LOGI(TAG, "Redirecting to configuration WIFI");
    return ESP_OK;
}

static httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_open_sockets = 3;
    config.lru_purge_enable = true;

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &root);
        httpd_register_uri_handler(server, &wifi_registration);
        httpd_register_err_handler(server, HTTPD_404_NOT_FOUND, http_404_error_handler);
    }
    return server;
}

extern void config_mode(void)
{
    /*
        Turn of warnings from HTTP server as redirecting traffic will yield
        lots of invalid requests
    */
    esp_log_level_set("httpd_uri", ESP_LOG_ERROR);
    esp_log_level_set("httpd_txrx", ESP_LOG_ERROR);
    esp_log_level_set("httpd_parse", ESP_LOG_ERROR);





    configure_wifi();

    start_webserver();
    // Start the DNS server that will redirect all queries to the softAP IP
    start_dns_server();



}


static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    static uint32_t s_retry_num = 0;
    static EventGroupHandle_t s_wifi_event_group;
    UNUSED(s_retry_num);

    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
    else
    {
        //Empty else branch
    }

}


static void configure_wifi()
{
    wifi_configuration * wifi_conf = (wifi_configuration * ) get_parameter(WIFI);
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    wifi_config_t wifi_config =
        {
            .ap = {
                .ssid_len = strlen((const char *)wifi_conf->ssid_configuration),
                .channel = wifi_conf->wifi_channel_configuration,
                .max_connection = wifi_conf->max_connection_configuration,
                .authmode = WIFI_AUTH_WPA_WPA2_PSK,
                .pmf_cfg = {
                    .required = false,
                },
            },
        };
        memcpy(wifi_config.ap.ssid,wifi_conf->ssid_configuration,strlen((const char *) wifi_conf->ssid_configuration));
        memcpy(wifi_config.ap.password,wifi_conf->ssid_passwd_configuration,strlen((const char *) wifi_conf->ssid_passwd_configuration));

        //Config Wifi
        ESP_ERROR_CHECK(esp_netif_init());
        ESP_ERROR_CHECK(esp_event_loop_create_default());
        esp_netif_create_default_wifi_ap();

        //Init wifi
        ESP_ERROR_CHECK(esp_wifi_init(&cfg));
        ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                            ESP_EVENT_ANY_ID,
                                                            &wifi_event_handler,
                                                            NULL,
                                                            NULL));

        //Type of free wifi
        if (strlen((const char *)wifi_conf->ssid_passwd_configuration) == 0) {
            wifi_config.ap.authmode = WIFI_AUTH_OPEN;
        }
        //Running wifi
        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
        ESP_ERROR_CHECK(esp_wifi_start());
        ESP_LOGI(TAG,"Max connection %d",wifi_conf->max_connection_configuration);
        ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%c password:%c channel:%d",
                 wifi_config.ap.ssid,wifi_config.ap.password, wifi_conf->wifi_channel_configuration);

}
