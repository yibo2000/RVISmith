// --seed 0xb397f9d2 --data_length 1 --sequence_length 6 --root vfloat32m2_t --segment 
// scheduling mode: allin 
#include <riscv_vector.h>

#define dataLen 1
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
uint64_t data_load_0[dataLen];
uint32_t data_load_1[dataLen];
float32_t data_load_2[dataLen];
float32_t data_load_3[dataLen];
int8_t data_load_4[dataLen];
int32_t data_load_5[dataLen];
uint64_t data_store_vreg_0[dataLen];
uint8_t data_store_vreg_1[dataLen];
int8_t data_store_vreg_2[dataLen];
int64_t data_store_vreg_3[dataLen];
float32_t data_store_vreg_memory_2[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint64_t tmp_0[dataLen] = {709522125ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  uint32_t tmp_1[dataLen] = {3860773992u, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint32_t tmp_2[dataLen] = {684918448u, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = convert_binary_u32_f32(tmp_2[i]); }
  uint32_t tmp_3[dataLen] = {3952290218u, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = convert_binary_u32_f32(tmp_3[i]); }
  int8_t tmp_4[dataLen] = {-80, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = tmp_4[i]; }
  int32_t tmp_5[dataLen] = {-1659049364, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = tmp_5[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_2[i] = 0; }
}

void CodeBlock_0() {
  int avl1 = dataLen;
  int8_t* ptr_mask = data_mask;
  uint64_t* ptr_load_0 = data_load_0;
  uint32_t* ptr_load_1 = data_load_1;
  float32_t* ptr_load_2 = data_load_2;
  float32_t* ptr_load_3 = data_load_3;
  int8_t* ptr_load_4 = data_load_4;
  int32_t* ptr_load_5 = data_load_5;
  uint64_t* ptr_store_vreg_0 = data_store_vreg_0;
  uint8_t* ptr_store_vreg_1 = data_store_vreg_1;
  int8_t* ptr_store_vreg_2 = data_store_vreg_2;
  int64_t* ptr_store_vreg_3 = data_store_vreg_3;
  float32_t* ptr_store_vreg_memory_2 = data_store_vreg_memory_2;
  for (size_t vl; avl1 > 0; avl1 -= vl){
    vl = __riscv_vsetvl_e32m2(avl1);
    vint8mf2_t mask_value= __riscv_vle8_v_i8mf2(ptr_mask, vl);
    vbool16_t vmask= __riscv_vmseq_vx_i8mf2_b16(mask_value, 1, vl);
    vuint64m4_t vreg_memory_0 = __riscv_vle64_v_u64m4(ptr_load_0, vl);
    vuint32mf2_t vreg_memory_1 = __riscv_vle32_v_u32mf2(ptr_load_1, vl);
    vfloat32m2_t vreg_memory_2 = __riscv_vlse32_v_f32m2_m(vmask, ptr_load_2, 4, vl);
    vfloat32m2_t vreg_memory_3 = __riscv_vle32_v_f32m2(ptr_load_3, vl);
    vint8mf2_t vreg_memory_4 = __riscv_vlse8_v_i8mf2(ptr_load_4, 1, vl);
    vint32m8_t vreg_memory_5 = __riscv_vle32_v_i32m8(ptr_load_5, vl);
    vuint64m2_t vreg_0 = __riscv_vlmul_trunc_v_u64m4_u64m2(vreg_memory_0);
    vuint8mf2_t vreg_1 = __riscv_vreinterpret_v_u32mf2_u8mf2(vreg_memory_1);
    vreg_memory_2 = __riscv_vfsub_vv_f32m2(vreg_memory_2, vreg_memory_3, vl);
    vbool16_t vreg_2 = __riscv_vmsge_vx_i8mf2_b16(vreg_memory_4, -71, vl);
    vint64m8_t vreg_3 = __riscv_vreinterpret_v_i32m8_i64m8(vreg_memory_5);
    vreg_memory_2 = __riscv_vfmul_vv_f32m2(vreg_memory_2, vreg_memory_3, vl);
    __riscv_vse64_v_u64m2(ptr_store_vreg_0, vreg_0, vl);
    __riscv_vse32_v_f32m2(ptr_store_vreg_memory_2, vreg_memory_2, vl);
    vint8mf2_t zero_0 = __riscv_vmv_v_x_i8mf2(0, __riscv_vsetvlmax_e8mf2());
    vint8mf2_t vstore_tmp_0 = __riscv_vmerge_vxm_i8mf2(zero_0, 1, vreg_2, vl);
    __riscv_vse8_v_i8mf2(ptr_store_vreg_2, vstore_tmp_0, vl);
    vuint8mf2_t idx_1 = __riscv_vsll_vx_u8mf2(__riscv_vid_v_u8mf2(vl), 2, vl);
    __riscv_vsoxei8_v_f32m2(ptr_store_vreg_memory_2, idx_1, vreg_memory_2, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_2 += vl;
    ptr_load_3 += vl;
    ptr_load_4 += vl;
    ptr_load_5 += vl;
    ptr_store_vreg_0 += vl;
    ptr_store_vreg_1 += vl;
    ptr_store_vreg_2 += vl;
    ptr_store_vreg_3 += vl;
    ptr_store_vreg_memory_2 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_2[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_memory_2[i])); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

