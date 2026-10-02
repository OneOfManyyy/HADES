/*******************************************************************************
Dev. by: Keyvan Shahin
Project: Hardware-Based Fixed Point Simulation
In this project we tried to accelerate floating point to fixed point conversion
of an algorithm, by implementing a width configurable version of the application,
and the algorithm for finding the optimized widths for all the intermediate
variables inside the application on hardware.
Module name: DR
this module performs the Dynamic Range calculation of the simulation
*******************************************************************************/
#include "DR.h"
// #include "hls_math.h"

void DR(
		width_t *FinalCIW // The Final Calculated Integer Widths for all Intermediate Variables - output of this module
		){

//#ifndef __SYNTHESIS__
//    printf("Just testing the Synth excluded printf\n");
//#endif



	width_t sCIW[IVNum];
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=sCIW
	width_t sCFW[IVNum];
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=sCFW
	int_part_t sIV[IVNum];
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=sIV

	width_t sIW1;
	width_t sIW2;

	fp_data_t sy1;
	fp_data_t sy2;

	fp_data_t sx;

	int_part_t sMax[IVNum];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=sMax
	int_part_t sMin[IVNum];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=sMin

	for (int i = 0; i < IVNum; i++){
#pragma HLS PIPELINE
		sMax[i] = -(1 << (GI - 1)); //setting the sMax to the lowest number and the sMin to the highest number so that they can be initialized by the first element of the IV array
		sMin[i] = (1 << (GI - 1)) - 1;
		sCIW[i] = GI; // this is only for a test. its not important later
		sCFW[i] = GF;
	}

	fp_data_t sIn_array[InArraySize];

	for (int i = 0; i <= InArraySize-1; i++){
//#pragma HLS PIPELINE
		sIn_array[i] = In_array[i];
	}

	if (InMode == 0){ // the entire input samples are stored in an array
		// restarting TIW in the start of simulation
		TIW(	TIW_Instance_Name, // Instance name
				true, // Rst to designs
				sCIW, // Configurable Integer Widths // routed to both design instances but the Golden instance does not look at it
				sCFW, // Configurable Fractional Widths // routed to both design instances but the Golden instance does not look at it
				sIV, // Intermediate Variable integer values // routed to IV output of the Golden Instance
				&sy1, // Golden output
				&sy2, // DUT output
				sx // input // routed the same to both instances
				);
		for (int i=0; i<InArraySize;i++){
#pragma HLS PIPELINE II=1
			sx = sIn_array[i];
			// using Golden instant with valid IV outputs for DR phase
			// During the DR phase we are only interested in IV values from the Golden Instance inside TIW
			// This means it is not important what are CIW and CFW in this call, and y2 is not used
			TIW(	TIW_Instance_Name, // Instance name
					false, // Rst to designs
					sCIW, // Configurable Integer Widths // routed to both design instances but the Golden instance does not look at it
					sCFW, // Configurable Fractional Widths // routed to both design instances but the Golden instance does not look at it
					sIV, // Intermediate Variable integer values // routed to IV output of the Golden Instance
					&sy1, // Golden output
					&sy2, // DUT output
					sx // input // routed the same to both instances
					);
//			printf("sx is %f\n", float(sx));

			for (int j=0; j<IVNum;j++){
//#pragma HLS UNROLL
				if (sMax[j]<sIV[j]){sMax[j]=sIV[j];} //saving the maximum values
				if (sMin[j]>sIV[j]){sMin[j]=sIV[j];} //saving the minimum values
				// printf("sIV[%d] is %d\n", j, int(sIV[j]));
				// printf("sMax[%d] is %d\n", j, int(sMax[j]));
				// printf("sMin[%d] is %d\n", j, int(sMin[j]));
				// printf("-------------\n");
			}
		}

		for (int j=0; j<=IVNum-1;j++){
			int_part_t sMaxVal = sMax[j];
			int_part_t sMinVal = sMin[j];

			//Calculate bits for sMax
			if (sMaxVal > 0) {
				// sIW1 = (width_t)GI - count_leading_zeros(sMaxVal) + 1;
				sIW1 = log2(sMaxVal) + 2;
				// printf("log2 = %f for sMaxVal = %d\n", log2(sMaxVal), sMaxVal);
			} else if (sMaxVal < 0) {
				// sIW1 = (width_t)GI - count_leading_zeros(-sMaxVal) + 1;
				sIW1 = log2(-sMaxVal) + 2;
			} else {
				sIW1 = 1; //special case
			}

			//Calculate bits for sMin
			if (sMinVal > 0) {
				// sIW2 = (width_t)GI - count_leading_zeros(sMinVal) + 1;
				sIW2 = log2(sMinVal) + 2;
			} else if (sMinVal < 0) {
				// sIW2 = (width_t)GI - count_leading_zeros(-sMinVal) + 1;
				sIW2 = log2(-sMinVal) + 2;
			} else {
				sIW2 = 1; //special case
			}

			// Choose the maximum width between sMax and sMin
			if (sIW1 > sIW2) {
				FinalCIW[j] = sIW1;
			} else {
				FinalCIW[j] = sIW2;
			}
#ifndef __SYNTHESIS__
			printf("FinalCIW[%d] = %d\n", j, FinalCIW[j]);
#endif

//			printf ("For sMax[%d] = %d, sMin[%d] = %d, the FinalCIW[%d] is %d\n", j, (int)sMax[j], j, (int)sMin[j], j, (int)FinalCIW[j]);
		}
	}
}

width_t count_leading_zeros(int_part_t x){
	width_t count = 0;
    // Shift left and count zeros until we reach the first 1
    for (width_t i = GI-1; i >= 0; i--) {
        // if (x[i] == 0) { // on hls we could access the bits of ap_int but here we need to use masks to have control over individual bits
		if((x & (1 << i)) != 0){
            count++;
        } else {
            break;
        }
    }
    return count;
}

