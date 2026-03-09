#include "app_main.h"

#include "common.h"
#include "dev_led.h"

void app_init(void)
{
}

void app_run(void)
{
    dev_led_on();
    delay_ms(1000);

    dev_led_off();
    delay_ms(1000);
}