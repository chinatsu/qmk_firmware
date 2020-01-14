#include QMK_KEYBOARD_H

#include "sten.h"
/*
 *  .---------------------------------------------------.
 *  | T0 | T1 | T2 | T3 | T4 | T5 | T6 | T7 | T8 | T9  |
 *  |--------------------------------------------------|
 *  | P0 | P1 | P2 | P3 | P4 | P5 | P6 | P7 | P8 | P9  |
 *  '--------------------------------------------------'
 */

#define FUNCT (P0 | P1 | P2 | P3)
#define MOVE  (T0 | T1| T2)
#define SYMA  (P0 | P1)
#define SYMB  (P8 | P9)

// QMK Layer Numbers
#define BASE 0
#define TETRIS 1

// Do not change QMK Layer 0! This is your main keyboard.
// Make your QMK modifications to the later layers, to add
// keys/customize on the first layer modify processQwerty():
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_butter(
      STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR,
      STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR
  ),
  [TETRIS] = LAYOUT_butter(
      KC_LSHIFT, KC_Z, KC_X, KC_C, KC_SPACE, KC_SPACE, KC_LEFT, KC_DOWN, KC_RIGHT, KC_F4,
      KC_LSHIFT, KC_Z, KC_X, KC_C, KC_SPACE, KC_SPACE, KC_LEFT, KC_DOWN, KC_RIGHT, TO(BASE)
  )
};
// Note: You can only use basic keycodes here!
// P() is just a wrapper to make your life easier, any C code can be executed.
// Only the longest matched chord is run!
//
// http://docs.gboards.ca
uint32_t processQwerty(bool lookup) {
    // SECRET AGENT CHORDS
    P( T0| P1 | P8 | T9, SEND_STRING(VERSION); SEND_STRING(__DATE__));
    P( T0 | T9, SEND(KC_BSPC));
    P( P0 | P9, SEND(KC_SPC));
    // Dual chords
    P( T2 | T3, SEND(KC_LGUI));
    P( T0 | T1, SEND(KC_LCTL));
    P( P0 | P1, SEND(KC_LSFT));
    P( P8 | P9, SEND(KC_LSFT));
    P( T5 | T6, SEND(KC_LGUI));
    P( T8 | T9, SEND(KC_LCTL));
    P( T7 | T8, SEND(KC_LALT));
    P( T9 | P8, SEND(KC_ENT));
    P( T8 | T9 | P8 | P9, SEND(KC_ALGR));
    P( T0 | T1 | P0 | P1, SEND(KC_ESC));

    // Function Layer
    P( FUNCT | T5, SEND(KC_F1));
    P( FUNCT | T6, SEND(KC_F2));
    P( FUNCT | T7, SEND(KC_F3));
    P( FUNCT | T7, SEND(KC_F4));
    P( FUNCT | T5 | P5, SEND(KC_F5));
    P( FUNCT | T6 | P6, SEND(KC_F6));
    P( FUNCT | T7 | P7, SEND(KC_F7));
    P( FUNCT | T8 | P8, SEND(KC_F8));
    P( FUNCT | P5, SEND(KC_F9));
    P( FUNCT | P6, SEND(KC_F10));
    P( FUNCT | P7, SEND(KC_F11));
    P( FUNCT | P8, SEND(KC_F12));

    // Movement Layer
    P( MOVE | P7, SEND(KC_LEFT));
    P( MOVE | P8, SEND(KC_DOWN));
    P( MOVE | T8, SEND(KC_UP));
    P( MOVE | P9, SEND(KC_RIGHT));
    P( MOVE | T4, SEND(KC_PGUP));
    P( MOVE | P4, SEND(KC_PGDN));
    P( MOVE | T5, SEND(KC_PGUP));
    P( MOVE | P5, SEND(KC_PGDN));

     P(SYMA | T0, SEND(KC_1));
     P(SYMA | T1, SEND(KC_2));
     P(SYMA | T2, SEND(KC_3))
     P(SYMA | T3, SEND(KC_4))
     P(SYMA | T4, SEND(KC_5))
     P(SYMA | T5, SEND(KC_6))
     P(SYMA | T6, SEND(KC_7))
     P(SYMA | T7, SEND(KC_8))
     P(SYMA | T8, SEND(KC_9))
     P(SYMA | T9, SEND(KC_0));

     P(SYMB | T0, SEND(KC_LSFT); SEND(KC_1));
     P(SYMB | T1, SEND(KC_LSFT); SEND(KC_2));
     P(SYMB | T2, SEND(KC_LSFT); SEND(KC_3))
     P(SYMB | T3, SEND(KC_LSFT); SEND(KC_4))
     P(SYMB | T4, SEND(KC_LSFT); SEND(KC_5))
     P(SYMB | T5, SEND(KC_LSFT); SEND(KC_6))
     P(SYMB | T6, SEND(KC_LSFT); SEND(KC_7))
     P(SYMB | T7, SEND(KC_LSFT); SEND(KC_8))
     P(SYMB | T8, SEND(KC_LSFT); SEND(KC_9))
     P(SYMB | T9, SEND(KC_LSFT); SEND(KC_0));

    // P( SYMB | ST0| ST1     SEND(KC_GRV));                    // `
    // P( SYMB | LP,            SEND(KC_LSFT); SEND(KC_LBRC));    // {
    // P( SYMB | LW,            SEND(KC_LBRC));
    // P( SYMB | LH,            SEND(KC_LSFT); SEND(KC_RBRC));    // }
    // P( SYMB | LR,            SEND(KC_RBRC));
    // P( SYMB | ST0           SEND(KC_LSFT); SEND(KC_BSLS));    // |
    // P( SYMB | ST1           SEND(KC_LSFT); SEND(KC_GRV));     // ~
    // P( SYMB | RP  | RB,      SEND(KC_QUOT));
    // P( SYMB | RP  | RG,      SEND(KC_LSFT); SEND(KC_QUOT));    // "
    // P( SYMB | RF,            SEND(KC_KP_PLUS));
    // P( SYMB | RP,            SEND(KC_MINS));
    // P( SYMB | RB,            SEND(KC_EQL));
    // P( SYMB | RL,            SEND(KC_SLSH));
    // P( SYMB | RG,            SEND(KC_COMM));
    // P( SYMB | RT,            SEND(KC_PAST));
    // P( SYMB | RS,            SEND(KC_DOT));

    // Letters
    P( T0 | P0, SEND(KC_A));
    P( T1 | P1, SEND(KC_S));
    P( T2 | P2, SEND(KC_D));
    P( T3 | P3, SEND(KC_F));
    P( T4 | P4, SEND(KC_G));
    P( T5 | P5, SEND(KC_H));
    P( T6 | P6, SEND(KC_L));
    P( T7 | P7, SEND(KC_SCLN));
    P( T8 | P8, SEND(KC_K));
    P( T9 | P9, SEND(KC_J));
    P( T0, SEND(KC_Q));
    P( P0, SEND(KC_Z));
    P( T1, SEND(KC_W));
    P( P1, SEND(KC_X));
    P( T2, SEND(KC_E));
    P( P2, SEND(KC_C));
    P( T3, SEND(KC_R));
    P( P3, SEND(KC_V));
    P( T4, SEND(KC_T));
    P( P4, SEND(KC_B));
    P( T5, SEND(KC_Y));
    P( P5, SEND(KC_N));
    P( T6, SEND(KC_U));
    P( P6, SEND(KC_M));
    P( T7, SEND(KC_I));
    P( P7, SEND(KC_COMM));
    P( T8, SEND(KC_O));
    P( P8, SEND(KC_DOT));
    P( T9, SEND(KC_P));
    P( P9, SEND(KC_SLSH));

    return 0;
}

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
