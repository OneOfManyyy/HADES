#include "LMS.h"
#include "WCMultiplier.h"
#include "WCAdder.h"

void lms (
    const char* inst_name,
    bool GoldenInst,
    bool Restart,
    width_t *CIW,
    width_t *CFW,
    int_part_t *IV,
    fp_data_t *y,
    fp_data_t x,
    fp_data_t d,
    fp_data_t *shift_reg_x,
    fp_data_t *w
) {
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

    fp_data_t acc_l;
    fp_data_t acc_n;
    fp_data_t mult_fw;

    fp_data_t err;
    fp_data_t mu_e;
    fp_data_t update_term;

    // =========================
    // RESET
    // =========================
    if (Restart) {
        for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
            shift_reg_x[i] = fp_data_t(0.0);
            w[i]           = fp_data_t(0.0);

            // 8 IVs per tap
            IV[8*i+0] = 0;
            IV[8*i+1] = 0;
            IV[8*i+2] = 0;
            IV[8*i+3] = 0;
            IV[8*i+4] = 0;
            IV[8*i+5] = 0;
            IV[8*i+6] = 0;
            IV[8*i+7] = 0;
        }
        *y = fp_data_t(0.0);
    }
    else {

    // =========================
    // SHIFT REGISTER
    // =========================
    for (int i = N-1; i >= 1; i--) {
#pragma HLS UNROLL
        shift_reg_x[i] = shift_reg_x[i-1];
    }
    shift_reg_x[0] = x;

    // =========================
    // FORWARD PATH (FIR)
    // =========================
    acc_l = fp_data_t(0.0);

    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL

        // x * w
        WCMultiplier(
            GoldenInst,
            shift_reg_x[i],
            w[i],
            CIW[8*i+0], CFW[8*i+0],
            CIW[8*i+1], CFW[8*i+1],
            &mult_fw
        );

        // accumulate
        WCAdder(
            GoldenInst,
            acc_l,
            mult_fw,
            CIW[8*i+2], CFW[8*i+2],
            CIW[8*i+3], CFW[8*i+3],
            &acc_n
        );

        // IV logging (Golden only)
        if (GoldenInst) {
            IV[8*i+0] = int_part_t(shift_reg_x[i]);
            IV[8*i+1] = int_part_t(w[i]);
            IV[8*i+2] = int_part_t(acc_l);
            IV[8*i+3] = int_part_t(mult_fw);
        } else {
            IV[8*i+0] = 0;
            IV[8*i+1] = 0;
            IV[8*i+2] = 0;
            IV[8*i+3] = 0;
        }

        acc_l = acc_n;
    }

    *y = acc_l;

    // =========================
    // ERROR: e = d - y
    // =========================
    WCAdder(
        GoldenInst,
        d,
        -(*y),
        CIW[Base], CFW[Base],
        CIW[Base+1], CFW[Base+1],
        &err
    );

    // =========================
    // COMPUTE Î¼ * e
    // =========================
    WCMultiplier(
        GoldenInst,
        mu,
        err,
        CIW[Base+2], CFW[Base+2],
        CIW[Base+3], CFW[Base+3],
        &mu_e
    );

    // =========================
    // UPDATE WEIGHTS
    // =========================
    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL

        // (Î¼e) * x
        WCMultiplier(
            GoldenInst,
            mu_e,
            shift_reg_x[i],
            CIW[8*i+4], CFW[8*i+4],
            CIW[8*i+5], CFW[8*i+5],
            &update_term
        );

        // w + update
        WCAdder(
            GoldenInst,
            w[i],
            update_term,
            CIW[8*i+6], CFW[8*i+6],
            CIW[8*i+7], CFW[8*i+7],
            &w[i]
        );

        // IV logging (Golden only)
        if (GoldenInst) {
            IV[8*i+4] = int_part_t(err);
            IV[8*i+5] = int_part_t(mu);
            IV[8*i+6] = int_part_t(mu_e);
            IV[8*i+7] = int_part_t(update_term);
        } else {
            IV[8*i+4] = 0;
            IV[8*i+5] = 0;
            IV[8*i+6] = 0;
            IV[8*i+7] = 0;
        }
    }

    }
}
