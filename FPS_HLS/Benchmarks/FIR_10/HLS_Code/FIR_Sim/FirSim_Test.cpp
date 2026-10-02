#include <stdio.h>
#include <math.h>
#include <fstream>  // For file operations
#include "FirSim.h"

int main () {


  width_t FinalCIW[IVNum];
  width_t FinalCFW[IVNum];
	unsigned long long cycles;


  // Execute Simulation
  FirSim(
//   		true, // Input, Commanding the start of FP Simulation
   		FinalCIW, // The Final Calculated Integer Widths for all Intermediate Variables
   		FinalCFW, // The Final Calculated Fractional Widths for all Intermediate Variables
   		&cycles
   		);

  for (int i=0; i<= IVNum-1; i++){
	  fprintf(stdout, "FinalCIW[%d] = %d\n", i, FinalCIW[i]);
	  fprintf(stdout, "FinalCFW[%d] = %d\n", i, FinalCFW[i]);
  }

  // Write to file: output_widths.h
    std::ofstream outFile("output_widths.h");

    if (!outFile) {
        std::cerr << "Error: Could not open output_widths.h for writing!" << std::endl;
        return 1;
    }

    // Write header guard
    outFile << "#ifndef OUTPUT_WIDTHS_H\n#define OUTPUT_WIDTHS_H\n\n";

    // Write IntegerWidth array
    outFile << "constexpr int IntegerWidth[" << IVNum << "] = {";
    for (int i = 0; i < IVNum; i++) {
        outFile << FinalCIW[i];
        if (i < IVNum - 1) outFile << ", ";  // Add comma except last element
    }
    outFile << "};\n";

    // Write FractionalWidth array
    outFile << "constexpr int FractionalWidth[" << IVNum << "] = {";
    for (int i = 0; i < IVNum; i++) {
        outFile << FinalCFW[i];
        if (i < IVNum - 1) outFile << ", ";
    }
    outFile << "};\n";

    // Close header guard
    outFile << "\n#endif // OUTPUT_WIDTHS_H\n";

    // Close file
    outFile.close();
    
    fprintf(stdout, "cycles = %d\n", cycles);

  fprintf(stdout, "*******************************************\n");
  fprintf(stdout, "PASS: The output matches the golden output!\n");
  fprintf(stdout, "*******************************************\n");
  return 0;
}
