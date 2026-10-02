#pragma once

#include "GlobalParameters.h"
#include <ap_fixed.h>

void poly (
    const char* inst_name,
    bool GoldenInst,
    bool Restart, // not used (kept for interface consistency)
    width_t *CIW,
    width_t *CFW,
    int_part_t *IV,
    fp_data_t *y,
    fp_data_t x
);
