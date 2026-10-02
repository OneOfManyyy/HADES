#pragma once

#include "GlobalParameters.h"
// #include <ap_fixed.h>


void unknown_sys (
		bool Restart, // restart signal for setting the shift register
		fp_data_t *y, //output of FIR
		fp_data_t x, //signal input
		fp_data_t *shift_reg
  );
