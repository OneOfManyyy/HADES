#pragma once

#include "Application.h"

void TIW(
        const char* inst_name, // Instance name
        bool Rst,
        width_t *CIW,
        width_t *CFW,
        int_part_t *IV,
        fp_data_t *y1, // Golden output
        fp_data_t *y2, // DUT output
        fp_data_t x
        );
