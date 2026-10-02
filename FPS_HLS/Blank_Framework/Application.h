#pragma once

#include "GlobalParameters.h"

void Application(
    const char* inst_name,
    bool GoldenInst,
    bool reset,
    width_t* CIW,
    width_t* CFW,
    const fp_data_t* input,
    fp_data_t* output
    /* ... application-specific ports ... */
);
