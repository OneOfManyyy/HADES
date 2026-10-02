#include "fir.h"
#include "WCMultiplier.h"
#include "WCAdder.h"

void fir (
	const char* inst_name, // Instance name, different Instances are instantiated based on this input, needed for referencing to this instance
	bool GoldenInst, // shows if this is the Golden instance with constant widths
	bool Restart, // restart signal for setting the shift register
	width_t *CIW, //intermediate integer Widths
	width_t *CFW, //intermediate fractional Widths
	int_part_t *IV, //intermediate variable integer values
	fp_data_t *y, //output of FIR
	fp_data_t x, //signal input,
	fp_data_t *shift_reg
  ) {
#pragma HLS INLINE off
#pragma HLS FUNCTION_INSTANTIATE variable=inst_name

	// clash of software and hardware implementation!!!
	// even though the FUNCTION_INSTANTIATE pragma should force two distinct instances, the "static" nature of shift_register is
	// making it to be shared between different instances anyway (kind of stupid but what to do?)
	// so for "static" variables/arrays, we need to make distinct variables/arrays for each instance manually
	// here we need two distinct instances for example

	// in summary, static variables and FUNCTION_INSTANTIATE do not interact as I would have wished, what we do is to push the static variables
	// out of the design function to the two-instance wrapper, duplicate them (for 2 instances), and give them as input/output to the design function:

//////////// moving following static variables to wrapper
	//	static fp_data_t shift_reg[N];
///////////

	fp_data_t acc;
	fp_data_t accTemp;
	fp_data_t mult_out;

//	printf("start address of sr in %s is  %d \n",inst_name, &shift_reg[0]);
////////////////
	if (Restart){
		for(int i=0; i<N; i++){
#pragma HLS UNROLL
			shift_reg[i] = fp_data_t(0.0);
			IV[4*i] = int_part_t(0);
			IV[4*i+1] = int_part_t(0);
			IV[4*i+2] = int_part_t(0);
			IV[4*i+3] = int_part_t(0);
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
				GoldenInst, // shows if this is the Golden instance with constant widths
//				TestGoldenInst, // shows if this is the Golden instance with constant widths
				shift_reg[i], //input 1
				taps[i], //input 2 c
				CIW[4*i], //input 1 integer Width
				CFW[4*i], //input 1 fractional Width
				CIW[4*i+1], //input 2 integer Width
				CFW[4*i+1], //input 2 fractional Width
				&mult_out //multiplier output
			);

			WCAdder (
				GoldenInst, // shows if this is the Golden instance with constant widths
//				TestGoldenInst, // shows if this is the Golden instance with constant widths
				acc, //input 1
				mult_out, //input 2
				CIW[4*i+2], //input 1 integer Width
				CFW[4*i+2], //input 1 fractional Width
				CIW[4*i+3], //input 2 integer Width
				CFW[4*i+3], //input 2 fractional Width
				&accTemp //Adder output
	  		);
			//Commented the following if only for test purposes
			if (GoldenInst){ // IV only used for Golden Instance
				IV[4*i] = int_part_t(shift_reg[i]); //Mult in 1 integer part
				IV[4*i+1] = int_part_t(taps[i]); //Mult in 2 integer part
				IV[4*i+2] = int_part_t(acc); //Add in 1 integer part
				IV[4*i+3] = int_part_t(mult_out); //Add in 2 integer part
			} else {
				IV[4*i] = int_part_t(0); //Not important for DUT
				IV[4*i+1] = int_part_t(0); //Not important for DUT
				IV[4*i+2] = int_part_t(0); //Not important for DUT
				IV[4*i+3] = int_part_t(0); //Not important for DUT
			}

			//Important: since we are saving the input nodes for the DR simulation, it is essential to not use the same variable for the input and the output of the modules
			//for example we should not use "acc" as the input and the output of the accumulator as we normally would. instead save the output as "accTemp", pass "acc" to "IV" then update "acc" with "accTemp"
			acc = accTemp;

		}

		*y=acc; //output of the last MAC
	}
}

