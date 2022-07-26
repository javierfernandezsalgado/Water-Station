#include <unity.h>
#include "event.h"
#include "parameters.h"
#include "esp_log.h"

#define TAG "Event mode"
TEST_CASE("task_body next event","[event]")
{
    initialization();
    reset_factory();


    temp_event_conf * temp_event=get_parameter(EVENT_TEMPERATURE);
    ph_event_conf * ph_event = get_parameter(EVENT_PH);
    ppm_event_conf *  ppm_event = get_parameter(EVENT_PPM);

    temp_event->max_temp.period=1;
    temp_event->max_temp.isActived=true;

    temp_event->min_temp.period=1;
    temp_event->min_temp.isActived=true;

    ph_event->min_ph.period=1;
    ph_event->min_ph.isActived=true;

    ph_event->max_ph.period=1;
    ph_event->max_ph.isActived=true;

    ppm_event->max_ppm.period=1;
    ppm_event->max_ppm.isActived=true;

    ppm_event->min_ppm.period=1;
    ppm_event->min_ppm.isActived=true;

    set_parameter(EVENT_TEMPERATURE,temp_event);
    set_parameter(EVENT_PH,ph_event);
    set_parameter(EVENT_PPM,ppm_event);

    event_initilization();


    TEST_ASSERT_EQUAL(1u,event_task_body());


    temp_event->max_temp.period=5;
    temp_event->max_temp.isActived=true;

    temp_event->min_temp.period=5;
    temp_event->min_temp.isActived=true;

    ph_event->min_ph.period=10;
    ph_event->min_ph.isActived=true;

    ph_event->max_ph.period=10;
    ph_event->max_ph.isActived=true;

    ppm_event->max_ppm.period=1;
    ppm_event->max_ppm.isActived=true;

    ppm_event->min_ppm.period=1;
    ppm_event->min_ppm.isActived=true;


    set_parameter(EVENT_TEMPERATURE,temp_event);
    set_parameter(EVENT_PH,ph_event);
    set_parameter(EVENT_PPM,ppm_event);

    event_initilization();

    TEST_ASSERT_EQUAL(1u,event_task_body());

    temp_event->max_temp.period=5;
    temp_event->max_temp.isActived=true;

    temp_event->min_temp.period=5;
    temp_event->min_temp.isActived=true;

    ph_event->min_ph.period=10;
    ph_event->min_ph.isActived=true;

    ph_event->max_ph.period=10;
    ph_event->max_ph.isActived=true;

    ppm_event->max_ppm.period=10;
    ppm_event->max_ppm.isActived=true;

    ppm_event->min_ppm.period=10;
    ppm_event->min_ppm.isActived=true;


    set_parameter(EVENT_TEMPERATURE,temp_event);
    set_parameter(EVENT_PH,ph_event);
    set_parameter(EVENT_PPM,ppm_event);

    event_initilization();

    TEST_ASSERT_EQUAL(5u,event_task_body());

    temp_event->max_temp.period=2;
    temp_event->max_temp.isActived=true;

    temp_event->min_temp.period=2;
    temp_event->min_temp.isActived=true;

    ph_event->min_ph.period=2;
    ph_event->min_ph.isActived=true;

    ph_event->max_ph.period=2;
    ph_event->max_ph.isActived=true;

    ppm_event->max_ppm.period=3;
    ppm_event->max_ppm.isActived=true;

    ppm_event->min_ppm.period=3;
    ppm_event->min_ppm.isActived=true;


    set_parameter(EVENT_TEMPERATURE,temp_event);
    set_parameter(EVENT_PH,ph_event);
    set_parameter(EVENT_PPM,ppm_event);

    event_initilization();

    TEST_ASSERT_EQUAL(2u,event_task_body());

    ESP_LOGI(TAG,"SECOND_EXAMPLE--------");

    TEST_ASSERT_EQUAL(1u,event_task_body());




}


TEST_CASE("task_body deactivated events","[event]")
{

    initialization();
    reset_factory();


    temp_event_conf * temp_event=get_parameter(EVENT_TEMPERATURE);
    ph_event_conf * ph_event = get_parameter(EVENT_PH);
    ppm_event_conf *  ppm_event = get_parameter(EVENT_PPM);

    temp_event->max_temp.period=1;
    temp_event->max_temp.isActived=false;

    temp_event->min_temp.period=1;
    temp_event->min_temp.isActived=false;

    ph_event->min_ph.period=1;
    ph_event->min_ph.isActived=false;

    ph_event->max_ph.period=1;
    ph_event->max_ph.isActived=false;

    ppm_event->max_ppm.period=1;
    ppm_event->max_ppm.isActived=false;

    ppm_event->min_ppm.period=1;
    ppm_event->min_ppm.isActived=false;

    set_parameter(EVENT_TEMPERATURE,temp_event);
    set_parameter(EVENT_PH,ph_event);
    set_parameter(EVENT_PPM,ppm_event);

    event_initilization();


    TEST_ASSERT_EQUAL(1000u,event_task_body());

    temp_event->max_temp.period=1;
    temp_event->max_temp.isActived=true;

    temp_event->min_temp.period=1;
    temp_event->min_temp.isActived=true;

    ph_event->min_ph.period=1;
    ph_event->min_ph.isActived=false;

    ph_event->max_ph.period=1;
    ph_event->max_ph.isActived=false;

    ppm_event->max_ppm.period=1;
    ppm_event->max_ppm.isActived=false;

    ppm_event->min_ppm.period=1;
    ppm_event->min_ppm.isActived=false;

    set_parameter(EVENT_TEMPERATURE,temp_event);
    set_parameter(EVENT_PH,ph_event);
    set_parameter(EVENT_PPM,ppm_event);

    event_initilization();


    TEST_ASSERT_EQUAL(1u,event_task_body());

    temp_event->max_temp.period=100;
    temp_event->max_temp.isActived=true;

    temp_event->min_temp.period=100;
    temp_event->min_temp.isActived=true;

    ph_event->min_ph.period=1;
    ph_event->min_ph.isActived=false;

    ph_event->max_ph.period=1;
    ph_event->max_ph.isActived=false;

    ppm_event->max_ppm.period=1;
    ppm_event->max_ppm.isActived=false;

    ppm_event->min_ppm.period=1;
    ppm_event->min_ppm.isActived=false;

    set_parameter(EVENT_TEMPERATURE,temp_event);
    set_parameter(EVENT_PH,ph_event);
    set_parameter(EVENT_PPM,ppm_event);

    event_initilization();


    TEST_ASSERT_EQUAL(100u,event_task_body());
}
