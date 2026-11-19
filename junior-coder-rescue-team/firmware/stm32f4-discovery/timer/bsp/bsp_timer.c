/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp_timer.h"

#include "board_timer_config.h"

typedef enum {
    ULTRA_STATE_IDLE = 0,
    ULTRA_STATE_TRIGGERED,
    ULTRA_STATE_WAIT_RISING,
    ULTRA_STATE_WAIT_FALLING,
    ULTRA_STATE_DONE,
    ULTRA_STATE_ERROR
} ultra_state_e;

static uint32_t _timer_get_us(void);
static void _delay_us(uint32_t us);

static volatile uint32_t rising_time = 0;
static volatile uint32_t falling_time = 0;
static volatile uint32_t pulse_width = 0;

static volatile ultra_state_e state = ULTRA_STATE_IDLE;

int bsp_timer_init(void)
{
    HAL_TIM_IC_Start_IT(BOARD_TIMER_HANDLE, TIM_CHANNEL_3);
    return 0;
}

void bsp_timer_trigger(void)
{
    if (state != ULTRA_STATE_IDLE)
        return;

    HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
    _delay_us(10);
    HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);

    state = ULTRA_STATE_WAIT_RISING;
}

int bsp_timer_get_pulse(uint32_t *pulse)
{
    if (state != ULTRA_STATE_DONE)
        return -1;

    *pulse = pulse_width;
    state = ULTRA_STATE_IDLE;

    return 0;
}

uint32_t bsp_timer_get_tick(void)
{
    return HAL_GetTick();
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance != TIM3 || htim->Channel != HAL_TIM_ACTIVE_CHANNEL_3)
        return;

    uint32_t captured = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);

    switch (state)
    {
    case ULTRA_STATE_WAIT_RISING:
        rising_time = captured;

        __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3,
                                      TIM_INPUTCHANNELPOLARITY_FALLING);

        state = ULTRA_STATE_WAIT_FALLING;
        break;

    case ULTRA_STATE_WAIT_FALLING:
        falling_time = captured;

        if (falling_time >= rising_time)
            pulse_width = falling_time - rising_time;
        else
            pulse_width =
                (__HAL_TIM_GET_AUTORELOAD(BOARD_TIMER_HANDLE) - rising_time) +
                falling_time + 1;

        __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3,
                                      TIM_INPUTCHANNELPOLARITY_RISING);

        state = ULTRA_STATE_DONE;
        break;

    default:
        state = ULTRA_STATE_ERROR;
        break;
    }
}

static uint32_t _timer_get_us(void)
{
    return __HAL_TIM_GET_COUNTER(BOARD_TIMER_HANDLE);
}

static void _delay_us(uint32_t us)
{
    uint32_t start = _timer_get_us();
    while ((_timer_get_us() - start) < us)
        ;
}
