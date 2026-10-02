#include "WidthAdapter.h"

void WidthAdapter (
	fp_data_t x,
	width_t cI,
	width_t cF,
	fp_data_t *y
	) {


	fp_data_t data;
	
	/* integer part - sign extension*/
	if (cI>=GI) {
			data(GI+GF-1,GF) = x(GI+GF-1,GF);
	} else {
		for (int i = GI+GF-1; i >= GF; i--) {
#pragma HLS UNROLL
			if (i >= cI+GF) {
				data[i] = x[GI+GF-1]; // replacing data with the sign bit due to down-sizing
			} else {
				data[i] = x[i]; // the actual data
			}
		}
	}

	/* fractional part - setting LSBs to zero */
	if (cF>=GF) {
			data(GF-1,0) = x(GF-1,0);
	} else {
		for (int i = GF-1; i >= 0; i--) {
#pragma HLS UNROLL
			if (i >= GF-cF) {
				data[i] = x[i]; // the actual data
			} else {
				data[i] = 0; // removing the bits outside of the desired fractional width
			}
		}
	}
		
	*y = data;	
 }
