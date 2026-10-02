/*******************************************************************************
Dev. by: Keyvan Shahin
Project: Hardware-Based Fixed Point Simulation
In this project we tried to accelerate floating point to fixed point conversion
of an algorithm, by implementing a width configurable version of the application,
and the algorithm for finding the optimized widths for all the intermediate
variables inside the application on hardware.
Module name: IIRSim
it's the top module containing both the application design and the tailored FPSim
*******************************************************************************/
#include "LMSSim.h"
#include "DR.h"
#include "FracOpt.h"

void LMSSim(
//		bool SimRun, // Input, Commanding the start of FP Simulation
		width_t *FinalCIW, // The Final Calculated Integer Widths for all Intermediate Variables
		width_t *FinalCFW, // The Final Calculated Fractional Widths for all Intermediate Variables
		unsigned long long *cycles //counting the number of cycles in the most ran parts of the execution to find th execution time of the whole conversion process
		){
	// AXI Interface for FinalCIW and FinalCFW
	#pragma HLS INTERFACE m_axi port=FinalCIW offset=slave bundle=gmem depth=IVNum
	#pragma HLS INTERFACE m_axi port=FinalCFW offset=slave bundle=gmem depth=IVNum

	// Set FinalCIW and FinalCFW as pointers to memory
	#pragma HLS INTERFACE s_axilite port=FinalCIW bundle=control
	#pragma HLS INTERFACE s_axilite port=FinalCFW bundle=control

	// Control interface (for input/output)
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	// Dataflow for pipelining the design
//	#pragma HLS DATAFLOW

	// Partition the vectors FinalCIW and FinalCFW to allow parallel access
	#pragma HLS ARRAY_PARTITION variable=FinalCIW complete dim=1
	#pragma HLS ARRAY_PARTITION variable=FinalCFW complete dim=1

	// Unroll loops in the design for better parallelism (adjust according to your needs)
//	#pragma HLS UNROLL factor=2

	// Pipe the loops if there are dependencies that can be exploited for parallelism
//	#pragma HLS PIPELINE



	width_t sCIW[IVNum];
	width_t sCFW[IVNum];
	int_part_t sIV[IVNum];


	int sIVabs;
	bool RunDR = true; // DR is the first phase
	fp_data_t sIn_array[InArraySize];

	for (int i = 0; i <= InArraySize-1; i++){
		sIn_array[i] = In_array[i];
//#ifndef __SYNTHESIS__
//    printf("sIn_array[%d] = %f\n", i, (float)sIn_array[i]);
//#endif
	}

	// Running the Dynamic Range Simulation first
	DR(
		sCIW // The Final Calculated Integer Widths for all Intermediate Variables
	);
//#ifndef __SYNTHESIS__
//	printf("sCIWs after DR\n");
//	for (int i = 0; i <= IVNum-1; i++){
//		printf("sCIW[%d] = %d\n", i, sCIW[i]);
//	}
//#endif


	RunDR = false; // DR phase over

#ifndef __SYNTHESIS__
	printf ("Dynamic Range Calculation is Done! \n");
	printf ("===================================\n");

//	for (int i = 0; i < IVNum; i++){
//		printf ("sCIW[%d] = %d\n", i, (int)sCIW[i]);
//	}
#endif

	//Add fractional width part here
	FracOpt(
			sCIW, // The Final Calculated Integer Widths for all Intermediate Variables - input of this module
			sCFW // The Final Calculated Fractional Widths for all Intermediate Variables - output of this module
			// cycles
			);

	// final results
#ifndef __SYNTHESIS__
	printf("FinalCIW after FracOpt\n");
#endif

	for (int i=0; i<=IVNum-1; i++){
		FinalCIW[i] = sCIW[i];
//#ifndef __SYNTHESIS__
//			printf("FinalCIW[%d] in IIRSim after FracOpt = %d\n", i, FinalCIW[i]);
//#endif
//		printf("FinalCIW[%d] = %d\n", i, FinalCIW[i]);
		FinalCFW[i] = sCFW[i];
//#ifndef __SYNTHESIS__
//			printf("FinalCFW[%d] in IIRSim after FracOpt = %d\n", i, FinalCFW[i]);
//#endif
//		printf("FinalCFW[%d] = %d\n", i, FinalCFW[i]);
	}
}


