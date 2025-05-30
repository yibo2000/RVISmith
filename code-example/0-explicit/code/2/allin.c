// --seed 0xb5f743fb --data_length 3 --sequence_length 9 --root vint32m8_t --segment 
// scheduling mode: allin 
#include <riscv_vector.h>

#define dataLen 3
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
int32_t data_load_0[dataLen];
uint16_t data_load_1[dataLen];
float32_t data_load_2[dataLen];
int16_t data_load_3[dataLen];
uint32_t data_load_4[dataLen];
float16_t data_load_5[dataLen];
uint8_t data_load_6[dataLen];
uint16_t data_load_7[dataLen];
uint8_t data_load_8[dataLen];
uint8_t data_load_9[dataLen];
int32_t data_store_vreg_0[dataLen];
int16_t data_store_vreg_1[dataLen];
uint32_t data_store_vreg_2[dataLen];
uint16_t data_store_vreg_3[dataLen];
uint8_t data_store_vreg_4[dataLen];
uint16_t data_store_vreg_memory_1[dataLen];
float32_t data_store_vreg_memory_2[dataLen];
float16_t data_store_vreg_memory_5[dataLen];
uint8_t data_store_vreg_memory_6[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  int32_t tmp_0[dataLen] = {-1016459832, 1870742175, 852577973, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  uint16_t tmp_1[dataLen] = {25329, 24887, 56256, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint32_t tmp_2[dataLen] = {36130019u, 4001280117u, 3008268611u, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = convert_binary_u32_f32(tmp_2[i]); }
  int16_t tmp_3[dataLen] = {-24851, 25040, 23521, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_3[i]; }
  uint32_t tmp_4[dataLen] = {748246724u, 3951361407u, 2651152637u, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = tmp_4[i]; }
  uint16_t tmp_5[dataLen] = {42928, 21292, 24435, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = convert_binary_u16_f16(tmp_5[i]); }
  uint8_t tmp_6[dataLen] = {47, 206, 145, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = tmp_6[i]; }
  uint16_t tmp_7[dataLen] = {57648, 243, 16009, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = tmp_7[i]; }
  uint8_t tmp_8[dataLen] = {38, 155, 16, };
  for (int i = 0; i < dataLen; ++i) { data_load_8[i] = tmp_8[i]; }
  uint8_t tmp_9[dataLen] = {86, 103, 34, };
  for (int i = 0; i < dataLen; ++i) { data_load_9[i] = tmp_9[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_4[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_5[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_6[i] = 0; }
}

void CodeBlock_0() {
  int avl1 = dataLen;
  int8_t* ptr_mask = data_mask;
  int32_t* ptr_load_0 = data_load_0;
  uint16_t* ptr_load_1 = data_load_1;
  float32_t* ptr_load_2 = data_load_2;
  int16_t* ptr_load_3 = data_load_3;
  uint32_t* ptr_load_4 = data_load_4;
  float16_t* ptr_load_5 = data_load_5;
  uint8_t* ptr_load_6 = data_load_6;
  uint16_t* ptr_load_7 = data_load_7;
  uint8_t* ptr_load_8 = data_load_8;
  uint8_t* ptr_load_9 = data_load_9;
  int32_t* ptr_store_vreg_0 = data_store_vreg_0;
  int16_t* ptr_store_vreg_1 = data_store_vreg_1;
  uint32_t* ptr_store_vreg_2 = data_store_vreg_2;
  uint16_t* ptr_store_vreg_3 = data_store_vreg_3;
  uint8_t* ptr_store_vreg_4 = data_store_vreg_4;
  uint16_t* ptr_store_vreg_memory_1 = data_store_vreg_memory_1;
  float32_t* ptr_store_vreg_memory_2 = data_store_vreg_memory_2;
  float16_t* ptr_store_vreg_memory_5 = data_store_vreg_memory_5;
  uint8_t* ptr_store_vreg_memory_6 = data_store_vreg_memory_6;
  for (size_t vl; avl1 > 0; avl1 -= vl){
    vl = __riscv_vsetvl_e32m8(avl1);
    vint8m2_t mask_value= __riscv_vle8_v_i8m2(ptr_mask, vl);
    vbool4_t vmask= __riscv_vmseq_vx_i8m2_b4(mask_value, 1, vl);
    vint32m8_t vreg_memory_0 = __riscv_vle32_v_i32m8(ptr_load_0, vl);
    vuint16m4_t idx_0 = __riscv_vsll_vx_u16m4(__riscv_vid_v_u16m4(vl), 1, vl);
    vuint16m4_t vreg_memory_1 = __riscv_vluxei16_v_u16m4_m(vmask, ptr_load_1, idx_0, vl);
    vfloat32m8_t vreg_memory_2 = __riscv_vle32_v_f32m8_m(vmask, ptr_load_2, vl);
    vint16m8_t vreg_memory_3 = __riscv_vle16_v_i16m8(ptr_load_3, vl);
    vuint32m4_t vreg_memory_4 = __riscv_vle32_v_u32m4(ptr_load_4, vl);
    vuint16m4_t idx_5 = __riscv_vsll_vx_u16m4(__riscv_vid_v_u16m4(vl), 1, vl);
    vfloat16m4_t vreg_memory_5 = __riscv_vluxei16_v_f16m4_m(vmask, ptr_load_5, idx_5, vl);
    vuint16m4_t idx_6 = __riscv_vsll_vx_u16m4(__riscv_vid_v_u16m4(vl), 0, vl);
    vuint8m2_t vreg_memory_6 = __riscv_vluxei16_v_u8m2_m(vmask, ptr_load_6, idx_6, vl);
    vuint16mf4_t vreg_memory_7 = __riscv_vle16_v_u16mf4(ptr_load_7, vl);
    vuint8m2_t vreg_memory_8 = __riscv_vle8_v_u8m2(ptr_load_8, vl);
    vuint8m2_t vreg_memory_9 = __riscv_vle8_v_u8m2(ptr_load_9, vl);
    vint32m2_t vreg_0 = __riscv_vlmul_trunc_v_i32m8_i32m2(vreg_memory_0);
    vreg_memory_1 = __riscv_vor_vv_u16m4_m(vmask, vreg_memory_1, vreg_memory_1, vl);
    vreg_memory_2 = __riscv_vfsgnjn_vf_f32m8_m(vmask, vreg_memory_2, convert_binary_u32_f32(10419u), vl);
    vint16m1_t vreg_1 = __riscv_vlmul_trunc_v_i16m8_i16m1(vreg_memory_3);
    vuint32m1_t vreg_2 = __riscv_vlmul_trunc_v_u32m4_u32m1(vreg_memory_4);
    vreg_memory_5 = __riscv_vfsgnj_vv_f16m4(vreg_memory_5, vreg_memory_5, vl);
    vreg_memory_6 = __riscv_vadd_vv_u8m2_m(vmask, vreg_memory_6, vreg_memory_6, vl);
    vuint16m4_t vreg_3 = __riscv_vlmul_ext_v_u16mf4_u16m4(vreg_memory_7);
    vuint8m2_t vreg_4 = __riscv_vslideup_vx_u8m2(vreg_memory_8, vreg_memory_9, 3953666234u, vl);
    __riscv_vse32_v_i32m2(ptr_store_vreg_0, vreg_0, vl);
    vuint8m2_t idx_2 = __riscv_vsll_vx_u8m2(__riscv_vid_v_u8m2(vl), 1, vl);
    __riscv_vsoxei8_v_u16m4(ptr_store_vreg_memory_1, idx_2, vreg_memory_1, vl);
    vuint32m8_t idx_4 = __riscv_vsll_vx_u32m8(__riscv_vid_v_u32m8(vl), 2, vl);
    __riscv_vsuxei32_v_f32m8(ptr_store_vreg_memory_2, idx_4, vreg_memory_2, vl);
    __riscv_vse16_v_i16m1(ptr_store_vreg_1, vreg_1, vl);
    __riscv_vse32_v_u32m1(ptr_store_vreg_2, vreg_2, vl);
    __riscv_vse16_v_f16m4(ptr_store_vreg_memory_5, vreg_memory_5, vl);
    __riscv_vse8_v_u8m2_m(vmask, ptr_store_vreg_memory_6, vreg_memory_6, vl);
    __riscv_vse8_v_u8m2(ptr_store_vreg_4, vreg_4, vl);
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
    ptr_load_9 += vl;
    ptr_store_vreg_0 += vl;
    ptr_store_vreg_1 += vl;
    ptr_store_vreg_2 += vl;
    ptr_store_vreg_3 += vl;
    ptr_store_vreg_4 += vl;
    ptr_store_vreg_memory_1 += vl;
    ptr_store_vreg_memory_2 += vl;
    ptr_store_vreg_memory_5 += vl;
    ptr_store_vreg_memory_6 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_2[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_4[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_memory_2[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_memory_5[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_6[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

