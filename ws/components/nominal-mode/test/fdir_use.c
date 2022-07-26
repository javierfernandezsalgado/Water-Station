#include <unity.h>
#include "fdir.h"
#include "parameters.h"
#include "esp_log.h"

#define TAG "Event mode"
TEST_CASE("task_body next event","[event]")
{
    initialization();
    reset_factory();


    power_fdir_conf * power_fdir=get_parameter(FDIR_POWER);
    wifi_fdir_conf * wifi_fdir = get_parameter(FDIR_WIFI);


    wifi_fdir->no_connection.period=1;
    wifi_fdir->no_connection.isActived=true;

    wifi_fdir->poor_connection.period=1;
    wifi_fdir->poor_connection.isActived=true;

    wifi_fdir->poor_connection.period=1;
    wifi_fdir->poor_connection.isActived=true;

    wifi_fdir->too_many_connections.period=1;
    wifi_fdir->too_many_connections.isActived=true;

    power_fdir->power_max.period=1;
    power_fdir->power_max.isActived=true;

    power_fdir->power_min.period=1;
    power_fdir->power_min.isActived=true;


    set_parameter(FDIR_POWER,power_fdir);
    set_parameter(FDIR_WIFI,wifi_fdir);

    fdir_initialization();

    TEST_ASSERT_EQUAL(1,fdir_task_body());

    wifi_fdir->no_connection.period=20;
    wifi_fdir->no_connection.isActived=true;

    wifi_fdir->poor_connection.period=40;
    wifi_fdir->poor_connection.isActived=true;

    wifi_fdir->poor_connection.period=20;
    wifi_fdir->poor_connection.isActived=true;

    wifi_fdir->too_many_connections.period=15;
    wifi_fdir->too_many_connections.isActived=true;

    power_fdir->power_max.period=2;
    power_fdir->power_max.isActived=true;

    power_fdir->power_min.period=1;
    power_fdir->power_min.isActived=false;

    set_parameter(FDIR_POWER,power_fdir);
    set_parameter(FDIR_WIFI,wifi_fdir);

    fdir_initialization();

    TEST_ASSERT_EQUAL(2,fdir_task_body());

    wifi_fdir->no_connection.period=1;
    wifi_fdir->no_connection.isActived=false;

    wifi_fdir->poor_connection.period=15;
    wifi_fdir->poor_connection.isActived=true;

    wifi_fdir->poor_connection.period=0;
    wifi_fdir->poor_connection.isActived=false;

    wifi_fdir->too_many_connections.period=5;
    wifi_fdir->too_many_connections.isActived=true;

    power_fdir->power_max.period=1;
    power_fdir->power_max.isActived=false;

    power_fdir->power_min.period=1;
    power_fdir->power_min.isActived=false;

    set_parameter(FDIR_POWER,power_fdir);
    set_parameter(FDIR_WIFI,wifi_fdir);

    fdir_initialization();


    TEST_ASSERT_EQUAL(5,fdir_task_body());


    wifi_fdir->no_connection.period=6;
    wifi_fdir->no_connection.isActived=true;

    wifi_fdir->poor_connection.period=4;
    wifi_fdir->poor_connection.isActived=true;

    wifi_fdir->poor_connection.period=3;
    wifi_fdir->poor_connection.isActived=true;

    wifi_fdir->too_many_connections.period=2;
    wifi_fdir->too_many_connections.isActived=true;

    power_fdir->power_max.period=7;
    power_fdir->power_max.isActived=true;

    power_fdir->power_min.period=2;
    power_fdir->power_min.isActived=true;

    set_parameter(FDIR_POWER,power_fdir);
    set_parameter(FDIR_WIFI,wifi_fdir);


    fdir_initialization();


    TEST_ASSERT_EQUAL(2,fdir_task_body());
    TEST_ASSERT_EQUAL(1,fdir_task_body());
    TEST_ASSERT_EQUAL(1,fdir_task_body());
    TEST_ASSERT_EQUAL(2,fdir_task_body());
    TEST_ASSERT_EQUAL(1,fdir_task_body());
    TEST_ASSERT_EQUAL(1,fdir_task_body());
    TEST_ASSERT_EQUAL(1,fdir_task_body());
    TEST_ASSERT_EQUAL(1,fdir_task_body());
    TEST_ASSERT_EQUAL(2,fdir_task_body());




}
