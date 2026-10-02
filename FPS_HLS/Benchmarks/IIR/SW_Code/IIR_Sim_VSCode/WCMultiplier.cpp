#include "WCMultiplier.h"

void WCMultiplier (
	bool GoldenInst, // shows if this is the Golden instance with constant widths
	fp_data_t x1, //input 1
	fp_data_t x2, //input 2
	width_t cI1, //input 1 integer Width
	width_t cF1, //input 1 fractional Width
	width_t cI2, //input 2 integer Width
	width_t cF2, //input 2 fractional Width
	fp_data_t *y //multiplier output
	) {

	fp_data_t_sq data; // actual result of the multiplier using twice the global widths
	fp_data_t data_sized; // sized data to fit the global widths

	fp_data_t x1_WA, x2_WA; // Width Adapted inputs

	if (GoldenInst){ // no Width adaptor required. we use maximum global widths
		x1_WA = x1;
		x2_WA = x2;
	}
	else{
		x1_WA = WdithMod(x1, cI1, cF1);
		// WidthAdapter (
		// 	x1,
		// 	cI1,
		// 	cF1,
		// 	&x1_WA
		// );
		x2_WA = WdithMod(x2, cI2, cF2);
		// WidthAdapter (
		// 	x2,
		// 	cI2,
		// 	cF2,
		// 	&x2_WA
		// );
	}

	data = x1_WA * x2_WA;
	// data_sized(GI+GF-1,0) = data((GI+2*GF-1),GF); //no longer needed when dealing with floating point on software
	data_sized = data;
	*y = data_sized;
 }
