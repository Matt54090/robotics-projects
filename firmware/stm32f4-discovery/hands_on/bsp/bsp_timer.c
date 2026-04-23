/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp/bsp_timer.h"

#include "common/board_config.h"
#include "common/common_hands_on.h"

#ifdef UNIT_TEST
#define TIM3 ((TIM_HandleTypeDef *)0x40000400)

#define TIM_CHANNEL_3 0x00000008U
#define HAL_TIM_ACTIVE_CHANNEL_3 TIM_CHANNEL_3

#define TIM_INPUTCHANNELPOLARITY_RISING 0
#define TIM_INPUTCHANNELPOLARITY_FALLING 1
#endif

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

static uint32_t trigger_start_tick = 0;

int bsp_timer_init(void)
{
    HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);

    HAL_TIM_IC_Start_IT(&BOARD_TIMER_HANDLE, TIM_CHANNEL_3);

    __HAL_TIM_SET_CAPTUREPOLARITY(&BOARD_TIMER_HANDLE, TIM_CHANNEL_3,
                                  TIM_INPUTCHANNELPOLARITY_RISING);

    state = ULTRA_STATE_IDLE;

    return 0;
}

int bsp_timer_trigger(void)
{
    uint32_t now = bsp_get_tick();

    if (state != ULTRA_STATE_IDLE)
    {
        if ((uint32_t)(now - trigger_start_tick) > 50)
            state = ULTRA_STATE_IDLE;
        else
            return RETURN_ERROR;
    }
    trigger_start_tick = now;

    HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
    _delay_us(10);
    HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);

    state = ULTRA_STATE_WAIT_RISING;

    return 0;
}

int bsp_timer_get_pulse(uint32_t *pulse)
{
    uint32_t now = bsp_get_tick();

    if (state == ULTRA_STATE_WAIT_RISING || state == ULTRA_STATE_WAIT_FALLING)
    {
        if ((uint32_t)(now - trigger_start_tick) > 50)
        {
            state = ULTRA_STATE_IDLE;
            return RETURN_ERROR;
        }
    }

    if (state != ULTRA_STATE_DONE)
        return RETURN_ERROR;

    *pulse = pulse_width;
    state = ULTRA_STATE_IDLE;

    return 0;
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
                (__HAL_TIM_GET_AUTORELOAD(&BOARD_TIMER_HANDLE) - rising_time) +
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
    return __HAL_TIM_GET_COUNTER(&BOARD_TIMER_HANDLE);
}

static void _delay_us(uint32_t us)
{
    uint32_t start = _timer_get_us();
    while ((_timer_get_us() - start) < us)
        ;
}
