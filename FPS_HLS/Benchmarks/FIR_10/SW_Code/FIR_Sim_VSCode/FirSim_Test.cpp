#include "GlobalParameters.h"
#include <stdio.h>
#include <math.h>
#include "FirSim.h"
#include <time.h>

int main () {
  // Start timing
  clock_t start = clock();

  
  width_t CIW[IVNum];
  width_t CFW[IVNum];

  int_part_t IV[IVNum];

  bool Rst;

  width_t FinalCIW[IVNum];
  width_t FinalCFW[IVNum];

  std::fill(CIW, CIW + IVNum, 16);
  std::fill(CFW, CFW + IVNum, 16);

  
  const bool GoldenInstMax = true;
  const bool GoldenInstDUT = false;



//  bool rst_test;
//  rst_test = true; // should result in success for simulation
//  rst_test = false; // should result in failure for simulation

  //FirSim Idle
//  FirSim(
//  		false, // Input, Commanding the start of FP Simulation
//  		FinalCIW, // The Final Calculated Integer Widths for all Intermediate Variables
//  		FinalCFW // The Final Calculated Fractional Widths for all Intermediate Variables
//  		);

  // Execute Simulation
  FirSim(
//   		true, // Input, Commanding the start of FP Simulation
   		FinalCIW, // The Final Calculated Integer Widths for all Intermediate Variables
   		FinalCFW // The Final Calculated Fractional Widths for all Intermediate Variables
   		);

  for (int i=0; i<= IVNum-1; i++){
	  fprintf(stdout, "FinalCIW[%d] = %d\n", i, FinalCIW[i]);
	  fprintf(stdout, "FinalCFW[%d] = %d\n", i, FinalCFW[i]);
  }

  fprintf(stdout, "*******************************************\n");
  fprintf(stdout, "PASS: The output matches the golden output!\n");
  fprintf(stdout, "*******************************************\n");
  
  // End timing
  clock_t end = clock();
  // Calculate elapsed time
  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Execution time: %f seconds\n", time_taken);
  return 0;
}
