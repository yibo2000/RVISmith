// --seed 0xb62863c7 --data_length 3 --sequence_length 9 --root vint8mf4_t --segment  --overloaded 
// scheduling mode: random 
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
float32_t data_load_0[dataLen];
uint8_t data_load_1[dataLen];
int64_t data_load_2[dataLen];
float16_t data_load_3[dataLen];
float32_t data_load_4[dataLen];
float64_t data_load_5[dataLen];
int32_t data_load_6[dataLen];
float32_t data_load_7[dataLen];
uint8_t data_store_vreg_0[dataLen];
int8_t data_store_vreg_1[dataLen];
float64_t data_store_vreg_2[dataLen];
int8_t data_store_vreg_3[dataLen];
uint16_t data_store_vreg_4[dataLen];
float32_t data_store_vreg_memory_0[dataLen];
float16_t data_store_vreg_memory_3[dataLen];
int32_t data_store_vreg_memory_6[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint32_t tmp_0[dataLen] = {356838715u, 1882427720u, 3329571576u, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = convert_binary_u32_f32(tmp_0[i]); }
  uint8_t tmp_1[dataLen] = {75, 203, 6, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  int64_t tmp_2[dataLen] = {4550828734610724387ll, 1708323409222172549ll, 1162269759018405763ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = tmp_2[i]; }
  uint16_t tmp_3[dataLen] = {37563, 18110, 15524, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = convert_binary_u16_f16(tmp_3[i]); }
  uint32_t tmp_4[dataLen] = {474066348u, 406869887u, 2673878430u, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = convert_binary_u32_f32(tmp_4[i]); }
  uint64_t tmp_5[dataLen] = {2975683467ull, 3712654934ull, 4162850965ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = convert_binary_u64_f64(tmp_5[i]); }
  int32_t tmp_6[dataLen] = {1663249536, -1552041554, -1337632638, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = tmp_6[i]; }
  uint32_t tmp_7[dataLen] = {3820074117u, 887081953u, 1879545980u, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = convert_binary_u32_f32(tmp_7[i]); }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_4[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_6[i] = 0; }
}

void CodeBlock_0() {
  int avl0 = dataLen;
  int8_t* ptr_mask = data_mask;
  float32_t* ptr_load_0 = data_load_0;
  uint8_t* ptr_load_1 = data_load_1;
  int64_t* ptr_load_2 = data_load_2;
  float16_t* ptr_load_3 = data_load_3;
  float32_t* ptr_load_4 = data_load_4;
  float64_t* ptr_load_5 = data_load_5;
  int32_t* ptr_load_6 = data_load_6;
  float32_t* ptr_load_7 = data_load_7;
  uint8_t* ptr_store_vreg_0 = data_store_vreg_0;
  int8_t* ptr_store_vreg_1 = data_store_vreg_1;
  float64_t* ptr_store_vreg_2 = data_store_vreg_2;
  int8_t* ptr_store_vreg_3 = data_store_vreg_3;
  uint16_t* ptr_store_vreg_4 = data_store_vreg_4;
  float32_t* ptr_store_vreg_memory_0 = data_store_vreg_memory_0;
  float16_t* ptr_store_vreg_memory_3 = data_store_vreg_memory_3;
  int32_t* ptr_store_vreg_memory_6 = data_store_vreg_memory_6;
  for (size_t vl; avl0 > 0; avl0 -= vl){
    vl = __riscv_vsetvl_e8mf4(avl0);
    vint8mf4_t mask_value= __riscv_vle8_v_i8mf4(ptr_mask, vl);
    vbool32_t vmask= __riscv_vmseq_vx_i8mf4_b32(mask_value, 1, vl);
    vfloat32m1_t vreg_memory_0 = __riscv_vle32_v_f32m1(ptr_load_0, vl);
    vfloat32m1_t vreg_memory_4 = __riscv_vle32_v_f32m1(ptr_load_4, vl);
    vuint8m8_t vreg_memory_1 = __riscv_vle8_v_u8m8(ptr_load_1, vl);
    vreg_memory_0 = __riscv_vfwadd_wf(vreg_memory_0, convert_binary_u16_f16(7428), __RISCV_FRM_RUP, vl);
    __riscv_vse32(ptr_store_vreg_memory_0, vreg_memory_0, vl);
    vuint8mf4_t vreg_0 = __riscv_vlmul_trunc_u8mf4(vreg_memory_1);
    __riscv_vse8(ptr_store_vreg_0, vreg_0, vl);
    vuint64m2_t idx_0 = __riscv_vsll_vx_u64m2(__riscv_vid_v_u64m2(vl), 3, vl);
    vint64m2_t vreg_memory_2 = __riscv_vluxei64(vmask, ptr_load_2, idx_0, vl);
    vbool32_t vreg_1 = __riscv_vmsle(vreg_memory_2, vreg_memory_2, vl);
    vfloat64m1_t vreg_memory_5 = __riscv_vle64_v_f64m1(ptr_load_5, vl);
    vuint32m1_t idx_3 = __riscv_vsll_vx_u32m1(__riscv_vid_v_u32m1(vl), 2, vl);
    vint8mf4_t zero_0 = __riscv_vmv_v_x_i8mf4(0, __riscv_vsetvlmax_e8mf4());
    vint32m1_t vreg_memory_6 = __riscv_vle32_v_i32m1(ptr_load_6, vl);
    vfloat16mf2_t vreg_memory_3 = __riscv_vlse16(vmask, ptr_load_3, 2, vl);
    vint8mf4_t vstore_tmp_0 = __riscv_vmerge_vxm_i8mf4(zero_0, 1, vreg_1, vl);
    __riscv_vse8_v_i8mf4(ptr_store_vreg_1, vstore_tmp_0, vl);
    vreg_memory_3 = __riscv_vfadd(vmask, vreg_memory_3, vreg_memory_3, vl);
    vfloat32m1_t vreg_memory_7 = __riscv_vluxei32(ptr_load_7, idx_3, vl);
    __riscv_vse16(ptr_store_vreg_memory_3, vreg_memory_3, vl);
    vfloat64m1_t vreg_2 = __riscv_vfwredosum(vreg_memory_4, vreg_memory_5, vl);
    __riscv_vse64(ptr_store_vreg_2, vreg_2, vl);
    vreg_memory_6 = __riscv_vssra(vreg_memory_6, 2447280921u, __RISCV_VXRM_RNE, vl);
    vuint32m1_t idx_2 = __riscv_vsll_vx_u32m1(__riscv_vid_v_u32m1(vl), 2, vl);
    __riscv_vsoxei32(ptr_store_vreg_memory_6, idx_2, vreg_memory_6, vl);
    vbool32_t vreg_3 = __riscv_vmsge(vreg_memory_2, vreg_memory_2, vl);
    vint8mf4_t zero_1 = __riscv_vmv_v_x_i8mf4(0, __riscv_vsetvlmax_e8mf4());
    vint8mf4_t vstore_tmp_1 = __riscv_vmerge_vxm_i8mf4(zero_1, 1, vreg_3, vl);
    __riscv_vse8_v_i8mf4(ptr_store_vreg_3, vstore_tmp_1, vl);
    vreg_0 = __riscv_vssubu(vreg_0, vreg_0, vl);
    __riscv_vse8(ptr_store_vreg_0, vreg_0, vl);
    vuint16mf2_t vreg_4 = __riscv_vfncvt_xu(vreg_memory_7, __RISCV_FRM_RUP, vl);
    __riscv_vsse16(ptr_store_vreg_4, 2, vreg_4, vl);
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
    ptr_store_vreg_1 += vl;
    ptr_store_vreg_2 += vl;
    ptr_store_vreg_3 += vl;
    ptr_store_vreg_4 += vl;
    ptr_store_vreg_memory_0 += vl;
    ptr_store_vreg_memory_3 += vl;
    ptr_store_vreg_memory_6 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<1; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_2[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_3[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_4[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_memory_0[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_memory_3[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_6[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

