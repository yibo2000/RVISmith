// --seed 0x604e2499 --data_length 8 --sequence_length 5 --root vbool8_t --segment 
// scheduling mode: allin 
#include <riscv_vector.h>

#define dataLen 8
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
float64_t data_load_0[dataLen];
float32_t data_load_1[dataLen];
uint16_t data_load_2[dataLen];
int64_t data_load_3[dataLen];
uint32_t data_load_4[dataLen];
float16_t data_load_5[dataLen];
uint8_t data_load_6[dataLen];
int32_t data_store_vreg_0[dataLen];
float16_t data_store_vreg_1[dataLen];
float64_t data_store_vreg_memory_0[dataLen];
uint16_t data_store_vreg_memory_2[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 0, 1, 0, 1, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint64_t tmp_0[dataLen] = {394693947ull, 1933430523ull, 1826531834ull, 3977557794ull, 2306743791ull, 953246848ull, 1217554902ull, 2061963720ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = convert_binary_u64_f64(tmp_0[i]); }
  uint32_t tmp_1[dataLen] = {3136115871u, 1934103798u, 526883541u, 3646339802u, 2497274255u, 2715494126u, 2549111685u, 2609883055u, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = convert_binary_u32_f32(tmp_1[i]); }
  uint16_t tmp_2[dataLen] = {30773, 38615, 50397, 4414, 50645, 9148, 2798, 54942, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = tmp_2[i]; }
  int64_t tmp_3[dataLen] = {1704619282421265365ll, 7994441282877587039ll, 8068809604059899637ll, -4899392225809097437ll, 6170395312419464024ll, 9057174488672855753ll, -1993463589902894922ll, -2174469106341511579ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_3[i]; }
  uint32_t tmp_4[dataLen] = {645684391u, 2400442181u, 2769558602u, 706078002u, 4209446414u, 868456452u, 2092174818u, 1668704447u, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = tmp_4[i]; }
  uint16_t tmp_5[dataLen] = {31890, 43306, 31132, 33080, 13341, 10109, 53879, 5119, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = convert_binary_u16_f16(tmp_5[i]); }
  uint8_t tmp_6[dataLen] = {38, 147, 211, 41, 138, 25, 27, 76, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = tmp_6[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_2[i] = 0; }
}

void CodeBlock_0() {
  int avl1 = dataLen;
  int8_t* ptr_mask = data_mask;
  float64_t* ptr_load_0 = data_load_0;
  float32_t* ptr_load_1 = data_load_1;
  uint16_t* ptr_load_2 = data_load_2;
  int64_t* ptr_load_3 = data_load_3;
  uint32_t* ptr_load_4 = data_load_4;
  float16_t* ptr_load_5 = data_load_5;
  uint8_t* ptr_load_6 = data_load_6;
  int32_t* ptr_store_vreg_0 = data_store_vreg_0;
  float16_t* ptr_store_vreg_1 = data_store_vreg_1;
  float64_t* ptr_store_vreg_memory_0 = data_store_vreg_memory_0;
  uint16_t* ptr_store_vreg_memory_2 = data_store_vreg_memory_2;
  for (size_t vl; avl1 > 0; avl1 -= vl){
    vl = __riscv_vsetvl_e8m1(avl1);
    vint8m1_t mask_value= __riscv_vle8_v_i8m1(ptr_mask, vl);
    vbool8_t vmask= __riscv_vmseq_vx_i8m1_b8(mask_value, 1, vl);
    vfloat64m8_t vreg_memory_0 = __riscv_vle64_v_f64m8(ptr_load_0, vl);
    vfloat32m4_t vreg_memory_1 = __riscv_vlse32_v_f32m4(ptr_load_1, 4, vl);
    vuint16m2_t vreg_memory_2 = __riscv_vle16_v_u16m2(ptr_load_2, vl);
    vuint32m4_t idx_2 = __riscv_vsll_vx_u32m4(__riscv_vid_v_u32m4(vl), 3, vl);
    vint64m8_t vreg_memory_3 = __riscv_vloxei32_v_i64m8_m(vmask, ptr_load_3, idx_2, vl);
    vuint32m4_t vreg_memory_4 = __riscv_vle32_v_u32m4(ptr_load_4, vl);
    vfloat16mf4_t vreg_memory_5 = __riscv_vle16_v_f16mf4(ptr_load_5, vl);
    vuint8m1_t vreg_memory_6 = __riscv_vlse8_v_u8m1(ptr_load_6, 1, vl);
    vreg_memory_0 = __riscv_vfwmsac_vf_f64m8(vreg_memory_0, convert_binary_u32_f32(41493u), vreg_memory_1, vl);
    vreg_memory_2 = __riscv_vslidedown_vx_u16m2(vreg_memory_2, 709788982u, vl);
    vint32m4_t vreg_0 = __riscv_vnsra_wv_i32m4_m(vmask, vreg_memory_3, vreg_memory_4, vl);
    vfloat16mf2_t vreg_1 = __riscv_vlmul_ext_v_f16mf4_f16mf2(vreg_memory_5);
    vreg_memory_2 = __riscv_vwmulu_vx_u16m2_m(vmask, vreg_memory_6, 162, vl);
    vuint16m2_t idx_1 = __riscv_vsll_vx_u16m2(__riscv_vid_v_u16m2(vl), 3, vl);
    __riscv_vsuxei16_v_f64m8_m(vmask, ptr_store_vreg_memory_0, idx_1, vreg_memory_0, vl);
    __riscv_vse16_v_u16m2(ptr_store_vreg_memory_2, vreg_memory_2, vl);
    __riscv_vse32_v_i32m4(ptr_store_vreg_0, vreg_0, vl);
    __riscv_vsse16_v_u16m2(ptr_store_vreg_memory_2, 2, vreg_memory_2, vl);
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
    ptr_store_vreg_memory_2 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_memory_0[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_2[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

