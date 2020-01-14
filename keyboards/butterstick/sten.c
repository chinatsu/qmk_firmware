#include QMK_KEYBOARD_H

#include "sten.h"

// Chord state
uint32_t cChord     = 0;  // Current Chord
int      chordIndex = 0;  // Keys in previousachord
int32_t  chordState[32];  // Full Chord history
#define QWERBUF 24        // Size of chords to buffer for output

bool     repeatFlag  = false;  // Should we repeat?
uint32_t pChord      = 0;      // Previous Chord
int      pChordIndex = 0;      // Keys in previousachord
uint32_t pChordState[32];      // Previous chord sate
uint32_t stickyBits = 0;       // Or'd with every incoming press
#ifndef NO_DEBUG
char debugMsg[32];
#endif

// StenoLayer
uint32_t releasedChord = 0;  // Keys released from current chord
uint32_t tChord        = 0;  // Protects state of cChord

#ifndef STENOLAYERS
uint32_t stenoLayers[]   = {P4};
size_t   stenoLayerCount = sizeof(stenoLayers) / sizeof(stenoLayers[0]);
#endif

// Mode state
enum MODE { STENO = 0, QWERTY, COMMAND };
enum MODE pMode;
bool      QWERSTENO = false;
#ifdef ONLYQWERTY
enum MODE cMode = QWERTY;
#else
enum MODE cMode = STENO;
#endif

// Command State
#define MAX_CMD_BUF 20
uint8_t CMDLEN = 0;
uint8_t CMDBUF[MAX_CMD_BUF];

// Key Repeat state
bool     inChord    = false;
bool     repEngaged = false;
uint16_t repTimer   = 0;
#define REP_INIT_DELAY 750
#define REP_DELAY 25

// All processing done at chordUp goes through here
bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]) {
    // Check for mousekeys, this is release

    // handle command mode
    if (cChord == (T0| P0 | T9| P9)) {
#ifndef NO_DEBUG
        uprintf("COMMAND Toggle\n");
#endif
        if (cMode != COMMAND) {  // Entering Command Mode
            CMDLEN = 0;
            pMode  = cMode;
            cMode  = COMMAND;
        } else {  // Exiting Command Mode
            cMode = pMode;

            // Press all and release all
            for (int i = 0; i < CMDLEN; i++) {
                register_code(CMDBUF[i]);
            }
            clear_keyboard();
        }

        goto out;
    }

    // Handle Gaming Toggle,
    if (cChord == (T0| P0 | T9| P9 | T1| P1 | T8| P8) && keymapsCount > 1) {
#ifndef NO_DEBUG
        uprintf("Switching to QMK\n");
#endif
        layer_on(1);
        goto out;
    }

    // Do QWERTY and Momentary QWERTY
    if (cMode == QWERTY || (cMode == COMMAND)) {
        processChord(false);
        goto out;
    }

    // Fallback NKRO Steno
    if (cMode == STENO && QWERSTENO) {
        processChord(true);
        goto out;
    }


out:
    cChord     = 0;
    inChord    = false;
    chordIndex = 0;
    clear_keyboard();
    repEngaged = false;
    for (int i = 0; i < 32; i++) chordState[i] = 0xFFFF;

    return false;
}

// Update Chord State
bool process_steno_user(uint16_t keycode, keyrecord_t *record) {
    // Everything happens in here when steno keys come in.
    // Bail on keyup
    if (!record->event.pressed) return true;

    // Update key repeat timers
    repTimer = timer_read();
    inChord  = true;

    // Switch on the press adding to chord
    bool pr = record->event.pressed;
    switch (keycode) {
        // Mods and stuff
        case STN_ST1:
            pr ? (cChord |= (T4)) : (cChord &= ~(T4));
            break;
        case STN_ST2:
            pr ? (cChord |= (P4)) : (cChord &= ~(P4));
            break;

        // All the letter keys
        case STN_S1:
            pr ? (cChord |= (T0)) : (cChord &= ~(T0));
            break;
        case STN_S2:
            pr ? (cChord |= (P0)) : (cChord &= ~(P0));
            break;
        case STN_TL:
            pr ? (cChord |= (T1)) : (cChord &= ~(T1));
            break;
        case STN_KL:
            pr ? (cChord |= (P1)) : (cChord &= ~(P1));
            break;
        case STN_PL:
            pr ? (cChord |= (T2)) : (cChord &= ~(T2));
            break;
        case STN_WL:
            pr ? (cChord |= (P2)) : (cChord &= ~(P2));
            break;
        case STN_HL:
            pr ? (cChord |= (T3)) : (cChord &= ~(T3));
            break;
        case STN_RL:
            pr ? (cChord |= (P3)) : (cChord &= ~(P3));
            break;
        case STN_FR:
            pr ? (cChord |= (T5)) : (cChord &= ~(T5));
            break;
        case STN_RR:
            pr ? (cChord |= (P5)) : (cChord &= ~(P5));
            break;
        case STN_PR:
            pr ? (cChord |= (T6)) : (cChord &= ~(T6));
            break;
        case STN_BR:
            pr ? (cChord |= (P6)) : (cChord &= ~(P6));
            break;
        case STN_LR:
            pr ? (cChord |= (T7)) : (cChord &= ~(T7));
            break;
        case STN_GR:
            pr ? (cChord |= (P7)) : (cChord &= ~(P7));
            break;
        case STN_TR:
            pr ? (cChord |= (T8)) : (cChord &= ~(T8));
            break;
        case STN_SR:
            pr ? (cChord |= (P8)) : (cChord &= ~(P8));
            break;
        case STN_DR:
            pr ? (cChord |= (T9)) : (cChord &= ~(T9));
            break;
        case STN_ZR:
            pr ? (cChord |= (P9)) : (cChord &= ~(P9));
            break;
    }

    // Store previous state for fastQWER
    if (pr) {
        chordState[chordIndex] = cChord;
        chordIndex++;
    }

    return true;
}
void matrix_scan_user(void) {
    // We abuse this for early sending of key
    // Key repeat only on QWER/SYMB layers
    if (cMode != QWERTY || !inChord) return;

        // Check timers
#ifndef NO_REPEAT
    if (repEngaged && timer_elapsed(repTimer) > REP_DELAY) {
        // Process Key for report
        processChord(false);

        // Send report to host
        send_keyboard_report();
        clear_keyboard();
        repTimer = timer_read();
    }

    if (!repEngaged && timer_elapsed(repTimer) > REP_INIT_DELAY) {
        repEngaged = true;
    }
#endif
};

// For Plover NKRO
uint32_t processFakeSteno(bool lookup) {

    return 0;
}

// Traverse the chord history to a given point
// Returns the mask to use
void processChord(bool useFakeSteno) {
    // Save the clean chord state
    uint32_t savedChord = cChord;

    // Apply Stick Bits if needed
    if (stickyBits != 0) {
        cChord |= stickyBits;
        for (int i = 0; i <= chordIndex; i++) chordState[i] |= stickyBits;
    }

    // First we test if a whole chord was passsed
    // If so we just run it handling repeat logic
    if (processQwerty(true) == cChord) {
        processQwerty(false);
        // Repeat logic
        if (repeatFlag) {
            restoreState();
            repeatFlag = false;
            processChord(false);
        } else {
            saveState(cChord);
        }
        return;
    }

    // Iterate through chord picking out the individual
    // and longest chords
    uint32_t bufChords[QWERBUF];
    int      bufLen = 0;
    uint32_t mask   = 0;

    // We iterate over it multiple times to catch the longest
    // chord. Then that gets addded to the mask and re run.
    while (savedChord != mask) {
        uint32_t test         = 0;
        uint32_t longestChord = 0;

        for (int i = 0; i <= chordIndex; i++) {
            cChord = chordState[i] & ~mask;
            if (cChord == 0) continue;

            // Testing for keycodes
            if (useFakeSteno) {
                test = processFakeSteno(true);
            } else {
                test = processQwerty(true);
            }

            if (test != 0) {
                longestChord = test;
            }
        }

        mask |= longestChord;
        bufChords[bufLen] = longestChord;
        bufLen++;

        // That's a loop of sorts, halt processing
        if (bufLen >= QWERBUF) {
            return;
        }
    }

    // Now that the buffer is populated, we run it
    for (int i = 0; i < bufLen; i++) {
        cChord = bufChords[i];
        if (useFakeSteno) {
            processFakeSteno(false);
        } else {
            processQwerty(false);
        }
    }

    // Save state in case of repeat
    if (!repeatFlag) {
        saveState(savedChord);
    }

    // Restore cChord for held repeat
    cChord = savedChord;

    return;
}
void saveState(uint32_t cleanChord) {
    pChord      = cleanChord;
    pChordIndex = chordIndex;
    for (int i = 0; i < 32; i++) pChordState[i] = chordState[i];
}
void restoreState() {
    cChord     = pChord;
    chordIndex = pChordIndex;
    for (int i = 0; i < 32; i++) chordState[i] = pChordState[i];
}

// Macros for calling from keymap.c
void SEND(uint8_t kc) {
    // Send Keycode, Does not work for Quantum Codes
    if (cMode == COMMAND && CMDLEN < MAX_CMD_BUF) {
#ifndef NO_DEBUG
        uprintf("CMD LEN: %d BUF: %d\n", CMDLEN, MAX_CMD_BUF);
#endif
        CMDBUF[CMDLEN] = kc;
        CMDLEN++;
    }

    if (cMode != COMMAND) register_code(kc);
    return;
}
void REPEAT(void) {
    if (cMode != QWERTY) return;

    repeatFlag = true;
    return;
}
void SET_STICKY(uint32_t stick) {
    stickyBits = stick;
    return;
}
void SWITCH_LAYER(int layer) {
    if (keymapsCount >= layer) layer_on(layer);
}
