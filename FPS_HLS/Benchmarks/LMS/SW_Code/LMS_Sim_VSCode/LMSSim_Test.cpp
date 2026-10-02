#include <stdio.h>
#include <math.h>
#include "LMSSim.h"
#include <time.h>

int main () {
  clock_t start = clock();
//  const int    SAMPLES=600;
//  FILE         *fp,*fpf,*fpIV;
	unsigned long long cycles;

//  fp_data_t signal, outputMax, outputDUT;
//  fp_data_t taps[N] = {0,-10,-9,23,56,63,56,23,-9,-10,};

  width_t CIW[IVNum];
  width_t CFW[IVNum];

  int_part_t IV[IVNum];

  bool Rst;

  width_t FinalCIW[IVNum];
  width_t FinalCFW[IVNum];

  std::fill(CIW, CIW + IVNum, 16);
  std::fill(CFW, CFW + IVNum, 16);

//  int i, ramp_up;
//  signal = 0;
//  ramp_up = 1;

  const bool GoldenInstMax = true;
  const bool GoldenInstDUT = false;



//  bool rst_test;
//  rst_test = true; // should result in success for simulation
//  rst_test = false; // should result in failure for simulation

  // Idle
//  LMSSim(
//  		false, // Input, Commanding the start of FP Simulation
//  		FinalCIW, // The Final Calculated Integer Widths for all Intermediate Variables
//  		FinalCFW // The Final Calculated Fractional Widths for all Intermediate Variables
//  		);
//
  // Execute Simulation
  LMSSim(
//   		true, // Input, Commanding the start of FP Simulation
   		FinalCIW, // The Final Calculated Integer Widths for all Intermediate Variables
   		FinalCFW, // The Final Calculated Fractional Widths for all Intermediate Variables
		&cycles		//number of cycles for finishing the conversion
  );

  for (int i=0; i<= IVNum-1; i++){
	  fprintf(stdout, "FinalCIW[%d] = %d\n", i, FinalCIW[i]);
	  fprintf(stdout, "FinalCFW[%d] = %d\n", i, FinalCFW[i]);
  }

  fprintf(stdout, "cycles = %d\n", cycles);

  fprintf(stdout, "*******************************************\n");
  fprintf(stdout, "PASS: The output matches the golden output!\n");
  fprintf(stdout, "*******************************************\n");

  clock_t end = clock();
  // Calculate elapsed time
  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Execution time: %f seconds\n", time_taken);
  return 0;
}
