// Copyright 2023 artic-plus (@artic-plus)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define ENCODERS_PAD_A { B1 }
#define ENCODERS_PAD_B { F7 }

#define ENCODER_RESOLUTION 4
#define ENCODER_MAP_KEY_DELAY 10

#define BACKLIGHT_PINS { F4, F5 }

