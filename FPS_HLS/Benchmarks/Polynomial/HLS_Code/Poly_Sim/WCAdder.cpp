/*******************************************************************************
Dev. by: Keyvan Shahin
Project: Hardware-Based Fixed Point Simulation
In this project we tried to accelerate floating point to fixed point conversion
of an algorithm, by implementing a width configurable version of the application,
and the algorithm for finding the optimized widths for all the intermediate
variables inside the application on hardware.
Module name: WCAdder
it's an adder that also receives the widths of inputs
*******************************************************************************/
#include "WCAdder.h"

void WCAdder (
	bool GoldenInst, // shows if this is the Golden instance with constant widths
	fp_data_t x1, //input 1
	fp_data_t x2, //input 2
	width_t cI1, //input 1 integer Width
	width_t cF1, //input 1 fractional Width
	width_t cI2, //input 2 integer Width
	width_t cF2, //input 2 fractional Width
	fp_data_t *y //Adder output
	) {

	fp_data_t data; // sized data to fit the global widths

	fp_data_t x1_WA, x2_WA; // Width Adapted inputs

	if (GoldenInst){ // no Width adaptor required. we use maximum global widths
		x1_WA = x1;
		x2_WA = x2;
	}
	else{
		WidthAdapter (
			x1,
			cI1,
			cF1,
			&x1_WA
		);
		WidthAdapter (
			x2,
			cI2,
			cF2,
			&x2_WA
		);
	}
	data = x1_WA + x2_WA;
	*y = data;
 }
