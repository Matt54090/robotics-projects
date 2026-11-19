/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef HAL_TIMER_MOCK_H
#define HAL_TIMER_MOCK_H

#include <stdint.h>

#define GPIOC ((GPIO_TypeDef)0x40020800)

#define GPIO_PIN_8 (1U << 8)
#define GPIO_PIN_9 (1U << 9)

#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0

#define TIM3 ((TIM_HandleTypeDef *)0x40000400)

#define TIM_CHANNEL_3 0x00000008U
#define HAL_TIM_ACTIVE_CHANNEL_3 TIM_CHANNEL_3

#define TIM_INPUTCHANNELPOLARITY_RISING 0
#define TIM_INPUTCHANNELPOLARITY_FALLING 1

typedef struct {
    void *Instance;
    uint32_t Channel;
    uint32_t counter;
} TIM_HandleTypeDef;

typedef void *GPIO_TypeDef;

extern TIM_HandleTypeDef htim3;

static inline int HAL_TIM_IC_Start_IT(TIM_HandleTypeDef *htim, uint32_t ch)
{
    (void)htim;
    (void)ch;

    return 0;
}

static inline uint32_t HAL_TIM_ReadCapturedValue(TIM_HandleTypeDef *htim,
                                                 uint32_t ch)
{
    (void)htim;
    (void)ch;

    return 0;
}

static inline void __HAL_TIM_SET_CAPTUREPOLARITY(TIM_HandleTypeDef *htim,
                                                 uint32_t ch, uint32_t polarity)
{
    (void)htim;
    (void)ch;
    (void)polarity;
}

static inline uint32_t __HAL_TIM_GET_COUNTER(TIM_HandleTypeDef *htim)
{
    (void)htim;

    return 0;
}

static inline uint32_t __HAL_TIM_GET_AUTORELOAD(TIM_HandleTypeDef *htim)
{
    (void)htim;

    return 0;
}

static inline int HAL_GPIO_ReadPin(void *port, uint16_t pin)
{
    (void)port;
    (void)pin;

    return 0;
}

static inline void HAL_GPIO_WritePin(void *port, uint16_t pin, int state)
{
    (void)port;
    (void)pin;
    (void)state;
}

static inline uint32_t HAL_GetTick(void)
{
    return 0;
}

#endif /* HAL_TIMER_MOCK_H */
