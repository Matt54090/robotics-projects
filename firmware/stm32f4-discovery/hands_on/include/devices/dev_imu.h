/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef DEV_IMU_H
#define DEV_IMU_H

#include <stdint.h>

int dev_imu_init(void);

int dev_imu_read_id(uint8_t *id);

float dev_imu_get_accel(void);

#endif /* DEV_IMU_H */
