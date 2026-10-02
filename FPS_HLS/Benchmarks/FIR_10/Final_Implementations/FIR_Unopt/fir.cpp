#include "fir.h"


void fir (
	bool Restart, // restart signal for setting the shift register
	fp_data_t *y, //output of FIR
	fp_data_t x //signal input,
  ) {

#pragma HLS INLINE off
#pragma HLS PIPELINE II=1


//	MyTupleType Custom_ap_fixed_T = constructTuple(std::make_index_sequence<NumElements>{});


	static fp_data_t shift_reg_0 = 0.0;
	static fp_data_t shift_reg_1 = 0.0;
	static fp_data_t shift_reg_2 = 0.0;
	static fp_data_t shift_reg_3 = 0.0;
	static fp_data_t shift_reg_4 = 0.0;
	static fp_data_t shift_reg_5 = 0.0;
	static fp_data_t shift_reg_6 = 0.0;
	static fp_data_t shift_reg_7 = 0.0;
	static fp_data_t shift_reg_8 = 0.0;
	static fp_data_t shift_reg_9 = 0.0;

	fp_data_t taps_0 = taps[0];
	fp_data_t taps_1 = taps[1];
	fp_data_t taps_2 = taps[2];
	fp_data_t taps_3 = taps[3];
	fp_data_t taps_4 = taps[4];
	fp_data_t taps_5 = taps[5];
	fp_data_t taps_6 = taps[6];
	fp_data_t taps_7 = taps[7];
	fp_data_t taps_8 = taps[8];
	fp_data_t taps_9 = taps[9];

	fp_data_t acc_0 = 0.0;
	fp_data_t acc_1 = 0.0;
	fp_data_t acc_2 = 0.0;
	fp_data_t acc_3 = 0.0;
	fp_data_t acc_4 = 0.0;
	fp_data_t acc_5 = 0.0;
	fp_data_t acc_6 = 0.0;
	fp_data_t acc_7 = 0.0;
	fp_data_t acc_8 = 0.0;
	fp_data_t acc_9 = 0.0;

	fp_data_t mult_out_0 = 0.0;
	fp_data_t mult_out_1 = 0.0;
	fp_data_t mult_out_2 = 0.0;
	fp_data_t mult_out_3 = 0.0;
	fp_data_t mult_out_4 = 0.0;
	fp_data_t mult_out_5 = 0.0;
	fp_data_t mult_out_6 = 0.0;
	fp_data_t mult_out_7 = 0.0;
	fp_data_t mult_out_8 = 0.0;
	fp_data_t mult_out_9 = 0.0;

#pragma HLS BIND_OP variable=mult_out_0 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_1 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_2 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_3 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_4 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_5 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_6 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_7 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_8 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_9 op=mul impl=dsp

	if (Restart){
		shift_reg_0 = 0.0;
		shift_reg_1 = 0.0;
		shift_reg_2 = 0.0;
		shift_reg_3 = 0.0;
		shift_reg_4 = 0.0;
		shift_reg_5 = 0.0;
		shift_reg_6 = 0.0;
		shift_reg_7 = 0.0;
		shift_reg_8 = 0.0;
		shift_reg_9 = 0.0;
		*y = fp_data_t(0.0);
	} else {
////////////////	SR
		shift_reg_9 = shift_reg_8;
		shift_reg_8 = shift_reg_7;
		shift_reg_7 = shift_reg_6;
		shift_reg_6 = shift_reg_5;
		shift_reg_5 = shift_reg_4;
		shift_reg_4 = shift_reg_3;
		shift_reg_3 = shift_reg_2;
		shift_reg_2 = shift_reg_1;
		shift_reg_1 = shift_reg_0;
		shift_reg_0 = x;


		mult_out_0 = shift_reg_0 * taps_0;
		mult_out_1 = shift_reg_1 * taps_1;
		mult_out_2 = shift_reg_2 * taps_2;
		mult_out_3 = shift_reg_3 * taps_3;
		mult_out_4 = shift_reg_4 * taps_4;
		mult_out_5 = shift_reg_5 * taps_5;
		mult_out_6 = shift_reg_6 * taps_6;
		mult_out_7 = shift_reg_7 * taps_7;
		mult_out_8 = shift_reg_8 * taps_8;
		mult_out_9 = shift_reg_9 * taps_9;
//		printf ("mult_out_1 = %s\n", mult_out_1.to_string(10,true).c_str());

		acc_0 = fp_data_t(0.0) + mult_out_0;
		acc_1 = acc_0 + mult_out_1;
		acc_2 = acc_1 + mult_out_2;
		acc_3 = acc_2 + mult_out_3;
		acc_4 = acc_3 + mult_out_4;
		acc_5 = acc_4 + mult_out_5;
		acc_6 = acc_5 + mult_out_6;
		acc_7 = acc_6 + mult_out_7;
		acc_8 = acc_7 + mult_out_8;
		acc_9 = acc_8 + mult_out_9;

		*y=acc_9; //output of the last MAC
	}
}

