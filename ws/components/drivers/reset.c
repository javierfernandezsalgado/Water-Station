#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "parameters.h"
#include "driver/gpio.h"
#include <stdint.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define ESP_INTR_FLAG_DEFAULT 0
#define PIN_RESET 12
#define TAG "RESET"

static void IRAM_ATTR gpio_isr_handler_reset(void* arg)
{
  gpio_intr_disable( PIN_RESET);
  uint32_t i=0;
  ESP_LOGI(TAG, "RESET detected");
  for (;i<300000;i++)
    {
      if (gpio_get_level(PIN_RESET)!=1)
        {
          gpio_intr_enable( PIN_RESET);
          ESP_LOGI(TAG, "RESET not enought time pressed buttom");
          break;
        }
      else
        {
          ESP_LOGI(TAG, "RESETING");
          //Reset to factory values.
          load_init_factory_values();
          //Reboot
          fflush(stdout);
          esp_restart();
        }
    }
}



extern void reset_set_up(void)
{

  ESP_LOGI(TAG, "Configuration of the RESET function");
  gpio_config_t io_conf = {};

  //interrupt of rising edge
  io_conf.intr_type = GPIO_INTR_POSEDGE;
  //bit mask of the pins, use GPIO4/5 here
  io_conf.pin_bit_mask = PIN_RESET;
  //set as input mode
  io_conf.mode = GPIO_MODE_INPUT;
  //enable pull-up mode
  io_conf.pull_up_en = 1;

  gpio_config(&io_conf);

  gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
  gpio_isr_handler_add(PIN_RESET, gpio_isr_handler_reset, (void*) PIN_RESET);

  ESP_LOGI(TAG, "Configuration has been set up");

}
