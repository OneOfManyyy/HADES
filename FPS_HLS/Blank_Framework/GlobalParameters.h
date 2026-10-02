#pragma once

#include <ap_fixed.h>

#define IIValue 1 // testing with #pragma HLS PIPELINE II=IIValue

#define GI	16
#define GF	16

typedef ap_fixed<(GI+GF),GI> fp_data_t;
typedef ap_fixed<(2*(GI+GF)),(2*GI)> fp_data_t_sq;
typedef ap_fixed<64,32> BigFloatT; // big-width float type to be used for parts that are not included in the DUT, for error calculation for example

typedef ap_int<GI> int_part_t;

typedef int width_t;

/// Application-specific parameters
// These parameters must be defined by the user for the target application.
//
// IVNum: number of intermediate variables exposed by the application.
// InArraySize: number of input samples / input vectors used for one simulation.
//
// The values depend on the application and simulation dataset.
// For example, a FIR filter may use the number of input samples,
// while an application with multiple input signals should account for
// the corresponding input structure in its Application() implementation.

#define IVNum <NUMBER_OF_VARIABLES>
#define InArraySize <NUMBER_OF_INPUT_SAMPLES>
#define InArraySizeR <write it as 1/InArraySize> // This is required for RMSE calculation

static const char* Golden_Instance_Name = "Golden"; // golden instance
static const char* DUT_Instance_Name = "DUT"; // design under test
static const char* TIW_Instance_Name = "TIW"; // two-instance wrapper

#define InMode 0 // 0 = input array
#define DRMode 0 // 0 = All inputs scan for dynamic range calc (Maximum Absolute Value Method)	1 = using mean and variance of the values to estimate the range (Statistical Method)
#define ErrMethod 0 // 0 = RMSE (root mean square error)
static const BigFloatT ErrorThreshold = 0.05; // like 5% RMSE
static const int SCALING_FACTOR = 3; // number of standard deviations used for range estimation when DRMode=1

//enum InModeEnum {input_array}

//InModeEnum InMode = input_array;
