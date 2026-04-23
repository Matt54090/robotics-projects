/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef DEV_VARI_R_H
#define DEV_VARI_R_H

#define BATTERY_LOW_THRESHOLD 1.65f

void dev_vari_r_init(void);
float dev_vari_r_read_voltage(void);

#endif /* DEV_VARI_R_H */
