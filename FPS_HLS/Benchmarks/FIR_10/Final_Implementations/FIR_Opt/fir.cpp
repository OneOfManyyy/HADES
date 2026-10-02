#include "fir.h"


void fir (
	bool Restart, // restart signal for setting the shift register
	fp_data_t *y, //output of FIR
	fp_data_t x //signal input,
  ) {

#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

//	MyTupleType Custom_ap_fixed_T = constructTuple(std::make_index_sequence<NumElements>{});


	static Custom_ap_fixed_T_0 shift_reg_0 = 0.0;
	static Custom_ap_fixed_T_4 shift_reg_1 = 0.0;
	static Custom_ap_fixed_T_8 shift_reg_2 = 0.0;
	static Custom_ap_fixed_T_12 shift_reg_3 = 0.0;
	static Custom_ap_fixed_T_16 shift_reg_4 = 0.0;
	static Custom_ap_fixed_T_20 shift_reg_5 = 0.0;
	static Custom_ap_fixed_T_24 shift_reg_6 = 0.0;
	static Custom_ap_fixed_T_28 shift_reg_7 = 0.0;
	static Custom_ap_fixed_T_32 shift_reg_8 = 0.0;
	static Custom_ap_fixed_T_34 shift_reg_9 = 0.0;

	Custom_ap_fixed_T_1 taps_0 = taps[0];
	Custom_ap_fixed_T_5 taps_1 = taps[1];
	Custom_ap_fixed_T_9 taps_2 = taps[2];
	Custom_ap_fixed_T_13 taps_3 = taps[3];
	Custom_ap_fixed_T_17 taps_4 = taps[4];
	Custom_ap_fixed_T_21 taps_5 = taps[5];
	Custom_ap_fixed_T_25 taps_6 = taps[6];
	Custom_ap_fixed_T_29 taps_7 = taps[7];
	Custom_ap_fixed_T_33 taps_8 = taps[8];
	Custom_ap_fixed_T_37 taps_9 = taps[9];

	Custom_ap_fixed_T_2 acc_0 = 0.0;
	Custom_ap_fixed_T_6 acc_1 = 0.0;
	Custom_ap_fixed_T_10 acc_2 = 0.0;
	Custom_ap_fixed_T_14 acc_3 = 0.0;
	Custom_ap_fixed_T_18 acc_4 = 0.0;
	Custom_ap_fixed_T_22 acc_5 = 0.0;
	Custom_ap_fixed_T_26 acc_6 = 0.0;
	Custom_ap_fixed_T_30 acc_7 = 0.0;
	Custom_ap_fixed_T_34 acc_8 = 0.0;
	Custom_ap_fixed_T_38 acc_9 = 0.0;

	Custom_ap_fixed_T_3 mult_out_0 = 0.0;
	Custom_ap_fixed_T_7 mult_out_1 = 0.0;
	Custom_ap_fixed_T_11 mult_out_2 = 0.0;
	Custom_ap_fixed_T_15 mult_out_3 = 0.0;
	Custom_ap_fixed_T_19 mult_out_4 = 0.0;
	Custom_ap_fixed_T_23 mult_out_5 = 0.0;
	Custom_ap_fixed_T_27 mult_out_6 = 0.0;
	Custom_ap_fixed_T_31 mult_out_7 = 0.0;
	Custom_ap_fixed_T_35 mult_out_8 = 0.0;
	Custom_ap_fixed_T_39 mult_out_9 = 0.0;

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

