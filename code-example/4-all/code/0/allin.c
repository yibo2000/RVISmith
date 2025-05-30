// --seed 0x9ded618f --data_length 2 --sequence_length 5 --root vfloat16mf4_t --segment  --policy  --overloaded 
// scheduling mode: allin 
#include <riscv_vector.h>

#define dataLen 2
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
uint64_t data_load_1[dataLen];
float64_t data_load_2[dataLen];
float32_t data_load_3[dataLen];
uint16_t data_load_4[dataLen];
float16_t data_load_5[dataLen];
uint16_t data_load_6[dataLen];
uint64_t data_store_vreg_0[dataLen];
float64_t data_store_vreg_1[dataLen];
uint16_t data_store_vreg_2[dataLen];
uint32_t data_store_vreg_memory_0[dataLen];
uint16_t data_store_vreg_memory_4[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint32_t tmp_0[dataLen] = {1648621544u, 173945891u, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  uint64_t tmp_1[dataLen] = {2874073846ull, 2040562857ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint64_t tmp_2[dataLen] = {2529234972ull, 3454602575ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = convert_binary_u64_f64(tmp_2[i]); }
  uint32_t tmp_3[dataLen] = {730499348u, 3209530379u, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = convert_binary_u32_f32(tmp_3[i]); }
  uint16_t tmp_4[dataLen] = {63470, 65506, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = tmp_4[i]; }
  uint16_t tmp_5[dataLen] = {2135, 58339, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = convert_binary_u16_f16(tmp_5[i]); }
  uint16_t tmp_6[dataLen] = {5200, 4342, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = tmp_6[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_4[i] = 0; }
}

void CodeBlock_0() {
  int avl1 = dataLen;
  int8_t* ptr_mask = data_mask;
  uint32_t* ptr_load_0 = data_load_0;
  uint64_t* ptr_load_1 = data_load_1;
  float64_t* ptr_load_2 = data_load_2;
  float32_t* ptr_load_3 = data_load_3;
  uint16_t* ptr_load_4 = data_load_4;
  float16_t* ptr_load_5 = data_load_5;
  uint16_t* ptr_load_6 = data_load_6;
  uint64_t* ptr_store_vreg_0 = data_store_vreg_0;
  float64_t* ptr_store_vreg_1 = data_store_vreg_1;
  uint16_t* ptr_store_vreg_2 = data_store_vreg_2;
  uint32_t* ptr_store_vreg_memory_0 = data_store_vreg_memory_0;
  uint16_t* ptr_store_vreg_memory_4 = data_store_vreg_memory_4;
  for (size_t vl; avl1 > 0; avl1 -= vl){
    vl = __riscv_vsetvl_e16mf4(avl1);
    vint8mf8_t mask_value= __riscv_vle8_v_i8mf8(ptr_mask, vl);
    vbool64_t vmask= __riscv_vmseq_vx_i8mf8_b64(mask_value, 1, vl);
    vuint32mf2_t vd_load_0 = __riscv_vmv_v_x_u32mf2(0, __riscv_vsetvlmax_e32mf2());
    vuint32mf2_t vreg_memory_0 = __riscv_vle32_v_u32mf2_tu(vd_load_0, ptr_load_0, vl);
    vuint64m1_t vd_load_1 = __riscv_vmv_v_x_u64m1(0, __riscv_vsetvlmax_e64m1());
    vuint64m1_t idx_0 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 3, vl);
    vuint64m1_t vreg_memory_1 = __riscv_vluxei64_tum(vmask, vd_load_1, ptr_load_1, idx_0, vl);
    vfloat64m1_t vd_load_2 = __riscv_vfmv_v_f_f64m1(0, __riscv_vsetvlmax_e64m1());
    vuint32mf2_t idx_1 = __riscv_vsll_vx_u32mf2(__riscv_vid_v_u32mf2(vl), 3, vl);
    vfloat64m1_t vreg_memory_2 = __riscv_vluxei32_tu(vd_load_2, ptr_load_2, idx_1, vl);
    vfloat32mf2_t vd_load_3 = __riscv_vfmv_v_f_f32mf2(0, __riscv_vsetvlmax_e32mf2());
    vfloat32mf2_t vreg_memory_3 = __riscv_vle32_tum(vmask, vd_load_3, ptr_load_3, vl);
    vuint16mf4_t vd_load_4 = __riscv_vmv_v_x_u16mf4(0, __riscv_vsetvlmax_e16mf4());
    vuint16mf4_t vreg_memory_4 = __riscv_vle16_tum(vmask, vd_load_4, ptr_load_4, vl);
    vfloat16mf4_t vd_load_5 = __riscv_vfmv_v_f_f16mf4(0, __riscv_vsetvlmax_e16mf4());
    vfloat16mf4_t vreg_memory_5 = __riscv_vle16_v_f16mf4_tu(vd_load_5, ptr_load_5, vl);
    vuint16mf4_t vd_load_6 = __riscv_vmv_v_x_u16mf4(0, __riscv_vsetvlmax_e16mf4());
    vuint16mf4_t vreg_memory_6 = __riscv_vle16_v_u16mf4_tu(vd_load_6, ptr_load_6, vl);
    vreg_memory_0 = __riscv_vmaxu(vmask, vreg_memory_0, 903120185u, vl);
    vuint64m1_t vreg_0 = __riscv_vwmaccu_tumu(vmask, vreg_memory_1, vreg_memory_0, vreg_memory_0, vl);
    vfloat64m1_t vreg_1 = __riscv_vfwmsac_vv_f64m1_rm_mu(vmask, vreg_memory_2, vreg_memory_3, vreg_memory_3, __RISCV_FRM_RDN, vl);
    vreg_memory_4 = __riscv_vfcvt_rtz_xu_tum(vmask, vreg_memory_4, vreg_memory_5, vl);
    vuint16m8_t vreg_2 = __riscv_vlmul_ext_u16m8(vreg_memory_6);
    __riscv_vse32_v_u32mf2(ptr_store_vreg_memory_0, vreg_memory_0, vl);
    __riscv_vse64_v_u64m1(ptr_store_vreg_0, vreg_0, vl);
    __riscv_vsse64_v_f64m1_m(vmask, ptr_store_vreg_1, 8, vreg_1, vl);
    __riscv_vse16_v_u16mf4(ptr_store_vreg_memory_4, vreg_memory_4, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_2 += vl;
    ptr_load_3 += vl;
    ptr_load_4 += vl;
    ptr_load_5 += vl;
    ptr_load_6 += vl;
    ptr_store_vreg_0 += vl;
    ptr_store_vreg_1 += vl;
    ptr_store_vreg_2 += vl;
    ptr_store_vreg_memory_0 += vl;
    ptr_store_vreg_memory_4 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_1[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_4[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

