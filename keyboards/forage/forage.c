#include "quantum.h"

void keyboard_pre_init_kb(void) {
    // Disable the PD peripheral in pre-init because its pins are being used in the matrix:
    PWR->CR3 |= PWR_CR3_UCPD_DBDIS;
    // Call the corresponding _user() function (see https://docs.qmk.fm/#/custom_quantum_functions)
    keyboard_pre_init_user();
    // Customise these values to desired behaviour:
    //debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;
}