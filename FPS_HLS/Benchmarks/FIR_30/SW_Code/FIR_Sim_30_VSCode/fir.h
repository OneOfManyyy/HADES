#pragma once

#include "GlobalParameters.h"
// #include <ap_fixed.h>


void fir (
		const char* inst_name, // Instance name, different Instances are instantiated based on this input, needed for referencing to this instance
		bool GoldenInst, // shows if this is the Golden instance with constant widths
		bool Restart, // restart signal for setting the shift register
		width_t *CIW, //intermediate integer Widths
		width_t *CFW, //intermediate fractional Widths
		int_part_t *IV, //intermediate variable integer values
		fp_data_t *y, //output of FIR
		fp_data_t x, //signal input
		fp_data_t *shift_reg
  );

