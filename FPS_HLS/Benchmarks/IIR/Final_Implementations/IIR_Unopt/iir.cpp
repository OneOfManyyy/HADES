#include "iir.h"

void iir (
	bool Restart,
	fp_data_t *y,
	fp_data_t x
  ) {

#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

//////////////// Shift Registers

	static fp_data_t shift_reg_x_0 = 0.0;
	static fp_data_t shift_reg_x_1 = 0.0;
	static fp_data_t shift_reg_x_2 = 0.0;
	static fp_data_t shift_reg_x_3 = 0.0;
	static fp_data_t shift_reg_x_4 = 0.0;
	static fp_data_t shift_reg_x_5 = 0.0;
	static fp_data_t shift_reg_x_6 = 0.0;
	static fp_data_t shift_reg_x_7 = 0.0;
	static fp_data_t shift_reg_x_8 = 0.0;
	static fp_data_t shift_reg_x_9 = 0.0;
	static fp_data_t shift_reg_x_10 = 0.0;

	static fp_data_t shift_reg_y_0 = 0.0;
	static fp_data_t shift_reg_y_1 = 0.0;
	static fp_data_t shift_reg_y_2 = 0.0;
	static fp_data_t shift_reg_y_3 = 0.0;
	static fp_data_t shift_reg_y_4 = 0.0;
	static fp_data_t shift_reg_y_5 = 0.0;
	static fp_data_t shift_reg_y_6 = 0.0;
	static fp_data_t shift_reg_y_7 = 0.0;
	static fp_data_t shift_reg_y_8 = 0.0;
	static fp_data_t shift_reg_y_9 = 0.0;
	static fp_data_t shift_reg_y_10 = 0.0;

//////////////// Coefficients

	fp_data_t b_0 = b[0];
	fp_data_t b_1 = b[1];
	fp_data_t b_2 = b[2];
	fp_data_t b_3 = b[3];
	fp_data_t b_4 = b[4];
	fp_data_t b_5 = b[5];
	fp_data_t b_6 = b[6];
	fp_data_t b_7 = b[7];
	fp_data_t b_8 = b[8];
	fp_data_t b_9 = b[9];
	fp_data_t b_10 = b[10];

	fp_data_t a_1 = -a[1];
	fp_data_t a_2 = -a[2];
	fp_data_t a_3 = -a[3];
	fp_data_t a_4 = -a[4];
	fp_data_t a_5 = -a[5];
	fp_data_t a_6 = -a[6];
	fp_data_t a_7 = -a[7];
	fp_data_t a_8 = -a[8];
	fp_data_t a_9 = -a[9];
	fp_data_t a_10 = -a[10];

//////////////// Feedforward Multipliers

	fp_data_t mult_b_0 = 0.0;
	fp_data_t mult_b_1 = 0.0;
	fp_data_t mult_b_2 = 0.0;
	fp_data_t mult_b_3 = 0.0;
	fp_data_t mult_b_4 = 0.0;
	fp_data_t mult_b_5 = 0.0;
	fp_data_t mult_b_6 = 0.0;
	fp_data_t mult_b_7 = 0.0;
	fp_data_t mult_b_8 = 0.0;
	fp_data_t mult_b_9 = 0.0;
	fp_data_t mult_b_10 = 0.0;

//////////////// Feedback Multipliers

	fp_data_t mult_a_1 = 0.0;
	fp_data_t mult_a_2 = 0.0;
	fp_data_t mult_a_3 = 0.0;
	fp_data_t mult_a_4 = 0.0;
	fp_data_t mult_a_5 = 0.0;
	fp_data_t mult_a_6 = 0.0;
	fp_data_t mult_a_7 = 0.0;
	fp_data_t mult_a_8 = 0.0;
	fp_data_t mult_a_9 = 0.0;
	fp_data_t mult_a_10 = 0.0;

//////////////// Feedforward Accumulators

	fp_data_t acc_ff_0 = 0.0;
	fp_data_t acc_ff_1 = 0.0;
	fp_data_t acc_ff_2 = 0.0;
	fp_data_t acc_ff_3 = 0.0;
	fp_data_t acc_ff_4 = 0.0;
	fp_data_t acc_ff_5 = 0.0;
	fp_data_t acc_ff_6 = 0.0;
	fp_data_t acc_ff_7 = 0.0;
	fp_data_t acc_ff_8 = 0.0;
	fp_data_t acc_ff_9 = 0.0;
	fp_data_t acc_ff_10 = 0.0;

//////////////// Feedback Accumulators

	fp_data_t acc_fb_1 = 0.0;
	fp_data_t acc_fb_2 = 0.0;
	fp_data_t acc_fb_3 = 0.0;
	fp_data_t acc_fb_4 = 0.0;
	fp_data_t acc_fb_5 = 0.0;
	fp_data_t acc_fb_6 = 0.0;
	fp_data_t acc_fb_7 = 0.0;
	fp_data_t acc_fb_8 = 0.0;
	fp_data_t acc_fb_9 = 0.0;
	fp_data_t acc_fb_10 = 0.0;

//#pragma HLS BIND_OP variable=mult_a_0 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_a_1 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_a_2 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_a_3 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_a_4 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_a_5 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_a_6 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_a_7 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_a_8 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_a_9 op=mul impl=dsp

#pragma HLS BIND_OP variable=mult_b_0 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_b_1 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_b_2 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_b_3 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_b_4 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_b_5 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_b_6 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_b_7 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_b_8 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_b_9 op=mul impl=dsp

	if (Restart){

		shift_reg_x_0 = 0.0;
		shift_reg_x_1 = 0.0;
		shift_reg_x_2 = 0.0;
		shift_reg_x_3 = 0.0;
		shift_reg_x_4 = 0.0;
		shift_reg_x_5 = 0.0;
		shift_reg_x_6 = 0.0;
		shift_reg_x_7 = 0.0;
		shift_reg_x_8 = 0.0;
		shift_reg_x_9 = 0.0;
		shift_reg_x_10 = 0.0;

		shift_reg_y_0 = 0.0;
		shift_reg_y_1 = 0.0;
		shift_reg_y_2 = 0.0;
		shift_reg_y_3 = 0.0;
		shift_reg_y_4 = 0.0;
		shift_reg_y_5 = 0.0;
		shift_reg_y_6 = 0.0;
		shift_reg_y_7 = 0.0;
		shift_reg_y_8 = 0.0;
		shift_reg_y_9 = 0.0;
		shift_reg_y_10 = 0.0;

		*y = fp_data_t(0.0);

	} else {

//////////////// Shift Registers

		shift_reg_x_10 = shift_reg_x_9;
		shift_reg_x_9  = shift_reg_x_8;
		shift_reg_x_8  = shift_reg_x_7;
		shift_reg_x_7  = shift_reg_x_6;
		shift_reg_x_6  = shift_reg_x_5;
		shift_reg_x_5  = shift_reg_x_4;
		shift_reg_x_4  = shift_reg_x_3;
		shift_reg_x_3  = shift_reg_x_2;
		shift_reg_x_2  = shift_reg_x_1;
		shift_reg_x_1  = shift_reg_x_0;
		shift_reg_x_0  = x;

		shift_reg_y_10 = shift_reg_y_9;
		shift_reg_y_9  = shift_reg_y_8;
		shift_reg_y_8  = shift_reg_y_7;
		shift_reg_y_7  = shift_reg_y_6;
		shift_reg_y_6  = shift_reg_y_5;
		shift_reg_y_5  = shift_reg_y_4;
		shift_reg_y_4  = shift_reg_y_3;
		shift_reg_y_3  = shift_reg_y_2;
		shift_reg_y_2  = shift_reg_y_1;
		shift_reg_y_1  = shift_reg_y_0;

//////////////// Feedforward

		mult_b_0  = shift_reg_x_0  * b_0;
		mult_b_1  = shift_reg_x_1  * b_1;
		mult_b_2  = shift_reg_x_2  * b_2;
		mult_b_3  = shift_reg_x_3  * b_3;
		mult_b_4  = shift_reg_x_4  * b_4;
		mult_b_5  = shift_reg_x_5  * b_5;
		mult_b_6  = shift_reg_x_6  * b_6;
		mult_b_7  = shift_reg_x_7  * b_7;
		mult_b_8  = shift_reg_x_8  * b_8;
		mult_b_9  = shift_reg_x_9  * b_9;
		mult_b_10 = shift_reg_x_10 * b_10;

		acc_ff_0  = fp_data_t(0.0) + mult_b_0;
		acc_ff_1  = acc_ff_0  + mult_b_1;
		acc_ff_2  = acc_ff_1  + mult_b_2;
		acc_ff_3  = acc_ff_2  + mult_b_3;
		acc_ff_4  = acc_ff_3  + mult_b_4;
		acc_ff_5  = acc_ff_4  + mult_b_5;
		acc_ff_6  = acc_ff_5  + mult_b_6;
		acc_ff_7  = acc_ff_6  + mult_b_7;
		acc_ff_8  = acc_ff_7  + mult_b_8;
		acc_ff_9  = acc_ff_8  + mult_b_9;
		acc_ff_10 = acc_ff_9  + mult_b_10;

//////////////// Feedback

		mult_a_1  = shift_reg_y_1  * a_1;
		mult_a_2  = shift_reg_y_2  * a_2;
		mult_a_3  = shift_reg_y_3  * a_3;
		mult_a_4  = shift_reg_y_4  * a_4;
		mult_a_5  = shift_reg_y_5  * a_5;
		mult_a_6  = shift_reg_y_6  * a_6;
		mult_a_7  = shift_reg_y_7  * a_7;
		mult_a_8  = shift_reg_y_8  * a_8;
		mult_a_9  = shift_reg_y_9  * a_9;
		mult_a_10 = shift_reg_y_10 * a_10;

		acc_fb_1  = fp_data_t(0.0) + mult_a_1;
		acc_fb_2  = acc_fb_1  + mult_a_2;
		acc_fb_3  = acc_fb_2  + mult_a_3;
		acc_fb_4  = acc_fb_3  + mult_a_4;
		acc_fb_5  = acc_fb_4  + mult_a_5;
		acc_fb_6  = acc_fb_5  + mult_a_6;
		acc_fb_7  = acc_fb_6  + mult_a_7;
		acc_fb_8  = acc_fb_7  + mult_a_8;
		acc_fb_9  = acc_fb_8  + mult_a_9;
		acc_fb_10 = acc_fb_9  + mult_a_10;

//////////////// Output

		shift_reg_y_0 = acc_ff_10 + acc_fb_10;

		*y = shift_reg_y_0;
	}
}
