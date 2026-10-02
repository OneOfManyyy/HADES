// fixed_point_types.h
#pragma once

//#include <tuple>
#include "GlobalParameters.h"


// Compile-time arrays for integer and fractional widths // these are written in a file during the testbench run of the fixed-point conversion
constexpr int IntegerWidth[IVNum] = {8, 1, 1, 1, 8, 5, 1, 11, 8, 5, 11, 11, 8, 6, 12, 12, 8, 7, 12, 14, 8, 7, 14, 14, 8, 7, 15, 14, 8, 6, 15, 12, 8, 5, 15, 11, 8, 5, 15, 11};
constexpr int FractionalWidth[IVNum] = {0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 6, 5, 0, 0, 6, 6, 0, 0, 5, 6, 0, 0, 6, 6, 0, 0, 6, 5, 0, 0, 6, 6, 0, 0, 5, 5, 0, 0, 5, 5};


// could not make use of templates in Vitis atm unfortunately but i don't think it's going to be a problem.
//// Helper to construct the tuple (Avoids direct array indexing in templates)
//template <size_t... Indices>
//auto constructTuple(std::index_sequence<Indices...>) {
//    return std::tuple<ap_fixed<(FractionalWidth[Indices] + IntegerWidth[Indices]), IntegerWidth[Indices]>...>{};
//}
//
//// Define tuple type
//constexpr size_t NumElements = IVNum; // Adjust as needed
//using MyTupleType = decltype(constructTuple(std::make_index_sequence<NumElements>{}));


typedef ap_fixed<IntegerWidth[0]+FractionalWidth[0],IntegerWidth[0]> Custom_ap_fixed_T_0;
typedef ap_fixed<IntegerWidth[1]+FractionalWidth[1],IntegerWidth[1]> Custom_ap_fixed_T_1;
typedef ap_fixed<IntegerWidth[2]+FractionalWidth[2],IntegerWidth[2]> Custom_ap_fixed_T_2;
typedef ap_fixed<IntegerWidth[3]+FractionalWidth[3],IntegerWidth[3]> Custom_ap_fixed_T_3;
typedef ap_fixed<IntegerWidth[4]+FractionalWidth[4],IntegerWidth[4]> Custom_ap_fixed_T_4;
typedef ap_fixed<IntegerWidth[5]+FractionalWidth[5],IntegerWidth[5]> Custom_ap_fixed_T_5;
typedef ap_fixed<IntegerWidth[6]+FractionalWidth[6],IntegerWidth[6]> Custom_ap_fixed_T_6;
typedef ap_fixed<IntegerWidth[7]+FractionalWidth[7],IntegerWidth[7]> Custom_ap_fixed_T_7;
typedef ap_fixed<IntegerWidth[8]+FractionalWidth[8],IntegerWidth[8]> Custom_ap_fixed_T_8;
typedef ap_fixed<IntegerWidth[9]+FractionalWidth[9],IntegerWidth[9]> Custom_ap_fixed_T_9;
typedef ap_fixed<IntegerWidth[10]+FractionalWidth[10],IntegerWidth[10]> Custom_ap_fixed_T_10;
typedef ap_fixed<IntegerWidth[11]+FractionalWidth[11],IntegerWidth[11]> Custom_ap_fixed_T_11;
typedef ap_fixed<IntegerWidth[12]+FractionalWidth[12],IntegerWidth[12]> Custom_ap_fixed_T_12;
typedef ap_fixed<IntegerWidth[13]+FractionalWidth[13],IntegerWidth[13]> Custom_ap_fixed_T_13;
typedef ap_fixed<IntegerWidth[14]+FractionalWidth[14],IntegerWidth[14]> Custom_ap_fixed_T_14;
typedef ap_fixed<IntegerWidth[15]+FractionalWidth[15],IntegerWidth[15]> Custom_ap_fixed_T_15;
typedef ap_fixed<IntegerWidth[16]+FractionalWidth[16],IntegerWidth[16]> Custom_ap_fixed_T_16;
typedef ap_fixed<IntegerWidth[17]+FractionalWidth[17],IntegerWidth[17]> Custom_ap_fixed_T_17;
typedef ap_fixed<IntegerWidth[18]+FractionalWidth[18],IntegerWidth[18]> Custom_ap_fixed_T_18;
typedef ap_fixed<IntegerWidth[19]+FractionalWidth[19],IntegerWidth[19]> Custom_ap_fixed_T_19;
typedef ap_fixed<IntegerWidth[20]+FractionalWidth[20],IntegerWidth[20]> Custom_ap_fixed_T_20;
typedef ap_fixed<IntegerWidth[21]+FractionalWidth[21],IntegerWidth[21]> Custom_ap_fixed_T_21;
typedef ap_fixed<IntegerWidth[22]+FractionalWidth[22],IntegerWidth[22]> Custom_ap_fixed_T_22;
typedef ap_fixed<IntegerWidth[23]+FractionalWidth[23],IntegerWidth[23]> Custom_ap_fixed_T_23;
typedef ap_fixed<IntegerWidth[24]+FractionalWidth[24],IntegerWidth[24]> Custom_ap_fixed_T_24;
typedef ap_fixed<IntegerWidth[25]+FractionalWidth[25],IntegerWidth[25]> Custom_ap_fixed_T_25;
typedef ap_fixed<IntegerWidth[26]+FractionalWidth[26],IntegerWidth[26]> Custom_ap_fixed_T_26;
typedef ap_fixed<IntegerWidth[27]+FractionalWidth[27],IntegerWidth[27]> Custom_ap_fixed_T_27;
typedef ap_fixed<IntegerWidth[28]+FractionalWidth[28],IntegerWidth[28]> Custom_ap_fixed_T_28;
typedef ap_fixed<IntegerWidth[29]+FractionalWidth[29],IntegerWidth[29]> Custom_ap_fixed_T_29;
typedef ap_fixed<IntegerWidth[30]+FractionalWidth[30],IntegerWidth[30]> Custom_ap_fixed_T_30;
typedef ap_fixed<IntegerWidth[31]+FractionalWidth[31],IntegerWidth[31]> Custom_ap_fixed_T_31;
typedef ap_fixed<IntegerWidth[32]+FractionalWidth[32],IntegerWidth[32]> Custom_ap_fixed_T_32;
typedef ap_fixed<IntegerWidth[33]+FractionalWidth[33],IntegerWidth[33]> Custom_ap_fixed_T_33;
typedef ap_fixed<IntegerWidth[34]+FractionalWidth[34],IntegerWidth[34]> Custom_ap_fixed_T_34;
typedef ap_fixed<IntegerWidth[35]+FractionalWidth[35],IntegerWidth[35]> Custom_ap_fixed_T_35;
typedef ap_fixed<IntegerWidth[36]+FractionalWidth[36],IntegerWidth[36]> Custom_ap_fixed_T_36;
typedef ap_fixed<IntegerWidth[37]+FractionalWidth[37],IntegerWidth[37]> Custom_ap_fixed_T_37;
typedef ap_fixed<IntegerWidth[38]+FractionalWidth[38],IntegerWidth[38]> Custom_ap_fixed_T_38;
typedef ap_fixed<IntegerWidth[39]+FractionalWidth[39],IntegerWidth[39]> Custom_ap_fixed_T_39;
