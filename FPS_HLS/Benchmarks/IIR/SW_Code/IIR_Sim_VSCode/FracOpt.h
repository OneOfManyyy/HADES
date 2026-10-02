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
#pragma once
#include "GlobalParameters.h"
#include "TIW.h"
#include <algorithm>
#include <cmath>


void FracOpt(
//		bool SimRun, // Input, Commanding the start of FP Simulation
//		fp_data_t *sIn_array, // Array containing the inputs to the design
		width_t *FinalCIW, // The Final Calculated Integer Widths for all Intermediate Variables - input of this module
		width_t *FinalCFW // The Final Calculated Fractional Widths for all Intermediate Variables - output of this module
		);

BigFloatT CalcError (
		const fp_data_t sGoldenOutput[InArraySize], //Output array from the Golden Inst
		const fp_data_t sDUTOutput[InArraySize] //Output array from the DUT Inst
		);
