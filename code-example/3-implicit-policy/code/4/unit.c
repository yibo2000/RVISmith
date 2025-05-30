// --seed 0xf4e05b9b --data_length 9 --sequence_length 7 --root vuint64m2_t --segment  --policy  --overloaded 
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
float32_t data_load_0[dataLen];
uint16_t data_load_1[dataLen];
uint32_t data_load_2[dataLen];
int16_t data_load_3[dataLen];
int32_t data_load_4[dataLen];
int64_t data_load_5[dataLen];
uint32_t data_load_6[dataLen];
int32_t data_load_7[dataLen];
float32_t data_store_vreg_0[dataLen];
uint16_t data_store_vreg_memory_1[dataLen];
int16_t data_store_vreg_memory_3[dataLen];
int32_t data_store_vreg_memory_4[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 1, 1, 1, 1, 1, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint32_t tmp_0[dataLen] = {869531036u, 1179182697u, 2054543289u, 3958658531u, 3242047135u, 2783727242u, 25230927u, 129713424u, 33259683u, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = convert_binary_u32_f32(tmp_0[i]); }
  uint16_t tmp_1[dataLen] = {38381, 23188, 37756, 22710, 46687, 57228, 44977, 1300, 12945, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint32_t tmp_2[dataLen] = {2076607356u, 1090662503u, 2730239602u, 982207599u, 3524784965u, 4036903429u, 4021375591u, 2851882974u, 1738375417u, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = tmp_2[i]; }
  int16_t tmp_3[dataLen] = {-9120, -25825, 21503, -12108, -23555, -11871, 21052, 19471, -14948, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_3[i]; }
  int32_t tmp_4[dataLen] = {-2067258723, -1000180540, -1470621641, 1042717080, -434295224, -1943085083, 1025114889, -705511904, -1388306428, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = tmp_4[i]; }
  int64_t tmp_5[dataLen] = {-7126219438751512150ll, -5041614112461776701ll, -3200465692409554319ll, -4025238265986639116ll, 6882972521798902394ll, -7832644526360611132ll, -1472063168049700611ll, 4998762740872944395ll, -1016946528265392750ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = tmp_5[i]; }
  uint32_t tmp_6[dataLen] = {2314288472u, 245547187u, 2238492573u, 642117738u, 3765231104u, 2522446367u, 2654806913u, 4030873290u, 2248207187u, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = tmp_6[i]; }
  int32_t tmp_7[dataLen] = {33755689, -1428346681, 2065133103, -1099598197, -642918108, 1600620294, -835375685, -1630368959, 150168678, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = tmp_7[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_4[i] = 0; }
}

void CodeBlock_0() {
  int avl2 = dataLen;
  int8_t* ptr_mask = data_mask;
  float32_t* ptr_load_0 = data_load_0;
  uint16_t* ptr_load_1 = data_load_1;
  uint32_t* ptr_load_2 = data_load_2;
  int16_t* ptr_load_3 = data_load_3;
  int32_t* ptr_load_4 = data_load_4;
  int64_t* ptr_load_5 = data_load_5;
  uint32_t* ptr_load_6 = data_load_6;
  int32_t* ptr_load_7 = data_load_7;
  float32_t* ptr_store_vreg_0 = data_store_vreg_0;
  uint16_t* ptr_store_vreg_memory_1 = data_store_vreg_memory_1;
  int16_t* ptr_store_vreg_memory_3 = data_store_vreg_memory_3;
  int32_t* ptr_store_vreg_memory_4 = data_store_vreg_memory_4;
  for (size_t vl; avl2 > 0; avl2 -= vl){
    vl = __riscv_vsetvl_e64m2(avl2);
    vint8mf4_t mask_value= __riscv_vle8_v_i8mf4(ptr_mask, vl);
    vbool32_t vmask= __riscv_vmseq_vx_i8mf4_b32(mask_value, 1, vl);
    vfloat32m1_t vd_load_0 = __riscv_vfmv_v_f_f32m1(0, __riscv_vsetvlmax_e32m1());
    vfloat32m1_t vreg_memory_0 = __riscv_vle32_v_f32m1_tu(vd_load_0, ptr_load_0, vl);
    vfloat32m1_t vreg_0 = __riscv_vfmacc_mu(vmask, vreg_memory_0, convert_binary_u32_f32(33898u), vreg_memory_0, vl);
    __riscv_vsse32_v_f32m1(ptr_store_vreg_0, 4, vreg_0, vl);
    vuint16mf2_t vd_load_1 = __riscv_vmv_v_x_u16mf2(0, __riscv_vsetvlmax_e16mf2());
    vuint64m2_t idx_0 = __riscv_vsll_vx_u64m2(__riscv_vid_v_u64m2(vl), 1, vl);
    vuint16mf2_t vreg_memory_1 = __riscv_vloxei64_tu(vd_load_1, ptr_load_1, idx_0, vl);
    vuint32m1_t vd_load_2 = __riscv_vmv_v_x_u32m1(0, __riscv_vsetvlmax_e32m1());
    vuint32m1_t idx_1 = __riscv_vsll_vx_u32m1(__riscv_vid_v_u32m1(vl), 2, vl);
    vuint32m1_t vreg_memory_2 = __riscv_vloxei32_tumu(vmask, vd_load_2, ptr_load_2, idx_1, vl);
    vreg_memory_1 = __riscv_vnsrl_tu(vreg_memory_1, vreg_memory_2, vreg_memory_1, vl);
    vuint16mf2_t idx_3 = __riscv_vsll_vx_u16mf2(__riscv_vid_v_u16mf2(vl), 1, vl);
    __riscv_vsoxei16_v_u16mf2(ptr_store_vreg_memory_1, idx_3, vreg_memory_1, vl);
    vint16mf2_t vd_load_3 = __riscv_vmv_v_x_i16mf2(0, __riscv_vsetvlmax_e16mf2());
    vuint32m1_t idx_4 = __riscv_vsll_vx_u32m1(__riscv_vid_v_u32m1(vl), 1, vl);
    vint16mf2_t vreg_memory_3 = __riscv_vloxei32_tu(vd_load_3, ptr_load_3, idx_4, vl);
    vreg_memory_3 = __riscv_vwadd_wx_tumu(vmask, vreg_memory_3, vreg_memory_3, 102, vl);
    vuint32m1_t idx_6 = __riscv_vsll_vx_u32m1(__riscv_vid_v_u32m1(vl), 1, vl);
    __riscv_vsuxei32_v_i16mf2(ptr_store_vreg_memory_3, idx_6, vreg_memory_3, vl);
    vint32m1_t vd_load_4 = __riscv_vmv_v_x_i32m1(0, __riscv_vsetvlmax_e32m1());
    vint32m1_t vreg_memory_4 = __riscv_vlse32_v_i32m1_tu(vd_load_4, ptr_load_4, 4, vl);
    vint64m2_t vd_load_5 = __riscv_vmv_v_x_i64m2(0, __riscv_vsetvlmax_e64m2());
    vuint32m1_t idx_7 = __riscv_vsll_vx_u32m1(__riscv_vid_v_u32m1(vl), 3, vl);
    vint64m2_t vreg_memory_5 = __riscv_vluxei32_tu(vd_load_5, ptr_load_5, idx_7, vl);
    vreg_memory_4 = __riscv_vnsra_tum(vmask, vreg_memory_4, vreg_memory_5, vreg_memory_2, vl);
    __riscv_vsse32_v_i32m1_m(vmask, ptr_store_vreg_memory_4, 4, vreg_memory_4, vl);
    vuint32m1_t vd_load_6 = __riscv_vmv_v_x_u32m1(0, __riscv_vsetvlmax_e32m1());
    vuint32m1_t vreg_memory_6 = __riscv_vlse32_tumu(vmask, vd_load_6, ptr_load_6, 4, vl);
    vreg_memory_4 = __riscv_vmulhsu_tum(vmask, vreg_memory_4, vreg_memory_4, vreg_memory_6, vl);
    vuint16mf2_t idx_9 = __riscv_vsll_vx_u16mf2(__riscv_vid_v_u16mf2(vl), 2, vl);
    __riscv_vsuxei16_v_i32m1(ptr_store_vreg_memory_4, idx_9, vreg_memory_4, vl);
    vint32m1_t vd_load_7 = __riscv_vmv_v_x_i32m1(0, __riscv_vsetvlmax_e32m1());
    vint32m1_t vreg_memory_7 = __riscv_vle32_v_i32m1_tu(vd_load_7, ptr_load_7, vl);
    vreg_memory_4 = __riscv_vssub_tumu(vmask, vreg_memory_7, vreg_memory_7, -1971126069, vl);
    vuint16mf2_t idx_11 = __riscv_vsll_vx_u16mf2(__riscv_vid_v_u16mf2(vl), 2, vl);
    __riscv_vsoxei16_v_i32m1_m(vmask, ptr_store_vreg_memory_4, idx_11, vreg_memory_4, vl);
    vreg_0 = __riscv_vfmax_tumu(vmask, vreg_memory_0, vreg_0, vreg_memory_0, vl);
    __riscv_vse32_v_f32m1(ptr_store_vreg_0, vreg_0, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_2 += vl;
    ptr_load_3 += vl;
    ptr_load_4 += vl;
    ptr_load_5 += vl;
    ptr_load_6 += vl;
    ptr_load_7 += vl;
    ptr_store_vreg_0 += vl;
    ptr_store_vreg_memory_1 += vl;
    ptr_store_vreg_memory_3 += vl;
    ptr_store_vreg_memory_4 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_0[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_3[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_4[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

