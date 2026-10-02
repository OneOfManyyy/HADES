#include "Application.h"
#include "WCMultiplier.h"
#include "WCAdder.h"

void Application(
    const char* inst_name,
    bool GoldenInst,
    bool reset,
    width_t* CIW,
    width_t* CFW,
    const fp_data_t* input,
    fp_data_t* output
    /* ... application-specific ports ... */
)
{
    // ============================================================
    // **Explanation**
    // This function represents the application datapath to be
    // evaluated by HADES.
    //
    // Two instances of the application are required:
    //   - Golden instance: uses the maximum/reference widths.
    //   - DUT instance: uses the runtime-configurable widths.
    //
    // Replace this function with the application-specific
    // datapath. WCAdder and WCMultiplier are used for operations
    // whose widths are subject to optimization.
    //
    // The application must expose all intermediate variables
    // participating in width optimization through the arrays
    // described below.
    // ============================================================


    // ============================================================
    // **Explanation**
    // Define the number of intermediate variables whose widths
    // are optimized.
    //
    // Example:
    //   const int NumVariables = <NUMBER_OF_VARIABLES>;
    //
    // The same number determines the size of:
    //   - the intermediate-value array used by DR
    //   - the configurable-width arrays
    //
    // Each intermediate variable must have a corresponding entry
    // in these arrays.
    // ============================================================


    // Intermediate values to be evaluated by the framework
    fp_data_t intermediate_values[/* NumVariables */];


    // Runtime integer and fractional widths
    width_t CIW_local[/* NumVariables */];
    width_t CFW_local[/* NumVariables */];


    // ============================================================
    // **Explanation**
    // Implement the application datapath here.
    //
    // Use GoldenInst to distinguish between:
    //
    //   GoldenInst == true:
    //       reference/golden datapath using fixed maximum widths
    //
    //   GoldenInst == false:
    //       DUT datapath using runtime-configurable widths
    //
    // For the DUT, connect the corresponding CIW/CFW values to
    // the configurable arithmetic operators.
    //
    // Store every intermediate variable required by the dynamic
    // range and fractional-width optimization in intermediate_values.
    // ============================================================


    // Application output
    output[0] = /* application result */;
}