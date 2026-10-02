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
#pragma once
#include "GlobalParameters.h"
#include "TIW.h"
#include <algorithm>
#include <cmath>


void DR(
		width_t *FinalCIW // The Final Calculated Integer Widths for all Intermediate Variables - output of this module
		);

width_t count_leading_zeros(int_part_t x);
