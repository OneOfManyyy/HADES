#include "WidthMod.h"

float WdithMod(float input_value, int cI, int cF) { // essentially doing what WA was doing in the hardware version

    // std::cout << "Original value: " << input_value << std::endl;

    // Convert the input value to the fixed-point simulation using float
    float ScaleI = powf(2,cI); // maybe use PowerLUT instead later
    float ScaleF = powf(2,cF);
    float ScaledIn = input_value/ScaleI;
    float TrimmedInt = ScaledIn - (int64_t) ScaledIn;
    float ScaledFrac = (int64_t)(TrimmedInt * ScaleI * ScaleF);
    float TrimmedOut = ScaledFrac / ScaleF;
    // std::cout << "Final value: " << TrimmedOut << std::endl;

    return TrimmedOut;
}

void PowerLUT(float exponent, float *pow2, float *pow2minus) {
    // Precomputed values for 2^exponent and 2^-exponent
    static const float pow2_vals[33] = {
        1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f, 128.0f, 256.0f, 512.0f,
        1024.0f, 2048.0f, 4096.0f, 8192.0f, 16384.0f, 32768.0f, 65536.0f, 131072.0f,
        262144.0f, 524288.0f, 1048576.0f, 2097152.0f, 4194304.0f, 8388608.0f, 16777216.0f,
        33554432.0f, 67108864.0f, 134217728.0f, 268435456.0f, 536870912.0f, 1073741824.0f,
        2147483648.0f, 4294967296.0f
    };

    static const float pow2minus_vals[33] = {
        1.0f, 0.5f, 0.25f, 0.125f, 0.0625f, 0.03125f, 0.015625f, 0.0078125f,
        0.00390625f, 0.001953125f, 0.0009765625f, 0.00048828125f, 0.000244140625f,
        0.0001220703125f, 0.00006103515625f, 0.000030517578125f, 0.0000152587890625f,
        0.00000762939453125f, 0.000003814697265625f, 0.0000019073486328125f,
        0.00000095367431640625f, 0.000000476837158203125f, 0.0000002384185791015625f,
        0.00000011920928955078125f, 0.000000059604644775390625f, 0.0000000298023223876953125f,
        0.00000001490116119384765625f, 0.000000007450580596923828125f, 0.0000000037252902984619140625f,
        0.00000000186264514923095703125f, 0.000000000931322574615478515625f, 
        0.0000000004656612873077392578125f, 0.00000000023283064365386962890625f
    };

    // Copy precomputed values to output arrays
    for (int i = 0; i <= 32; i++) {
        pow2[i] = pow2_vals[i];
        pow2minus[i] = pow2minus_vals[i];
    }
}