// --seed 0x44593cd5 --data_length 4 --sequence_length 2 --root vint64m1_t --segment  --policy  --overloaded 
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
uint16_t data_load_0[dataLen];
uint64_t data_load_1[dataLen];
uint64_t data_load_2[dataLen];
uint64_t data_load_3[dataLen];
uint16_t data_store_vreg_0[dataLen];
uint64_t data_store_vreg_1[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 0, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint16_t tmp_0[dataLen] = {13435, 63372, 62523, 47302, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  uint64_t tmp_1[dataLen] = {807783374ull, 606605193ull, 2213177625ull, 1926870324ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint64_t tmp_2[dataLen] = {4255500787ull, 2825862976ull, 2729285315ull, 42752795ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = tmp_2[i]; }
  uint64_t tmp_3[dataLen] = {2040346923ull, 4080062415ull, 2714537176ull, 626017832ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_3[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
}

void CodeBlock_0() {
  int avl1 = dataLen;
  int8_t* ptr_mask = data_mask;
  uint16_t* ptr_load_0 = data_load_0;
  uint64_t* ptr_load_1 = data_load_1;
  uint64_t* ptr_load_2 = data_load_2;
  uint64_t* ptr_load_3 = data_load_3;
  uint16_t* ptr_store_vreg_0 = data_store_vreg_0;
  uint64_t* ptr_store_vreg_1 = data_store_vreg_1;
  for (size_t vl; avl1 > 0; avl1 -= vl){
    vl = __riscv_vsetvl_e64m1(avl1);
    vint8mf8_t mask_value= __riscv_vle8_v_i8mf8(ptr_mask, vl);
    vbool64_t vmask= __riscv_vmseq_vx_i8mf8_b64(mask_value, 1, vl);
    vuint16mf4_t vd_load_0 = __riscv_vmv_v_x_u16mf4(0, __riscv_vsetvlmax_e16mf4());
    vuint16mf4_t vreg_memory_0 = __riscv_vle16_tumu(vmask, vd_load_0, ptr_load_0, vl);
    vuint64m1_t vd_load_1 = __riscv_vmv_v_x_u64m1(0, __riscv_vsetvlmax_e64m1());
    vuint16mf4_t idx_0 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 3, vl);
    vuint64m1_t vreg_memory_1 = __riscv_vloxei16_tu(vd_load_1, ptr_load_1, idx_0, vl);
    vuint64m1_t vd_load_2 = __riscv_vmv_v_x_u64m1(0, __riscv_vsetvlmax_e64m1());
    vuint64m1_t vreg_memory_2 = __riscv_vle64_v_u64m1_tu(vd_load_2, ptr_load_2, vl);
    vuint64m1_t vd_load_3 = __riscv_vmv_v_x_u64m1(0, __riscv_vsetvlmax_e64m1());
    vuint64m1_t vreg_memory_3 = __riscv_vle64_v_u64m1_tu(vd_load_3, ptr_load_3, vl);
    vuint16mf4_t vreg_0 = __riscv_vor_vv_u16mf4_m(vmask, vreg_memory_0, vreg_memory_0, vl);
    vuint64m1_t vreg_1 = __riscv_vredmaxu_vs_u64m1_u64m1_tu(vreg_memory_1, vreg_memory_2, vreg_memory_3, vl);
    __riscv_vse16_v_u16mf4(ptr_store_vreg_0, vreg_0, vl);
    vuint16mf4_t idx_2 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 3, vl);
    __riscv_vsuxei16_v_u64m1(ptr_store_vreg_1, idx_2, vreg_1, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_2 += vl;
    ptr_load_3 += vl;
    ptr_store_vreg_0 += vl;
    ptr_store_vreg_1 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

