#include "Poly.h"
#include "WCMultiplier.h"
#include "WCAdder.h"

void poly (
    const char* inst_name,
    bool GoldenInst,
    bool Restart,
    width_t *CIW,
    width_t *CFW,
    int_part_t *IV,
    fp_data_t *y,
    fp_data_t x
){
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

    // =========================
    // Coefficients ([-pi, pi])
    // =========================
    const fp_data_t a0 = 0.0;
    const fp_data_t a1 = 0.9999793130;
    const fp_data_t a2 = 0.0;
    const fp_data_t a3 = -0.1666244320;
    const fp_data_t a4 = 0.0;
    const fp_data_t a5 = 0.0083087010;
    const fp_data_t a6 = 0.0;
    const fp_data_t a7 = -0.0001836360;

    // =========================
    // Horner chain
    // =========================

    fp_data_t t0, t1, t2, t3, t4, t5, t6;
    fp_data_t mult_out, add_out;

    // -------------------------
    // Stage 0: t0 = a7
    // -------------------------
    t0 = a7;

    // -------------------------
    // Stage 1: t1 = a6 + x*t0
    // -------------------------
    WCMultiplier(GoldenInst, x, t0,
                 CIW[0], CFW[0],
                 CIW[1], CFW[1],
                 &mult_out);

    WCAdder(GoldenInst, a6, mult_out,
            CIW[2], CFW[2],
            CIW[3], CFW[3],
            &t1);

    if (GoldenInst){
        IV[0] = int_part_t(x);
        IV[1] = int_part_t(t0);
        IV[2] = int_part_t(a6);
        IV[3] = int_part_t(mult_out);
    } else {
        IV[0]=IV[1]=IV[2]=IV[3]=0;
    }

    // -------------------------
    // Stage 2: t2 = a5 + x*t1
    // -------------------------
    WCMultiplier(GoldenInst, x, t1,
                 CIW[4], CFW[4],
                 CIW[5], CFW[5],
                 &mult_out);

    WCAdder(GoldenInst, a5, mult_out,
            CIW[6], CFW[6],
            CIW[7], CFW[7],
            &t2);

    if (GoldenInst){
        IV[4] = int_part_t(x);
        IV[5] = int_part_t(t1);
        IV[6] = int_part_t(a5);
        IV[7] = int_part_t(mult_out);
    } else {
        IV[4]=IV[5]=IV[6]=IV[7]=0;
    }

    // -------------------------
    // Stage 3: t3 = a4 + x*t2
    // -------------------------
    WCMultiplier(GoldenInst, x, t2,
                 CIW[8], CFW[8],
                 CIW[9], CFW[9],
                 &mult_out);

    WCAdder(GoldenInst, a4, mult_out,
            CIW[10], CFW[10],
            CIW[11], CFW[11],
            &t3);

    if (GoldenInst){
        IV[8]  = int_part_t(x);
        IV[9]  = int_part_t(t2);
        IV[10] = int_part_t(a4);
        IV[11] = int_part_t(mult_out);
    } else {
        IV[8]=IV[9]=IV[10]=IV[11]=0;
    }

    // -------------------------
    // Stage 4: t4 = a3 + x*t3
    // -------------------------
    WCMultiplier(GoldenInst, x, t3,
                 CIW[12], CFW[12],
                 CIW[13], CFW[13],
                 &mult_out);

    WCAdder(GoldenInst, a3, mult_out,
            CIW[14], CFW[14],
            CIW[15], CFW[15],
            &t4);

    if (GoldenInst){
        IV[12] = int_part_t(x);
        IV[13] = int_part_t(t3);
        IV[14] = int_part_t(a3);
        IV[15] = int_part_t(mult_out);
    } else {
        IV[12]=IV[13]=IV[14]=IV[15]=0;
    }

    // -------------------------
    // Stage 5: t5 = a2 + x*t4
    // -------------------------
    WCMultiplier(GoldenInst, x, t4,
                 CIW[16], CFW[16],
                 CIW[17], CFW[17],
                 &mult_out);

    WCAdder(GoldenInst, a2, mult_out,
            CIW[18], CFW[18],
            CIW[19], CFW[19],
            &t5);

    if (GoldenInst){
        IV[16] = int_part_t(x);
        IV[17] = int_part_t(t4);
        IV[18] = int_part_t(a2);
        IV[19] = int_part_t(mult_out);
    } else {
        IV[16]=IV[17]=IV[18]=IV[19]=0;
    }

    // -------------------------
    // Stage 6: t6 = a1 + x*t5
    // -------------------------
    WCMultiplier(GoldenInst, x, t5,
                 CIW[20], CFW[20],
                 CIW[21], CFW[21],
                 &mult_out);

    WCAdder(GoldenInst, a1, mult_out,
            CIW[22], CFW[22],
            CIW[23], CFW[23],
            &t6);

    if (GoldenInst){
        IV[20] = int_part_t(x);
        IV[21] = int_part_t(t5);
        IV[22] = int_part_t(a1);
        IV[23] = int_part_t(mult_out);
    } else {
        IV[20]=IV[21]=IV[22]=IV[23]=0;
    }

    // -------------------------
    // Final: y = a0 + x*t6
    // -------------------------
    WCMultiplier(GoldenInst, x, t6,
                 CIW[24], CFW[24],
                 CIW[25], CFW[25],
                 &mult_out);

    WCAdder(GoldenInst, a0, mult_out,
            CIW[26], CFW[26],
            CIW[27], CFW[27],
            y);

    if (GoldenInst){
        IV[24] = int_part_t(x);
        IV[25] = int_part_t(t6);
        IV[26] = int_part_t(a0);
        IV[27] = int_part_t(mult_out);
    } else {
        IV[24]=IV[25]=IV[26]=IV[27]=0;
    }
}
