// --seed 0xe5366882 --data_length 6 --sequence_length 1 --root vint32mf2_t --segment  --policy  --overloaded 
// scheduling mode: random 
#include <riscv_vector.h>

#define dataLen 6
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
float32_t data_load_1[dataLen];
float32_t data_store_vreg_memory_0[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 1, 1, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint32_t tmp_0[dataLen] = {1499705518u, 3734829574u, 1893383544u, 2513693013u, 3151253292u, 57279755u, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = convert_binary_u32_f32(tmp_0[i]); }
  uint32_t tmp_1[dataLen] = {1865551110u, 2864262810u, 3906792565u, 390158824u, 378183447u, 2469408264u, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = convert_binary_u32_f32(tmp_1[i]); }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_0[i] = 0; }
}

void CodeBlock_0() {
  int avl0 = dataLen;
  int8_t* ptr_mask = data_mask;
  float32_t* ptr_load_0 = data_load_0;
  float32_t* ptr_load_1 = data_load_1;
  float32_t* ptr_store_vreg_memory_0 = data_store_vreg_memory_0;
  for (size_t vl; avl0 > 0; avl0 -= vl){
    vl = __riscv_vsetvl_e32mf2(avl0);
    vint8mf8_t mask_value= __riscv_vle8_v_i8mf8(ptr_mask, vl);
    vbool64_t vmask= __riscv_vmseq_vx_i8mf8_b64(mask_value, 1, vl);
    vfloat32mf2_t vd_load_0 = __riscv_vfmv_v_f_f32mf2(0, __riscv_vsetvlmax_e32mf2());
    vfloat32mf2_t vreg_memory_0 = __riscv_vle32_v_f32mf2_tu(vd_load_0, ptr_load_0, vl);
    vfloat32mf2_t vd_load_1 = __riscv_vfmv_v_f_f32mf2(0, __riscv_vsetvlmax_e32mf2());
    vuint8mf8_t idx_0 = __riscv_vsll_vx_u8mf8(__riscv_vid_v_u8mf8(vl), 2, vl);
    vfloat32mf2_t vreg_memory_1 = __riscv_vloxei8_tu(vd_load_1, ptr_load_1, idx_0, vl);
    vreg_memory_0 = __riscv_vfsub_tu(vreg_memory_0, vreg_memory_1, vreg_memory_0, __RISCV_FRM_RDN, vl);
    __riscv_vsse32_v_f32mf2(ptr_store_vreg_memory_0, 4, vreg_memory_0, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_store_vreg_memory_0 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_memory_0[i])); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

