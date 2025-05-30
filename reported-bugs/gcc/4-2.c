// --seed 0x4d2d1ea5 --data_length 8 --sequence_length 63 --root vfloat64m1_t --segment 
// scheduling mode: unit 
#include <riscv_vector.h>

#define dataLen 8
#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & 0x03FF))
#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & 0x007FFFFF))
#define isNaNF64UI( a ) (((~(a) & UINT64_C( 0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF )))
typedef _Float16 float16_t;
typedef float float32_t;
typedef double float64_t;

float16_t convert_binary_u16_f16(uint16_t u16){
  union { float16_t f16; uint16_t u16; } converter;
  converter.u16 = u16;
  if(isNaNF16UI(converter.u16)) return 0;
  return converter.f16;
}
float32_t convert_binary_u32_f32(uint32_t u32){
  union { float32_t f32; uint32_t u32; } converter;
  converter.u32 = u32;
  if(isNaNF32UI(converter.u32)) return 0;
  return converter.f32;
}
float64_t convert_binary_u64_f64(uint64_t u64){
  union { float64_t f64; uint64_t u64; } converter;
  converter.u64 = u64;
  if(isNaNF64UI(converter.u64)) return 0;
  return converter.f64;
}
uint16_t convert_binary_f16_u16(float16_t f16){
  union { float16_t f16; uint16_t u16; } converter;
  converter.f16 = f16;
  return converter.u16;
}
uint32_t convert_binary_f32_u32(float32_t f32){
  union { float32_t f32; uint32_t u32; } converter;
  converter.f32 = f32;
  return converter.u32;
}
uint64_t convert_binary_f64_u64(float64_t f64){
  union { float64_t f64; uint64_t u64; } converter;
  converter.f64 = f64;
  return converter.u64;
}

int8_t data_mask[dataLen];
int8_t data_load_0[dataLen];
int8_t data_load_1[dataLen];
float32_t data_load_10[dataLen];
int32_t data_load_11[dataLen];
int32_t data_load_12[dataLen];
int16_t data_load_13[dataLen];
uint8_t data_load_14[dataLen];
uint64_t data_load_15[dataLen];
float16_t data_load_16[dataLen];
float16_t data_load_17[dataLen];
int16_t data_load_18[dataLen];
float64_t data_load_19[dataLen];
int16_t data_load_2[dataLen];
uint8_t data_load_20[dataLen];
float16_t data_load_21[dataLen];
int8_t data_load_22[dataLen];
int8_t data_load_23[dataLen];
uint16_t data_load_24[dataLen];
float16_t data_load_25[dataLen];
uint16_t data_load_26[dataLen];
uint64_t data_load_27[dataLen];
float16_t data_load_28[dataLen];
float16_t data_load_29[dataLen];
float64_t data_load_3[dataLen];
int8_t data_load_30[dataLen];
uint16_t data_load_31[dataLen];
int64_t data_load_32[dataLen];
int64_t data_load_33[dataLen];
float32_t data_load_34[dataLen];
int8_t data_load_35[dataLen];
int32_t data_load_36[dataLen];
int32_t data_load_37[dataLen];
int32_t data_load_38[dataLen];
int32_t data_load_39[dataLen];
int32_t data_load_4[dataLen];
float32_t data_load_40[dataLen];
uint8_t data_load_41[dataLen];
uint8_t data_load_42[dataLen];
float64_t data_load_43[dataLen];
int8_t data_load_44[dataLen];
float64_t data_load_45[dataLen];
float16_t data_load_46[dataLen];
int64_t data_load_47[dataLen];
uint8_t data_load_48[dataLen];
uint8_t data_load_49[dataLen];
float32_t data_load_5[dataLen];
uint16_t data_load_50[dataLen];
uint16_t data_load_51[dataLen];
float16_t data_load_52[dataLen];
int64_t data_load_53[dataLen];
int64_t data_load_54[dataLen];
uint32_t data_load_55[dataLen];
float32_t data_load_6[dataLen];
uint8_t data_load_7[dataLen];
int64_t data_load_8[dataLen];
float32_t data_load_9[dataLen];
uint8_t data_store_vreg_0[dataLen];
int8_t data_store_vreg_1[dataLen];
int8_t data_store_vreg_10[dataLen];
uint8_t data_store_vreg_11[dataLen];
float16_t data_store_vreg_12[dataLen];
uint32_t data_store_vreg_13[dataLen];
float16_t data_store_vreg_14[dataLen];
uint8_t data_store_vreg_15[dataLen];
float16_t data_store_vreg_16[dataLen];
int8_t data_store_vreg_17[dataLen];
int32_t data_store_vreg_18[dataLen];
uint8_t data_store_vreg_19[dataLen];
float32_t data_store_vreg_2[dataLen];
float64_t data_store_vreg_20[dataLen];
int16_t data_store_vreg_21[dataLen];
float16_t data_store_vreg_22[dataLen];
uint8_t data_store_vreg_23[dataLen];
uint16_t data_store_vreg_24[dataLen];
float16_t data_store_vreg_25[dataLen];
uint32_t data_store_vreg_26[dataLen];
int32_t data_store_vreg_27[dataLen];
uint32_t data_store_vreg_28[dataLen];
float32_t data_store_vreg_29[dataLen];
uint8_t data_store_vreg_3[dataLen];
float32_t data_store_vreg_4[dataLen];
int32_t data_store_vreg_5[dataLen];
int8_t data_store_vreg_6[dataLen];
uint64_t data_store_vreg_7[dataLen];
uint16_t data_store_vreg_8[dataLen];
float64_t data_store_vreg_9[dataLen];
int32_t data_store_vreg_memory_11[dataLen];
float16_t data_store_vreg_memory_16[dataLen];
float16_t data_store_vreg_memory_17[dataLen];
int16_t data_store_vreg_memory_18[dataLen];
int16_t data_store_vreg_memory_2[dataLen];
float16_t data_store_vreg_memory_21[dataLen];
uint64_t data_store_vreg_memory_27[dataLen];
float64_t data_store_vreg_memory_3[dataLen];
int8_t data_store_vreg_memory_30[dataLen];
float32_t data_store_vreg_memory_34[dataLen];
int32_t data_store_vreg_memory_4[dataLen];
int64_t data_store_vreg_memory_53[dataLen];
int64_t data_store_vreg_memory_8[dataLen];
float32_t data_store_vreg_memory_9[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 1, 1, 1, 1, 0, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  int8_t tmp_0[dataLen] = {-79, -81, -41, -41, -6, 45, -74, 80, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  int8_t tmp_1[dataLen] = {-26, -123, -105, -41, -10, -88, -99, -114, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint32_t tmp_2[dataLen] = {1177235425u, 1394165790u, 2633620714u, 3968366965u, 2099544135u, 4125897250u, 1407802857u, 739435199u, };
  for (int i = 0; i < dataLen; ++i) { data_load_10[i] = convert_binary_u32_f32(tmp_2[i]); }
  int32_t tmp_3[dataLen] = {-1671527460, -494796334, 411727750, 1218625159, -619041655, 2060679654, 939731756, -1503023624, };
  for (int i = 0; i < dataLen; ++i) { data_load_11[i] = tmp_3[i]; }
  int32_t tmp_4[dataLen] = {-1092699106, -1253600392, 2026838740, -1631660865, 1403814303, -1346433436, 1771716093, -670909679, };
  for (int i = 0; i < dataLen; ++i) { data_load_12[i] = tmp_4[i]; }
  int16_t tmp_5[dataLen] = {-24190, 8724, -20447, 11857, -6596, -117, -21449, -15690, };
  for (int i = 0; i < dataLen; ++i) { data_load_13[i] = tmp_5[i]; }
  uint8_t tmp_6[dataLen] = {202, 192, 132, 66, 157, 150, 131, 123, };
  for (int i = 0; i < dataLen; ++i) { data_load_14[i] = tmp_6[i]; }
  uint64_t tmp_7[dataLen] = {447588717ull, 2669865342ull, 1946744069ull, 1037527395ull, 1456229080ull, 252392956ull, 1260032867ull, 2008189264ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_15[i] = tmp_7[i]; }
  uint16_t tmp_8[dataLen] = {20998, 45046, 24227, 18869, 39887, 50168, 36081, 58767, };
  for (int i = 0; i < dataLen; ++i) { data_load_16[i] = convert_binary_u16_f16(tmp_8[i]); }
  uint16_t tmp_9[dataLen] = {43004, 46781, 33322, 47295, 26355, 49092, 8037, 58105, };
  for (int i = 0; i < dataLen; ++i) { data_load_17[i] = convert_binary_u16_f16(tmp_9[i]); }
  int16_t tmp_10[dataLen] = {-547, -28466, 24781, 13630, 32194, -23961, -15077, 25278, };
  for (int i = 0; i < dataLen; ++i) { data_load_18[i] = tmp_10[i]; }
  uint64_t tmp_11[dataLen] = {2446954281ull, 2146946301ull, 3477810755ull, 3802486675ull, 22900564ull, 2978715108ull, 877801123ull, 721042142ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_19[i] = convert_binary_u64_f64(tmp_11[i]); }
  int16_t tmp_12[dataLen] = {6901, 9285, 4611, -3529, 21101, 18126, -15582, 7933, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = tmp_12[i]; }
  uint8_t tmp_13[dataLen] = {0, 125, 47, 144, 195, 220, 44, 182, };
  for (int i = 0; i < dataLen; ++i) { data_load_20[i] = tmp_13[i]; }
  uint16_t tmp_14[dataLen] = {60028, 3747, 35827, 40375, 45943, 19370, 17587, 3635, };
  for (int i = 0; i < dataLen; ++i) { data_load_21[i] = convert_binary_u16_f16(tmp_14[i]); }
  int8_t tmp_15[dataLen] = {-42, -48, 56, 62, 33, -75, -43, 80, };
  for (int i = 0; i < dataLen; ++i) { data_load_22[i] = tmp_15[i]; }
  int8_t tmp_16[dataLen] = {-18, -75, -128, 81, -78, -111, 127, 35, };
  for (int i = 0; i < dataLen; ++i) { data_load_23[i] = tmp_16[i]; }
  uint16_t tmp_17[dataLen] = {3340, 59803, 43083, 49937, 65465, 4223, 58677, 24645, };
  for (int i = 0; i < dataLen; ++i) { data_load_24[i] = tmp_17[i]; }
  uint16_t tmp_18[dataLen] = {1422, 39275, 21682, 42792, 33651, 14615, 61505, 46152, };
  for (int i = 0; i < dataLen; ++i) { data_load_25[i] = convert_binary_u16_f16(tmp_18[i]); }
  uint16_t tmp_19[dataLen] = {52168, 50993, 56818, 7088, 61257, 29802, 13594, 44684, };
  for (int i = 0; i < dataLen; ++i) { data_load_26[i] = tmp_19[i]; }
  uint64_t tmp_20[dataLen] = {3698155222ull, 2554363811ull, 2227119580ull, 2125351086ull, 3608049711ull, 680637549ull, 4138567112ull, 2897067142ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_27[i] = tmp_20[i]; }
  uint16_t tmp_21[dataLen] = {50695, 47240, 37810, 32464, 33650, 58115, 16100, 64979, };
  for (int i = 0; i < dataLen; ++i) { data_load_28[i] = convert_binary_u16_f16(tmp_21[i]); }
  uint16_t tmp_22[dataLen] = {20466, 21632, 32424, 54256, 40054, 60536, 19232, 5266, };
  for (int i = 0; i < dataLen; ++i) { data_load_29[i] = convert_binary_u16_f16(tmp_22[i]); }
  uint64_t tmp_23[dataLen] = {2246297721ull, 3343570722ull, 2395799870ull, 1841460047ull, 105641098ull, 1935162974ull, 368351123ull, 3108495102ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = convert_binary_u64_f64(tmp_23[i]); }
  int8_t tmp_24[dataLen] = {1, 1, 1, 1, 1, 1, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_load_30[i] = tmp_24[i]; }
  uint16_t tmp_25[dataLen] = {58138, 10299, 60153, 12907, 12852, 58140, 37421, 899, };
  for (int i = 0; i < dataLen; ++i) { data_load_31[i] = tmp_25[i]; }
  int64_t tmp_26[dataLen] = {8406712251811997899ll, 7456620481597218373ll, 8161445483901092638ll, -7732587836914053487ll, -5045700506168071601ll, 2907326568844365319ll, 7379012511531450092ll, 5152584782572173728ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_32[i] = tmp_26[i]; }
  int64_t tmp_27[dataLen] = {6121995011859240487ll, 1525617404500781040ll, -2331006585757597212ll, -889332860221531139ll, 2771840844918421319ll, 1952571276179571279ll, 1215540027954422436ll, 4242798386872373941ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_33[i] = tmp_27[i]; }
  uint32_t tmp_28[dataLen] = {3338580006u, 551626838u, 1191781050u, 2214969495u, 3900346264u, 6539334u, 3966526881u, 417851468u, };
  for (int i = 0; i < dataLen; ++i) { data_load_34[i] = convert_binary_u32_f32(tmp_28[i]); }
  int8_t tmp_29[dataLen] = {-58, 103, 117, 76, -45, -58, 67, -97, };
  for (int i = 0; i < dataLen; ++i) { data_load_35[i] = tmp_29[i]; }
  int32_t tmp_30[dataLen] = {384013363, 996552223, -312740477, 1438326715, 1394732086, -713445601, -1116734318, -815528378, };
  for (int i = 0; i < dataLen; ++i) { data_load_36[i] = tmp_30[i]; }
  int32_t tmp_31[dataLen] = {-615979422, -1113289223, 932694170, -1694450577, 39945765, -903935103, 196295215, -541707174, };
  for (int i = 0; i < dataLen; ++i) { data_load_37[i] = tmp_31[i]; }
  int32_t tmp_32[dataLen] = {-1990292426, 1373210038, 1156344262, 546261153, -243573113, 546455197, -1328951575, -1023948343, };
  for (int i = 0; i < dataLen; ++i) { data_load_38[i] = tmp_32[i]; }
  int32_t tmp_33[dataLen] = {169862437, 1735273156, -335330388, -1422593093, -546176888, 1835415519, 878504785, -1265774208, };
  for (int i = 0; i < dataLen; ++i) { data_load_39[i] = tmp_33[i]; }
  int32_t tmp_34[dataLen] = {-2031059036, -1735305891, 1018914483, 1784824301, -1498201869, 1754001056, 1325688372, 309213221, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = tmp_34[i]; }
  uint32_t tmp_35[dataLen] = {3081376547u, 3435282946u, 545701844u, 4268783342u, 668708028u, 232774334u, 2046723649u, 1835363070u, };
  for (int i = 0; i < dataLen; ++i) { data_load_40[i] = convert_binary_u32_f32(tmp_35[i]); }
  uint8_t tmp_36[dataLen] = {90, 172, 233, 133, 208, 131, 193, 114, };
  for (int i = 0; i < dataLen; ++i) { data_load_41[i] = tmp_36[i]; }
  uint8_t tmp_37[dataLen] = {9, 102, 253, 237, 67, 85, 249, 251, };
  for (int i = 0; i < dataLen; ++i) { data_load_42[i] = tmp_37[i]; }
  uint64_t tmp_38[dataLen] = {2750655623ull, 385371478ull, 2635246451ull, 3596310385ull, 2416018429ull, 1043487414ull, 1690519764ull, 2872931245ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_43[i] = convert_binary_u64_f64(tmp_38[i]); }
  int8_t tmp_39[dataLen] = {-127, 83, -106, 109, 26, -22, -69, -80, };
  for (int i = 0; i < dataLen; ++i) { data_load_44[i] = tmp_39[i]; }
  uint64_t tmp_40[dataLen] = {4053944528ull, 2902793360ull, 2055001996ull, 4132551403ull, 614129300ull, 47946801ull, 2776615136ull, 2908170238ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_45[i] = convert_binary_u64_f64(tmp_40[i]); }
  uint16_t tmp_41[dataLen] = {15313, 51934, 64070, 55564, 12003, 12760, 45314, 40939, };
  for (int i = 0; i < dataLen; ++i) { data_load_46[i] = convert_binary_u16_f16(tmp_41[i]); }
  int64_t tmp_42[dataLen] = {3239275562033606378ll, 6815745558777000324ll, -1311352255175161886ll, 543103538781981137ll, -7714606517761981570ll, 6226220985617172601ll, 2707740666923393986ll, -5152647198539306057ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_47[i] = tmp_42[i]; }
  uint8_t tmp_43[dataLen] = {218, 136, 22, 170, 153, 90, 81, 71, };
  for (int i = 0; i < dataLen; ++i) { data_load_48[i] = tmp_43[i]; }
  uint8_t tmp_44[dataLen] = {218, 103, 171, 194, 83, 130, 146, 63, };
  for (int i = 0; i < dataLen; ++i) { data_load_49[i] = tmp_44[i]; }
  uint32_t tmp_45[dataLen] = {1315784191u, 1411564355u, 1332379792u, 709453501u, 3709828755u, 143754723u, 156303981u, 1867514421u, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = convert_binary_u32_f32(tmp_45[i]); }
  uint16_t tmp_46[dataLen] = {39699, 6504, 26556, 42669, 64189, 42885, 64126, 57542, };
  for (int i = 0; i < dataLen; ++i) { data_load_50[i] = tmp_46[i]; }
  uint16_t tmp_47[dataLen] = {47507, 35522, 7601, 30067, 2860, 40199, 37903, 6547, };
  for (int i = 0; i < dataLen; ++i) { data_load_51[i] = tmp_47[i]; }
  uint16_t tmp_48[dataLen] = {24503, 22051, 44971, 58027, 43242, 22661, 42981, 33005, };
  for (int i = 0; i < dataLen; ++i) { data_load_52[i] = convert_binary_u16_f16(tmp_48[i]); }
  int64_t tmp_49[dataLen] = {-2619000507079106237ll, 7010779390353658105ll, -2612804614019328869ll, 215234153557600443ll, 1804629805400771250ll, -7573109621625475229ll, -615936540807871321ll, 7851715829478957694ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_53[i] = tmp_49[i]; }
  int64_t tmp_50[dataLen] = {-5644971804477457287ll, 3878420055933517646ll, -1698423611444021608ll, -2388049001219953061ll, 576475437623693345ll, 4928145326586363555ll, 3052914688123589820ll, 9085069235679813999ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_54[i] = tmp_50[i]; }
  uint32_t tmp_51[dataLen] = {398516105u, 1562850928u, 949421120u, 2497298987u, 3871544159u, 273699986u, 321917492u, 600593313u, };
  for (int i = 0; i < dataLen; ++i) { data_load_55[i] = tmp_51[i]; }
  uint32_t tmp_52[dataLen] = {968417191u, 3472403541u, 1127837238u, 1978737026u, 222248536u, 753978558u, 2756085869u, 382510680u, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = convert_binary_u32_f32(tmp_52[i]); }
  uint8_t tmp_53[dataLen] = {33, 117, 75, 98, 49, 46, 117, 19, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = tmp_53[i]; }
  int64_t tmp_54[dataLen] = {-4873116811719128953ll, -4633114920152817438ll, -7285414308614282535ll, 6431841128474116477ll, -1784182033134759661ll, -3896436532836926787ll, -7934702157059764137ll, -4462759914561194487ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_8[i] = tmp_54[i]; }
  uint32_t tmp_55[dataLen] = {2955596908u, 4035860957u, 2010428799u, 2812248784u, 3881044471u, 2254014502u, 4150781953u, 1307359494u, };
  for (int i = 0; i < dataLen; ++i) { data_load_9[i] = convert_binary_u32_f32(tmp_55[i]); }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_10[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_11[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_12[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_13[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_14[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_15[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_16[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_17[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_18[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_19[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_20[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_21[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_22[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_23[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_24[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_25[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_26[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_27[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_28[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_29[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_4[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_5[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_6[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_7[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_8[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_9[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_11[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_16[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_17[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_18[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_21[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_27[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_30[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_34[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_4[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_53[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_8[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_9[i] = 0; }
}

void CodeBlock_0() {
  int avl2 = dataLen;
  int8_t* ptr_mask = data_mask;
  int8_t* ptr_load_0 = data_load_0;
  int8_t* ptr_load_1 = data_load_1;
  float32_t* ptr_load_10 = data_load_10;
  int32_t* ptr_load_11 = data_load_11;
  int32_t* ptr_load_12 = data_load_12;
  int16_t* ptr_load_13 = data_load_13;
  uint8_t* ptr_load_14 = data_load_14;
  uint64_t* ptr_load_15 = data_load_15;
  float16_t* ptr_load_16 = data_load_16;
  float16_t* ptr_load_17 = data_load_17;
  int16_t* ptr_load_18 = data_load_18;
  float64_t* ptr_load_19 = data_load_19;
  int16_t* ptr_load_2 = data_load_2;
  uint8_t* ptr_load_20 = data_load_20;
  float16_t* ptr_load_21 = data_load_21;
  int8_t* ptr_load_22 = data_load_22;
  int8_t* ptr_load_23 = data_load_23;
  uint16_t* ptr_load_24 = data_load_24;
  float16_t* ptr_load_25 = data_load_25;
  uint16_t* ptr_load_26 = data_load_26;
  uint64_t* ptr_load_27 = data_load_27;
  float16_t* ptr_load_28 = data_load_28;
  float16_t* ptr_load_29 = data_load_29;
  float64_t* ptr_load_3 = data_load_3;
  int8_t* ptr_load_30 = data_load_30;
  uint16_t* ptr_load_31 = data_load_31;
  int64_t* ptr_load_32 = data_load_32;
  int64_t* ptr_load_33 = data_load_33;
  float32_t* ptr_load_34 = data_load_34;
  int8_t* ptr_load_35 = data_load_35;
  int32_t* ptr_load_36 = data_load_36;
  int32_t* ptr_load_37 = data_load_37;
  int32_t* ptr_load_38 = data_load_38;
  int32_t* ptr_load_39 = data_load_39;
  int32_t* ptr_load_4 = data_load_4;
  float32_t* ptr_load_40 = data_load_40;
  uint8_t* ptr_load_41 = data_load_41;
  uint8_t* ptr_load_42 = data_load_42;
  float64_t* ptr_load_43 = data_load_43;
  int8_t* ptr_load_44 = data_load_44;
  float64_t* ptr_load_45 = data_load_45;
  float16_t* ptr_load_46 = data_load_46;
  int64_t* ptr_load_47 = data_load_47;
  uint8_t* ptr_load_48 = data_load_48;
  uint8_t* ptr_load_49 = data_load_49;
  float32_t* ptr_load_5 = data_load_5;
  uint16_t* ptr_load_50 = data_load_50;
  uint16_t* ptr_load_51 = data_load_51;
  float16_t* ptr_load_52 = data_load_52;
  int64_t* ptr_load_53 = data_load_53;
  int64_t* ptr_load_54 = data_load_54;
  uint32_t* ptr_load_55 = data_load_55;
  float32_t* ptr_load_6 = data_load_6;
  uint8_t* ptr_load_7 = data_load_7;
  int64_t* ptr_load_8 = data_load_8;
  float32_t* ptr_load_9 = data_load_9;
  uint8_t* ptr_store_vreg_0 = data_store_vreg_0;
  int8_t* ptr_store_vreg_1 = data_store_vreg_1;
  int8_t* ptr_store_vreg_10 = data_store_vreg_10;
  uint8_t* ptr_store_vreg_11 = data_store_vreg_11;
  float16_t* ptr_store_vreg_12 = data_store_vreg_12;
  uint32_t* ptr_store_vreg_13 = data_store_vreg_13;
  float16_t* ptr_store_vreg_14 = data_store_vreg_14;
  uint8_t* ptr_store_vreg_15 = data_store_vreg_15;
  float16_t* ptr_store_vreg_16 = data_store_vreg_16;
  int8_t* ptr_store_vreg_17 = data_store_vreg_17;
  int32_t* ptr_store_vreg_18 = data_store_vreg_18;
  uint8_t* ptr_store_vreg_19 = data_store_vreg_19;
  float32_t* ptr_store_vreg_2 = data_store_vreg_2;
  float64_t* ptr_store_vreg_20 = data_store_vreg_20;
  int16_t* ptr_store_vreg_21 = data_store_vreg_21;
  float16_t* ptr_store_vreg_22 = data_store_vreg_22;
  uint8_t* ptr_store_vreg_23 = data_store_vreg_23;
  uint16_t* ptr_store_vreg_24 = data_store_vreg_24;
  float16_t* ptr_store_vreg_25 = data_store_vreg_25;
  uint32_t* ptr_store_vreg_26 = data_store_vreg_26;
  int32_t* ptr_store_vreg_27 = data_store_vreg_27;
  uint32_t* ptr_store_vreg_28 = data_store_vreg_28;
  float32_t* ptr_store_vreg_29 = data_store_vreg_29;
  uint8_t* ptr_store_vreg_3 = data_store_vreg_3;
  float32_t* ptr_store_vreg_4 = data_store_vreg_4;
  int32_t* ptr_store_vreg_5 = data_store_vreg_5;
  int8_t* ptr_store_vreg_6 = data_store_vreg_6;
  uint64_t* ptr_store_vreg_7 = data_store_vreg_7;
  uint16_t* ptr_store_vreg_8 = data_store_vreg_8;
  float64_t* ptr_store_vreg_9 = data_store_vreg_9;
  int32_t* ptr_store_vreg_memory_11 = data_store_vreg_memory_11;
  float16_t* ptr_store_vreg_memory_16 = data_store_vreg_memory_16;
  float16_t* ptr_store_vreg_memory_17 = data_store_vreg_memory_17;
  int16_t* ptr_store_vreg_memory_18 = data_store_vreg_memory_18;
  int16_t* ptr_store_vreg_memory_2 = data_store_vreg_memory_2;
  float16_t* ptr_store_vreg_memory_21 = data_store_vreg_memory_21;
  uint64_t* ptr_store_vreg_memory_27 = data_store_vreg_memory_27;
  float64_t* ptr_store_vreg_memory_3 = data_store_vreg_memory_3;
  int8_t* ptr_store_vreg_memory_30 = data_store_vreg_memory_30;
  float32_t* ptr_store_vreg_memory_34 = data_store_vreg_memory_34;
  int32_t* ptr_store_vreg_memory_4 = data_store_vreg_memory_4;
  int64_t* ptr_store_vreg_memory_53 = data_store_vreg_memory_53;
  int64_t* ptr_store_vreg_memory_8 = data_store_vreg_memory_8;
  float32_t* ptr_store_vreg_memory_9 = data_store_vreg_memory_9;
  for (size_t vl; avl2 > 0; avl2 -= vl){
    vl = __riscv_vsetvl_e64m1(avl2);
    vint8mf8_t mask_value= __riscv_vle8_v_i8mf8(ptr_mask, vl);
    vbool64_t vmask= __riscv_vmseq_vx_i8mf8_b64(mask_value, 1, vl);
    vint8mf4_t vload_tmp_0 = __riscv_vle8_v_i8mf4(ptr_load_0, vl);
    vbool32_t vreg_memory_0 = __riscv_vmseq_vx_i8mf4_b32(vload_tmp_0, 1, vl);
    vuint8m1_t vreg_0 = __riscv_vreinterpret_v_b32_u8m1(vreg_memory_0);
    vint8mf8_t vload_tmp_1 = __riscv_vle8_v_i8mf8(ptr_load_1, vl);
    vbool64_t vreg_memory_1 = __riscv_vmseq_vx_i8mf8_b64(vload_tmp_1, 1, vl);
    vbool64_t vreg_1 = __riscv_vmxor_mm_b64(vreg_memory_1, vreg_memory_1, vl);
    vint8mf8_t zero_2 = __riscv_vmv_v_x_i8mf8(0, __riscv_vsetvlmax_e8mf8());
    vint8mf8_t vstore_tmp_2 = __riscv_vmerge_vxm_i8mf8(zero_2, 1, vreg_1, vl);
    __riscv_vse8_v_i8mf8(ptr_store_vreg_1, vstore_tmp_2, vl);
    vint16mf4_t vreg_memory_2 = __riscv_vlse16_v_i16mf4_m(vmask, ptr_load_2, 2, vl);
    vreg_memory_2 = __riscv_vsub_vv_i16mf4(vreg_memory_2, vreg_memory_2, vl);
    vuint32mf2_t idx_1 = __riscv_vsll_vx_u32mf2(__riscv_vid_v_u32mf2(vl), 1, vl);
    __riscv_vsoxei32_v_i16mf4(ptr_store_vreg_memory_2, idx_1, vreg_memory_2, vl);
    vfloat64m1_t vreg_memory_3 = __riscv_vlse64_v_f64m1_m(vmask, ptr_load_3, 8, vl);
    vreg_memory_3 = __riscv_vfdiv_vf_f64m1_rm(vreg_memory_3, convert_binary_u64_f64(6647ull), __RISCV_FRM_RNE, vl);
    __riscv_vse64_v_f64m1(ptr_store_vreg_memory_3, vreg_memory_3, vl);
    vint32mf2_t vreg_memory_4 = __riscv_vle32_v_i32mf2(ptr_load_4, vl);
    vreg_memory_4 = __riscv_vwadd_wx_i32mf2_m(vmask, vreg_memory_4, 12111, vl);
    vuint16mf4_t idx_3 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 2, vl);
    __riscv_vsuxei16_v_i32mf2(ptr_store_vreg_memory_4, idx_3, vreg_memory_4, vl);
    vfloat32mf2_t vreg_memory_5 = __riscv_vle32_v_f32mf2_m(vmask, ptr_load_5, vl);
    vfloat32mf2_t vreg_memory_6 = __riscv_vle32_v_f32mf2_m(vmask, ptr_load_6, vl);
    vfloat32mf2_t vreg_2 = __riscv_vfnmacc_vv_f32mf2_m(vmask, vreg_memory_5, vreg_memory_6, vreg_memory_6, vl);
    vuint8mf8_t idx_5 = __riscv_vsll_vx_u8mf8(__riscv_vid_v_u8mf8(vl), 2, vl);
    __riscv_vsuxei8_v_f32mf2(ptr_store_vreg_2, idx_5, vreg_2, vl);
    vuint8m8_t vreg_memory_7 = __riscv_vle8_v_u8m8(ptr_load_7, vl);
    vuint8mf4_t vreg_3 = __riscv_vlmul_trunc_v_u8m8_u8mf4(vreg_memory_7);
    __riscv_vse8_v_u8mf4(ptr_store_vreg_3, vreg_3, vl);
    vint64m1_t vreg_memory_8 = __riscv_vle64_v_i64m1(ptr_load_8, vl);
    vreg_memory_8 = __riscv_vmacc_vx_i64m1_m(vmask, vreg_memory_8, 3380410960808392941ll, vreg_memory_8, vl);
    __riscv_vsse64_v_i64m1(ptr_store_vreg_memory_8, 8, vreg_memory_8, vl);
    vfloat32mf2_t vreg_memory_9 = __riscv_vle32_v_f32mf2(ptr_load_9, vl);
    vfloat32m1_t vreg_memory_10 = __riscv_vle32_v_f32m1(ptr_load_10, vl);
    vfloat32m1_t vreg_4 = __riscv_vfredosum_vs_f32mf2_f32m1(vreg_memory_9, vreg_memory_10, vl);
    __riscv_vse32_v_f32m1(ptr_store_vreg_4, vreg_4, vl);
    vint32mf2_t vreg_memory_11 = __riscv_vle32_v_i32mf2(ptr_load_11, vl);
    vint32m1_t vreg_memory_12 = __riscv_vle32_v_i32m1(ptr_load_12, vl);
    vint32m1_t vreg_5 = __riscv_vredand_vs_i32mf2_i32m1(vreg_memory_11, vreg_memory_12, vl);
    __riscv_vse32_v_i32m1(ptr_store_vreg_5, vreg_5, vl);
    vint16m1_t vreg_memory_13 = __riscv_vle16_v_i16m1(ptr_load_13, vl);
    vbool4_t vreg_6 = __riscv_vreinterpret_v_i16m1_b4(vreg_memory_13);
    vint8m2_t zero_3 = __riscv_vmv_v_x_i8m2(0, __riscv_vsetvlmax_e8m2());
    vint8m2_t vstore_tmp_3 = __riscv_vmerge_vxm_i8m2(zero_3, 1, vreg_6, vl);
    __riscv_vse8_v_i8m2(ptr_store_vreg_6, vstore_tmp_3, vl);
    vuint32mf2_t idx_6 = __riscv_vsll_vx_u32mf2(__riscv_vid_v_u32mf2(vl), 0, vl);
    vuint8mf8_t vreg_memory_14 = __riscv_vloxei32_v_u8mf8_m(vmask, ptr_load_14, idx_6, vl);
    vreg_1 = __riscv_vmsgeu_vv_u8mf8_b64_m(vmask, vreg_memory_14, vreg_memory_14, vl);
    vint8mf8_t zero_4 = __riscv_vmv_v_x_i8mf8(0, __riscv_vsetvlmax_e8mf8());
    vint8mf8_t vstore_tmp_4 = __riscv_vmerge_vxm_i8mf8(zero_4, 1, vreg_1, vl);
    __riscv_vse8_v_i8mf8(ptr_store_vreg_1, vstore_tmp_4, vl);
    vuint64m4_t vreg_memory_15 = __riscv_vle64_v_u64m4(ptr_load_15, vl);
    vuint64m2_t vreg_7 = __riscv_vlmul_trunc_v_u64m4_u64m2(vreg_memory_15);
    __riscv_vse64_v_u64m2(ptr_store_vreg_7, vreg_7, vl);
    vfloat16mf4_t vreg_memory_16 = __riscv_vle16_v_f16mf4_m(vmask, ptr_load_16, vl);
    vuint16mf4_t vreg_8 = __riscv_vfclass_v_u16mf4(vreg_memory_16, vl);
    __riscv_vse16_v_u16mf4(ptr_store_vreg_8, vreg_8, vl);
    vreg_memory_16 = __riscv_vfmv_s_f_f16mf4(convert_binary_u16_f16(43830), vl); // sigill
    __riscv_vse16_v_f16mf4(ptr_store_vreg_memory_16, vreg_memory_16, vl);
    vreg_memory_8 = __riscv_vmv_s_x_i64m1(-7934185305375023961ll, vl); // sigill
    __riscv_vse64_v_i64m1(ptr_store_vreg_memory_8, vreg_memory_8, vl);
    
    vfloat16mf4_t vreg_memory_17 = __riscv_vlse16_v_f16mf4(ptr_load_17, 2, vl);
    vreg_memory_17 = __riscv_vfslide1up_vf_f16mf4(vreg_memory_17, convert_binary_u16_f16(54316), vl);
    vuint32mf2_t idx_8 = __riscv_vsll_vx_u32mf2(__riscv_vid_v_u32mf2(vl), 1, vl);
    __riscv_vsoxei32_v_f16mf4(ptr_store_vreg_memory_17, idx_8, vreg_memory_17, vl);
    vreg_memory_2 = __riscv_vmv_s_x_i16mf4(1527, vl);
    __riscv_vse16_v_i16mf4(ptr_store_vreg_memory_2, vreg_memory_2, vl);
    vreg_memory_11 = __riscv_vwsub_wx_i32mf2_m(vmask, vreg_memory_4, -31788, vl);
    __riscv_vsse32_v_i32mf2(ptr_store_vreg_memory_11, 4, vreg_memory_11, vl);
    vuint8mf8_t idx_9 = __riscv_vsll_vx_u8mf8(__riscv_vid_v_u8mf8(vl), 1, vl);
    vint16mf4_t vreg_memory_18 = __riscv_vluxei8_v_i16mf4(ptr_load_18, idx_9, vl);
    vreg_memory_18 = __riscv_vslide1up_vx_i16mf4(vreg_memory_18, -30423, vl);
    __riscv_vse16_v_i16mf4(ptr_store_vreg_memory_18, vreg_memory_18, vl);
    vreg_8 = __riscv_vssubu_vx_u16mf4_m(vmask, vreg_8, 15551, vl);
    vuint64m1_t idx_11 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 1, vl);
    __riscv_vsoxei64_v_u16mf4(ptr_store_vreg_8, idx_11, vreg_8, vl);
    vfloat64m1_t vreg_9 = __riscv_vfwcvt_f_x_v_f64m1(vreg_memory_4, vl);
    __riscv_vsse64_v_f64m1_m(vmask, ptr_store_vreg_9, 8, vreg_9, vl);
    vuint16mf4_t idx_12 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 3, vl);
    vfloat64m1_t vreg_memory_19 = __riscv_vloxei16_v_f64m1(ptr_load_19, idx_12, vl);
    vreg_memory_3 = __riscv_vrgather_vx_f64m1(vreg_memory_19, 2084907685u%vl, vl);
    __riscv_vse64_v_f64m1(ptr_store_vreg_memory_3, vreg_memory_3, vl);
    vreg_2 = __riscv_vfmsub_vf_f32mf2_rm(vreg_memory_9, convert_binary_u32_f32(6099u), vreg_2, __RISCV_FRM_RNE, vl);
    vuint16mf4_t idx_14 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 2, vl);
    __riscv_vsoxei16_v_f32mf2(ptr_store_vreg_2, idx_14, vreg_2, vl);
    vuint16mf4_t idx_15 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 0, vl);
    vuint8mf8_t vreg_memory_20 = __riscv_vloxei16_v_u8mf8(ptr_load_20, idx_15, vl);
    vreg_memory_17 = __riscv_vfwcvt_f_xu_v_f16mf4(vreg_memory_20, vl);
    __riscv_vse16_v_f16mf4(ptr_store_vreg_memory_17, vreg_memory_17, vl);
    vreg_memory_17 = __riscv_vfmacc_vf_f16mf4(vreg_memory_17, convert_binary_u16_f16(8669), vreg_memory_17, vl);
    __riscv_vsse16_v_f16mf4(ptr_store_vreg_memory_17, 2, vreg_memory_17, vl);
    vuint32mf2_t idx_16 = __riscv_vsll_vx_u32mf2(__riscv_vid_v_u32mf2(vl), 1, vl);
    vfloat16mf4_t vreg_memory_21 = __riscv_vloxei32_v_f16mf4(ptr_load_21, idx_16, vl);
    vreg_2 = __riscv_vfwnmsac_vv_f32mf2_rm_m(vmask, vreg_2, vreg_memory_21, vreg_memory_21, __RISCV_FRM_RNE, vl);
    __riscv_vsse32_v_f32mf2_m(vmask, ptr_store_vreg_2, 4, vreg_2, vl);
    vint8m2_t vreg_memory_22 = __riscv_vle8_v_i8m2(ptr_load_22, vl);
    vint8m2_t vreg_memory_23 = __riscv_vle8_v_i8m2(ptr_load_23, vl);
    vint8m4_t vreg_10 = __riscv_vcreate_v_i8m2_i8m4(vreg_memory_22, vreg_memory_23);
    __riscv_vse8_v_i8m4(ptr_store_vreg_10, vreg_10, vl);
    vuint16mf4_t vreg_memory_24 = __riscv_vle16_v_u16mf4(ptr_load_24, vl);
    vuint8mf4_t vreg_11 = __riscv_vreinterpret_v_u16mf4_u8mf4(vreg_memory_24);
    vfloat16m8_t vreg_memory_25 = __riscv_vle16_v_f16m8(ptr_load_25, vl);
    vfloat16mf4_t vreg_12 = __riscv_vlmul_trunc_v_f16m8_f16mf4(vreg_memory_25);
    __riscv_vse16_v_f16mf4(ptr_store_vreg_12, vreg_12, vl);
    vuint16mf4_t idx_17 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 1, vl);
    vuint16mf4_t vreg_memory_26 = __riscv_vluxei16_v_u16mf4(ptr_load_26, idx_17, vl);
    vuint32mf2_t vreg_13 = __riscv_vwaddu_vx_u32mf2(vreg_memory_26, 57110, vl);
    __riscv_vsse32_v_u32mf2(ptr_store_vreg_13, 4, vreg_13, vl);
    vuint64m1_t idx_18 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 3, vl);
    vuint64m1_t vreg_memory_27 = __riscv_vloxei64_v_u64m1(ptr_load_27, idx_18, vl);
    vreg_memory_27 = __riscv_vsub_vv_u64m1_m(vmask, vreg_memory_27, vreg_memory_27, vl);
    __riscv_vsse64_v_u64m1_m(vmask, ptr_store_vreg_memory_27, 8, vreg_memory_27, vl);
    vfloat16mf4_t vreg_memory_28 = __riscv_vlse16_v_f16mf4(ptr_load_28, 2, vl);
    vreg_memory_21 = __riscv_vfneg_v_f16mf4(vreg_memory_28, vl);
    __riscv_vse16_v_f16mf4(ptr_store_vreg_memory_21, vreg_memory_21, vl);

    vreg_1 = __riscv_vmsle_vv_i32mf2_b64(vreg_memory_11, vreg_memory_4, vl);
    vint8mf8_t zero_5 = __riscv_vmv_v_x_i8mf8(0, __riscv_vsetvlmax_e8mf8());
    vint8mf8_t vstore_tmp_5 = __riscv_vmerge_vxm_i8mf8(zero_5, 1, vreg_1, vl);
    __riscv_vse8_v_i8mf8(ptr_store_vreg_1, vstore_tmp_5, vl);
    
    vfloat16mf4_t vreg_memory_29 = __riscv_vle16_v_f16mf4(ptr_load_29, vl);
    vint8mf8_t vload_tmp_6 = __riscv_vle8_v_i8mf8(ptr_load_30, vl);
    vbool64_t vreg_memory_30 = __riscv_vmseq_vx_i8mf8_b64(vload_tmp_6, 1, vl);
    vfloat16mf4_t vreg_14 = __riscv_vcompress_vm_f16mf4(vreg_memory_29, vreg_memory_30, vl);
    __riscv_vse16_v_f16mf4(ptr_store_vreg_14, vreg_14, vl);

    vuint16m1_t vreg_memory_31 = __riscv_vle16_v_u16m1(ptr_load_31, vl);
    vuint8m1_t vreg_15 = __riscv_vreinterpret_v_u16m1_u8m1(vreg_memory_31);
    vuint64m1_t idx_19 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 3, vl);
    vint64m1_t vreg_memory_32 = __riscv_vloxei64_v_i64m1(ptr_load_32, idx_19, vl);
    vuint32mf2_t idx_20 = __riscv_vsll_vx_u32mf2(__riscv_vid_v_u32mf2(vl), 3, vl);
    vint64m1_t vreg_memory_33 = __riscv_vluxei32_v_i64m1(ptr_load_33, idx_20, vl);
    vreg_memory_30 = __riscv_vmsge_vv_i64m1_b64(vreg_memory_32, vreg_memory_33, vl);
    vint8mf8_t zero_7 = __riscv_vmv_v_x_i8mf8(0, __riscv_vsetvlmax_e8mf8());
    vint8mf8_t vstore_tmp_7 = __riscv_vmerge_vxm_i8mf8(zero_7, 1, vreg_memory_30, vl);
    __riscv_vse8_v_i8mf8(ptr_store_vreg_memory_30, vstore_tmp_7, vl);
    
    vreg_memory_11 = __riscv_vfcvt_x_f_v_i32mf2_rm(vreg_memory_9, __RISCV_FRM_RNE, vl);
    __riscv_vse32_v_i32mf2(ptr_store_vreg_memory_11, vreg_memory_11, vl);
    vreg_memory_27 = __riscv_vmulhu_vv_u64m1(vreg_memory_27, vreg_memory_27, vl);
    __riscv_vsse64_v_u64m1(ptr_store_vreg_memory_27, 8, vreg_memory_27, vl);
    vreg_memory_18 = __riscv_vmacc_vx_i16mf4(vreg_memory_18, 27129, vreg_memory_18, vl);
    __riscv_vsse16_v_i16mf4_m(vmask, ptr_store_vreg_memory_18, 2, vreg_memory_18, vl);


    vint8m2_t vreg_memory_35 = __riscv_vle8_v_i8m2(ptr_load_35, vl);
    vint8m4_t vreg_17 = __riscv_vlmul_ext_v_i8m2_i8m4(vreg_memory_35);
    vint32m2_t vreg_memory_36 = __riscv_vle32_v_i32m2(ptr_load_36, vl);
    vint32m2_t vreg_memory_37 = __riscv_vle32_v_i32m2(ptr_load_37, vl);
    vint32m2_t vreg_memory_38 = __riscv_vle32_v_i32m2(ptr_load_38, vl);
    vint32m2_t vreg_memory_39 = __riscv_vle32_v_i32m2(ptr_load_39, vl);
    vint32m8_t vreg_18 = __riscv_vcreate_v_i32m2_i32m8(vreg_memory_36, vreg_memory_37, vreg_memory_38, vreg_memory_39);
    __riscv_vse32_v_i32m8(ptr_store_vreg_18, vreg_18, vl);


    vreg_12 = __riscv_vfrec7_v_f16mf4_m(vmask, vreg_14, vl);
    vuint8mf8_t idx_24 = __riscv_vsll_vx_u8mf8(__riscv_vid_v_u8mf8(vl), 1, vl);
    __riscv_vsoxei8_v_f16mf4(ptr_store_vreg_12, idx_24, vreg_12, vl);
    
    vfloat32mf2_t vreg_memory_40 = __riscv_vlse32_v_f32mf2(ptr_load_40, 4, vl);
    vreg_memory_9 = __riscv_vfnmacc_vv_f32mf2(vreg_memory_5, vreg_memory_5, vreg_memory_40, vl);
    __riscv_vse32_v_f32mf2_m(vmask, ptr_store_vreg_memory_9, vreg_memory_9, vl);

    vuint64m1_t idx_25 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 3, vl);
    vfloat64m1_t vreg_memory_43 = __riscv_vluxei64_v_f64m1_m(vmask, ptr_load_43, idx_25, vl);
    vfloat64m1_t vreg_20 = __riscv_vfdiv_vf_f64m1(vreg_memory_43, convert_binary_u64_f64(10440ull), vl);
    vuint16mf4_t idx_27 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 3, vl);
    __riscv_vsuxei16_v_f64m1_m(vmask, ptr_store_vreg_20, idx_27, vreg_20, vl);

    vint8mf4_t vreg_memory_44 = __riscv_vle8_v_i8mf4(ptr_load_44, vl);
    vint16mf4_t vreg_21 = __riscv_vreinterpret_v_i8mf4_i16mf4(vreg_memory_44);
    vuint64m1_t idx_28 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 3, vl);
    vfloat64m1_t vreg_memory_45 = __riscv_vloxei64_v_f64m1(ptr_load_45, idx_28, vl);
    vreg_memory_3 = __riscv_vfsgnjx_vv_f64m1(vreg_9, vreg_memory_45, vl);
    __riscv_vse64_v_f64m1(ptr_store_vreg_memory_3, vreg_memory_3, vl);

    vreg_memory_9 = __riscv_vfmadd_vf_f32mf2_m(vmask, vreg_2, convert_binary_u32_f32(33902u), vreg_memory_9, vl);
    vuint64m1_t idx_30 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 2, vl);
    __riscv_vsoxei64_v_f32mf2_m(vmask, ptr_store_vreg_memory_9, idx_30, vreg_memory_9, vl);

    vuint32mf2_t idx_34 = __riscv_vsll_vx_u32mf2(__riscv_vid_v_u32mf2(vl), 1, vl);
    vuint16mf4_t vreg_memory_50 = __riscv_vluxei32_v_u16mf4(ptr_load_50, idx_34, vl);
    vuint16mf4_t vreg_memory_51 = __riscv_vle16_v_u16mf4(ptr_load_51, vl);
    vreg_memory_51 = __riscv_vremu_vx_u16mf4(vreg_memory_51, (uint16_t)(vl), vl);
    vuint16mf4_t vreg_24 = __riscv_vrgatherei16_vv_u16mf4(vreg_memory_50, vreg_memory_51, vl);
    __riscv_vse16_v_u16mf4(ptr_store_vreg_24, vreg_24, vl);




    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_10 += vl;
    ptr_load_11 += vl;
    ptr_load_12 += vl;
    ptr_load_13 += vl;
    ptr_load_14 += vl;
    ptr_load_15 += vl;
    ptr_load_16 += vl;
    ptr_load_17 += vl;
    ptr_load_18 += vl;
    ptr_load_19 += vl;
    ptr_load_2 += vl;
    ptr_load_20 += vl;
    ptr_load_21 += vl;
    ptr_load_22 += vl;
    ptr_load_23 += vl;
    ptr_load_24 += vl;
    ptr_load_25 += vl;
    ptr_load_26 += vl;
    ptr_load_27 += vl;
    ptr_load_28 += vl;
    ptr_load_29 += vl;
    ptr_load_3 += vl;
    ptr_load_30 += vl;
    ptr_load_31 += vl;
    ptr_load_32 += vl;
    ptr_load_33 += vl;
    ptr_load_34 += vl;
    ptr_load_35 += vl;
    ptr_load_36 += vl;
    ptr_load_37 += vl;
    ptr_load_38 += vl;
    ptr_load_39 += vl;
    ptr_load_4 += vl;
    ptr_load_40 += vl;
    ptr_load_41 += vl;
    ptr_load_42 += vl;
    ptr_load_43 += vl;
    ptr_load_44 += vl;
    ptr_load_45 += vl;
    ptr_load_46 += vl;
    ptr_load_47 += vl;
    ptr_load_48 += vl;
    ptr_load_49 += vl;
    ptr_load_5 += vl;
    ptr_load_50 += vl;
    ptr_load_51 += vl;
    ptr_load_52 += vl;
    ptr_load_53 += vl;
    ptr_load_54 += vl;
    ptr_load_55 += vl;
    ptr_load_6 += vl;
    ptr_load_7 += vl;
    ptr_load_8 += vl;
    ptr_load_9 += vl;
    ptr_store_vreg_0 += vl;
    ptr_store_vreg_1 += vl;
    ptr_store_vreg_10 += vl;
    ptr_store_vreg_11 += vl;
    ptr_store_vreg_12 += vl;
    ptr_store_vreg_13 += vl;
    ptr_store_vreg_14 += vl;
    ptr_store_vreg_15 += vl;
    ptr_store_vreg_16 += vl;
    ptr_store_vreg_17 += vl;
    ptr_store_vreg_18 += vl;
    ptr_store_vreg_19 += vl;
    ptr_store_vreg_2 += vl;
    ptr_store_vreg_20 += vl;
    ptr_store_vreg_21 += vl;
    ptr_store_vreg_22 += vl;
    ptr_store_vreg_23 += vl;
    ptr_store_vreg_24 += vl;
    ptr_store_vreg_25 += vl;
    ptr_store_vreg_26 += vl;
    ptr_store_vreg_27 += vl;
    ptr_store_vreg_28 += vl;
    ptr_store_vreg_29 += vl;
    ptr_store_vreg_3 += vl;
    ptr_store_vreg_4 += vl;
    ptr_store_vreg_5 += vl;
    ptr_store_vreg_6 += vl;
    ptr_store_vreg_7 += vl;
    ptr_store_vreg_8 += vl;
    ptr_store_vreg_9 += vl;
    ptr_store_vreg_memory_11 += vl;
    ptr_store_vreg_memory_16 += vl;
    ptr_store_vreg_memory_17 += vl;
    ptr_store_vreg_memory_18 += vl;
    ptr_store_vreg_memory_2 += vl;
    ptr_store_vreg_memory_21 += vl;
    ptr_store_vreg_memory_27 += vl;
    ptr_store_vreg_memory_3 += vl;
    ptr_store_vreg_memory_30 += vl;
    ptr_store_vreg_memory_34 += vl;
    ptr_store_vreg_memory_4 += vl;
    ptr_store_vreg_memory_53 += vl;
    ptr_store_vreg_memory_8 += vl;
    ptr_store_vreg_memory_9 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_10[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_12[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_13[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_14[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_16[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_18[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<1; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_19[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_2[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_20[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_22[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_23[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_24[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_25[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_26[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_27[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_28[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_29[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_3[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<1; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_4[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<1; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_5[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_6[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_7[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_8[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_9[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_11[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<1; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_memory_16[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_memory_17[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_18[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<1; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_2[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_memory_21[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_memory_27[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_memory_3[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_30[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_memory_34[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_4[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<1; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_memory_53[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<1; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_memory_8[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_memory_9[i])); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

