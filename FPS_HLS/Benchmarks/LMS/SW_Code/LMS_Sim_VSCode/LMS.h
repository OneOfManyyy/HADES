#pragma once

#include "GlobalParameters.h"
// #include <ap_fixed.h>


void lms (
    const char* inst_name,
    bool GoldenInst,
    bool Restart,
    width_t *CIW,
    width_t *CFW,
    int_part_t *IV,
    fp_data_t *y,
    fp_data_t x,
    fp_data_t d,
    fp_data_t *shift_reg_x,
    fp_data_t *w
);
