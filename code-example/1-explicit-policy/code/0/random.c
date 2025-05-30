// --seed 0x55c83a7d --data_length 8 --sequence_length 7 --root vint64m4_t --segment  --policy 
// scheduling mode: random 
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
uint8_t data_load_0[dataLen];
uint16_t data_load_1[dataLen];
float64_t data_load_2[dataLen];
int16_t data_load_3[dataLen];
int64_t data_load_4[dataLen];
float32_t data_load_5[dataLen];
float32_t data_load_6[dataLen];
uint64_t data_load_7[dataLen];
uint64_t data_load_8[dataLen];
float32_t data_store_vreg_0[dataLen];
uint8_t data_store_vreg_memory_0[dataLen];
uint16_t data_store_vreg_memory_1[dataLen];
float64_t data_store_vreg_memory_2[dataLen];
int16_t data_store_vreg_memory_3[dataLen];
int64_t data_store_vreg_memory_4[dataLen];
uint64_t data_store_vreg_memory_8[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 1, 1, 1, 1, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint8_t tmp_0[dataLen] = {91, 62, 192, 163, 177, 14, 28, 0, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  uint16_t tmp_1[dataLen] = {60150, 57732, 9971, 7905, 20883, 7965, 20442, 43523, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint64_t tmp_2[dataLen] = {1007406952ull, 1284857122ull, 2759862234ull, 2198017261ull, 3067274426ull, 2589324794ull, 103909765ull, 2887303209ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = convert_binary_u64_f64(tmp_2[i]); }
  int16_t tmp_3[dataLen] = {-29569, -28284, 2782, 30037, -16909, 30565, 2479, 2743, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_3[i]; }
  int64_t tmp_4[dataLen] = {-7365041054831752477ll, 3041772301764626078ll, -3330983683404453183ll, -6815276144443975222ll, 4443080880165466192ll, -5314531259083939830ll, 6067538230782142130ll, -5037493018791086413ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = tmp_4[i]; }
  uint32_t tmp_5[dataLen] = {4248559903u, 3661218088u, 921420561u, 2845717450u, 2184666922u, 3785353168u, 2932558229u, 2498683757u, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = convert_binary_u32_f32(tmp_5[i]); }
  uint32_t tmp_6[dataLen] = {2498234094u, 31229545u, 3290120931u, 1828259019u, 1519301340u, 3913639107u, 928816708u, 3828925879u, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = convert_binary_u32_f32(tmp_6[i]); }
  uint64_t tmp_7[dataLen] = {4080044487ull, 2023595406ull, 2369857536ull, 272836052ull, 1631271846ull, 3517965620ull, 1224137004ull, 2815019339ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = tmp_7[i]; }
  uint64_t tmp_8[dataLen] = {3707900047ull, 1045206645ull, 4059735372ull, 3912849336ull, 692063516ull, 870737916ull, 619497951ull, 3245911102ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_8[i] = tmp_8[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_4[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_8[i] = 0; }
}

void CodeBlock_0() {
  int avl0 = dataLen;
  int8_t* ptr_mask = data_mask;
  uint8_t* ptr_load_0 = data_load_0;
  uint16_t* ptr_load_1 = data_load_1;
  float64_t* ptr_load_2 = data_load_2;
  int16_t* ptr_load_3 = data_load_3;
  int64_t* ptr_load_4 = data_load_4;
  float32_t* ptr_load_5 = data_load_5;
  float32_t* ptr_load_6 = data_load_6;
  uint64_t* ptr_load_7 = data_load_7;
  uint64_t* ptr_load_8 = data_load_8;
  float32_t* ptr_store_vreg_0 = data_store_vreg_0;
  uint8_t* ptr_store_vreg_memory_0 = data_store_vreg_memory_0;
  uint16_t* ptr_store_vreg_memory_1 = data_store_vreg_memory_1;
  float64_t* ptr_store_vreg_memory_2 = data_store_vreg_memory_2;
  int16_t* ptr_store_vreg_memory_3 = data_store_vreg_memory_3;
  int64_t* ptr_store_vreg_memory_4 = data_store_vreg_memory_4;
  uint64_t* ptr_store_vreg_memory_8 = data_store_vreg_memory_8;
  for (size_t vl; avl0 > 0; avl0 -= vl){
    vl = __riscv_vsetvl_e64m4(avl0);
    vint8mf2_t mask_value= __riscv_vle8_v_i8mf2(ptr_mask, vl);
    vbool16_t vmask= __riscv_vmseq_vx_i8mf2_b16(mask_value, 1, vl);
    vint16m1_t vd_load_3 = __riscv_vmv_v_x_i16m1(0, __riscv_vsetvlmax_e16m1());
    vfloat32m2_t vd_load_5 = __riscv_vfmv_v_f_f32m2(0, __riscv_vsetvlmax_e32m2());
    vuint8mf2_t vd_load_0 = __riscv_vmv_v_x_u8mf2(0, __riscv_vsetvlmax_e8mf2());
    vuint8mf2_t idx_0 = __riscv_vsll_vx_u8mf2(__riscv_vid_v_u8mf2(vl), 0, vl);
    vint64m4_t vd_load_4 = __riscv_vmv_v_x_i64m4(0, __riscv_vsetvlmax_e64m4());
    vuint8mf2_t vreg_memory_0 = __riscv_vluxei8_v_u8mf2_tum(vmask, vd_load_0, ptr_load_0, idx_0, vl);
    vreg_memory_0 = __riscv_vasubu_vx_u8mf2_tumu(vmask, vreg_memory_0, vreg_memory_0, 117, __RISCV_VXRM_RNU, vl);
    vuint32m2_t idx_2 = __riscv_vsll_vx_u32m2(__riscv_vid_v_u32m2(vl), 0, vl);
    __riscv_vsuxei32_v_u8mf2_m(vmask, ptr_store_vreg_memory_0, idx_2, vreg_memory_0, vl);
    vuint16m1_t vd_load_1 = __riscv_vmv_v_x_u16m1(0, __riscv_vsetvlmax_e16m1());
    vuint32m2_t idx_3 = __riscv_vsll_vx_u32m2(__riscv_vid_v_u32m2(vl), 1, vl);
    vuint16m1_t vreg_memory_1 = __riscv_vloxei32_v_u16m1_tu(vd_load_1, ptr_load_1, idx_3, vl);
    vint64m4_t vreg_memory_4 = __riscv_vle64_v_i64m4_tu(vd_load_4, ptr_load_4, vl);
    vreg_memory_1 = __riscv_vmul_vx_u16m1_tumu(vmask, vreg_memory_1, vreg_memory_1, 41096, vl);
    vfloat64m4_t vd_load_2 = __riscv_vfmv_v_f_f64m4(0, __riscv_vsetvlmax_e64m4());
    vfloat64m4_t vreg_memory_2 = __riscv_vle64_v_f64m4_tumu(vmask, vd_load_2, ptr_load_2, vl);
    vint16m1_t vreg_memory_3 = __riscv_vlse16_v_i16m1_tu(vd_load_3, ptr_load_3, 2, vl);
    vuint64m4_t idx_5 = __riscv_vsll_vx_u64m4(__riscv_vid_v_u64m4(vl), 1, vl);
    __riscv_vsoxei64_v_u16m1(ptr_store_vreg_memory_1, idx_5, vreg_memory_1, vl);
    vreg_memory_2 = __riscv_vfsgnjn_vf_f64m4_mu(vmask, vreg_memory_2, vreg_memory_2, convert_binary_u64_f64(28434ull), vl);
    __riscv_vse64_v_f64m4(ptr_store_vreg_memory_2, vreg_memory_2, vl);
    vreg_memory_3 = __riscv_vsll_vx_i16m1_tum(vmask, vreg_memory_3, vreg_memory_3, 2415561037u, vl);
    vuint64m4_t vd_load_7 = __riscv_vmv_v_x_u64m4(0, __riscv_vsetvlmax_e64m4());
    vuint8mf2_t idx_7 = __riscv_vsll_vx_u8mf2(__riscv_vid_v_u8mf2(vl), 1, vl);
    vuint16m1_t idx_10 = __riscv_vsll_vx_u16m1(__riscv_vid_v_u16m1(vl), 2, vl);
    __riscv_vsuxei8_v_i16m1(ptr_store_vreg_memory_3, idx_7, vreg_memory_3, vl);
    vuint16m1_t idx_11 = __riscv_vsll_vx_u16m1(__riscv_vid_v_u16m1(vl), 3, vl);
    vfloat32m2_t vreg_memory_5 = __riscv_vluxei16_v_f32m2_tu(vd_load_5, ptr_load_5, idx_10, vl);
    vreg_memory_4 = __riscv_vand_vx_i64m4_tu(vreg_memory_4, vreg_memory_4, 4075797307522012767ll, vl);
    vfloat32m2_t vd_load_6 = __riscv_vfmv_v_f_f32m2(0, __riscv_vsetvlmax_e32m2());
    vfloat32m2_t vreg_memory_6 = __riscv_vle32_v_f32m2_tu(vd_load_6, ptr_load_6, vl);
    vuint8mf2_t idx_9 = __riscv_vsll_vx_u8mf2(__riscv_vid_v_u8mf2(vl), 3, vl);
    __riscv_vsuxei8_v_i64m4_m(vmask, ptr_store_vreg_memory_4, idx_9, vreg_memory_4, vl);
    vfloat32m2_t vreg_0 = __riscv_vslideup_vx_f32m2_tumu(vmask, vreg_memory_5, vreg_memory_6, 1963756853u, vl);
    __riscv_vse32_v_f32m2(ptr_store_vreg_0, vreg_0, vl);
    vuint64m4_t vreg_memory_7 = __riscv_vluxei16_v_u64m4_tu(vd_load_7, ptr_load_7, idx_11, vl);
    vuint64m4_t vd_load_8 = __riscv_vmv_v_x_u64m4(0, __riscv_vsetvlmax_e64m4());
    vuint64m4_t vreg_memory_8 = __riscv_vle64_v_u64m4_tu(vd_load_8, ptr_load_8, vl);
    vreg_memory_8 = __riscv_vslidedown_vx_u64m4_tum(vmask, vreg_memory_7, vreg_memory_8, 1465213891u, vl);
    vuint16m1_t idx_13 = __riscv_vsll_vx_u16m1(__riscv_vid_v_u16m1(vl), 3, vl);
    __riscv_vsuxei16_v_u64m4(ptr_store_vreg_memory_8, idx_13, vreg_memory_8, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_2 += vl;
    ptr_load_3 += vl;
    ptr_load_4 += vl;
    ptr_load_5 += vl;
    ptr_load_6 += vl;
    ptr_load_7 += vl;
    ptr_load_8 += vl;
    ptr_store_vreg_0 += vl;
    ptr_store_vreg_memory_0 += vl;
    ptr_store_vreg_memory_1 += vl;
    ptr_store_vreg_memory_2 += vl;
    ptr_store_vreg_memory_3 += vl;
    ptr_store_vreg_memory_4 += vl;
    ptr_store_vreg_memory_8 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_0[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_memory_2[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_3[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_memory_4[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_memory_8[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

