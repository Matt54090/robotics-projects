/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "app/app_main.h"

#include <stdio.h>

#include "devices/dev_imu.h"
#include "devices/dev_lcd.h"
#include "devices/dev_led.h"
#include "devices/dev_log.h"
#include "devices/dev_servo.h"
#include "devices/dev_ultrasonic.h"
#include "devices/dev_vari_r.h"

typedef enum {
    FLAG_OFF,
    FLAG_ON
} flag_e;

typedef enum {
    LIMIT_DIST = 10,
    LIMIT_ACCEL = 2,

    LIMIT_BATT_TIME = 1000,
    LIMIT_DOOR_TIME = 5000,
    LIMIT_ALERT_TIME = 5000

} limit_e;

static void _process_inputs(app_ctx_t *ctx);
static void _handle_event(app_ctx_t *ctx, system_event_e evt, uint32_t data);
static void _update_state(app_ctx_t *ctx);

int app_main_init(app_ctx_t *ctx)
{
    ctx->state = SYSTEM_STATE_IDLE;
    ctx->tick = 0;

    dev_imu_init();
    dev_lcd_init();
    dev_led_init();
    dev_log_init();
    dev_servo_init();
    dev_ultrasonic_init();
    dev_vari_r_init();

    return 0;
}

int app_main_run(app_ctx_t *ctx)
{
    _process_inputs(ctx);
    _update_state(ctx);

    return 0;
}

static void _process_inputs(app_ctx_t *ctx)
{
    static int door_flag = FLAG_OFF;
    static int imu_flag = FLAG_OFF;

    uint32_t dist;
    int ret = dev_ultrasonic_read_cm(&dist);
    if (ret == RETURN_OK)
    {
        if (dist < LIMIT_DIST)
        {
            if (door_flag == FLAG_OFF)
            {
                _handle_event(ctx, EVENT_ULTRASONIC, dist);
                door_flag = FLAG_ON;
            }
        }
        else
            door_flag = FLAG_OFF;
    }

    float accel = dev_imu_get_accel();
    if (accel > (float)LIMIT_ACCEL)
    {
        if (imu_flag == FLAG_OFF)
        {
            _handle_event(ctx, EVENT_IMU, (uint32_t)(accel * 100));
            imu_flag = FLAG_ON;
        }
    }
    else
        imu_flag = FLAG_OFF;
}

static void _handle_event(app_ctx_t *ctx, system_event_e evt, uint32_t data)
{
    switch (evt)
    {
    case EVENT_ULTRASONIC:
        ctx->state = SYSTEM_STATE_DOOR_OPEN;
        ctx->door_tick = dev_get_tick();
        ctx->door_open = FLAG_ON;

        dev_protocol_send(PROTOCOL_DOOR_OPEN, data);
        break;

    case EVENT_IMU:
        ctx->state = SYSTEM_STATE_ALERT;
        ctx->tick = dev_get_tick();

        dev_protocol_send(PROTOCOL_IMU_ALERT, data);
        break;

    default:
        break;
    }
}

static void _update_state(app_ctx_t *ctx)
{
    uint32_t now = dev_get_tick();

    switch (ctx->state)
    {
    case SYSTEM_STATE_IDLE:
        char buf[32];
        float voltage = dev_vari_r_read_voltage();

        static uint32_t last_bat_tx = 0;
        if (voltage < BATTERY_LOW_THRESHOLD)
        {
            dev_led_blink(LED_RED);
            dev_led_set(LED_YELLOW, LED_OFF);
            dev_led_set(LED_GREEN, LED_OFF);

            snprintf(buf, sizeof(buf), "Low Bat: %.2fV ", voltage);

            if (dev_get_tick() - last_bat_tx > LIMIT_BATT_TIME)
            {
                dev_protocol_send(PROTOCOL_BATTERY_LOW,
                                  (uint32_t)(voltage * 100));
                last_bat_tx = dev_get_tick();
            }
        }
        else
        {
            dev_led_set(LED_RED, LED_OFF);
            dev_led_set(LED_YELLOW, LED_OFF);
            dev_led_set(LED_GREEN, LED_ON);

            snprintf(buf, sizeof(buf), "Battery: %.2fV ", voltage);
        }

        dev_lcd_set_cursor(LCD_FIRST_ROW, LCD_FIRST_COL);
        dev_lcd_printf("[JCRT] Idle,,   ");
        dev_lcd_set_cursor(LCD_SECOND_ROW, LCD_FIRST_COL);
        dev_lcd_printf(buf);

        break;

    case SYSTEM_STATE_DOOR_OPEN:
        dev_servo_open();
        dev_led_set(LED_RED, LED_OFF);
        dev_led_blink(LED_YELLOW);
        dev_led_set(LED_GREEN, LED_ON);

        dev_lcd_set_cursor(LCD_FIRST_ROW, LCD_FIRST_COL);
        dev_lcd_printf("[JCRT] Door Open");

        if (now - ctx->door_tick > LIMIT_DOOR_TIME)
        {
            dev_servo_close();
            ctx->door_open = FLAG_OFF;
            ctx->state = SYSTEM_STATE_IDLE;
        }
        break;

    case SYSTEM_STATE_ALERT:
        dev_led_blink(LED_RED);
        dev_led_set(LED_YELLOW, LED_OFF);
        dev_led_set(LED_GREEN, LED_ON);

        dev_lcd_set_cursor(LCD_FIRST_ROW, LCD_FIRST_COL);
        dev_lcd_printf("[JCRT] Alert!!!!");

        if (now - ctx->tick > LIMIT_ALERT_TIME)
            ctx->state = SYSTEM_STATE_IDLE;

        if (ctx->door_open == FLAG_ON)
        {
            if (now - ctx->door_tick > LIMIT_DOOR_TIME)
            {
                dev_servo_close();
                ctx->door_open = FLAG_OFF;
            }
        }
        break;
    }
}
