#include "TIW.h"

void TIW(
        const char* inst_name,
        bool Rst,
        width_t *CIW,
        width_t *CFW,
        int_part_t *IV,
        fp_data_t *y1, // Golden
        fp_data_t *y2, // DUT
        fp_data_t x
){
#pragma HLS INLINE off
#pragma HLS FUNCTION_INSTANTIATE variable=inst_name


    int_part_t sIVDUT[IVNum];

    fp_data_t sy1, sy2;
    fp_data_t sx1, sx2;
    // =========================
    // INPUT DUPLICATION
    // =========================
    sx1 = x;
    sx2 = x;


    // =========================
    // GOLDEN
    // =========================
    poly(
    	 Golden_Instance_Name,
         true,
         Rst,
         CIW,
         CFW,
         IV,
         &sy1,
         sx1);


    // =========================
    // DUT
    // =========================
    poly(
    	 DUT_Instance_Name,
         false,
         Rst,
         CIW,
         CFW,
         sIVDUT,
         &sy2,
         sx2);

    *y1 = sy1;
    *y2 = sy2;
}
