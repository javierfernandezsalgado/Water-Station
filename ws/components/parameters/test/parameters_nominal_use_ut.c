#include <unity.h>
#include "parameters.h"
#include "esp_log.h"
#include <stdint.h>

#define TAG "TEST_CASE"
#include <string.h>

TEST_CASE("set_wifi_parameter","[parameters]")
{
    initialization();
    reset_factory();
    wifi_configuration * wifi_conf;
    wifi_conf = get_parameter(WIFI);

    uint16_t port = wifi_conf->http_port=80u;
    set_parameter(WIFI,wifi_conf);

    TEST_ASSERT_EQUAL(port,((wifi_configuration *)get_parameter(WIFI))->http_port);

    /*SSID_CONFIGURATION*/

    wifi_conf = get_parameter(WIFI);

    memcpy(wifi_conf->ssid_configuration,"example\0",strlen("example "));
    set_parameter(WIFI,wifi_conf);

    TEST_ASSERT_EQUAL_STRING("example\0",(char *)((wifi_configuration *)get_parameter(WIFI))->ssid_configuration);

    /*SSID_PASSWD*/
    wifi_conf = get_parameter(WIFI);

    memcpy(wifi_conf->ssid_passwd_configuration,"passwd\0",strlen("paaswd "));

    set_parameter(WIFI,wifi_conf);
    TEST_ASSERT_EQUAL_STRING("passwd\0",(char *)((wifi_configuration *)get_parameter(WIFI))->ssid_passwd_configuration);


/*SSID*/

    wifi_conf = get_parameter(WIFI);

    memcpy(wifi_conf->ssid_nominal,"example\0",strlen("example "));

    set_parameter(WIFI,wifi_conf);
    TEST_ASSERT_EQUAL_STRING("example\0",((wifi_configuration *)get_parameter(WIFI))->ssid_nominal);


    /*SSID PASW*/

    wifi_conf = get_parameter(WIFI);

    memcpy(wifi_conf->ssid_passwd_nominal,"example\0",strlen("example "));

    set_parameter(WIFI,wifi_conf);
    TEST_ASSERT_EQUAL_STRING("example\0",((wifi_configuration *)get_parameter(WIFI))->ssid_passwd_nominal);



/*IP*/

    uint8_t ip_address_compare[4u]={255,255,255,255};
    wifi_conf = get_parameter(WIFI);

    memcpy(wifi_conf->ip_address_configuration,ip_address_compare,sizeof(uint8_t)*4);

    set_parameter(WIFI,wifi_conf);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ip_address_compare,((wifi_configuration *)get_parameter(WIFI))->ip_address_configuration,4u);
}



TEST_CASE("system_mode_configuration ","[parameters]")
{
    initialization();
    reset_factory();

    system_mode sm=CONFIGURATION;
    global_configuration * global = (global_configuration * ) get_parameter(GLOBAL);

    TEST_ASSERT_EQUAL(global->sm,sm);

    global->sm = NOMINAL;
    set_parameter(GLOBAL,global);
    TEST_ASSERT_EQUAL(NOMINAL,((global_configuration *)get_parameter(GLOBAL))->sm);

    global->sm = STANDBY;
    set_parameter(GLOBAL,global);
    TEST_ASSERT_EQUAL(STANDBY,((global_configuration *)get_parameter(GLOBAL))->sm);



}

TEST_CASE("ph_configuration ","[parameters]")
{
    ESP_LOGI(TAG,"PH Configuration test cases starting");
    initialization();
    reset_factory();

    ESP_LOGI(TAG,"Memory initializate in the PH");
    ph_configuration * ph_parameters;
    ph_parameters = get_parameter(PH);

    ESP_LOGI(TAG,"PH Get parameter");
    uint8_t pin=255u;

    ph_parameters->pin=pin;

    ESP_LOGI(TAG,"PH set parameter");
    set_parameter(GNS,ph_parameters);

    ESP_LOGI(TAG,"PH get parameter");
    ph_parameters = get_parameter(PH);


    TEST_ASSERT_EQUAL(ph_parameters->pin,pin);
    ESP_LOGI(TAG,"Assert done");
    pin=0u;

    ph_parameters->pin=pin;
    set_parameter(GNS,ph_parameters);
    ph_parameters = get_parameter(PH);

    TEST_ASSERT_EQUAL(ph_parameters->pin,pin);


    pin=125u;

    ph_parameters->pin=pin;
    set_parameter(GNS,ph_parameters);
    ph_parameters = get_parameter(PH);
    TEST_ASSERT_EQUAL(ph_parameters->pin,pin);

}

TEST_CASE("gns_configuration ","[parameters]")
{
    initialization();
    reset_factory();

    gns_configuration * gns_parameters;
    gns_parameters=get_parameter(GNS);

    uint8_t pin=255u;

    gns_parameters->pin=pin;
    set_parameter(GNS,gns_parameters);
    TEST_ASSERT_EQUAL(gns_parameters->pin,pin);

    pin=0u;

    gns_parameters->pin=pin;
    set_parameter(GNS,gns_parameters);
    TEST_ASSERT_EQUAL(gns_parameters->pin,pin);


    pin=125u;

    gns_parameters->pin=pin;
    set_parameter(GNS,gns_parameters);
    TEST_ASSERT_EQUAL(gns_parameters->pin,pin);

}

TEST_CASE("power_configuration ","[parameters]")
{


}

TEST_CASE("fdir_configuration ","[parameters]")
{


}

TEST_CASE("event_configuration","[parameters]")
{


}

TEST_CASE("temp_configuration","[parameters]")
{


}
