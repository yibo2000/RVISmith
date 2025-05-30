// --seed 0xc54f4817 --data_length 9 --sequence_length 10 --root vbool2_t --segment  --policy 
// scheduling mode: unit 
#include <riscv_vector.h>

#define dataLen 9
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
  if(isNaNF16UI(converter.u16)) return -1;  return converter.u16;
}
uint32_t convert_binary_f32_u32(float32_t f32){
  union { float32_t f32; uint32_t u32; } converter;
  converter.f32 = f32;
  if(isNaNF32UI(converter.u32)) return -1;  return converter.u32;
}
uint64_t convert_binary_f64_u64(float64_t f64){
  union { float64_t f64; uint64_t u64; } converter;
  converter.f64 = f64;
  if(isNaNF64UI(converter.u64)) return -1;  return converter.u64;
}

int8_t data_mask[dataLen];
int16_t data_load_0[dataLen];
int8_t data_load_1[dataLen];
uint16_t data_load_10[dataLen];
uint16_t data_load_11[dataLen];
int16_t data_load_12[dataLen];
uint16_t data_load_2[dataLen];
uint8_t data_load_3[dataLen];
float32_t data_load_4[dataLen];
float16_t data_load_5[dataLen];
float32_t data_load_6[dataLen];
int16_t data_load_7[dataLen];
int8_t data_load_8[dataLen];
uint16_t data_load_9[dataLen];
int16_t data_store_vreg_0[dataLen];
float32_t data_store_vreg_1[dataLen];
int16_t data_store_vreg_2[dataLen];
int16_t data_store_vreg_3[dataLen];
uint16_t data_store_vreg_4[dataLen];
int16_t data_store_vreg_memory_0[dataLen];
uint16_t data_store_vreg_memory_2[dataLen];
float16_t data_store_vreg_memory_5[dataLen];
int16_t data_store_vreg_memory_7[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 1, 1, 1, 1, 1, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  int16_t tmp_0[dataLen] = {15399, 22610, 22866, -22375, 10457, 19070, -27463, -22697, 10189, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  int8_t tmp_1[dataLen] = {-45, 2, -48, 1, -16, 122, 47, 98, -122, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint16_t tmp_2[dataLen] = {20780, 9303, 54550, 30839, 40196, 58467, 24834, 52486, 6241, };
  for (int i = 0; i < dataLen; ++i) { data_load_10[i] = tmp_2[i]; }
  uint16_t tmp_3[dataLen] = {41279, 1628, 32754, 53755, 20560, 34464, 50950, 35379, 7407, };
  for (int i = 0; i < dataLen; ++i) { data_load_11[i] = tmp_3[i]; }
  int16_t tmp_4[dataLen] = {21119, 3826, 10459, -9825, -32066, -2742, -24974, 14181, 13295, };
  for (int i = 0; i < dataLen; ++i) { data_load_12[i] = tmp_4[i]; }
  uint16_t tmp_5[dataLen] = {57755, 7331, 47779, 56855, 42672, 41664, 62252, 48767, 11713, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = tmp_5[i]; }
  uint8_t tmp_6[dataLen] = {27, 54, 46, 220, 92, 148, 47, 149, 214, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_6[i]; }
  uint32_t tmp_7[dataLen] = {3486422259u, 2293439645u, 1443347057u, 2503096219u, 1142042761u, 2507837783u, 3967194286u, 2095430881u, 152626378u, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = convert_binary_u32_f32(tmp_7[i]); }
  uint16_t tmp_8[dataLen] = {48155, 41866, 34314, 50069, 60896, 40164, 62381, 44573, 5832, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = convert_binary_u16_f16(tmp_8[i]); }
  uint32_t tmp_9[dataLen] = {3413150582u, 1875044594u, 2409956882u, 1599525972u, 3419888531u, 1544654416u, 690034370u, 3524451286u, 1037949328u, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = convert_binary_u32_f32(tmp_9[i]); }
  int16_t tmp_10[dataLen] = {-25254, 20581, 4460, -25548, -17990, 21843, 16495, -1713, -23564, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = tmp_10[i]; }
  int8_t tmp_11[dataLen] = {-104, -74, 39, -6, 46, -41, -99, -126, -60, };
  for (int i = 0; i < dataLen; ++i) { data_load_8[i] = tmp_11[i]; }
  uint16_t tmp_12[dataLen] = {26305, 11539, 33456, 46374, 16524, 46567, 30289, 24068, 16851, };
  for (int i = 0; i < dataLen; ++i) { data_load_9[i] = tmp_12[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_4[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_5[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_7[i] = 0; }
}

void CodeBlock_0() {
  int avl2 = dataLen;
  int8_t* ptr_mask = data_mask;
  int16_t* ptr_load_0 = data_load_0;
  int8_t* ptr_load_1 = data_load_1;
  uint16_t* ptr_load_10 = data_load_10;
  uint16_t* ptr_load_11 = data_load_11;
  int16_t* ptr_load_12 = data_load_12;
  uint16_t* ptr_load_2 = data_load_2;
  uint8_t* ptr_load_3 = data_load_3;
  float32_t* ptr_load_4 = data_load_4;
  float16_t* ptr_load_5 = data_load_5;
  float32_t* ptr_load_6 = data_load_6;
  int16_t* ptr_load_7 = data_load_7;
  int8_t* ptr_load_8 = data_load_8;
  uint16_t* ptr_load_9 = data_load_9;
  int16_t* ptr_store_vreg_0 = data_store_vreg_0;
  float32_t* ptr_store_vreg_1 = data_store_vreg_1;
  int16_t* ptr_store_vreg_2 = data_store_vreg_2;
  int16_t* ptr_store_vreg_3 = data_store_vreg_3;
  uint16_t* ptr_store_vreg_4 = data_store_vreg_4;
  int16_t* ptr_store_vreg_memory_0 = data_store_vreg_memory_0;
  uint16_t* ptr_store_vreg_memory_2 = data_store_vreg_memory_2;
  float16_t* ptr_store_vreg_memory_5 = data_store_vreg_memory_5;
  int16_t* ptr_store_vreg_memory_7 = data_store_vreg_memory_7;
  for (size_t vl; avl2 > 0; avl2 -= vl){
    vl = __riscv_vsetvl_e16m8(avl2);
    vint8m4_t mask_value= __riscv_vle8_v_i8m4(ptr_mask, vl);
    vbool2_t vmask= __riscv_vmseq_vx_i8m4_b2(mask_value, 1, vl);
    vint16m8_t vd_load_0 = __riscv_vmv_v_x_i16m8(0, __riscv_vsetvlmax_e16m8());
    vint16m8_t vreg_memory_0 = __riscv_vle16_v_i16m8_tu(vd_load_0, ptr_load_0, vl);
    vint8m4_t vd_load_1 = __riscv_vmv_v_x_i8m4(0, __riscv_vsetvlmax_e8m4());
    vint8m4_t vreg_memory_1 = __riscv_vlse8_v_i8m4_mu(vmask, vd_load_1, ptr_load_1, 1, vl);
    vreg_memory_0 = __riscv_vsext_vf2_i16m8_mu(vmask, vreg_memory_0, vreg_memory_1, vl);
    __riscv_vse16_v_i16m8(ptr_store_vreg_memory_0, vreg_memory_0, vl);
    vint16m8_t vreg_0 = __riscv_vwmacc_vv_i16m8_mu(vmask, vreg_memory_0, vreg_memory_1, vreg_memory_1, vl);
    __riscv_vsse16_v_i16m8(ptr_store_vreg_0, 2, vreg_0, vl);
    vuint16m8_t vd_load_2 = __riscv_vmv_v_x_u16m8(0, __riscv_vsetvlmax_e16m8());
    vuint16m8_t vreg_memory_2 = __riscv_vle16_v_u16m8_tumu(vmask, vd_load_2, ptr_load_2, vl);
    vuint8m4_t vd_load_3 = __riscv_vmv_v_x_u8m4(0, __riscv_vsetvlmax_e8m4());
    vuint16m8_t idx_0 = __riscv_vsll_vx_u16m8(__riscv_vid_v_u16m8(vl), 0, vl);
    vuint8m4_t vreg_memory_3 = __riscv_vluxei16_v_u8m4_tu(vd_load_3, ptr_load_3, idx_0, vl);
    vreg_memory_2 = __riscv_vwmulu_vv_u16m8_tum(vmask, vreg_memory_2, vreg_memory_3, vreg_memory_3, vl);
    __riscv_vsse16_v_u16m8_m(vmask, ptr_store_vreg_memory_2, 2, vreg_memory_2, vl);
    vfloat32m1_t vd_load_4 = __riscv_vfmv_v_f_f32m1(0, __riscv_vsetvlmax_e32m1());
    vfloat32m1_t vreg_memory_4 = __riscv_vle32_v_f32m1_tu(vd_load_4, ptr_load_4, vl);
    vfloat16m8_t vd_load_5 = __riscv_vfmv_v_f_f16m8(0, __riscv_vsetvlmax_e16m8());
    vfloat16m8_t vreg_memory_5 = __riscv_vle16_v_f16m8_tu(vd_load_5, ptr_load_5, vl);
    vfloat32m1_t vd_load_6 = __riscv_vfmv_v_f_f32m1(0, __riscv_vsetvlmax_e32m1());
    vfloat32m1_t vreg_memory_6 = __riscv_vle32_v_f32m1_tu(vd_load_6, ptr_load_6, vl);
    vfloat32m1_t vreg_1 = __riscv_vfwredusum_vs_f16m8_f32m1_tum(vmask, vreg_memory_4, vreg_memory_5, vreg_memory_6, vl);
    __riscv_vse32_v_f32m1(ptr_store_vreg_1, vreg_1, vl);
    vreg_memory_5 = __riscv_vfnmadd_vv_f16m8_tumu(vmask, vreg_memory_5, vreg_memory_5, vreg_memory_5, vl);
    __riscv_vsse16_v_f16m8_m(vmask, ptr_store_vreg_memory_5, 2, vreg_memory_5, vl);
    vint16m8_t vd_load_7 = __riscv_vmv_v_x_i16m8(0, __riscv_vsetvlmax_e16m8());
    vint16m8_t vreg_memory_7 = __riscv_vle16_v_i16m8_tu(vd_load_7, ptr_load_7, vl);
    vreg_memory_7 = __riscv_vor_vv_i16m8_tum(vmask, vreg_memory_0, vreg_memory_7, vreg_0, vl);
    __riscv_vse16_v_i16m8_m(vmask, ptr_store_vreg_memory_7, vreg_memory_7, vl);
    vint16m8_t vreg_2 = __riscv_vnmsac_vx_i16m8_tu(vreg_memory_0, 32214, vreg_0, vl);
    vuint16m8_t idx_2 = __riscv_vsll_vx_u16m8(__riscv_vid_v_u16m8(vl), 1, vl);
    __riscv_vsoxei16_v_i16m8_m(vmask, ptr_store_vreg_2, idx_2, vreg_2, vl);
    vint8m4_t vd_load_8 = __riscv_vmv_v_x_i8m4(0, __riscv_vsetvlmax_e8m4());
    vint8m4_t vreg_memory_8 = __riscv_vlse8_v_i8m4_tumu(vmask, vd_load_8, ptr_load_8, 1, vl);
    vint16m8_t vreg_3 = __riscv_vsext_vf2_i16m8_tu(vreg_2, vreg_memory_8, vl);
    vuint8m4_t idx_4 = __riscv_vsll_vx_u8m4(__riscv_vid_v_u8m4(vl), 1, vl);
    __riscv_vsoxei8_v_i16m8(ptr_store_vreg_3, idx_4, vreg_3, vl);
    vuint16m1_t vd_load_9 = __riscv_vmv_v_x_u16m1(0, __riscv_vsetvlmax_e16m1());
    vuint16m1_t vreg_memory_9 = __riscv_vle16_v_u16m1_tu(vd_load_9, ptr_load_9, vl);
    vuint16m8_t vd_load_10 = __riscv_vmv_v_x_u16m8(0, __riscv_vsetvlmax_e16m8());
    vuint16m8_t vreg_memory_10 = __riscv_vle16_v_u16m8_tu(vd_load_10, ptr_load_10, vl);
    vuint16m1_t vd_load_11 = __riscv_vmv_v_x_u16m1(0, __riscv_vsetvlmax_e16m1());
    vuint16m1_t vreg_memory_11 = __riscv_vle16_v_u16m1_tu(vd_load_11, ptr_load_11, vl);
    vuint16m1_t vreg_4 = __riscv_vredxor_vs_u16m8_u16m1_tum(vmask, vreg_memory_9, vreg_memory_10, vreg_memory_11, vl);
    __riscv_vse16_v_u16m1(ptr_store_vreg_4, vreg_4, vl);
    vint16m8_t vd_load_12 = __riscv_vmv_v_x_i16m8(0, __riscv_vsetvlmax_e16m8());
    vuint8m4_t idx_5 = __riscv_vsll_vx_u8m4(__riscv_vid_v_u8m4(vl), 1, vl);
    vint16m8_t vreg_memory_12 = __riscv_vloxei8_v_i16m8_tu(vd_load_12, ptr_load_12, idx_5, vl);
    vreg_memory_0 = __riscv_vfcvt_x_f_v_i16m8_mu(vmask, vreg_memory_12, vreg_memory_5, vl);
    __riscv_vse16_v_i16m8_m(vmask, ptr_store_vreg_memory_0, vreg_memory_0, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_10 += vl;
    ptr_load_11 += vl;
    ptr_load_12 += vl;
    ptr_load_2 += vl;
    ptr_load_3 += vl;
    ptr_load_4 += vl;
    ptr_load_5 += vl;
    ptr_load_6 += vl;
    ptr_load_7 += vl;
    ptr_load_8 += vl;
    ptr_load_9 += vl;
    ptr_store_vreg_0 += vl;
    ptr_store_vreg_1 += vl;
    ptr_store_vreg_2 += vl;
    ptr_store_vreg_3 += vl;
    ptr_store_vreg_4 += vl;
    ptr_store_vreg_memory_0 += vl;
    ptr_store_vreg_memory_2 += vl;
    ptr_store_vreg_memory_5 += vl;
    ptr_store_vreg_memory_7 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_1[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_2[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_3[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_4[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_2[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_memory_5[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_7[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

