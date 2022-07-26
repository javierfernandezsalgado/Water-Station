#include <unity.h>
#include "parameters.h"


TEST_CASE("temperature","[acq]")
{
    initialization();

    float temperature = 0.0f;
    set_aquition(&temperature,TEMPERATURE_ACQ);
    TEST_ASSERT_EQUAL(temperature,(*(float *)get_adquisition(TEMPERATURE_ACQ)));

    temperature = 125.5f;
    set_aquition(&temperature,TEMPERATURE_ACQ);
    TEST_ASSERT_EQUAL(temperature,(*(float *)get_adquisition(TEMPERATURE_ACQ)));

    temperature = 42.42f;
    set_aquition(&temperature,TEMPERATURE_ACQ);
    TEST_ASSERT_EQUAL(temperature,(*(float *)get_adquisition(TEMPERATURE_ACQ)));

}

TEST_CASE("ph","[acq]")
{
    float ph = 0.0f;
    set_aquition(&ph,PH_ACQ);
    TEST_ASSERT_EQUAL(ph,(*(float *)get_adquisition(PH_ACQ)));

    ph = 125.5f;
    set_aquition(&ph,PH_ACQ);
    TEST_ASSERT_EQUAL(ph,(*(float *)get_adquisition(PH_ACQ)));

    ph = 42.42f;
    set_aquition(&ph,PH_ACQ);
    TEST_ASSERT_EQUAL(ph,(*(float *)get_adquisition(PH_ACQ)));


}


TEST_CASE("power","[acq]")
{
    float power = 0.0f;
    set_aquition(&power,POWER_ACQ);
    TEST_ASSERT_EQUAL(power,(*(float *)get_adquisition(POWER_ACQ)));

    power = 125.5f;
    set_aquition(&power,POWER_ACQ);
    TEST_ASSERT_EQUAL(power,(*(float *)get_adquisition(POWER_ACQ)));

    power = 42.42f;
    set_aquition(&power,POWER_ACQ);
    TEST_ASSERT_EQUAL(power,(*(float *)get_adquisition(POWER_ACQ)));

}



TEST_CASE("user_connections","[acq]")
{
    uint8_t user_connections = 0;
    set_aquition(&user_connections,USER_CONNECTIONS_ACQ);
    TEST_ASSERT_EQUAL(user_connections,(*(uint8_t *)get_adquisition(USER_CONNECTIONS_ACQ)));

    user_connections = 125;
    set_aquition(&user_connections,USER_CONNECTIONS_ACQ);
    TEST_ASSERT_EQUAL(user_connections,(*(uint8_t *)get_adquisition(USER_CONNECTIONS_ACQ)));

    user_connections = 255;
    set_aquition(&user_connections,USER_CONNECTIONS_ACQ);
    TEST_ASSERT_EQUAL(user_connections,(*(uint8_t *)get_adquisition(USER_CONNECTIONS_ACQ)));

}

TEST_CASE("ppm","[acq]")
{
    float ppm = 0.0f;
    set_aquition(&ppm,PPM_ACQ);
    TEST_ASSERT_EQUAL(ppm,(*(float *)get_adquisition(PPM_ACQ)));

    ppm = 125.5f;
    set_aquition(&ppm,PPM_ACQ);
    TEST_ASSERT_EQUAL(ppm,(*(float *)get_adquisition(PPM_ACQ)));

    ppm = 42.42f;
    set_aquition(&ppm,PPM_ACQ);
    TEST_ASSERT_EQUAL(ppm,(*(float *)get_adquisition(PPM_ACQ)));

}


TEST_CASE("wifi_connection_db","[acq]")
{
    float wifi_conecton_db = 0.0f;
    set_aquition(&wifi_conecton_db,WIFI_CONECTION_DB_ACQ);
    TEST_ASSERT_EQUAL(wifi_conecton_db,(*(float *)get_adquisition(WIFI_CONECTION_DB_ACQ)));

    wifi_conecton_db = 125.5f;
    set_aquition(&wifi_conecton_db,WIFI_CONECTION_DB_ACQ);
    TEST_ASSERT_EQUAL(wifi_conecton_db,(*(float *)get_adquisition(WIFI_CONECTION_DB_ACQ)));

    wifi_conecton_db = 42.42f;
    set_aquition(&wifi_conecton_db,WIFI_CONECTION_DB_ACQ);
    TEST_ASSERT_EQUAL(wifi_conecton_db,(*(float *)get_adquisition(WIFI_CONECTION_DB_ACQ)));
}
