#include "unknown_sys.h"
#include "WCMultiplier.h"
#include "WCAdder.h"

void unknown_sys (
	bool Restart, // restart signal for setting the shift register
	fp_data_t *y, //output of FIR
	fp_data_t x, //signal input,
	fp_data_t *shift_reg
  ) {
#pragma HLS INLINE off
//#pragma HLS FUNCTION_INSTANTIATE variable=inst_name

	fp_data_t acc;
	fp_data_t accTemp;
	fp_data_t mult_out;

	if (Restart){
		for(int i=0; i<N; i++){
#pragma HLS UNROLL
			shift_reg[i] = fp_data_t(0.0);
//			IV[4*i] = int_part_t(0);
//			IV[4*i+1] = int_part_t(0);
//			IV[4*i+2] = int_part_t(0);
//			IV[4*i+3] = int_part_t(0);
		}
		*y = fp_data_t(0.0);
	} else {
////////////////
		SR_Loop:
		for (int i=N-1;i>=1;i--)
		{
#pragma HLS UNROLL
			shift_reg[i]=shift_reg[i-1];
		}
		shift_reg[0] = x;
////////////////

		acc = fp_data_t(0.0);

		MACs_Loop:
		for (int i=0;i<N;i++)
		{
#pragma HLS UNROLL
			WCMultiplier (
				true, // shows if this is the Golden instance with constant widths
//				TestGoldenInst, // shows if this is the Golden instance with constant widths
				shift_reg[i], //input 1
				h[i], //input 2 c
				GI, //input 1 integer Width
				GF, //input 1 fractional Width
				GI, //input 2 integer Width
				GF, //input 2 fractional Width
				&mult_out //multiplier output
			);

			WCAdder (
				true, // shows if this is the Golden instance with constant widths
//				TestGoldenInst, // shows if this is the Golden instance with constant widths
				acc, //input 1
				mult_out, //input 2
				GI, //input 1 integer Width
				GF, //input 1 fractional Width
				GI, //input 2 integer Width
				GF, //input 2 fractional Width
				&accTemp //Adder output
	  		);
			//Commented the following if only for test purposes
//			if (GoldenInst){ // IV only used for Golden Instance
//				IV[4*i] = int_part_t(shift_reg[i]); //Mult in 1 integer part
//				IV[4*i+1] = int_part_t(h[i]); //Mult in 2 integer part
//				IV[4*i+2] = int_part_t(acc); //Add in 1 integer part
//				IV[4*i+3] = int_part_t(mult_out); //Add in 2 integer part
//			} else {
//				IV[4*i] = int_part_t(0); //Not important for DUT
//				IV[4*i+1] = int_part_t(0); //Not important for DUT
//				IV[4*i+2] = int_part_t(0); //Not important for DUT
//				IV[4*i+3] = int_part_t(0); //Not important for DUT
//			}

			//Important: since we are saving the input nodes for the DR simulation, it is essential to not use the same variable for the input and the output of the modules
			//for example we should not use "acc" as the input and the output of the accumulator as we normally would. instead save the output as "accTemp", pass "acc" to "IV" then update "acc" with "accTemp"
			acc = accTemp;

		}

		*y=acc; //output of the last MAC
	}
}
