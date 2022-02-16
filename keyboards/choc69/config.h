/*
Copyright 2022 chinatsu

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

#define VENDOR_ID    0xC337
#define PRODUCT_ID   0x0069
#define DEVICE_VER   0x0001
#define MANUFACTURER chinatsu
#define PRODUCT      choc69

#define MATRIX_ROWS 10
#define MATRIX_COLS 7

 
#define MATRIX_COL_PINS { D3, D2, D1, D0, D4, C6, D7 }
#define MATRIX_ROW_PINS { E6, B4, B5, B6, B2, B3, B1, F7, F6, F5 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

