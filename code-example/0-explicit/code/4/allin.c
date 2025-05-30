// --seed 0x1e67f7d3 --data_length 4 --sequence_length 2 --root vint32m2_t --segment 
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
int32_t data_load_0[dataLen];
uint16_t data_load_1[dataLen];
int8_t data_store_vreg_0[dataLen];
int16_t data_store_vreg_1[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 0, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  int32_t tmp_0[dataLen] = {689635242, 1490438894, 1048265798, -311506608, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  uint16_t tmp_1[dataLen] = {36353, 65005, 33633, 46796, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
}

void CodeBlock_0() {
  int avl1 = dataLen;
  int8_t* ptr_mask = data_mask;
  int32_t* ptr_load_0 = data_load_0;
  uint16_t* ptr_load_1 = data_load_1;
  int8_t* ptr_store_vreg_0 = data_store_vreg_0;
  int16_t* ptr_store_vreg_1 = data_store_vreg_1;
  for (size_t vl; avl1 > 0; avl1 -= vl){
    vl = __riscv_vsetvl_e32m2(avl1);
    vint8mf2_t mask_value= __riscv_vle8_v_i8mf2(ptr_mask, vl);
    vbool16_t vmask= __riscv_vmseq_vx_i8mf2_b16(mask_value, 1, vl);
    vint32m2_t vreg_memory_0 = __riscv_vlse32_v_i32m2(ptr_load_0, 4, vl);
    vuint16m1_t idx_0 = __riscv_vsll_vx_u16m1(__riscv_vid_v_u16m1(vl), 1, vl);
    vuint16m1_t vreg_memory_1 = __riscv_vluxei16_v_u16m1(ptr_load_1, idx_0, vl);
    vbool16_t vreg_0 = __riscv_vmsne_vv_i32m2_b16_m(vmask, vreg_memory_0, vreg_memory_0, vl);
    vint16m1_t vreg_1 = __riscv_vnclip_wv_i16m1(vreg_memory_0, vreg_memory_1, __RISCV_VXRM_ROD, vl);
    vint8mf2_t zero_0 = __riscv_vmv_v_x_i8mf2(0, __riscv_vsetvlmax_e8mf2());
    vint8mf2_t vstore_tmp_0 = __riscv_vmerge_vxm_i8mf2(zero_0, 1, vreg_0, vl);
    __riscv_vse8_v_i8mf2(ptr_store_vreg_0, vstore_tmp_0, vl);
    __riscv_vsse16_v_i16m1(ptr_store_vreg_1, 2, vreg_1, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_store_vreg_0 += vl;
    ptr_store_vreg_1 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

