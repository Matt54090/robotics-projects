/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef HAL_PWM_MOCK_H
#define HAL_PWM_MOCK_H

#include <stdint.h>

#define TIM_CHANNEL_2 2

typedef struct {
    uint32_t dummy;
} TIM_HandleTypeDef;

extern TIM_HandleTypeDef htim4;

static inline void HAL_TIM_PWM_Start(void *htim, uint32_t channel)
{
    (void)htim;
    (void)channel;
}

static inline void __HAL_TIM_SET_COMPARE(void *htim, uint32_t channel,
                                         uint32_t pulse)
{
    (void)htim;
    (void)channel;
    (void)pulse;
}

static inline uint32_t HAL_GetTick(void)
{
    return 0;
}

#endif /* HAL_PWM_MOCK_H */
