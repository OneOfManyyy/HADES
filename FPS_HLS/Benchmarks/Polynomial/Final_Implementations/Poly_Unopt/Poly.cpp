#include "Poly.h"

void poly (
	bool Restart,
	fp_data_t *y,
	fp_data_t x
){

#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

//////////////// COEFFICIENTS

	const fp_data_t a0 = 0.0;
	const fp_data_t a1 = 0.9999793130;
	const fp_data_t a2 = 0.0;
	const fp_data_t a3 = -0.1666244320;
	const fp_data_t a4 = 0.0;
	const fp_data_t a5 = 0.0083087010;
	const fp_data_t a6 = 0.0;
	const fp_data_t a7 = -0.0001836360;

//////////////// TEMP VARIABLES

	fp_data_t t0 = 0.0;
	fp_data_t t1 = 0.0;
	fp_data_t t2 = 0.0;
	fp_data_t t3 = 0.0;
	fp_data_t t4 = 0.0;
	fp_data_t t5 = 0.0;
	fp_data_t t6 = 0.0;

	fp_data_t mult_out_0 = 0.0;
	fp_data_t mult_out_1 = 0.0;
	fp_data_t mult_out_2 = 0.0;
	fp_data_t mult_out_3 = 0.0;
	fp_data_t mult_out_4 = 0.0;
	fp_data_t mult_out_5 = 0.0;
	fp_data_t mult_out_6 = 0.0;

#pragma HLS BIND_OP variable=mult_out_0 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_1 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_2 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_3 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_4 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_5 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_6 op=mul impl=dsp


//////////////// STAGE 0

	t0 = a7;

//////////////// STAGE 1

	mult_out_0 = x * t0;
	t1 = a6 + mult_out_0;

//////////////// STAGE 2

	mult_out_1 = x * t1;
	t2 = a5 + mult_out_1;

//////////////// STAGE 3

	mult_out_2 = x * t2;
	t3 = a4 + mult_out_2;

//////////////// STAGE 4

	mult_out_3 = x * t3;
	t4 = a3 + mult_out_3;

//////////////// STAGE 5

	mult_out_4 = x * t4;
	t5 = a2 + mult_out_4;

//////////////// STAGE 6

	mult_out_5 = x * t5;
	t6 = a1 + mult_out_5;

//////////////// FINAL

	mult_out_6 = x * t6;
	*y = a0 + mult_out_6;
}
