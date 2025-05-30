// --seed 0xe8b5d12d --data_length 9 --sequence_length 5 --root vint32m4_t --segment 
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
int32_t data_load_0[dataLen];
int8_t data_load_1[dataLen];
float32_t data_load_2[dataLen];
uint32_t data_load_3[dataLen];
float16_t data_load_4[dataLen];
float16_t data_load_5[dataLen];
uint8_t data_load_6[dataLen];
float32_t data_store_vreg_0[dataLen];
uint32_t data_store_vreg_1[dataLen];
int32_t data_store_vreg_memory_0[dataLen];
int8_t data_store_vreg_memory_1[dataLen];
uint8_t data_store_vreg_memory_6[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {0, 1, 1, 1, 1, 0, 1, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  int32_t tmp_0[dataLen] = {721682732, 2102310705, -923168315, 1502974250, -700254001, -1810568801, 1607114488, 270298370, 1228421263, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  int8_t tmp_1[dataLen] = {47, -5, 36, 58, 55, -97, -17, -103, 49, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint32_t tmp_2[dataLen] = {4139598801u, 3462352254u, 3740654793u, 3019147534u, 790501089u, 4032958043u, 3381643061u, 2856643283u, 318231105u, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = convert_binary_u32_f32(tmp_2[i]); }
  uint32_t tmp_3[dataLen] = {891468100u, 2542177132u, 285745782u, 1236401442u, 907680039u, 2415715658u, 221782237u, 361537211u, 1159505948u, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_3[i]; }
  uint16_t tmp_4[dataLen] = {39958, 62886, 43218, 48973, 37947, 1482, 41053, 34847, 40489, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = convert_binary_u16_f16(tmp_4[i]); }
  uint16_t tmp_5[dataLen] = {5444, 40580, 7172, 19128, 45338, 34864, 56468, 10319, 9287, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = convert_binary_u16_f16(tmp_5[i]); }
  uint8_t tmp_6[dataLen] = {182, 7, 234, 167, 96, 72, 116, 36, 251, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = tmp_6[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_6[i] = 0; }
}

void CodeBlock_0() {
  int avl2 = dataLen;
  int8_t* ptr_mask = data_mask;
  int32_t* ptr_load_0 = data_load_0;
  int8_t* ptr_load_1 = data_load_1;
  float32_t* ptr_load_2 = data_load_2;
  uint32_t* ptr_load_3 = data_load_3;
  float16_t* ptr_load_4 = data_load_4;
  float16_t* ptr_load_5 = data_load_5;
  uint8_t* ptr_load_6 = data_load_6;
  float32_t* ptr_store_vreg_0 = data_store_vreg_0;
  uint32_t* ptr_store_vreg_1 = data_store_vreg_1;
  int32_t* ptr_store_vreg_memory_0 = data_store_vreg_memory_0;
  int8_t* ptr_store_vreg_memory_1 = data_store_vreg_memory_1;
  uint8_t* ptr_store_vreg_memory_6 = data_store_vreg_memory_6;
  for (size_t vl; avl2 > 0; avl2 -= vl){
    vl = __riscv_vsetvl_e32m4(avl2);
    vint8m1_t mask_value= __riscv_vle8_v_i8m1(ptr_mask, vl);
    vbool8_t vmask= __riscv_vmseq_vx_i8m1_b8(mask_value, 1, vl);
    vint32m4_t vreg_memory_0 = __riscv_vlse32_v_i32m4(ptr_load_0, 4, vl);
    vint8m1_t vload_tmp_0 = __riscv_vle8_v_i8m1(ptr_load_1, vl);
    vbool8_t vreg_memory_1 = __riscv_vmseq_vx_i8m1_b8(vload_tmp_0, 1, vl);
    vreg_memory_0 = __riscv_vmerge_vvm_i32m4(vreg_memory_0, vreg_memory_0, vreg_memory_1, vl);
    __riscv_vsse32_v_i32m4(ptr_store_vreg_memory_0, 4, vreg_memory_0, vl);
    vuint64m8_t idx_0 = __riscv_vsll_vx_u64m8(__riscv_vid_v_u64m8(vl), 2, vl);
    vfloat32m4_t vreg_memory_2 = __riscv_vloxei64_v_f32m4(ptr_load_2, idx_0, vl);
    vfloat32m4_t vreg_0 = __riscv_vfsqrt_v_f32m4_m(vmask, vreg_memory_2, vl);
    vuint64m8_t idx_2 = __riscv_vsll_vx_u64m8(__riscv_vid_v_u64m8(vl), 2, vl);
    __riscv_vsuxei64_v_f32m4(ptr_store_vreg_0, idx_2, vreg_0, vl);
    vuint32m4_t vreg_memory_3 = __riscv_vle32_v_u32m4(ptr_load_3, vl);
    vuint32m1_t vreg_1 = __riscv_vget_v_u32m4_u32m1(vreg_memory_3, 0);
    __riscv_vse32_v_u32m1(ptr_store_vreg_1, vreg_1, vl);
    vfloat16m2_t vreg_memory_4 = __riscv_vlse16_v_f16m2(ptr_load_4, 2, vl);
    vfloat16m2_t vreg_memory_5 = __riscv_vle16_v_f16m2(ptr_load_5, vl);
    vreg_memory_1 = __riscv_vmfeq_vv_f16m2_b8_m(vmask, vreg_memory_4, vreg_memory_5, vl);
    vint8m1_t zero_1 = __riscv_vmv_v_x_i8m1(0, __riscv_vsetvlmax_e8m1());
    vint8m1_t vstore_tmp_1 = __riscv_vmerge_vxm_i8m1(zero_1, 1, vreg_memory_1, vl);
    __riscv_vse8_v_i8m1(ptr_store_vreg_memory_1, vstore_tmp_1, vl);
    vuint8m1_t vreg_memory_6 = __riscv_vle8_v_u8m1_m(vmask, ptr_load_6, vl);
    vreg_memory_6 = __riscv_vxor_vx_u8m1_m(vmask, vreg_memory_6, 124, vl);
    __riscv_vse8_v_u8m1(ptr_store_vreg_memory_6, vreg_memory_6, vl);
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
    ptr_store_vreg_memory_0 += vl;
    ptr_store_vreg_memory_1 += vl;
    ptr_store_vreg_memory_6 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_0[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_6[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

