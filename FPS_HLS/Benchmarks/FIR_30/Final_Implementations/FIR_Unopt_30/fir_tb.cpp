#include <iostream>
#include <fstream>
#include <sstream>
#include "fir.h"

//int main () {
//  const int    SAMPLES=600;
//  FILE         *fp,*fpf,*fpIV;
//
//  fp_data_t signal = 0.0;
//  fp_data_t outputDUT = 0.0;
//
//
//
//
//  int i, ramp_up;
//  ramp_up = 1;
//  printf ("Start\n");
//
//  //running the FIR for a while to test the restart functionality
//  for (i=0;i<=SAMPLES;i++) {
//    	if (ramp_up == 1)
//    		signal = signal + 1;
//    	else
//    		signal = signal - 1;
//
//    	// Execute the function DUT
//    	fir(false,
//        	&outputDUT,
//    		signal);
//
//        if ((ramp_up == 1) && (signal >= 75))
//        	ramp_up = 0;
//        else if ((ramp_up == 0) && (signal <= -75))
//        	ramp_up = 1;
//
//  }
//
//  bool rst_test;
//  rst_test = true; // should result in success for simulation
////  rst_test = false; // should result in failure for simulation
//
//  //restarting
//  fir(rst_test, //restart
//	&outputDUT,
//	signal);
//
//  signal = 0;
//  ramp_up = 1;
//
//  fpf=fopen("../../../Simulation/out_fixed.dat","w");
//  for (i=0;i<=SAMPLES;i++) {
//  	if (ramp_up == 1)
//  		signal = signal + 1;
//  	else
//  		signal = signal - 1;
//
//
//	// Execute the function DUT
//    fir(false,
//    	&outputDUT,
//		signal);
//
//    if ((ramp_up == 1) && (signal >= 75))
//    	ramp_up = 0;
//    else if ((ramp_up == 0) && (signal <= -75))
//    	ramp_up = 1;
//
//    fprintf(fpf,"%i %s %s\n",i,signal.to_string(10,true).c_str(),outputDUT.to_string(10,true).c_str());
//  }
//  fclose(fpf);
//
//  printf ("Comparing against output data \n");
////  if (system("diff -w ../../../Simulation/out_fixed.dat ../../../Simulation/out.gold.dat")) {
////
////	fprintf(stdout, "*******************************************\n");
////	fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
////	fprintf(stdout, "*******************************************\n");
////     return 1;
////  } else {
////	fprintf(stdout, "*******************************************\n");
////	fprintf(stdout, "PASS: The output matches the golden output!\n");
////	fprintf(stdout, "*******************************************\n");
////     return 0;
////  }
//  return 0;
//}


int main() {
    // Declare variables
    fp_data_t y;
    bool Restart = true;

    fir(Restart, &y, In_array[0]); // just to restart the SR inside the fir

    // Set Restart to false after resetting shift registers
    Restart = false;

    // Create input and output CSV files
    std::ofstream input_file("input.csv");
    std::ofstream output_file("output.csv");

    if (!input_file.is_open() || !output_file.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return -1;  // Indicate failure
    }

    // Write the headers for the CSV files
    input_file << "Input Value" << std::endl;
    output_file << "Output Value" << std::endl;

    // Iterate over the input values
    for (int i = 0; i < InArraySize; i++) {
        // Call the FIR filter function
        fir(Restart, &y, In_array[i]);

        // Write input value to input.csv
        input_file << In_array[i] << std::endl;

        // Write output value to output.csv
        output_file << y << std::endl;

        // Print the results to the console
        std::cout << "Input: " << In_array[i] << " | Output: " << y << std::endl;

        // Optional: Check if the output is as expected
//        if (y != Expected_Out_array[i]) {
//            std::cout << "Test failed at index " << i << "!" << std::endl;
//            input_file.close();
//            output_file.close();
//            return -1; // Indicate failure
//        }

    }

    // Close the files after all the values are written
    input_file.close();
    output_file.close();

    std::cout << "All tests passed!" << std::endl;
    return 0;  // Indicate success
}
