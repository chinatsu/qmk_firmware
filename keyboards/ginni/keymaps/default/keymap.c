/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H
#include "sten.h"
#include <print.h>

uint32_t processQwerty(bool lookup) {
	P(F_1, 				SEND(KC_A));
	P(F_2, 				SEND(KC_S));
	P(F_3, 				SEND(KC_D));
	P(F_4, 				SEND(KC_F));
	P(F_5, 				SEND(KC_G));
	P(F_8, 				SEND(KC_H));
	P(F_9, 				SEND(KC_J));
	P(F_10, 				SEND(KC_K));
	P(F_11, 				SEND(KC_L));
	P(F_12, 				SEND(KC_SCLN));
	P(F_5 | F_8,			SEND(KC_ENT));
	P(F_1 | F_12,			SEND(KC_BSPC));
	return 0;
}
// Blank template at the bottom
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_georgi(
			STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,       STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
			STN_PWR, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,       STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
																 STN_N1,  STN_A,   STN_O,         STN_E,   STN_U,   STN_N7
	)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
  return true;
}

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
