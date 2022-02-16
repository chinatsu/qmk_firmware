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


#define LAYOUT( \
    sw1, sw6, sw11, sw16, sw21, sw26, sw31, sw36, sw41, sw46, sw51, sw56, sw61,   sw66,      sw68, \
    sw2,   sw7, sw12, sw17, sw22, sw27, sw32, sw37, sw42, sw47, sw52, sw57, sw62, sw67,      sw69, \
     sw3,  sw8, sw13, sw18, sw23, sw28, sw33, sw38, sw43, sw48, sw53, sw58,     sw63,              \
       sw4,   sw9, sw14, sw19, sw24, sw29, sw34, sw39, sw44, sw49, sw54,      sw59,    sw64,       \
        sw5, sw10, sw15,    sw20,    sw25,    sw30,   sw35,  sw40, sw45, sw50,   sw55, sw60, sw65  \
) { \
    { sw1, sw11, sw21, sw31, sw41, sw51, sw61 }, \
    { sw6, sw16, sw26, sw36, sw46, sw56, sw66 }, \
    { sw2, sw12, sw22, sw32, sw42, sw52, sw62 }, \
    { sw7, sw17, sw27, sw37, sw47, sw57, sw67 }, \
    { sw3, sw13, sw23, sw33, sw43, sw53, sw63 }, \
    { sw8, sw18, sw28, sw38, sw48, sw58, sw68 }, \
    { sw4, sw14, sw24, sw34, sw44, sw54, sw64 }, \
    { sw9, sw19, sw29, sw39, sw49, sw59, sw69 }, \
    { sw5, sw15, sw25, sw35, sw45, sw55, sw65 }, \
    { sw10, sw20, sw30, sw40, sw50, sw60, KC_NO } \
}
