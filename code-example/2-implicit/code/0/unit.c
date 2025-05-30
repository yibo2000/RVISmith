// --seed 0x4117b508 --data_length 2 --sequence_length 9 --root vint16mf4_t --segment  --overloaded 
// scheduling mode: unit 
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
int32_t data_load_0[dataLen];
uint16_t data_load_1[dataLen];
float32_t data_load_2[dataLen];
uint8_t data_load_3[dataLen];
float16_t data_load_4[dataLen];
float16_t data_load_5[dataLen];
float32_t data_load_6[dataLen];
float32_t data_load_7[dataLen];
int8_t data_load_8[dataLen];
uint32_t data_load_9[dataLen];
int32_t data_store_vreg_0[dataLen];
uint64_t data_store_vreg_1[dataLen];
float16_t data_store_vreg_2[dataLen];
int8_t data_store_vreg_3[dataLen];
float16_t data_store_vreg_4[dataLen];
uint8_t data_store_vreg_memory_3[dataLen];
float32_t data_store_vreg_memory_7[dataLen];
int8_t data_store_vreg_memory_8[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  int32_t tmp_0[dataLen] = {-1146995810, -337971226, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  uint16_t tmp_1[dataLen] = {20520, 31321, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint32_t tmp_2[dataLen] = {389679320u, 136054719u, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = convert_binary_u32_f32(tmp_2[i]); }
  uint8_t tmp_3[dataLen] = {75, 178, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_3[i]; }
  uint16_t tmp_4[dataLen] = {65008, 63827, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = convert_binary_u16_f16(tmp_4[i]); }
  uint16_t tmp_5[dataLen] = {38921, 1559, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = convert_binary_u16_f16(tmp_5[i]); }
  uint32_t tmp_6[dataLen] = {365450746u, 3325744156u, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = convert_binary_u32_f32(tmp_6[i]); }
  uint32_t tmp_7[dataLen] = {2079792414u, 1803141739u, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = convert_binary_u32_f32(tmp_7[i]); }
  int8_t tmp_8[dataLen] = {13, -33, };
  for (int i = 0; i < dataLen; ++i) { data_load_8[i] = tmp_8[i]; }
  uint32_t tmp_9[dataLen] = {2328252131u, 384831138u, };
  for (int i = 0; i < dataLen; ++i) { data_load_9[i] = tmp_9[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_4[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_7[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_8[i] = 0; }
}

void CodeBlock_0() {
  int avl2 = dataLen;
  int8_t* ptr_mask = data_mask;
  int32_t* ptr_load_0 = data_load_0;
  uint16_t* ptr_load_1 = data_load_1;
  float32_t* ptr_load_2 = data_load_2;
  uint8_t* ptr_load_3 = data_load_3;
  float16_t* ptr_load_4 = data_load_4;
  float16_t* ptr_load_5 = data_load_5;
  float32_t* ptr_load_6 = data_load_6;
  float32_t* ptr_load_7 = data_load_7;
  int8_t* ptr_load_8 = data_load_8;
  uint32_t* ptr_load_9 = data_load_9;
  int32_t* ptr_store_vreg_0 = data_store_vreg_0;
  uint64_t* ptr_store_vreg_1 = data_store_vreg_1;
  float16_t* ptr_store_vreg_2 = data_store_vreg_2;
  int8_t* ptr_store_vreg_3 = data_store_vreg_3;
  float16_t* ptr_store_vreg_4 = data_store_vreg_4;
  uint8_t* ptr_store_vreg_memory_3 = data_store_vreg_memory_3;
  float32_t* ptr_store_vreg_memory_7 = data_store_vreg_memory_7;
  int8_t* ptr_store_vreg_memory_8 = data_store_vreg_memory_8;
  for (size_t vl; avl2 > 0; avl2 -= vl){
    vl = __riscv_vsetvl_e16mf4(avl2);
    vint8mf8_t mask_value= __riscv_vle8_v_i8mf8(ptr_mask, vl);
    vbool64_t vmask= __riscv_vmseq_vx_i8mf8_b64(mask_value, 1, vl);
    vint32mf2_t vreg_memory_0 = __riscv_vlse32(vmask, ptr_load_0, 4, vl);
    vuint16mf4_t vreg_memory_1 = __riscv_vlse16_v_u16mf4(ptr_load_1, 2, vl);
    vint32mf2_t vreg_0 = __riscv_vwmaccsu(vmask, vreg_memory_0, 11217, vreg_memory_1, vl);
    vuint16mf4_t idx_1 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 2, vl);
    __riscv_vsuxei16(ptr_store_vreg_0, idx_1, vreg_0, vl);
    vfloat32mf2_t vreg_memory_2 = __riscv_vle32_v_f32mf2(ptr_load_2, vl);
    vuint64m1_t vreg_1 = __riscv_vfwcvt_xu(vmask, vreg_memory_2, vl);
    __riscv_vse64(ptr_store_vreg_1, vreg_1, vl);
    vuint8mf8_t vreg_memory_3 = __riscv_vle8_v_u8mf8(ptr_load_3, vl);
    vreg_memory_3 = __riscv_vnot(vmask, vreg_memory_3, vl);
    __riscv_vsse8(ptr_store_vreg_memory_3, 1, vreg_memory_3, vl);
    vuint16mf4_t idx_2 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 1, vl);
    vfloat16mf4_t vreg_memory_4 = __riscv_vluxei16(vmask, ptr_load_4, idx_2, vl);
    vuint8mf8_t idx_3 = __riscv_vsll_vx_u8mf8(__riscv_vid_v_u8mf8(vl), 1, vl);
    vfloat16mf4_t vreg_memory_5 = __riscv_vluxei8(ptr_load_5, idx_3, vl);
    vfloat16mf4_t vreg_2 = __riscv_vfnmadd(vmask, vreg_memory_4, convert_binary_u16_f16(37381), vreg_memory_5, vl);
    vuint64m1_t idx_5 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 1, vl);
    __riscv_vsuxei64(vmask, ptr_store_vreg_2, idx_5, vreg_2, vl);
    vfloat32mf2_t vreg_memory_6 = __riscv_vle32(vmask, ptr_load_6, vl);
    vbool64_t vreg_3 = __riscv_vmflt(vreg_memory_6, vreg_memory_2, vl);
    vint8mf8_t zero_0 = __riscv_vmv_v_x_i8mf8(0, __riscv_vsetvlmax_e8mf8());
    vint8mf8_t vstore_tmp_0 = __riscv_vmerge_vxm_i8mf8(zero_0, 1, vreg_3, vl);
    __riscv_vse8_v_i8mf8(ptr_store_vreg_3, vstore_tmp_0, vl);
    vuint8mf8_t idx_6 = __riscv_vsll_vx_u8mf8(__riscv_vid_v_u8mf8(vl), 2, vl);
    vfloat32mf2_t vreg_memory_7 = __riscv_vluxei8(ptr_load_7, idx_6, vl);
    vreg_memory_7 = __riscv_vfmadd(vreg_memory_7, convert_binary_u32_f32(6806u), vreg_memory_6, __RISCV_FRM_RNE, vl);
    __riscv_vse32(ptr_store_vreg_memory_7, vreg_memory_7, vl);
    vint8mf8_t vreg_memory_8 = __riscv_vle8_v_i8mf8(ptr_load_8, vl);
    vreg_memory_8 = __riscv_vslidedown(vmask, vreg_memory_8, 2608070694u, vl);
    __riscv_vsse8(ptr_store_vreg_memory_8, 1, vreg_memory_8, vl);
    vfloat16mf4_t vreg_4 = __riscv_vfnmsac(vmask, vreg_2, vreg_2, vreg_memory_4, __RISCV_FRM_RNE, vl);
    vuint16mf4_t idx_8 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 1, vl);
    __riscv_vsuxei16(ptr_store_vreg_4, idx_8, vreg_4, vl);
    vuint32mf2_t vreg_memory_9 = __riscv_vle32_v_u32mf2(ptr_load_9, vl);
    vreg_3 = __riscv_vmsleu(vreg_memory_9, 2005303637u, vl);
    vint8mf8_t zero_1 = __riscv_vmv_v_x_i8mf8(0, __riscv_vsetvlmax_e8mf8());
    vint8mf8_t vstore_tmp_1 = __riscv_vmerge_vxm_i8mf8(zero_1, 1, vreg_3, vl);
    __riscv_vse8_v_i8mf8(ptr_store_vreg_3, vstore_tmp_1, vl);
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
    ptr_store_vreg_memory_3 += vl;
    ptr_store_vreg_memory_7 += vl;
    ptr_store_vreg_memory_8 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_2[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_3[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_4[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_3[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_memory_7[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_8[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

