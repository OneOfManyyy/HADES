#pragma once

#include "GlobalParameters.h"
// #include "WidthAdapter.h"
#include "WidthMod.h"

void WCAdder (
	bool GoldenInst, // shows if this is the Golden instance with constant widths
	fp_data_t x1, //input 1
	fp_data_t x2, //input 2
	width_t cI1, //input 1 integer Width
	width_t cF1, //input 1 fractional Width
	width_t cI2, //input 2 integer Width
	width_t cF2, //input 2 fractional Width
	fp_data_t *y //multiplier output
	);
