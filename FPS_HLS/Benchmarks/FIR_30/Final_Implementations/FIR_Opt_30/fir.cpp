#include "fir.h"


void fir (
	bool Restart, // restart signal for setting the shift register
	fp_data_t *y, //output of FIR
	fp_data_t x //signal input,
  ) {

#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

//	MyTupleType Custom_ap_fixed_T = constructTuple(std::make_index_sequence<NumElements>{});


	static Custom_ap_fixed_T_0  	shift_reg_0  	= 0.0;
	static Custom_ap_fixed_T_4  	shift_reg_1  	= 0.0;
	static Custom_ap_fixed_T_8  	shift_reg_2  	= 0.0;
	static Custom_ap_fixed_T_12 	shift_reg_3  	= 0.0;
	static Custom_ap_fixed_T_16 	shift_reg_4  	= 0.0;
	static Custom_ap_fixed_T_20 	shift_reg_5  	= 0.0;
	static Custom_ap_fixed_T_24 	shift_reg_6  	= 0.0;
	static Custom_ap_fixed_T_28 	shift_reg_7  	= 0.0;
	static Custom_ap_fixed_T_32 	shift_reg_8  	= 0.0;
	static Custom_ap_fixed_T_36 	shift_reg_9  	= 0.0;
	static Custom_ap_fixed_T_40 	shift_reg_10 	= 0.0;
	static Custom_ap_fixed_T_44 	shift_reg_11 	= 0.0;
	static Custom_ap_fixed_T_48 	shift_reg_12 	= 0.0;
	static Custom_ap_fixed_T_52  	shift_reg_13 	= 0.0;
	static Custom_ap_fixed_T_56  	shift_reg_14 	= 0.0;
	static Custom_ap_fixed_T_60  	shift_reg_15 	= 0.0;
	static Custom_ap_fixed_T_64  	shift_reg_16 	= 0.0;
	static Custom_ap_fixed_T_68  	shift_reg_17 	= 0.0;
	static Custom_ap_fixed_T_72  	shift_reg_18 	= 0.0;
	static Custom_ap_fixed_T_76  	shift_reg_19 	= 0.0;
	static Custom_ap_fixed_T_80 	shift_reg_20 	= 0.0;
	static Custom_ap_fixed_T_84 	shift_reg_21 	= 0.0;
	static Custom_ap_fixed_T_88 	shift_reg_22 	= 0.0;
	static Custom_ap_fixed_T_92  	shift_reg_23 	= 0.0;
	static Custom_ap_fixed_T_96  	shift_reg_24 	= 0.0;
	static Custom_ap_fixed_T_100 	shift_reg_25 	= 0.0;
	static Custom_ap_fixed_T_104 	shift_reg_26 	= 0.0;
	static Custom_ap_fixed_T_108 	shift_reg_27 	= 0.0;
	static Custom_ap_fixed_T_112 	shift_reg_28 	= 0.0;
	static Custom_ap_fixed_T_116 	shift_reg_29 	= 0.0;

	Custom_ap_fixed_T_1  	taps_0  		= taps[0 ];
	Custom_ap_fixed_T_5  	taps_1  		= taps[1 ];
	Custom_ap_fixed_T_9  	taps_2  		= taps[2 ];
	Custom_ap_fixed_T_13 	taps_3  		= taps[3 ];
	Custom_ap_fixed_T_17 	taps_4  		= taps[4 ];
	Custom_ap_fixed_T_21 	taps_5  		= taps[5 ];
	Custom_ap_fixed_T_25 	taps_6  		= taps[6 ];
	Custom_ap_fixed_T_29 	taps_7  		= taps[7 ];
	Custom_ap_fixed_T_33 	taps_8  		= taps[8 ];
	Custom_ap_fixed_T_37 	taps_9  		= taps[9 ];
	Custom_ap_fixed_T_41 	taps_10 		= taps[10];
	Custom_ap_fixed_T_45 	taps_11 		= taps[11];
	Custom_ap_fixed_T_49 	taps_12 		= taps[12];
	Custom_ap_fixed_T_53  	taps_13 		= taps[13];
	Custom_ap_fixed_T_57  	taps_14 		= taps[14];
	Custom_ap_fixed_T_61  	taps_15 		= taps[15];
	Custom_ap_fixed_T_65  	taps_16 		= taps[16];
	Custom_ap_fixed_T_69  	taps_17 		= taps[17];
	Custom_ap_fixed_T_73  	taps_18 		= taps[18];
	Custom_ap_fixed_T_77  	taps_19 		= taps[19];
	Custom_ap_fixed_T_81 	taps_20 		= taps[20];
	Custom_ap_fixed_T_85 	taps_21 		= taps[21];
	Custom_ap_fixed_T_89 	taps_22 		= taps[22];
	Custom_ap_fixed_T_93  	taps_23 		= taps[23];
	Custom_ap_fixed_T_97  	taps_24 		= taps[24];
	Custom_ap_fixed_T_101 	taps_25 		= taps[25];
	Custom_ap_fixed_T_105 	taps_26 		= taps[26];
	Custom_ap_fixed_T_109 	taps_27 		= taps[27];
	Custom_ap_fixed_T_113 	taps_28 		= taps[28];
	Custom_ap_fixed_T_117 	taps_29 		= taps[29];

	Custom_ap_fixed_T_2  	acc_0  	= 0.0;
	Custom_ap_fixed_T_6  	acc_1  	= 0.0;
	Custom_ap_fixed_T_10  	acc_2  	= 0.0;
	Custom_ap_fixed_T_14  	acc_3  	= 0.0;
	Custom_ap_fixed_T_18  	acc_4  	= 0.0;
	Custom_ap_fixed_T_22  	acc_5  	= 0.0;
	Custom_ap_fixed_T_26  	acc_6  	= 0.0;
	Custom_ap_fixed_T_30  	acc_7  	= 0.0;
	Custom_ap_fixed_T_34  	acc_8  	= 0.0;
	Custom_ap_fixed_T_38  	acc_9  	= 0.0;
	Custom_ap_fixed_T_42 	acc_10 	= 0.0;
	Custom_ap_fixed_T_46 	acc_11 	= 0.0;
	Custom_ap_fixed_T_50  	acc_12 	= 0.0;
	Custom_ap_fixed_T_54  	acc_13 	= 0.0;
	Custom_ap_fixed_T_58  	acc_14 	= 0.0;
	Custom_ap_fixed_T_62  	acc_15 	= 0.0;
	Custom_ap_fixed_T_66  	acc_16 	= 0.0;
	Custom_ap_fixed_T_70  	acc_17 	= 0.0;
	Custom_ap_fixed_T_74  	acc_18 	= 0.0;
	Custom_ap_fixed_T_78  	acc_19 	= 0.0;
	Custom_ap_fixed_T_82 	acc_20 	= 0.0;
	Custom_ap_fixed_T_86 	acc_21 	= 0.0;
	Custom_ap_fixed_T_90  	acc_22 	= 0.0;
	Custom_ap_fixed_T_94  	acc_23 	= 0.0;
	Custom_ap_fixed_T_98  	acc_24 	= 0.0;
	Custom_ap_fixed_T_102 	acc_25 	= 0.0;
	Custom_ap_fixed_T_106 	acc_26 	= 0.0;
	Custom_ap_fixed_T_110 	acc_27 	= 0.0;
	Custom_ap_fixed_T_114 	acc_28 	= 0.0;
	Custom_ap_fixed_T_118 	acc_29 	= 0.0;

	Custom_ap_fixed_T_3  	mult_out_0  	= 0.0;
	Custom_ap_fixed_T_7  	mult_out_1  	= 0.0;
	Custom_ap_fixed_T_11  	mult_out_2  	= 0.0;
	Custom_ap_fixed_T_15  	mult_out_3  	= 0.0;
	Custom_ap_fixed_T_19  	mult_out_4  	= 0.0;
	Custom_ap_fixed_T_23  	mult_out_5  	= 0.0;
	Custom_ap_fixed_T_27  	mult_out_6  	= 0.0;
	Custom_ap_fixed_T_31  	mult_out_7  	= 0.0;
	Custom_ap_fixed_T_35  	mult_out_8  	= 0.0;
	Custom_ap_fixed_T_39  	mult_out_9  	= 0.0;
	Custom_ap_fixed_T_43 	mult_out_10 	= 0.0;
	Custom_ap_fixed_T_47 	mult_out_11 	= 0.0;
	Custom_ap_fixed_T_51  	mult_out_12 	= 0.0;
	Custom_ap_fixed_T_55  	mult_out_13 	= 0.0;
	Custom_ap_fixed_T_59  	mult_out_14 	= 0.0;
	Custom_ap_fixed_T_63  	mult_out_15 	= 0.0;
	Custom_ap_fixed_T_67  	mult_out_16 	= 0.0;
	Custom_ap_fixed_T_71  	mult_out_17 	= 0.0;
	Custom_ap_fixed_T_75  	mult_out_18 	= 0.0;
	Custom_ap_fixed_T_79  	mult_out_19 	= 0.0;
	Custom_ap_fixed_T_83 	mult_out_20 	= 0.0;
	Custom_ap_fixed_T_87 	mult_out_21 	= 0.0;
	Custom_ap_fixed_T_91  	mult_out_22 	= 0.0;
	Custom_ap_fixed_T_95  	mult_out_23 	= 0.0;
	Custom_ap_fixed_T_99  	mult_out_24 	= 0.0;
	Custom_ap_fixed_T_103 	mult_out_25 	= 0.0;
	Custom_ap_fixed_T_107 	mult_out_26 	= 0.0;
	Custom_ap_fixed_T_111 	mult_out_27 	= 0.0;
	Custom_ap_fixed_T_115 	mult_out_28 	= 0.0;
	Custom_ap_fixed_T_119 	mult_out_29 	= 0.0;
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
#pragma HLS BIND_OP variable=mult_out_10 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_11 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_12 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_13 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_14 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_15 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_16 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_17 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_18 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_19 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_20 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_21 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_22 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_23 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_24 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_25 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_26 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_27 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_28 op=mul impl=dsp
#pragma HLS BIND_OP variable=mult_out_29 op=mul impl=dsp
	if (Restart){
		shift_reg_0  	= 0.0;
		shift_reg_1  	= 0.0;
		shift_reg_2  	= 0.0;
		shift_reg_3  	= 0.0;
		shift_reg_4  	= 0.0;
		shift_reg_5  	= 0.0;
		shift_reg_6  	= 0.0;
		shift_reg_7  	= 0.0;
		shift_reg_8  	= 0.0;
		shift_reg_9  	= 0.0;
		shift_reg_10 	= 0.0;
		shift_reg_11 	= 0.0;
		shift_reg_12 	= 0.0;
		shift_reg_13 	= 0.0;
		shift_reg_14 	= 0.0;
		shift_reg_15 	= 0.0;
		shift_reg_16 	= 0.0;
		shift_reg_17 	= 0.0;
		shift_reg_18 	= 0.0;
		shift_reg_19 	= 0.0;
		shift_reg_20 	= 0.0;
		shift_reg_21 	= 0.0;
		shift_reg_22 	= 0.0;
		shift_reg_23 	= 0.0;
		shift_reg_24 	= 0.0;
		shift_reg_25 	= 0.0;
		shift_reg_26 	= 0.0;
		shift_reg_27 	= 0.0;
		shift_reg_28 	= 0.0;
		shift_reg_29 	= 0.0;
		*y = fp_data_t(0.0);
	} else {
////////////////	SR
		shift_reg_29 	= shift_reg_28;
		shift_reg_28 	= shift_reg_27;
		shift_reg_27 	= shift_reg_26;
		shift_reg_26 	= shift_reg_25;
		shift_reg_25 	= shift_reg_24;
		shift_reg_24 	= shift_reg_23;
		shift_reg_23 	= shift_reg_22;
		shift_reg_22 	= shift_reg_21;
		shift_reg_21 	= shift_reg_20;
		shift_reg_20 	= shift_reg_19;
		shift_reg_19 	= shift_reg_18;
		shift_reg_18 	= shift_reg_17;
		shift_reg_17 	= shift_reg_16;
		shift_reg_16 	= shift_reg_15;
		shift_reg_15 	= shift_reg_14;
		shift_reg_14 	= shift_reg_13;
		shift_reg_13	= shift_reg_12;
		shift_reg_12	= shift_reg_11;
		shift_reg_11	= shift_reg_10;
		shift_reg_10	= shift_reg_9;
		shift_reg_9 	= shift_reg_8;
		shift_reg_8 	= shift_reg_7;
		shift_reg_7 	= shift_reg_6;
		shift_reg_6 	= shift_reg_5;
		shift_reg_5 	= shift_reg_4;
		shift_reg_4 	= shift_reg_3;
		shift_reg_3 	= shift_reg_2;
		shift_reg_2 	= shift_reg_1;
		shift_reg_1 	= shift_reg_0;
		shift_reg_0 	= x;


		mult_out_0  		= shift_reg_0  	* taps_0 ;
		mult_out_1  		= shift_reg_1  	* taps_1 ;
		mult_out_2  		= shift_reg_2  	* taps_2 ;
		mult_out_3  		= shift_reg_3  	* taps_3 ;
		mult_out_4  		= shift_reg_4  	* taps_4 ;
		mult_out_5  		= shift_reg_5  	* taps_5 ;
		mult_out_6  		= shift_reg_6  	* taps_6 ;
		mult_out_7  		= shift_reg_7  	* taps_7 ;
		mult_out_8  		= shift_reg_8  	* taps_8 ;
		mult_out_9  		= shift_reg_9  	* taps_9 ;
		mult_out_10 		= shift_reg_10 	* taps_10;
		mult_out_11 		= shift_reg_11 	* taps_11;
		mult_out_12 		= shift_reg_12 	* taps_12;
		mult_out_13 		= shift_reg_13 	* taps_13;
		mult_out_14 		= shift_reg_14 	* taps_14;
		mult_out_15 		= shift_reg_15 	* taps_15;
		mult_out_16 		= shift_reg_16 	* taps_16;
		mult_out_17 		= shift_reg_17 	* taps_17;
		mult_out_18 		= shift_reg_18 	* taps_18;
		mult_out_19 		= shift_reg_19 	* taps_19;
		mult_out_20 		= shift_reg_20 	* taps_20;
		mult_out_21 		= shift_reg_21 	* taps_21;
		mult_out_22 		= shift_reg_22 	* taps_22;
		mult_out_23 		= shift_reg_23 	* taps_23;
		mult_out_24 		= shift_reg_24 	* taps_24;
		mult_out_25 		= shift_reg_25 	* taps_25;
		mult_out_26 		= shift_reg_26 	* taps_26;
		mult_out_27 		= shift_reg_27 	* taps_27;
		mult_out_28 		= shift_reg_28 	* taps_28;
		mult_out_29 		= shift_reg_29 	* taps_29;

		acc_0  	= mult_out_0; // 0 +
		acc_1  	= acc_0  	+ mult_out_1 ;
		acc_2  	= acc_1  	+ mult_out_2 ;
		acc_3  	= acc_2  	+ mult_out_3 ;
		acc_4  	= acc_3  	+ mult_out_4 ;
		acc_5  	= acc_4  	+ mult_out_5 ;
		acc_6  	= acc_5  	+ mult_out_6 ;
		acc_7  	= acc_6  	+ mult_out_7 ;
		acc_8  	= acc_7  	+ mult_out_8 ;
		acc_9  	= acc_8  	+ mult_out_9 ;
		acc_10 	= acc_9  	+ mult_out_10;
		acc_11 	= acc_10 	+ mult_out_11;
		acc_12 	= acc_11 	+ mult_out_12;
		acc_13 	= acc_12 	+ mult_out_13;
		acc_14 	= acc_13 	+ mult_out_14;
		acc_15 	= acc_14 	+ mult_out_15;
		acc_16 	= acc_15 	+ mult_out_16;
		acc_17 	= acc_16 	+ mult_out_17;
		acc_18 	= acc_17 	+ mult_out_18;
		acc_19 	= acc_18 	+ mult_out_19;
		acc_20 	= acc_19 	+ mult_out_20;
		acc_21 	= acc_20 	+ mult_out_21;
		acc_22 	= acc_21 	+ mult_out_22;
		acc_23 	= acc_22 	+ mult_out_23;
		acc_24 	= acc_23 	+ mult_out_24;
		acc_25 	= acc_24 	+ mult_out_25;
		acc_26 	= acc_25 	+ mult_out_26;
		acc_27 	= acc_26 	+ mult_out_27;
		acc_28 	= acc_27 	+ mult_out_28;
		acc_29 	= acc_28 	+ mult_out_29;

		*y=acc_29; //output of the last MAC
	}
}

