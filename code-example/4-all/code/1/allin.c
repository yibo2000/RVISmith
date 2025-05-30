// --seed 0x70016871 --data_length 4 --sequence_length 9 --root vuint8mf2_t --segment  --policy  --overloaded 
// scheduling mode: allin 
#include <riscv_vector.h>

#define dataLen 4
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
uint32_t data_load_0[dataLen];
int16_t data_load_1[dataLen];
float64_t data_load_10[dataLen];
float32_t data_load_2[dataLen];
float32_t data_load_3[dataLen];
float16_t data_load_4[dataLen];
int32_t data_load_5[dataLen];
int32_t data_load_6[dataLen];
uint16_t data_load_7[dataLen];
int64_t data_load_8[dataLen];
uint8_t data_load_9[dataLen];
int8_t data_store_vreg_0[dataLen];
int8_t data_store_vreg_1[dataLen];
uint8_t data_store_vreg_2[dataLen];
float64_t data_store_vreg_3[dataLen];
int16_t data_store_vreg_memory_1[dataLen];
float32_t data_store_vreg_memory_3[dataLen];
float16_t data_store_vreg_memory_4[dataLen];
int32_t data_store_vreg_memory_6[dataLen];
int64_t data_store_vreg_memory_8[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {0, 1, 1, 0, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint32_t tmp_0[dataLen] = {1223248430u, 970128669u, 3544620680u, 527336973u, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  int16_t tmp_1[dataLen] = {15352, -20482, 2364, 5599, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint64_t tmp_2[dataLen] = {3574337596ull, 1144781688ull, 2269403799ull, 457823427ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_10[i] = convert_binary_u64_f64(tmp_2[i]); }
  uint32_t tmp_3[dataLen] = {3872438654u, 716559314u, 4154620339u, 319091620u, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = convert_binary_u32_f32(tmp_3[i]); }
  uint32_t tmp_4[dataLen] = {2032255989u, 837681590u, 2310287130u, 3388839607u, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = convert_binary_u32_f32(tmp_4[i]); }
  uint16_t tmp_5[dataLen] = {1885, 49732, 57523, 6341, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = convert_binary_u16_f16(tmp_5[i]); }
  int32_t tmp_6[dataLen] = {-1097849746, 1396955577, -373400133, -76650369, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = tmp_6[i]; }
  int32_t tmp_7[dataLen] = {1216885867, -169025093, -973927847, -2103872345, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = tmp_7[i]; }
  uint16_t tmp_8[dataLen] = {16960, 26944, 31693, 12895, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = tmp_8[i]; }
  int64_t tmp_9[dataLen] = {-8211096608684560214ll, -1702859425896680732ll, 628654813268485502ll, 4127371199523685920ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_8[i] = tmp_9[i]; }
  uint8_t tmp_10[dataLen] = {7, 91, 115, 144, };
  for (int i = 0; i < dataLen; ++i) { data_load_9[i] = tmp_10[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_4[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_6[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_8[i] = 0; }
}

void CodeBlock_0() {
  int avl1 = dataLen;
  int8_t* ptr_mask = data_mask;
  uint32_t* ptr_load_0 = data_load_0;
  int16_t* ptr_load_1 = data_load_1;
  float64_t* ptr_load_10 = data_load_10;
  float32_t* ptr_load_2 = data_load_2;
  float32_t* ptr_load_3 = data_load_3;
  float16_t* ptr_load_4 = data_load_4;
  int32_t* ptr_load_5 = data_load_5;
  int32_t* ptr_load_6 = data_load_6;
  uint16_t* ptr_load_7 = data_load_7;
  int64_t* ptr_load_8 = data_load_8;
  uint8_t* ptr_load_9 = data_load_9;
  int8_t* ptr_store_vreg_0 = data_store_vreg_0;
  int8_t* ptr_store_vreg_1 = data_store_vreg_1;
  uint8_t* ptr_store_vreg_2 = data_store_vreg_2;
  float64_t* ptr_store_vreg_3 = data_store_vreg_3;
  int16_t* ptr_store_vreg_memory_1 = data_store_vreg_memory_1;
  float32_t* ptr_store_vreg_memory_3 = data_store_vreg_memory_3;
  float16_t* ptr_store_vreg_memory_4 = data_store_vreg_memory_4;
  int32_t* ptr_store_vreg_memory_6 = data_store_vreg_memory_6;
  int64_t* ptr_store_vreg_memory_8 = data_store_vreg_memory_8;
  for (size_t vl; avl1 > 0; avl1 -= vl){
    vl = __riscv_vsetvl_e8mf2(avl1);
    vint8mf2_t mask_value= __riscv_vle8_v_i8mf2(ptr_mask, vl);
    vbool16_t vmask= __riscv_vmseq_vx_i8mf2_b16(mask_value, 1, vl);
    vuint32m2_t vd_load_0 = __riscv_vmv_v_x_u32m2(0, __riscv_vsetvlmax_e32m2());
    vuint32m2_t vreg_memory_0 = __riscv_vlse32_tumu(vmask, vd_load_0, ptr_load_0, 4, vl);
    vint16m1_t vd_load_1 = __riscv_vmv_v_x_i16m1(0, __riscv_vsetvlmax_e16m1());
    vuint8mf2_t idx_0 = __riscv_vsll_vx_u8mf2(__riscv_vid_v_u8mf2(vl), 1, vl);
    vint16m1_t vreg_memory_1 = __riscv_vloxei8_tu(vd_load_1, ptr_load_1, idx_0, vl);
    vfloat32m2_t vd_load_2 = __riscv_vfmv_v_f_f32m2(0, __riscv_vsetvlmax_e32m2());
    vuint16m1_t idx_1 = __riscv_vsll_vx_u16m1(__riscv_vid_v_u16m1(vl), 2, vl);
    vfloat32m2_t vreg_memory_2 = __riscv_vloxei16_tumu(vmask, vd_load_2, ptr_load_2, idx_1, vl);
    vfloat32m2_t vd_load_3 = __riscv_vfmv_v_f_f32m2(0, __riscv_vsetvlmax_e32m2());
    vfloat32m2_t vreg_memory_3 = __riscv_vle32_v_f32m2_tu(vd_load_3, ptr_load_3, vl);
    vfloat16m1_t vd_load_4 = __riscv_vfmv_v_f_f16m1(0, __riscv_vsetvlmax_e16m1());
    vuint64m4_t idx_4 = __riscv_vsll_vx_u64m4(__riscv_vid_v_u64m4(vl), 1, vl);
    vfloat16m1_t vreg_memory_4 = __riscv_vluxei64_tu(vd_load_4, ptr_load_4, idx_4, vl);
    vint32m2_t vd_load_5 = __riscv_vmv_v_x_i32m2(0, __riscv_vsetvlmax_e32m2());
    vuint64m4_t idx_7 = __riscv_vsll_vx_u64m4(__riscv_vid_v_u64m4(vl), 2, vl);
    vint32m2_t vreg_memory_5 = __riscv_vluxei64_tu(vd_load_5, ptr_load_5, idx_7, vl);
    vint32m2_t vd_load_6 = __riscv_vmv_v_x_i32m2(0, __riscv_vsetvlmax_e32m2());
    vuint32m2_t idx_8 = __riscv_vsll_vx_u32m2(__riscv_vid_v_u32m2(vl), 2, vl);
    vint32m2_t vreg_memory_6 = __riscv_vluxei32_tu(vd_load_6, ptr_load_6, idx_8, vl);
    vuint16m1_t vd_load_7 = __riscv_vmv_v_x_u16m1(0, __riscv_vsetvlmax_e16m1());
    vuint16m1_t vreg_memory_7 = __riscv_vle16_v_u16m1_tu(vd_load_7, ptr_load_7, vl);
    vreg_memory_7 = __riscv_vremu_vx_u16m1(vreg_memory_7, (uint16_t)(vl), vl);
    vint64m4_t vd_load_8 = __riscv_vmv_v_x_i64m4(0, __riscv_vsetvlmax_e64m4());
    vint64m4_t vreg_memory_8 = __riscv_vle64_mu(vmask, vd_load_8, ptr_load_8, vl);
    vuint8mf2_t vd_load_9 = __riscv_vmv_v_x_u8mf2(0, __riscv_vsetvlmax_e8mf2());
    vuint8mf2_t vreg_memory_9 = __riscv_vle8_v_u8mf2_tu(vd_load_9, ptr_load_9, vl);
    vfloat64m4_t vd_load_10 = __riscv_vfmv_v_f_f64m4(0, __riscv_vsetvlmax_e64m4());
    vuint64m4_t idx_11 = __riscv_vsll_vx_u64m4(__riscv_vid_v_u64m4(vl), 3, vl);
    vfloat64m4_t vreg_memory_10 = __riscv_vluxei64_tum(vmask, vd_load_10, ptr_load_10, idx_11, vl);
    vbool16_t vreg_0 = __riscv_vmsleu_vx_u32m2_b16_m(vmask, vreg_memory_0, 3948555418u, vl);
    vreg_memory_1 = __riscv_vrgather(vreg_memory_1, 898791216u%vl, vl);
    vreg_memory_3 = __riscv_vfnmadd_vf_f32m2_rm(vreg_memory_2, convert_binary_u32_f32(24810u), vreg_memory_3, __RISCV_FRM_RUP, vl);
    vreg_memory_4 = __riscv_vfsqrt_v_f16m1_tum(vmask, vreg_memory_4, vreg_memory_4, vl);
    vreg_memory_6 = __riscv_vrgatherei16_mu(vmask, vreg_memory_5, vreg_memory_6, vreg_memory_7, vl);
    vbool16_t vreg_1 = __riscv_vmseq_vv_i64m4_b16_m(vmask, vreg_memory_8, vreg_memory_8, vl);
    vreg_memory_8 = __riscv_vmacc(vmask, vreg_memory_8, 7562834804224813605ll, vreg_memory_8, vl);
    vuint8mf2_t vreg_2 = __riscv_vnot_v_u8mf2_tumu(vmask, vreg_memory_9, vreg_memory_9, vl);
    vfloat64m4_t vreg_3 = __riscv_vfrsub_mu(vmask, vreg_memory_10, vreg_memory_10, convert_binary_u64_f64(63939ull), __RISCV_FRM_RNE, vl);
    vint8mf2_t zero_0 = __riscv_vmv_v_x_i8mf2(0, __riscv_vsetvlmax_e8mf2());
    vint8mf2_t vstore_tmp_0 = __riscv_vmerge_vxm_i8mf2(zero_0, 1, vreg_0, vl);
    __riscv_vse8_v_i8mf2(ptr_store_vreg_0, vstore_tmp_0, vl);
    __riscv_vse16_v_i16m1(ptr_store_vreg_memory_1, vreg_memory_1, vl);
    vuint64m4_t idx_3 = __riscv_vsll_vx_u64m4(__riscv_vid_v_u64m4(vl), 2, vl);
    __riscv_vsuxei64_v_f32m2_m(vmask, ptr_store_vreg_memory_3, idx_3, vreg_memory_3, vl);
    vuint8mf2_t idx_6 = __riscv_vsll_vx_u8mf2(__riscv_vid_v_u8mf2(vl), 1, vl);
    __riscv_vsuxei8_v_f16m1_m(vmask, ptr_store_vreg_memory_4, idx_6, vreg_memory_4, vl);
    __riscv_vse32_v_i32m2(ptr_store_vreg_memory_6, vreg_memory_6, vl);
    vint8mf2_t zero_1 = __riscv_vmv_v_x_i8mf2(0, __riscv_vsetvlmax_e8mf2());
    vint8mf2_t vstore_tmp_1 = __riscv_vmerge_vxm_i8mf2(zero_1, 1, vreg_1, vl);
    __riscv_vse8_v_i8mf2(ptr_store_vreg_1, vstore_tmp_1, vl);
    vuint32m2_t idx_10 = __riscv_vsll_vx_u32m2(__riscv_vid_v_u32m2(vl), 3, vl);
    __riscv_vsuxei32_v_i64m4(ptr_store_vreg_memory_8, idx_10, vreg_memory_8, vl);
    __riscv_vse8_v_u8mf2_m(vmask, ptr_store_vreg_2, vreg_2, vl);
    __riscv_vse64_v_f64m4_m(vmask, ptr_store_vreg_3, vreg_3, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_10 += vl;
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
    ptr_store_vreg_memory_1 += vl;
    ptr_store_vreg_memory_3 += vl;
    ptr_store_vreg_memory_4 += vl;
    ptr_store_vreg_memory_6 += vl;
    ptr_store_vreg_memory_8 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_2[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_3[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_memory_3[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_memory_4[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_6[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_memory_8[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

