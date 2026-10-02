/*******************************************************************************
Dev. by: Keyvan Shahin
Project: Hardware-Based Fixed Point Simulation
In this project we tried to accelerate floating point to fixed point conversion
of an algorithm, by implementing a width configurable version of the application,
and the algorithm for finding the optimized widths for all the intermediate
variables inside the application on hardware.
Module name: FirSim
it's the top module containing both the application design and the tailored FPSim
*******************************************************************************/
#pragma once

#include "TIW.h"
#include "GlobalParameters.h"
#include <algorithm>
#include <cmath>



void FirSim(
//		bool SimRun, // Input, Commanding the start of FP Simulation
		width_t *FinalCIW, // The Final Calculated Integer Widths for all Intermediate Variables
		width_t *FinalCFW, // The Final Calculated Fractional Widths for all Intermediate Variables
		unsigned long long *cycles //counting the number of cycles in the most ran parts of the execution to find th execution time of the whole conversion process
		);
