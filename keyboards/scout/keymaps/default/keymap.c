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
#include QMK_KEYBOARD_H

#define L_A LT(1, KC_A)
#define L_S LT(2, KC_S)
#define L_UP LT(3, KC_UP)
#define L_DOWN LT(4, KC_DOWN)

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _A,
    _S,
    _UP,
    _DOWN,
    _ENTERRIGHT
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_ENTER,
         L_A,     L_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     L_UP,
           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,           KC_LEFT, L_DOWN, KC_RIGHT
    ),
    [_A] = LAYOUT(
         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC, 
          _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC,
           _______, _______, _______, _______,  _______, _______, _______,       KC_COMM, KC_DOT, KC_SLSH
    ),
    [_S] = LAYOUT(
         KC_EXCLAIM,KC_AT,KC_HASH,KC_DOLLAR,KC_PERCENT,KC_CIRCUMFLEX,KC_AMPERSAND,KC_ASTERISK,KC_LEFT_PAREN,KC_RIGHT_PAREN,KC_BSPC,
         _______, _______, _______, _______, _______, _______, KC_UNDERSCORE,KC_PLUS,KC_LEFT_CURLY_BRACE,KC_RIGHT_CURLY_BRACE, 
           _______, _______, _______, _______,  _______, _______, _______,       KC_LABK, KC_RABK, KC_QUES
    ),
    [_UP] = LAYOUT(
      KC_ESC, KC_GRV, KC_TILDE, _______, _______, _______, _______, _______, _______, KC_SCLN, KC_QUOT, 
       KC_TAB, _______, _______, _______, _______, _______, _______, _______, _______, _______,
         _______, KC_LGUI, KC_LALT, _______,  _______, _______, _______,       KC_RALT, _______, _______
    ),
    [_DOWN] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
         _______, _______, _______, _______,  _______, _______, _______,       KC_LCTL, _______, KC_RSFT
    ),
    [_ENTERRIGHT] = LAYOUT(
      KC_F1, KC_F2, KC_F3, KC_F4, _______, _______, _______, _______, _______, KC_DQT, _______, 
       KC_F5, KC_F6, KC_F7, KC_F8, _______, _______, _______, _______, _______, _______,
         KC_F9, KC_F10, KC_F11, KC_F12,  _______, _______, _______,       KC_RALT, KC_LCTL, _______
    ),
};

enum myCombos {
    DF_SPACE,
    OP_BS,
    ENTERRIGHT_L5,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM enterright_combo[] = {KC_ENTER, KC_RIGHT, COMBO_END};

combo_t key_combos[] = {
  [DF_SPACE] = COMBO(df_combo, KC_SPC),
  [OP_BS] = COMBO(op_combo, KC_BSPC),
  [ENTERRIGHT_L5] = COMBO(enterright_combo, MO(5))
};