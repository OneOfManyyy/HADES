#include "iir.h"
#include "WCMultiplier.h"
#include "WCAdder.h"

void iir (
	const char* inst_name, // Instance name, different Instances are instantiated based on this input, needed for referencing to this instance
	bool GoldenInst, // shows if this is the Golden instance with constant widths
	bool Restart, // restart signal for setting the shift register
	width_t *CIW, //intermediate integer Widths
	width_t *CFW, //intermediate fractional Widths
	int_part_t *IV, //intermediate variable integer values
	fp_data_t *y, //output of IIR
	fp_data_t x, //signal input
	fp_data_t *shift_reg_x,
	fp_data_t *shift_reg_y
  ) {
#pragma HLS INLINE off
#pragma HLS FUNCTION_INSTANTIATE variable=inst_name

// #pragma HLS PIPELINE II=1

//    static data_t x_reg[N] = {0};
//    static data_t y_reg[N] = {0};

//#pragma HLS ARRAY_PARTITION variable=x_reg complete
//#pragma HLS ARRAY_PARTITION variable=y_reg complete

//	fp_data_t acc;
//	fp_data_t accTemp1, accTemp2;
	fp_data_t acc_l_ff, acc_n_ff;
	fp_data_t acc_l_fb, acc_n_fb;
	fp_data_t mult_b, mult_a;
	fp_data_t result;

    // Shift input history
    if (Restart){
    	for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        	shift_reg_x[i] = fp_data_t(0.0);
        	shift_reg_y[i] = fp_data_t(0.0);
    		IV[8*i] = int_part_t(0);
    		IV[8*i+1] = int_part_t(0);
    		IV[8*i+2] = int_part_t(0);
    		IV[8*i+3] = int_part_t(0);
    		IV[8*i+4] = int_part_t(0);
    		IV[8*i+5] = int_part_t(0);
    		IV[8*i+6] = int_part_t(0);
    		IV[8*i+7] = int_part_t(0);
    	}
    	*y = fp_data_t(0.0);
    }else {
///////////
    	SR_Loop_XY:
    	for (int i = N-1; i >= 1; i--)
    	{
#pragma HLS UNROLL
    		shift_reg_x[i] = shift_reg_x[i-1];
            shift_reg_y[i] = shift_reg_y[i-1];
    	}
    	shift_reg_x[0] = x;
//    	shift_reg_y[0] = result;
///////////

    	// Accumulator
    acc_l_ff = fp_data_t(0.0);
    acc_l_fb = fp_data_t(0.0);
//    acc_n_ff = fp_data_t(0.0);
//    acc_n_fb = fp_data_t(0.0);
//    result = fp_data_t(0.0);
    // Feedforward part
    	for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
    		WCMultiplier (
    				GoldenInst, // shows if this is the Golden instance with constant widths
//			TestGoldenInst, // shows if this is the Golden instance with constant widths
					shift_reg_x[i], //input 1
					b[i], //input 2 c
					CIW[8*i], //input 1 integer Width
					CFW[8*i], //input 1 fractional Width
					CIW[8*i+1], //input 2 integer Width
					CFW[8*i+1], //input 2 fractional Width
					&mult_b //multiplier output
    		);

    		WCAdder (
    				GoldenInst, // shows if this is the Golden instance with constant widths
//			TestGoldenInst, // shows if this is the Golden instance with constant widths
					acc_l_ff, //input 1
					mult_b, //input 2
					CIW[8*i+2], //input 1 integer Width
					CFW[8*i+2], //input 1 fractional Width
					CIW[8*i+3], //input 2 integer Width
					CFW[8*i+3], //input 2 fractional Width
					&acc_n_ff //Adder output
    		);

    		//Commented the following if only for test purposes
    		if (GoldenInst){ // IV only used for Golden Instance
    			IV[8*i]   = int_part_t(shift_reg_x[i]); //Mult in 1 integer part
    			IV[8*i+1] = int_part_t(b[i]); //Mult in 2 integer part
    			IV[8*i+2] = int_part_t(acc_l_ff); //Add in 1 integer part
    			IV[8*i+3] = int_part_t(mult_b); //Add in 2 integer part
    		} else {
    			IV[8*i]   = int_part_t(0); //Not important for DUT
    			IV[8*i+1] = int_part_t(0); //Not important for DUT
    			IV[8*i+2] = int_part_t(0); //Not important for DUT
    			IV[8*i+3] = int_part_t(0); //Not important for DUT
    		}

    		acc_l_ff = acc_n_ff;
    	}


    	// Feedback part
    	for (int i = 1; i < N; i++) {
#pragma HLS UNROLL
    		WCMultiplier (
    				GoldenInst, // shows if this is the Golden instance with constant widths
//			TestGoldenInst, // shows if this is the Golden instance with constant widths
					shift_reg_y[i], //input 1
					-a[i], //input 2 c
					CIW[8*i+4], //input 1 integer Width
					CFW[8*i+4], //input 1 fractional Width
					CIW[8*i+5], //input 2 integer Width
					CFW[8*i+5], //input 2 fractional Width
					&mult_a //multiplier output
    		);

    		WCAdder (
    				GoldenInst, // shows if this is the Golden instance with constant widths
//			TestGoldenInst, // shows if this is the Golden instance with constant widths
					acc_l_fb, //input 1
					mult_a, //input 2
					CIW[8*i+6], //input 1 integer Width
					CFW[8*i+6], //input 1 fractional Width
					CIW[8*i+7], //input 2 integer Width
					CFW[8*i+7], //input 2 fractional Width
					&acc_n_fb //Adder output
    		);

    		//Commented the following if only for test purposes
    		if (GoldenInst){ // IV only used for Golden Instance
    			IV[8*i+4] = int_part_t(shift_reg_y[i]); //Mult in 1 integer part
    			IV[8*i+5] = int_part_t(-a[i]); //Mult in 2 integer part
    			IV[8*i+6] = int_part_t(acc_l_fb); //Add in 1 integer part
    			IV[8*i+7] = int_part_t(mult_a); //Add in 2 integer part
    		} else {
    			IV[8*i+4] = int_part_t(0); //Not important for DUT
    			IV[8*i+5] = int_part_t(0); //Not important for DUT
    			IV[8*i+6] = int_part_t(0); //Not important for DUT
    			IV[8*i+7] = int_part_t(0); //Not important for DUT
    		}

    		acc_l_fb = acc_n_fb;
    	}
//        result = acc_l_ff + acc_l_fb;
        shift_reg_y[0] = acc_l_ff + acc_l_fb;
        *y = acc_l_ff + acc_l_fb;
    }
}
