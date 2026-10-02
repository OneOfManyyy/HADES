#include "iir.h"

void iir (
	bool Restart,
	fp_data_t *y,
	fp_data_t x
  ) {

#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

//////////////// Shift Registers

	static Custom_ap_fixed_T_0 shift_reg_x_0 = 0.0;
	static Custom_ap_fixed_T_8 shift_reg_x_1 = 0.0;
	static Custom_ap_fixed_T_16 shift_reg_x_2 = 0.0;
	static Custom_ap_fixed_T_24 shift_reg_x_3 = 0.0;
	static Custom_ap_fixed_T_32 shift_reg_x_4 = 0.0;
	static Custom_ap_fixed_T_40 shift_reg_x_5 = 0.0;
	static Custom_ap_fixed_T_48 shift_reg_x_6 = 0.0;
	static Custom_ap_fixed_T_56 shift_reg_x_7 = 0.0;
	static Custom_ap_fixed_T_64 shift_reg_x_8 = 0.0;
	static Custom_ap_fixed_T_72 shift_reg_x_9 = 0.0;
	static Custom_ap_fixed_T_80 shift_reg_x_10 = 0.0;

	static Custom_ap_fixed_T_4 shift_reg_y_0 = 0.0;
	static Custom_ap_fixed_T_12 shift_reg_y_1 = 0.0;
	static Custom_ap_fixed_T_20 shift_reg_y_2 = 0.0;
	static Custom_ap_fixed_T_28 shift_reg_y_3 = 0.0;
	static Custom_ap_fixed_T_36 shift_reg_y_4 = 0.0;
	static Custom_ap_fixed_T_44 shift_reg_y_5 = 0.0;
	static Custom_ap_fixed_T_52 shift_reg_y_6 = 0.0;
	static Custom_ap_fixed_T_60 shift_reg_y_7 = 0.0;
	static Custom_ap_fixed_T_68 shift_reg_y_8 = 0.0;
	static Custom_ap_fixed_T_76 shift_reg_y_9 = 0.0;
	static Custom_ap_fixed_T_84 shift_reg_y_10 = 0.0;

//////////////// Coefficients

	Custom_ap_fixed_T_1 b_0 = b[0];
	Custom_ap_fixed_T_9 b_1 = b[1];
	Custom_ap_fixed_T_17 b_2 = b[2];
	Custom_ap_fixed_T_25 b_3 = b[3];
	Custom_ap_fixed_T_33 b_4 = b[4];
	Custom_ap_fixed_T_41 b_5 = b[5];
	Custom_ap_fixed_T_49 b_6 = b[6];
	Custom_ap_fixed_T_57 b_7 = b[7];
	Custom_ap_fixed_T_65 b_8 = b[8];
	Custom_ap_fixed_T_73 b_9 = b[9];
	Custom_ap_fixed_T_81 b_10 = b[10];

	Custom_ap_fixed_T_5 a_0 = -a[0];
	Custom_ap_fixed_T_13 a_1 = -a[2];
	Custom_ap_fixed_T_21 a_2 = -a[3];
	Custom_ap_fixed_T_29 a_3 = -a[3];
	Custom_ap_fixed_T_37 a_4 = -a[4];
	Custom_ap_fixed_T_45 a_5 = -a[5];
	Custom_ap_fixed_T_53 a_6 = -a[6];
	Custom_ap_fixed_T_61 a_7 = -a[7];
	Custom_ap_fixed_T_69 a_8 = -a[8];
	Custom_ap_fixed_T_77 a_9 = -a[9];
	Custom_ap_fixed_T_85 a_10 = -a[10];

//////////////// Feedforward Multipliers

	Custom_ap_fixed_T_3 mult_b_0 = 0.0;
	Custom_ap_fixed_T_11 mult_b_1 = 0.0;
	Custom_ap_fixed_T_19 mult_b_2 = 0.0;
	Custom_ap_fixed_T_27 mult_b_3 = 0.0;
	Custom_ap_fixed_T_35 mult_b_4 = 0.0;
	Custom_ap_fixed_T_43 mult_b_5 = 0.0;
	Custom_ap_fixed_T_51 mult_b_6 = 0.0;
	Custom_ap_fixed_T_59 mult_b_7 = 0.0;
	Custom_ap_fixed_T_67 mult_b_8 = 0.0;
	Custom_ap_fixed_T_75 mult_b_9 = 0.0;
	Custom_ap_fixed_T_83 mult_b_10 = 0.0;

//////////////// Feedback Multipliers

	Custom_ap_fixed_T_7 mult_a_0 = 0.0;
	Custom_ap_fixed_T_15 mult_a_1 = 0.0;
	Custom_ap_fixed_T_23 mult_a_2 = 0.0;
	Custom_ap_fixed_T_31 mult_a_3 = 0.0;
	Custom_ap_fixed_T_39 mult_a_4 = 0.0;
	Custom_ap_fixed_T_47 mult_a_5 = 0.0;
	Custom_ap_fixed_T_55 mult_a_6 = 0.0;
	Custom_ap_fixed_T_63 mult_a_7 = 0.0;
	Custom_ap_fixed_T_71 mult_a_8 = 0.0;
	Custom_ap_fixed_T_79 mult_a_9 = 0.0;
	Custom_ap_fixed_T_87 mult_a_10 = 0.0;

//////////////// Feedforward Accumulators

	Custom_ap_fixed_T_2 acc_ff_0 = 0.0;
	Custom_ap_fixed_T_10 acc_ff_1 = 0.0;
	Custom_ap_fixed_T_18 acc_ff_2 = 0.0;
	Custom_ap_fixed_T_26 acc_ff_3 = 0.0;
	Custom_ap_fixed_T_34 acc_ff_4 = 0.0;
	Custom_ap_fixed_T_42 acc_ff_5 = 0.0;
	Custom_ap_fixed_T_50 acc_ff_6 = 0.0;
	Custom_ap_fixed_T_58 acc_ff_7 = 0.0;
	Custom_ap_fixed_T_66 acc_ff_8 = 0.0;
	Custom_ap_fixed_T_74 acc_ff_9 = 0.0;
	Custom_ap_fixed_T_82 acc_ff_10 = 0.0;

//////////////// Feedback Accumulators

	Custom_ap_fixed_T_6 acc_fb_0 = 0.0;
	Custom_ap_fixed_T_14 acc_fb_1 = 0.0;
	Custom_ap_fixed_T_20 acc_fb_2 = 0.0;
	Custom_ap_fixed_T_28 acc_fb_3 = 0.0;
	Custom_ap_fixed_T_36 acc_fb_4 = 0.0;
	Custom_ap_fixed_T_44 acc_fb_5 = 0.0;
	Custom_ap_fixed_T_52 acc_fb_6 = 0.0;
	Custom_ap_fixed_T_60 acc_fb_7 = 0.0;
	Custom_ap_fixed_T_68 acc_fb_8 = 0.0;
	Custom_ap_fixed_T_76 acc_fb_9 = 0.0;
	Custom_ap_fixed_T_84 acc_fb_10 = 0.0;

	#pragma HLS BIND_OP variable=mult_a_0 op=mul impl=dsp
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

		*y = Custom_ap_fixed_T_0(0.0);

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

		acc_ff_0  = Custom_ap_fixed_T_0(0.0) + mult_b_0;
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

		mult_a_0  = shift_reg_y_0  * a_0;
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

		acc_fb_1  = Custom_ap_fixed_T_0(0.0) + mult_a_1;
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
