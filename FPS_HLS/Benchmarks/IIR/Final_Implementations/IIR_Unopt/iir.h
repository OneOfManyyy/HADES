#pragma once

#include "GlobalParameters.h"
//#include "fixed_point_types.h"

void fir (
	bool Restart, // restart signal for setting the shift register
	fp_data_t *y, //output of FIR
	fp_data_t x //signal input,
  );
