#include "dev_led.h"

#include "bsp_gpio.h"
#include "main.h"

void dev_led_on(void)
{
    bsp_gpio_write(GPIO_G_LED_GPIO_Port, GPIO_G_LED_Pin, GPIO_PIN_SET);
}

void dev_led_off(void)
{
    bsp_gpio_write(GPIO_G_LED_GPIO_Port, GPIO_G_LED_Pin, GPIO_PIN_RESET);
}