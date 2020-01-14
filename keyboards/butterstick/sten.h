// 2019, g Heavy Industries
// Blessed mother of Christ, please keep this readable
// and protect us from segfaults. For thine is the clock,
// the slave and the master. Until we return from main.
//
// Amen.

#include QMK_KEYBOARD_H
#include "keymap.h"
#include "keymap_steno.h"
#include "wait.h"

extern size_t keymapsCount;			// Total keymaps
extern uint32_t cChord;				// Current Chord
extern uint32_t stenoLayers[];		// Chords that simulate QMK layers
extern size_t stenoLayerCount;		// Number of simulated layers
uint32_t refChord;					// Reference chord for PC macro

// Function defs
void 			processChord(bool useFakeSteno);
uint32_t	processQwerty(bool lookup);
uint32_t 	processFakeSteno(bool lookup);
void 			saveState(uint32_t cChord);
void 			restoreState(void);

// Macros for use in keymap.c
void 			SEND(uint8_t kc);
void 			REPEAT(void);
void 			SET_STICKY(uint32_t);
void 			SWITCH_LAYER(int);

// Keymap helper
#define P(chord, act) if (cChord == (chord)) { if (!lookup) {act;} return chord;}
#define PC(chord, act) if (cChord == (chord)) { if (!lookup) {act;} return chord;} \
	for(int i = 0; i < stenoLayerCount; i++) { \
		refChord = stenoLayers[i] | chord; \
		if (cChord == (refChord)) { if (!lookup) {act;} return refChord;}; \
}

// Shift to internal representation
// i.e) S(teno)R(ight)F
#define STN(n) (1L<<n)
enum ORDER {
		SFN = 0, SPWR, SST1, SST2, SST3, SST4, SNUML, SNUMR,
		SLSU, SLSD, SLT, SLK, SLP, SLW, SLH, SLR, SLA, SLO,
		SRE, SRU, SRF, SRR, SRP, SRB, SRL, SRG, SRT, SRS, SRD, SRZ, SRES1, SRES2
};


#define T0 STN(SLSU)
#define P0 STN(SLSD)
#define T1 STN(SLT)  	// (L)e(F)t (T), preprocessor conflict
#define P1  STN(SLK)
#define T2 STN(SLP)
#define P2  STN(SLW)
#define T3 STN(SLH)
#define P3  STN(SLR)
#define T4 STN(SST1)
#define P4 STN(SST2)

#define T5 STN(SRF)
#define P5  STN(SRR)
#define T6 STN(SRP)
#define P6  STN(SRB)
#define T7 STN(SRL)
#define P7  STN(SRG)
#define T8 STN(SRT)
#define P8  STN(SRS)
#define T9 STN(SRD)
#define P9  STN(SRZ)
