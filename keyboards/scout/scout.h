/* Copyright 2022 chinatsu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    sw1, sw4, sw7, sw10, sw13, sw16, sw19, sw22, sw25, sw28, sw31, \
      sw2, sw5, sw8, sw11, sw14, sw17, sw20, sw23, sw26, sw29,     \
        sw3, sw6, sw9, sw12, sw15, sw18, sw21, sw24, sw27, sw30    \
) { \
    { sw1, sw4, sw7, sw10, sw13, sw16, sw19, sw22, sw25, sw28, sw31  }, \
    { sw2, sw5, sw8, sw11, sw14, sw17, sw20, sw23, sw26, sw29, KC_NO }, \
    { sw3, sw6, sw9, sw12, sw15, sw18, sw21, sw24, sw27, sw30, KC_NO },  \
}
