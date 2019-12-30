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

const long a = F_1;
const long s = F_2;
const long e = F_3;
const long t = F_4;
const long n = F_9;
const long i = F_10;
const long o = F_11;
const long p = F_12;
const long m1 = F_5;
const long m2 = F_8;

uint32_t processQwerty(bool lookup) {
	P(m2, SEND(KC_SPC));
	P(m1, SEND(KC_LSHIFT));

	P(a | s | e | t, SEND(KC_TAB));
	P(n | i | o | p, SEND(KC_ENT));
	P(m2 | a | s | e | t, SEND(KC_TAB));
	P(m2 | n | i | o | p, SEND(KC_ENT));

	P(a, SEND(KC_A));
	P(s, SEND(KC_S));
	P(e, SEND(KC_E));
	P(t, SEND(KC_T));
	P(n, SEND(KC_N));
	P(i, SEND(KC_I));
	P(o, SEND(KC_O));
	P(p, SEND(KC_P));

	P(a | s, SEND(KC_W));
	P(a | e, SEND(KC_X));
	P(a | t, SEND(KC_F));
	P(a | n, SEND(KC_Q));
	P(a | i, SEND(KC_Z));
	P(a | o, SEND(KC_LBRC));
	P(a | p, SEND(KC_SLSH));

	P(s | e, SEND(KC_D));
	P(s | t, SEND(KC_C));
	P(s | n, SEND(KC_J));
	P(s | i, SEND(KC_K));
	P(s | o, SEND(KC_DOT));
	P(s | p, SEND(KC_RBRC));

	P(e | t, SEND(KC_R));
	P(e | n, SEND(KC_Y));
	P(e | i, SEND(KC_COMM));
	P(e | o, SEND(KC_MINS));
	P(e | p, SEND(KC_QUOT));

	P(t | n, SEND(KC_B));
	P(t | i, SEND(KC_V));
	P(t | o, SEND(KC_G));
	P(t | p, SEND(KC_BSPC));

	P(n | i, SEND(KC_H));
	P(n | o, SEND(KC_U));
	P(n | p, SEND(KC_M));

	P(i | o, SEND(KC_L));
	P(i | p, SEND(KC_LSHIFT); SEND(KC_1));
	P(m1 | i | p, SEND(KC_LSHIFT); SEND(KC_2));

	P(o | p, SEND(KC_SCLN));

	// Number layer?
	P(m2 | a, SEND(KC_1));
	P(m2 | s, SEND(KC_2));
	P(m2 | e, SEND(KC_3));
	P(m2 | t, SEND(KC_4));
	P(m2 | n, SEND(KC_7));
	P(m2 | i, SEND(KC_8));
	P(m2 | o, SEND(KC_9));
	P(m2 | p, SEND(KC_0));

	P(m2 | a | s, SEND_STRING(":)"));
	P(m2 | m1 | a | s, SEND_STRING(":("));
	P(m2 | a | e, SEND(KC_LSHIFT); SEND(KC_8));
	P(m2 | m1 | a | e, SEND(KC_SLSH));
	P(m2 | a | t, SEND(KC_LSHIFT); SEND(KC_LBRC));
	P(m2 | m1 | a | t, SEND(KC_LALT); SEND(KC_COMM));
	P(m2 | a | n, SEND(KC_GRV));
	P(m2 | a | i, SEND(KC_BSLS));
	P(m2 | a | o, SEND(KC_LBRC));
	P(m2 | a | p, SEND(KC_SLSH));

	P(m2 | s | e, SEND(KC_LALT); SEND(KC_3));
	P(m2 | m1 | s | e, SEND(KC_LALT); SEND(KC_4));
	P(m2 | s | t, SEND_STRING("<a>"));
	P(m2 | s | n, SEND_STRING("<bq>"));
	P(m2 | s | i, SEND(KC_LALT); SEND(KC_P));
	P(m2 | m1 | s | i, SEND(KC_LALT); SEND(KC_J));
	P(m2 | s | o, SEND(KC_DOT));
	P(m2 | s | p, SEND(KC_RBRC));

	P(m2 | e | t, SEND(KC_5));
	P(m2 | e | n, SEND_STRING("<p>"));
	P(m2 | e | i, SEND(KC_COMM));
	P(m2 | e | o, SEND(KC_MINS));
	P(m2 | e | p, SEND(KC_QUOT));

	P(m2 | t | n, SEND(KC_EQL));
	P(m2 | t | i, SEND_STRING("<i>"));
	P(m2 | t | o, SEND_STRING("<b>"));
	P(m2 | t | p, SEND(KC_BSPC));

	P(m2 | n | i, SEND(KC_6));
	P(m2 | n | o, SEND_STRING("<u>"));
	P(m2 | n | p, SEND(KC_LSHIFT); SEND(KC_RBRC));
	P(m2 | m1 | n | p, SEND(KC_LALT); SEND(KC_DOT));

	P(m2 | i | o, SEND(KC_LALT); SEND(KC_LSHIFT); SEND(KC_2));
	P(m2 | m1 | i | o, SEND(KC_LALT); SEND(KC_Y));
	P(m2 | i | p, SEND(KC_LSHIFT); SEND(KC_1));
	P(m2 | m1 | i | p, SEND(KC_LSHIFT); SEND(KC_2));

	P(m2 | o | p, SEND(KC_SCLN));
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
