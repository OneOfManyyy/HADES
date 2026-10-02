#pragma once

#include "GlobalParameters.h"
//#include "fixed_point_types.h"

void lms (
	bool Restart, // restart signal for setting the shift register
	fp_data_t *y, //output of FIR
	fp_data_t x, //signal input,
	fp_data_t d //desired system output
  );
