#include "TIW.h"

void TIW(
		const char* inst_name, // Instance name
		bool Rst,
		width_t *CIW,
		width_t *CFW,
		int_part_t *IV,
		fp_data_t *y1, //Golden output
		fp_data_t *y2, //DUT output
		fp_data_t x
		){
#pragma HLS INLINE off
#pragma HLS FUNCTION_INSTANTIATE variable=inst_name

	width_t MIW[IVNum]; // constant max widths of Golden instance
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=MIW
	width_t MFW[IVNum];
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=MFW

	int_part_t sIVDUT[IVNum]; //place holder
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=sIVDUT
	fp_data_t sy1, sy2;
	fp_data_t sx1, sx2;


	//////////// moved following static variables from design to here for some issues with the way c++ handles memory and shift registers in this case
	static fp_data_t shift_reg_G_x[N]; //static array for Golden Instance
	static fp_data_t shift_reg_G_y[N]; //static array for Golden Instance
	static fp_data_t shift_reg_D_x[N]; //static array for DUT Instance
	static fp_data_t shift_reg_D_y[N]; //static array for DUT Instance
	///////////

	sx1 = x;
	sx2 = x;


	iir (Golden_Instance_Name, //Golden
		true, // true = Golden / false = DUT
		Rst, // restarting the shift register in IIR
		CIW, // Conf Input of the Design // Widths of the integer part of the intermediate variables	// Golden Instance does not use these
		CFW, // Conf Input of the Design // Widths of the fractional part of the intermediate variables	// Golden Instance does not use these
		IV, // Conf Output of the Design - only used with Golden instant // Intermediate Variables value
		&sy1, // Output of the Design // main output of the design
		sx1, // Input of the Design
		shift_reg_G_x,
		shift_reg_G_y
	  );

	iir (DUT_Instance_Name, //DUT
		false, // true = Golden / false = DUT
		Rst, // restarting the shift register in IIR
		CIW, // Conf Input of the Design // Widths of the integer part of the intermediate variables
		CFW, // Conf Input of the Design // Widths of the fractional part of the intermediate variables
		sIVDUT, // Conf Output of the Design - only used with Golden instant // Intermediate Variables value // not used in DUT
		&sy2, // Output of the Design // main output of the design
		sx2, // Input of the Design
		shift_reg_D_x,
		shift_reg_D_y
	  );

//#ifndef __SYNTHESIS__
//	for (int i = 0; i < IVNum; i++){
//		if (IV[i]!=sIVDUT[i]) {
//			printf ("IV[%d] = %d\n", i, (int)IV[i]);
//			printf ("sIVDUT[%d] = %d\n", i, (int)sIVDUT[i]);
//			printf ("CIW[%d] = %d\n", i, (int)CIW[i]);
//			printf ("--------------------\n");
//		}
//	}
//#endif

	*y1 = sy1;
	*y2 = sy2;
}
