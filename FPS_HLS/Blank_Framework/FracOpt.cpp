/*******************************************************************************
Dev. by: Keyvan Shahin
Project: Hardware-Based Fixed Point Simulation
In this project we tried to accelerate floating point to fixed point conversion
of an algorithm, by implementing a width configurable version of the application,
and the algorithm for finding the optimized widths for all the intermediate
variables inside the application on hardware.
Module name: FracOpt
this module performs the Fractional part optimization of the simulation
*******************************************************************************/
#include "FracOpt.h"
#include <hls_math.h>

void FracOpt(
//		bool SimRun, // Input, Commanding the start of FP Simulation
//		fp_data_t *sIn_array, // Array containing the inputs to the design
		width_t *FinalCIW, // The Final Calculated Integer Widths for all Intermediate Variables - input of this module
		width_t *FinalCFW, // The Final Calculated Fractional Widths for all Intermediate Variables - output of this module
		unsigned long long *cycles //counting the number of cycles in the most ran parts of the execution to find th execution time of the whole conversion process
		){

	*cycles = 0;


	width_t sCIW[IVNum];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=sCIW
	width_t sCFW[IVNum];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=sCFW
	int_part_t sIV[IVNum];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=sIV

	width_t sIW1[IVNum];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=sIW1
	width_t sIW2[IVNum];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=sIW2

	fp_data_t sy1;
	fp_data_t sy2;

	fp_data_t sGoldenOutput[InArraySize];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=sGoldenOutput
	fp_data_t sDUTOutput[InArraySize];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=sDUTOutput

	fp_data_t sx;

	// 	CoarseFractionLength = 0;
	width_t L = 0;
	width_t H = GF;
	width_t M = 0;

	width_t FractionalCoarseWidthFinal = 0; //final global fractional width after the coarse optimization
	width_t FractionalWidths[IVNum];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=FractionalWidths
//	width_t FractionalWidthsFinal[IVNum];
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=FractionalWidthsFinal

	BigFloatT CalculatedErrorL, CalculatedErrorM, CalculatedErrorH, CalculatedError_fine;
	BigFloatT Err_i[IVNum];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=Err_i

	bool DoHCalc = true;
	bool DoLCalc = true;
	bool CoarseDone = false;
	bool FineStage1Done = false;
	bool FineStage2Done = false;

	fp_data_t sIn_array[InArraySize];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=sIn_array

	for (int i = 0; i <= InArraySize-1; i++){
		sIn_array[i] = In_array[i];
	}

	for (int i=0; i<IVNum; i++){
		sCIW[i] = FinalCIW[i]; // I could have just used the FinalCIW for the input to the TIW module but I prefer to have an internal variable alias for the FinalCIW (sCIW)
	}

	if (InMode == 0){ // the entire input samples are stored in an array
////////////////////////////
		//	Coarse Optimization
		//	initialize L and H and FractionLength
////////////////////////////
		#ifndef __SYNTHESIS__
			printf("========================================\n");
			printf("Start of Coarse Fractional Optimization!\n");
			printf("========================================\n");
		#endif

		while (!CoarseDone){
//#pragma HLS PIPELINE II=1
			M = (H+L)>>1; // M would be the average of lower and higher bound of fractional length span (integer average ofc since it represents a number of bits)

			#ifndef __SYNTHESIS__
				printf ("H,L,M are %d %d %d\n", H, L, M);
				printf("---------------------\n");
			#endif

			// During the Coarse optimization phase, we are looking for a global minimum fractional width which can be set for all the variables and satisfies the error threshold requirements

			// Computing Error for the fractional width of all the variables set to L
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
			(*cycles) += 1;
			if (DoLCalc){
				for (int j=0; j<=IVNum-1;j++){
#pragma HLS UNROLL
					sCFW[j] = L;	// setting all the fractional widths to L
				}
#ifndef __SYNTHESIS__
				printf("Calculating RMSE for L = %d \n", L);
#endif
				for (int i=0; i<InArraySize;i++){ // running all the inputs in the input vector
#pragma HLS PIPELINE II=IIValue
					sx = sIn_array[i];
					TIW(	TIW_Instance_Name, // Instance name
							false, // Rst to designs
							sCIW, // Configurable Integer Widths // routed to both design instances but the Golden instance does not look at it
							sCFW, // Configurable Fractional Widths // routed to both design instances but the Golden instance does not look at it
							sIV, // Intermediate Variable integer values // routed to IV output of the Golden Instance
							&sy1, // Golden output
							&sy2, // DUT output
							sx // input // routed the same to both instances
						);
				sGoldenOutput[i] = sy1;
				sDUTOutput[i] = sy2;
				}
				(*cycles) += (unsigned long long)InArraySize * IIValue;
				CalculatedErrorL = CalcError (sGoldenOutput,sDUTOutput); //Error calculated for L global fractional width
			}
			// Computing Error for the fractional width of all the variables set to H
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
			if (DoHCalc){
				for (int j=0; j<=IVNum-1;j++){
#pragma HLS UNROLL
					sCFW[j] = H;	// setting all the fractional widths to H
				}
#ifndef __SYNTHESIS__
				printf("Calculating RMSE for H = %d \n", H);
#endif
				for (int i=0; i<InArraySize;i++){ // running all the inputs in the input vector
#pragma HLS PIPELINE II=IIValue
					sx = sIn_array[i];
					TIW(	TIW_Instance_Name, // Instance name
							false, // Rst to designs
							sCIW, // Configurable Integer Widths // routed to both design instances but the Golden instance does not look at it
							sCFW, // Configurable Fractional Widths // routed to both design instances but the Golden instance does not look at it
							sIV, // Intermediate Variable integer values // routed to IV output of the Golden Instance
							&sy1, // Golden output
							&sy2, // DUT output
							sx // input // routed the same to both instances
							);
					sGoldenOutput[i] = sy1;
					sDUTOutput[i] = sy2;
				}
				(*cycles) += (unsigned long long)InArraySize * IIValue;
				CalculatedErrorH = CalcError (sGoldenOutput,sDUTOutput); //Error Calculated for H global fractional width
			}
			// Computing Error for the fractional width of all the variables set to M
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
			(*cycles) += 1;
			for (int j=0; j<=IVNum-1;j++){
#pragma HLS UNROLL
				sCFW[j] = M;	// setting all the fractional widths to M
			}
#ifndef __SYNTHESIS__
			printf("Calculating RMSE for M = %d \n", M);
#endif
			for (int i=0; i<InArraySize;i++){ // running all the inputs in the input vector
#pragma HLS PIPELINE II=IIValue
				sx = sIn_array[i];
				TIW(	TIW_Instance_Name, // Instance name
						false, // Rst to designs
						sCIW, // Configurable Integer Widths // routed to both design instances but the Golden instance does not look at it
						sCFW, // Configurable Fractional Widths // routed to both design instances but the Golden instance does not look at it
						sIV, // Intermediate Variable integer values // routed to IV output of the Golden Instance
						&sy1, // Golden output
						&sy2, // DUT output
						sx // input // routed the same to both instances
						);
				sGoldenOutput[i] = sy1;
				sDUTOutput[i] = sy2;
			}
			(*cycles) += (unsigned long long)InArraySize * IIValue;
			CalculatedErrorM = CalcError (sGoldenOutput,sDUTOutput); //Error Calculated for H global fractional width

#ifndef __SYNTHESIS__
		    printf("E_H for H = %d: %f\n", H, (float)CalculatedErrorH);
		    printf("E_L for L = %d: %f\n", L, (float)CalculatedErrorL);
		    printf("E_M for M = %d: %f\n", M, (float)CalculatedErrorM);
#endif

	        if (M==L || M==H){
				if (CalculatedErrorL < ErrorThreshold){ // just for test. change back to ErrorThreshold later
					M = L;
					CalculatedErrorM = CalculatedErrorL;
					CoarseDone = true;
				} else {
					M = H;
					CalculatedErrorM = CalculatedErrorH;
					CoarseDone = true;
				}
	        } else {
				if (CalculatedErrorM < ErrorThreshold) {
					H = M;
					CalculatedErrorH = CalculatedErrorM;
					DoHCalc = false; // since the next H is the current M, the calculation of error for the next H is not required
					DoLCalc = true;
				} else {
					L = M;
					CalculatedErrorL = CalculatedErrorM;
					DoHCalc = true;
					DoLCalc = false; // since the next L is the current M, the calculation of error for the next L is not required
				}
	        }


	        FractionalCoarseWidthFinal = M;
#ifndef __SYNTHESIS__
	        printf ("Final Coarse Fractional Width is %d and the error for that is %f\n", FractionalCoarseWidthFinal, (float)CalculatedErrorM);
	        printf("Coarse Optimization Is Done: %s\n", CoarseDone ? "true" : "false");
#endif
		}

		if (FractionalCoarseWidthFinal == 0){
#ifndef __SYNTHESIS__
	    	printf ("Fine Optimization not required ...\n");
#endif
	    	FineStage1Done = true;
	    	FineStage2Done = true;
		} else {
#ifndef __SYNTHESIS__
	    	printf ("Starting Fine Optimization stage 1 ...\n");
#endif
		}


/////////////////////////
//    	Fine Optimization
//    	initialization
/////////////////////////


    	CalculatedError_fine = CalculatedErrorM;
    	for (int i=0; i<=IVNum-1; i++){
#pragma HLS UNROLL
    		FractionalWidths[i] = FractionalCoarseWidthFinal; // initializing all the widths with the globally calculated Fractional Width from Coarse simulation
    	}


/////////////////////////
//    	Stage 1
/////////////////////////
//    	int TestStage1;
    	while (!FineStage1Done){
//#pragma HLS PIPELINE II=1
//    		TestStage1++;
//    		if (TestStage1 == 3){
//    			FineStage1Done = true;
//    		}
    		// checking if all the fractional widths are zero, then the stage is over (as well as the next stage)
    		FineStage1Done = true;
    		FineStage2Done = true;
	    	for (int i=0; i<=IVNum-1; i++){
	    		if (FractionalWidths[i] != 0) {
	    			FineStage1Done = false;
	        		FineStage2Done = false;
	    		}
	    	}
	    	for (int i=0; i<=IVNum-1; i++){
				Err_i[i] = 0; //initialize E_i
	    	}


//		calculate E_i
//	    	printf ("Calculating Err_i\n");
	    	for (int i=0; i<=IVNum-1; i++){
//		    	printf ("FractionalWidths[%d] = %d\n", i, FractionalWidths[i]);
				if (FractionalWidths[i] != 0) {
//			    	printf ("Calculating Err_i[%d] for FractionalWidths = %d\n", i, FractionalWidths[i]);
			    	for (int j=0; j<=IVNum-1; j++){
#pragma HLS UNROLL
			    		if (j==i){
			    			sCFW[j] = FractionalWidths[j] - 1;
//							MovingOne [j] = 1;
			    		} else {
			    			sCFW[j] = FractionalWidths[j];
//							MovingOne[j] = 0;
			    		}
			    	}
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
					(*cycles) += 1;
					for (int k=0; k<InArraySize;k++){ // running all the inputs in the input vector
#pragma HLS PIPELINE II=IIValue
						sx = sIn_array[k];
						TIW(	TIW_Instance_Name, // Instance name
								false, // Rst to designs
								sCIW, // Configurable Integer Widths // routed to both design instances but the Golden instance does not look at it
								sCFW, // Configurable Fractional Widths // routed to both design instances but the Golden instance does not look at it
								sIV, // Intermediate Variable integer values // routed to IV output of the Golden Instance
								&sy1, // Golden output
								&sy2, // DUT output
								sx // input // routed the same to both instances
								);
						sGoldenOutput[k] = sy1;
						sDUTOutput[k] = sy2;
					}
					(*cycles) += (unsigned long long)InArraySize * IIValue;
					Err_i[i] = CalcError (sGoldenOutput,sDUTOutput); //Error Calculated for H global fractional width
				} else {
					Err_i[i] = (BigFloatT)2.0*ErrorThreshold; // do not consider if FW[i] is already 0 and cannot be subtracted by 1
				}
	    	}
//			calculate DE_i
	    	BigFloatT min_Error = (BigFloatT)2.0*ErrorThreshold; // just an initialization to make sure if non of the Err_i elements can satisfy the criteria, the first stage is over
	    	int min_Error_index = 0;
	    	for (int i=0; i<=IVNum-1; i++){
//#ifndef __SYNTHESIS__
//    			printf("Err_i[%d] = %f, min_Err = %f\n", i, (float)Err_i[i], (float)min_Error);
//#endif
	    		if (Err_i[i] < min_Error){
	    			min_Error = Err_i[i];
	    			min_Error_index = i;
	    		}
	    	}
//#ifndef __SYNTHESIS__
//    		printf ("er = %f\n", (float)min_Error);
//#endif
	    	if (min_Error < ErrorThreshold) {
#ifndef __SYNTHESIS__
	    		printf ("reducing the width for element %d from %d to %d\n", min_Error_index, FractionalWidths[min_Error_index], FractionalWidths[min_Error_index]-1);
#endif
	    		FractionalWidths[min_Error_index] = FractionalWidths[min_Error_index] - 1;
	    	} else {
	    		FineStage1Done = true; // if even reducing one bit from the least sensitive IV still introduces unacceptable error, then the first stage is over
	    	}
		}


    	///////////////////////////////////////////////////////

#ifndef __SYNTHESIS__
    	printf ("Starting Stage2 of FinOpt\n");
#endif

//    	%%% Stage 2
    	while (!FineStage2Done){
//#pragma HLS PIPELINE II=1
    		// checking if all the fractional widths are zero, then the stage is over
    		FineStage2Done = true;
	    	for (int i=0; i<=IVNum-1; i++){
#pragma HLS UNROLL
	    		if (FractionalWidths[i] != 0) {
	        		FineStage2Done = false;
	    		}
	    	}

    		//init e_i
    		for (int i=0; i<=IVNum-1; i++){
#pragma HLS UNROLL
				Err_i[i] = 0; //initialize E_i
	    	}

//		calculate E_i
    		//	    	printf ("Calculating Err_i\n");
    		for (int i=0; i<=IVNum-1; i++){
    		//		    	printf ("FractionalWidths[%d] = %d\n", i, FractionalWidths[i]);
    		//			    	printf ("Calculating Err_i[%d] for FractionalWidths = %d\n", i, FractionalWidths[i]);
   		    	for (int j=0; j<=IVNum-1; j++){
   		    		if (j==i){
   		    			sCFW[j] = FractionalWidths[j] + 1; // Err_i is the error when the i-th fractional width is increased by one
   		    		} else {
   		    			sCFW[j] = FractionalWidths[j];
   		    		}
   		    	}
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
  				(*cycles) += 1;
   				for (int k=0; k<InArraySize;k++){ // running all the inputs in the input vector
#pragma HLS PIPELINE II=IIValue
   					sx = sIn_array[k];
   					TIW(	TIW_Instance_Name, // Instance name
   							false, // Rst to designs
   							sCIW, // Configurable Integer Widths // routed to both design instances but the Golden instance does not look at it
   							sCFW, // Configurable Fractional Widths // routed to both design instances but the Golden instance does not look at it
   							sIV, // Intermediate Variable integer values // routed to IV output of the Golden Instance
   							&sy1, // Golden output
   							&sy2, // DUT output
   							sx // input // routed the same to both instances
   							);
   					sGoldenOutput[k] = sy1;
   					sDUTOutput[k] = sy2;
				}
   				(*cycles) += (unsigned long long)InArraySize * IIValue;
				Err_i[i] = CalcError (sGoldenOutput,sDUTOutput); //Error Calculated for H global fractional width
		    }

//			calculate the least and most sensitive variables to width increase
    		BigFloatT min_Error = (BigFloatT)2.0*ErrorThreshold; // just an initialization to make sure if non of the Err_i elements can satisfy the criteria, the first stage is over
    		int min_Error_index = 0;
    		for (int i=0; i<=IVNum-1; i++){
#pragma HLS UNROLL
    			if (FractionalWidths[i]>=2) { // we want to reduce two from the width of the least sensitive bit, so it needs to have a width 2 at least
//    				printf("Err_i[%d] = %f, min_Err = %f\n", i, Err_i[i], min_Error);
    				if (Err_i[i] < min_Error){
    					min_Error = Err_i[i];
    					min_Error_index = i;
    				}
    			}
    		} // min error = lowest sensitivity
    		BigFloatT max_Error = 0; // just an initialization to make sure if non of the Err_i elements can satisfy the criteria, the first stage is over
    		int max_Error_index = 0;
    		for (int i=0; i<=IVNum-1; i++){
#pragma HLS UNROLL
    			if (FractionalWidths[i]<=GF-1) { // we need to add 1 bit to the width of the most sensitive IV, so it needs to have at most a width of GF-1
//    				printf("Err_i[%d] = %f, max_Err = %f\n", i, Err_i[i], max_Error);
    				if (Err_i[i] > max_Error){
    					max_Error = Err_i[i];
    					max_Error_index = i;
    				}
    			}
    		} // max error = highest sensitivity

// second part of stage 2
    		for (int i=0; i<=IVNum-1; i++){
#pragma HLS UNROLL
    			if (i == min_Error_index) {
    				sCFW[i] = FractionalWidths[i] - 2;
    			}
    			if (i == max_Error_index) {
    				sCFW[i] = FractionalWidths[i] + 1;
    			}
    		}

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
  				(*cycles) += 1;
   				for (int k=0; k<InArraySize;k++){ // running all the inputs in the input vector
#pragma HLS PIPELINE II=IIValue
   					sx = sIn_array[k];
   					TIW(	TIW_Instance_Name, // Instance name
   							false, // Rst to designs
   							sCIW, // Configurable Integer Widths // routed to both design instances but the Golden instance does not look at it
   							sCFW, // Configurable Fractional Widths // routed to both design instances but the Golden instance does not look at it
   							sIV, // Intermediate Variable integer values // routed to IV output of the Golden Instance
   							&sy1, // Golden output
   							&sy2, // DUT output
   							sx // input // routed the same to both instances
   							);
   					sGoldenOutput[k] = sy1;
   					sDUTOutput[k] = sy2;
				}
   				(*cycles) += (unsigned long long)InArraySize * IIValue;
   				BigFloatT Err_new = CalcError (sGoldenOutput,sDUTOutput);

//					printf ("er_new = %f\n", Err_new);
			    	if (Err_new < ErrorThreshold) {
//			    		printf ("reducing the width for element %d from %d to %d and increasing the width for element %d from %d to %d\n", min_Error_index, FractionalWidths[min_Error_index], FractionalWidths[min_Error_index]-2, max_Error_index, FractionalWidths[max_Error_index], FractionalWidths[min_Error_index]+1);
			    		FractionalWidths[min_Error_index] = FractionalWidths[min_Error_index] - 2;
			    		FractionalWidths[max_Error_index] = FractionalWidths[max_Error_index] + 1;
			    	} else {
			    		FineStage2Done = true; // if even reducing one bit from the least sensitive IV still introduces unacceptable error, then the first stage is over
//			    		printf("FineOpt stage 2 Over!!!!\n");
			    	}
			    for (int i=0; i<=IVNum-1; i++){
//			    	printf("FractionaWidth[%d] = %d\n", i, FractionalWidths[i]);
			    }

    	}

    	////////////////////////////////////////////////////////////

//		setting the final Fractional Widths
    	for (int i=0; i<=IVNum-1; i++){
	#pragma HLS PIPELINE
    		FinalCFW[i] = FractionalWidths[i]; // final widths
#ifndef __SYNTHESIS__
    		printf("final width [%d] = %d\n", i, FinalCFW[i]);
#endif
    	}

	}
}

BigFloatT CalcError (
		const fp_data_t sGoldenOutput[InArraySize], //Output array from the Golden Inst
		const fp_data_t sDUTOutput[InArraySize] //Output array from the DUT Inst
		){
#pragma HLS INLINE off
#pragma HLS ARRAY_PARTITION variable=sGoldenOutput type=cyclic factor=8 dim=1
#pragma HLS ARRAY_PARTITION variable=sDUTOutput type=cyclic factor=8 dim=1

	if (ErrMethod == 0) { //RMSE
		BigFloatT partial_sum[InArraySize];
		BigFloatT sum_error = 0.0;
//		printf("ErCalc Start!\n");
		for (int i = 0; i < InArraySize; i++){
#pragma HLS PIPELINE II=IIValue
			BigFloatT error = (BigFloatT)(sGoldenOutput[i] - sDUTOutput[i]);
			partial_sum[i] = error * error; //acc squared error
		}
		for (int i = 0; i < InArraySize; i++){
#pragma HLS UNROLL
			sum_error += partial_sum[i];
		}


		BigFloatT mean_error = sum_error / InArraySize;
//#ifndef __SYNTHESIS__
//			printf("mean = %f\n",  (float)mean_error);
//#endif
		BigFloatT rmse = hls::sqrt(mean_error); // HLS SQRT for synthesis
//#ifndef __SYNTHESIS__
//			printf("rmse = %f\n",  (float)rmse);
//#endif
		return rmse;
	}
}

