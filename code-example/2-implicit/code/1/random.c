// --seed 0x5a684731 --data_length 9 --sequence_length 3 --root vfloat64m4_t --segment  --overloaded 
// scheduling mode: random 
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
uint8_t data_load_0[dataLen];
int8_t data_load_1[dataLen];
int16_t data_load_2[dataLen];
int16_t data_load_3[dataLen];
uint8_t data_store_vreg_memory_0[dataLen];
int8_t data_store_vreg_memory_1[dataLen];
int16_t data_store_vreg_memory_2[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 1, 1, 1, 1, 1, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint8_t tmp_0[dataLen] = {165, 197, 174, 65, 90, 65, 221, 48, 228, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  int8_t tmp_1[dataLen] = {93, -34, -92, -49, 37, -13, -126, -45, 87, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  int16_t tmp_2[dataLen] = {14700, 12722, -32554, -25570, 28152, 24564, -11839, 10770, -32513, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = tmp_2[i]; }
  int16_t tmp_3[dataLen] = {10665, -19860, 23315, 10463, -7217, 6321, 27292, -32000, 17784, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_3[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_2[i] = 0; }
}

void CodeBlock_0() {
  int avl0 = dataLen;
  int8_t* ptr_mask = data_mask;
  uint8_t* ptr_load_0 = data_load_0;
  int8_t* ptr_load_1 = data_load_1;
  int16_t* ptr_load_2 = data_load_2;
  int16_t* ptr_load_3 = data_load_3;
  uint8_t* ptr_store_vreg_memory_0 = data_store_vreg_memory_0;
  int8_t* ptr_store_vreg_memory_1 = data_store_vreg_memory_1;
  int16_t* ptr_store_vreg_memory_2 = data_store_vreg_memory_2;
  for (size_t vl; avl0 > 0; avl0 -= vl){
    vl = __riscv_vsetvl_e64m4(avl0);
    vint8mf2_t mask_value= __riscv_vle8_v_i8mf2(ptr_mask, vl);
    vbool16_t vmask= __riscv_vmseq_vx_i8mf2_b16(mask_value, 1, vl);
    vuint16m1_t idx_0 = __riscv_vsll_vx_u16m1(__riscv_vid_v_u16m1(vl), 0, vl);
    vuint8mf2_t vreg_memory_0 = __riscv_vluxei16(ptr_load_0, idx_0, vl);
    vreg_memory_0 = __riscv_vsaddu(vreg_memory_0, 241, vl);
    vuint64m4_t idx_1 = __riscv_vsll_vx_u64m4(__riscv_vid_v_u64m4(vl), 0, vl);
    __riscv_vsse8(ptr_store_vreg_memory_0, 1, vreg_memory_0, vl);
    vint8mf2_t vreg_memory_1 = __riscv_vloxei64(vmask, ptr_load_1, idx_1, vl);
    vuint8mf2_t idx_2 = __riscv_vsll_vx_u8mf2(__riscv_vid_v_u8mf2(vl), 1, vl);
    vreg_memory_1 = __riscv_vor(vreg_memory_1, vreg_memory_1, vl);
    vint16m1_t vreg_memory_2 = __riscv_vluxei8(ptr_load_2, idx_2, vl);
    vint16m1_t vreg_memory_3 = __riscv_vle16_v_i16m1(ptr_load_3, vl);
    __riscv_vsse8(ptr_store_vreg_memory_1, 1, vreg_memory_1, vl);
    vreg_memory_2 = __riscv_vredor(vreg_memory_2, vreg_memory_3, vl);
    __riscv_vse16(ptr_store_vreg_memory_2, vreg_memory_2, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_2 += vl;
    ptr_load_3 += vl;
    ptr_store_vreg_memory_0 += vl;
    ptr_store_vreg_memory_1 += vl;
    ptr_store_vreg_memory_2 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<1; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_2[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

