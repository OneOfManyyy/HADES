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

    width_t MIW[IVNum];
    width_t MFW[IVNum];

    int_part_t sIVDUT[IVNum];

    fp_data_t sy1, sy2, sd;
    fp_data_t sx1, sx2, sxd;
//    fp_data_t sd1, sd2;

    // =========================
    // STATE (externalized like your IIR)
    // =========================
    static fp_data_t shift_reg_G_x[N];
    static fp_data_t w_G[N];

    static fp_data_t shift_reg_D_x[N];
    static fp_data_t w_D[N];

    static fp_data_t shift_reg_unknown_x[N];

    // =========================
    // INPUT DUPLICATION
    // =========================
    sx1 = x;
    sx2 = x;
    sxd = x;

//    sd1 = d;
//    sd2 = d;

    // unkown system FIR

    unknown_sys(
        Rst,
        &sd,
        sx1,
		shift_reg_unknown_x
    );


    // =========================
    // GOLDEN
    // =========================
    lms(
        Golden_Instance_Name,
        true,               // Golden
        Rst,
        CIW,
        CFW,
        IV,
        &sy1,
        sx1,
        sd,
        shift_reg_G_x,
        w_G
    );

    // =========================
    // DUT
    // =========================
    lms(
        DUT_Instance_Name,
        false,              // DUT
        Rst,
        CIW,
        CFW,
        sIVDUT,
        &sy2,
        sx2,
        sd,
        shift_reg_D_x,
        w_D
    );

    *y1 = sy1;
    *y2 = sy2;
}
