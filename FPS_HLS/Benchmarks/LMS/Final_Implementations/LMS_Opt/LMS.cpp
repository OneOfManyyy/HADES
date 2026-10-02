#include "LMS.h"
#include "fixed_point_types.h"

void lms (
	bool Restart,
	fp_data_t *y,
	fp_data_t x,
	fp_data_t d
) {

#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

//////////////// SHIFT REGISTER

	static Custom_ap_fixed_T_0  shift_reg_x_0 = 0.0;
	static Custom_ap_fixed_T_8  shift_reg_x_1 = 0.0;
	static Custom_ap_fixed_T_16 shift_reg_x_2 = 0.0;
	static Custom_ap_fixed_T_24 shift_reg_x_3 = 0.0;
	static Custom_ap_fixed_T_32 shift_reg_x_4 = 0.0;
	static Custom_ap_fixed_T_40 shift_reg_x_5 = 0.0;
	static Custom_ap_fixed_T_48 shift_reg_x_6 = 0.0;
	static Custom_ap_fixed_T_56 shift_reg_x_7 = 0.0;

//////////////// WEIGHTS

	static Custom_ap_fixed_T_1  w_0 = 0.0;
	static Custom_ap_fixed_T_9  w_1 = 0.0;
	static Custom_ap_fixed_T_17 w_2 = 0.0;
	static Custom_ap_fixed_T_25 w_3 = 0.0;
	static Custom_ap_fixed_T_33 w_4 = 0.0;
	static Custom_ap_fixed_T_41 w_5 = 0.0;
	static Custom_ap_fixed_T_49 w_6 = 0.0;
	static Custom_ap_fixed_T_57 w_7 = 0.0;

//////////////// FORWARD MULTIPLIERS

	Custom_ap_fixed_T_3  mult_fw_0 = 0.0;
	Custom_ap_fixed_T_11 mult_fw_1 = 0.0;
	Custom_ap_fixed_T_19 mult_fw_2 = 0.0;
	Custom_ap_fixed_T_27 mult_fw_3 = 0.0;
	Custom_ap_fixed_T_35 mult_fw_4 = 0.0;
	Custom_ap_fixed_T_43 mult_fw_5 = 0.0;
	Custom_ap_fixed_T_51 mult_fw_6 = 0.0;
	Custom_ap_fixed_T_59 mult_fw_7 = 0.0;

//////////////// ACCUMULATORS

	Custom_ap_fixed_T_2  acc_0 = 0.0;
	Custom_ap_fixed_T_10 acc_1 = 0.0;
	Custom_ap_fixed_T_18 acc_2 = 0.0;
	Custom_ap_fixed_T_26 acc_3 = 0.0;
	Custom_ap_fixed_T_34 acc_4 = 0.0;
	Custom_ap_fixed_T_42 acc_5 = 0.0;
	Custom_ap_fixed_T_50 acc_6 = 0.0;
	Custom_ap_fixed_T_58 acc_7 = 0.0;

//////////////// LMS UPDATE

	Custom_ap_fixed_T_65 err = 0.0;
	Custom_ap_fixed_T_67 mu_e = 0.0;

	Custom_ap_fixed_T_7  update_term_0 = 0.0;
	Custom_ap_fixed_T_15 update_term_1 = 0.0;
	Custom_ap_fixed_T_23 update_term_2 = 0.0;
	Custom_ap_fixed_T_31 update_term_3 = 0.0;
	Custom_ap_fixed_T_39 update_term_4 = 0.0;
	Custom_ap_fixed_T_47 update_term_5 = 0.0;
	Custom_ap_fixed_T_55 update_term_6 = 0.0;
	Custom_ap_fixed_T_63 update_term_7 = 0.0;

#pragma HLS BIND_OP variable=mult_fw_0 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_fw_1 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_fw_2 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_fw_3 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_fw_4 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_fw_5 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_fw_6 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_fw_7 op=mul impl=dsp

#pragma HLS BIND_OP variable=update_term_0 op=mul impl=dsp
#pragma HLS BIND_OP variable=update_term_1 op=mul impl=dsp
#pragma HLS BIND_OP variable=update_term_2 op=mul impl=dsp
#pragma HLS BIND_OP variable=update_term_3 op=mul impl=dsp
#pragma HLS BIND_OP variable=update_term_4 op=mul impl=dsp
#pragma HLS BIND_OP variable=update_term_5 op=mul impl=dsp
#pragma HLS BIND_OP variable=update_term_6 op=mul impl=dsp
#pragma HLS BIND_OP variable=update_term_7 op=mul impl=dsp

	if (Restart){

//////////////// RESET SHIFT REGISTERS

		shift_reg_x_0 = 0.0;
		shift_reg_x_1 = 0.0;
		shift_reg_x_2 = 0.0;
		shift_reg_x_3 = 0.0;
		shift_reg_x_4 = 0.0;
		shift_reg_x_5 = 0.0;
		shift_reg_x_6 = 0.0;
		shift_reg_x_7 = 0.0;

//////////////// RESET WEIGHTS

		w_0 = 0.0;
		w_1 = 0.0;
		w_2 = 0.0;
		w_3 = 0.0;
		w_4 = 0.0;
		w_5 = 0.0;
		w_6 = 0.0;
		w_7 = 0.0;

		*y = fp_data_t(0.0);

	} else {

//////////////// SHIFT REGISTER

		shift_reg_x_7 = shift_reg_x_6;
		shift_reg_x_6 = shift_reg_x_5;
		shift_reg_x_5 = shift_reg_x_4;
		shift_reg_x_4 = shift_reg_x_3;
		shift_reg_x_3 = shift_reg_x_2;
		shift_reg_x_2 = shift_reg_x_1;
		shift_reg_x_1 = shift_reg_x_0;
		shift_reg_x_0 = x;

//////////////// FORWARD PATH

		mult_fw_0 = shift_reg_x_0 * w_0;
		mult_fw_1 = shift_reg_x_1 * w_1;
		mult_fw_2 = shift_reg_x_2 * w_2;
		mult_fw_3 = shift_reg_x_3 * w_3;
		mult_fw_4 = shift_reg_x_4 * w_4;
		mult_fw_5 = shift_reg_x_5 * w_5;
		mult_fw_6 = shift_reg_x_6 * w_6;
		mult_fw_7 = shift_reg_x_7 * w_7;

		acc_0 = Custom_ap_fixed_T_2(0.0) + mult_fw_0;
		acc_1 = acc_0 + mult_fw_1;
		acc_2 = acc_1 + mult_fw_2;
		acc_3 = acc_2 + mult_fw_3;
		acc_4 = acc_3 + mult_fw_4;
		acc_5 = acc_4 + mult_fw_5;
		acc_6 = acc_5 + mult_fw_6;
		acc_7 = acc_6 + mult_fw_7;

		*y = acc_7;

//////////////// ERROR

		err = d - (*y);

//////////////// MU * ERROR

		mu_e = mu * err;

//////////////// UPDATE TERMS

		update_term_0 = mu_e * shift_reg_x_0;
		update_term_1 = mu_e * shift_reg_x_1;
		update_term_2 = mu_e * shift_reg_x_2;
		update_term_3 = mu_e * shift_reg_x_3;
		update_term_4 = mu_e * shift_reg_x_4;
		update_term_5 = mu_e * shift_reg_x_5;
		update_term_6 = mu_e * shift_reg_x_6;
		update_term_7 = mu_e * shift_reg_x_7;

//////////////// UPDATE WEIGHTS

		w_0 = w_0 + update_term_0;
		w_1 = w_1 + update_term_1;
		w_2 = w_2 + update_term_2;
		w_3 = w_3 + update_term_3;
		w_4 = w_4 + update_term_4;
		w_5 = w_5 + update_term_5;
		w_6 = w_6 + update_term_6;
		w_7 = w_7 + update_term_7;
	}
}
