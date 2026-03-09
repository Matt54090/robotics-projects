#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include "stm32f4xx_hal.h"

void bsp_gpio_write(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState state);

#endif /* BSP_GPIO_H */