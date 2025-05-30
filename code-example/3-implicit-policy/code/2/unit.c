// --seed 0xa8d85c89 --data_length 8 --sequence_length 9 --root vfloat64m4_t --segment  --policy  --overloaded 
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
int8_t data_load_0[dataLen];
int8_t data_load_1[dataLen];
float64_t data_load_10[dataLen];
float16_t data_load_11[dataLen];
uint32_t data_load_2[dataLen];
uint16_t data_load_3[dataLen];
int64_t data_load_4[dataLen];
uint8_t data_load_5[dataLen];
float32_t data_load_6[dataLen];
uint8_t data_load_7[dataLen];
uint8_t data_load_8[dataLen];
uint8_t data_load_9[dataLen];
int8_t data_store_vreg_0[dataLen];
int64_t data_store_vreg_1[dataLen];
uint8_t data_store_vreg_2[dataLen];
float64_t data_store_vreg_3[dataLen];
float16_t data_store_vreg_memory_11[dataLen];
uint32_t data_store_vreg_memory_2[dataLen];
uint16_t data_store_vreg_memory_3[dataLen];
float32_t data_store_vreg_memory_6[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 0, 1, 0, 0, 1, 0, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  int8_t tmp_0[dataLen] = {65, -81, 68, 35, -80, 14, 82, -17, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  int8_t tmp_1[dataLen] = {114, -55, 116, 100, 68, 94, -82, 71, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint64_t tmp_2[dataLen] = {1401453096ull, 950189264ull, 1981105581ull, 3656646329ull, 1709365905ull, 331463306ull, 477409310ull, 1649374993ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_10[i] = convert_binary_u64_f64(tmp_2[i]); }
  uint16_t tmp_3[dataLen] = {22108, 12907, 168, 26540, 45706, 21270, 31544, 57092, };
  for (int i = 0; i < dataLen; ++i) { data_load_11[i] = convert_binary_u16_f16(tmp_3[i]); }
  uint32_t tmp_4[dataLen] = {1404113108u, 990121743u, 2820003260u, 3199869718u, 1574565338u, 46440804u, 3047474366u, 520493763u, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = tmp_4[i]; }
  uint16_t tmp_5[dataLen] = {7563, 26452, 56791, 103, 39233, 22312, 44475, 44269, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_5[i]; }
  int64_t tmp_6[dataLen] = {2378977751741574480ll, 7152198824666309890ll, 4690613549100764978ll, -2025283627844051521ll, 2932308369161272364ll, 518176520941906012ll, -3969797339768886620ll, -2687253044131794897ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = tmp_6[i]; }
  uint8_t tmp_7[dataLen] = {209, 97, 184, 154, 95, 211, 39, 127, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = tmp_7[i]; }
  uint32_t tmp_8[dataLen] = {947876542u, 1833074252u, 1443795148u, 1064197731u, 822466787u, 2763347828u, 3858592810u, 3009819007u, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = convert_binary_u32_f32(tmp_8[i]); }
  uint8_t tmp_9[dataLen] = {156, 19, 243, 79, 194, 138, 184, 217, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = tmp_9[i]; }
  uint8_t tmp_10[dataLen] = {129, 228, 22, 133, 90, 6, 157, 140, };
  for (int i = 0; i < dataLen; ++i) { data_load_8[i] = tmp_10[i]; }
  uint8_t tmp_11[dataLen] = {60, 228, 230, 162, 209, 20, 40, 226, };
  for (int i = 0; i < dataLen; ++i) { data_load_9[i] = tmp_11[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_11[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_6[i] = 0; }
}

void CodeBlock_0() {
  int avl2 = dataLen;
  int8_t* ptr_mask = data_mask;
  int8_t* ptr_load_0 = data_load_0;
  int8_t* ptr_load_1 = data_load_1;
  float64_t* ptr_load_10 = data_load_10;
  float16_t* ptr_load_11 = data_load_11;
  uint32_t* ptr_load_2 = data_load_2;
  uint16_t* ptr_load_3 = data_load_3;
  int64_t* ptr_load_4 = data_load_4;
  uint8_t* ptr_load_5 = data_load_5;
  float32_t* ptr_load_6 = data_load_6;
  uint8_t* ptr_load_7 = data_load_7;
  uint8_t* ptr_load_8 = data_load_8;
  uint8_t* ptr_load_9 = data_load_9;
  int8_t* ptr_store_vreg_0 = data_store_vreg_0;
  int64_t* ptr_store_vreg_1 = data_store_vreg_1;
  uint8_t* ptr_store_vreg_2 = data_store_vreg_2;
  float64_t* ptr_store_vreg_3 = data_store_vreg_3;
  float16_t* ptr_store_vreg_memory_11 = data_store_vreg_memory_11;
  uint32_t* ptr_store_vreg_memory_2 = data_store_vreg_memory_2;
  uint16_t* ptr_store_vreg_memory_3 = data_store_vreg_memory_3;
  float32_t* ptr_store_vreg_memory_6 = data_store_vreg_memory_6;
  for (size_t vl; avl2 > 0; avl2 -= vl){
    vl = __riscv_vsetvl_e64m4(avl2);
    vint8mf2_t mask_value= __riscv_vle8_v_i8mf2(ptr_mask, vl);
    vbool16_t vmask= __riscv_vmseq_vx_i8mf2_b16(mask_value, 1, vl);
    vint8mf2_t vd_load_0 = __riscv_vmv_v_x_i8mf2(0, __riscv_vsetvlmax_e8mf2());
    vint8mf2_t vreg_memory_0 = __riscv_vle8_v_i8mf2_tu(vd_load_0, ptr_load_0, vl);
    vint8mf2_t vd_load_1 = __riscv_vmv_v_x_i8mf2(0, __riscv_vsetvlmax_e8mf2());
    vint8mf2_t vreg_memory_1 = __riscv_vle8_tumu(vmask, vd_load_1, ptr_load_1, vl);
    vint8mf2_t vreg_0 = __riscv_vmin_tumu(vmask, vreg_memory_0, vreg_memory_0, vreg_memory_1, vl);
    vuint32m2_t idx_1 = __riscv_vsll_vx_u32m2(__riscv_vid_v_u32m2(vl), 0, vl);
    __riscv_vsoxei32_v_i8mf2_m(vmask, ptr_store_vreg_0, idx_1, vreg_0, vl);
    vuint32m2_t vd_load_2 = __riscv_vmv_v_x_u32m2(0, __riscv_vsetvlmax_e32m2());
    vuint8mf2_t idx_2 = __riscv_vsll_vx_u8mf2(__riscv_vid_v_u8mf2(vl), 2, vl);
    vuint32m2_t vreg_memory_2 = __riscv_vluxei8_tu(vd_load_2, ptr_load_2, idx_2, vl);
    vuint16m1_t vd_load_3 = __riscv_vmv_v_x_u16m1(0, __riscv_vsetvlmax_e16m1());
    vuint16m1_t vreg_memory_3 = __riscv_vle16_tum(vmask, vd_load_3, ptr_load_3, vl);
    vreg_memory_2 = __riscv_vwcvtu_x_tumu(vmask, vreg_memory_2, vreg_memory_3, vl);
    vuint8mf2_t idx_4 = __riscv_vsll_vx_u8mf2(__riscv_vid_v_u8mf2(vl), 2, vl);
    __riscv_vsuxei8_v_u32m2(ptr_store_vreg_memory_2, idx_4, vreg_memory_2, vl);
    vint64m4_t vd_load_4 = __riscv_vmv_v_x_i64m4(0, __riscv_vsetvlmax_e64m4());
    vuint32m2_t idx_5 = __riscv_vsll_vx_u32m2(__riscv_vid_v_u32m2(vl), 3, vl);
    vint64m4_t vreg_memory_4 = __riscv_vloxei32_tu(vd_load_4, ptr_load_4, idx_5, vl);
    vint64m4_t vreg_1 = __riscv_vsadd_tum(vmask, vreg_memory_4, vreg_memory_4, -8755370498302921729ll, vl);
    __riscv_vse64_v_i64m4_m(vmask, ptr_store_vreg_1, vreg_1, vl);
    vuint8mf2_t vd_load_5 = __riscv_vmv_v_x_u8mf2(0, __riscv_vsetvlmax_e8mf2());
    vuint8mf2_t vreg_memory_5 = __riscv_vle8_v_u8mf2_tu(vd_load_5, ptr_load_5, vl);
    vreg_memory_3 = __riscv_vwmulu_tumu(vmask, vreg_memory_3, vreg_memory_5, vreg_memory_5, vl);
    vuint64m4_t idx_7 = __riscv_vsll_vx_u64m4(__riscv_vid_v_u64m4(vl), 1, vl);
    __riscv_vsoxei64_v_u16m1_m(vmask, ptr_store_vreg_memory_3, idx_7, vreg_memory_3, vl);
    vfloat32m2_t vd_load_6 = __riscv_vfmv_v_f_f32m2(0, __riscv_vsetvlmax_e32m2());
    vfloat32m2_t vreg_memory_6 = __riscv_vlse32_mu(vmask, vd_load_6, ptr_load_6, 4, vl);
    vreg_memory_6 = __riscv_vfadd_mu(vmask, vreg_memory_6, vreg_memory_6, vreg_memory_6, __RISCV_FRM_RUP, vl);
    __riscv_vsse32_v_f32m2(ptr_store_vreg_memory_6, 4, vreg_memory_6, vl);
    vuint8m1_t vd_load_7 = __riscv_vmv_v_x_u8m1(0, __riscv_vsetvlmax_e8m1());
    vuint8m1_t vreg_memory_7 = __riscv_vle8_v_u8m1_tu(vd_load_7, ptr_load_7, vl);
    vuint8mf2_t vd_load_8 = __riscv_vmv_v_x_u8mf2(0, __riscv_vsetvlmax_e8mf2());
    vuint8mf2_t vreg_memory_8 = __riscv_vle8_v_u8mf2_tu(vd_load_8, ptr_load_8, vl);
    vuint8m1_t vd_load_9 = __riscv_vmv_v_x_u8m1(0, __riscv_vsetvlmax_e8m1());
    vuint8m1_t vreg_memory_9 = __riscv_vle8_v_u8m1_tu(vd_load_9, ptr_load_9, vl);
    vuint8m1_t vreg_2 = __riscv_vredand_tu(vreg_memory_7, vreg_memory_8, vreg_memory_9, vl);
    __riscv_vse8_v_u8m1(ptr_store_vreg_2, vreg_2, vl);
    vfloat64m4_t vd_load_10 = __riscv_vfmv_v_f_f64m4(0, __riscv_vsetvlmax_e64m4());
    vuint16m1_t idx_8 = __riscv_vsll_vx_u16m1(__riscv_vid_v_u16m1(vl), 3, vl);
    vfloat64m4_t vreg_memory_10 = __riscv_vluxei16_tu(vd_load_10, ptr_load_10, idx_8, vl);
    vfloat64m4_t vreg_3 = __riscv_vfnmadd_mu(vmask, vreg_memory_10, convert_binary_u64_f64(26956ull), vreg_memory_10, __RISCV_FRM_RTZ, vl);
    __riscv_vsse64_v_f64m4_m(vmask, ptr_store_vreg_3, 8, vreg_3, vl);
    vfloat16m1_t vd_load_11 = __riscv_vfmv_v_f_f16m1(0, __riscv_vsetvlmax_e16m1());
    vuint64m4_t idx_9 = __riscv_vsll_vx_u64m4(__riscv_vid_v_u64m4(vl), 1, vl);
    vfloat16m1_t vreg_memory_11 = __riscv_vloxei64_tumu(vmask, vd_load_11, ptr_load_11, idx_9, vl);
    vreg_memory_11 = __riscv_vfsqrt_tumu(vmask, vreg_memory_11, vreg_memory_11, vl);
    vuint16m1_t idx_11 = __riscv_vsll_vx_u16m1(__riscv_vid_v_u16m1(vl), 1, vl);
    __riscv_vsuxei16_v_f16m1_m(vmask, ptr_store_vreg_memory_11, idx_11, vreg_memory_11, vl);
    vreg_memory_2 = __riscv_vfcvt_rtz_xu_tumu(vmask, vreg_memory_2, vreg_memory_6, vl);
    __riscv_vsse32_v_u32m2(ptr_store_vreg_memory_2, 4, vreg_memory_2, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_10 += vl;
    ptr_load_11 += vl;
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
    ptr_store_vreg_memory_11 += vl;
    ptr_store_vreg_memory_2 += vl;
    ptr_store_vreg_memory_3 += vl;
    ptr_store_vreg_memory_6 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_2[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_3[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_memory_11[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_2[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_3[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_memory_6[i])); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

