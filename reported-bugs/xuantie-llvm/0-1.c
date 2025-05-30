#include <riscv_vector.h>

#define dataLen 42
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
float16_t data_load_0[dataLen];
float32_t data_load_1[dataLen];
uint16_t data_load_2[dataLen];
int32_t data_store_vreg_0[dataLen];
float32_t data_store_vreg_memory_1[dataLen];
uint16_t data_store_vreg_memory_2[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint16_t tmp_0[dataLen] = {4660, 595, 9876, 23730, 41923, 10288, 53271, 39684, 33526, 58894, 29506, 60975, 4739, 23477, 32951, 60285, 4, 5175, 60332, 58465, 34021, 28286, 13138, 19782, 47494, 32264, 17655, 5855, 58006, 56702, 31228, 39196, 7031, 21020, 24311, 57764, 57048, 37562, 25795, 1874, 60864, 47574, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = convert_binary_u16_f16(tmp_0[i]); }
  uint32_t tmp_1[dataLen] = {1767485983u, 868016585u, 2517402604u, 1415259722u, 2146459023u, 182723328u, 2833670177u, 4142174655u, 2573055677u, 3060608838u, 921053283u, 2021024037u, 558127864u, 4135469946u, 4083649506u, 3784929716u, 3386193104u, 3408384446u, 1239435832u, 1460415729u, 2424400792u, 2597479851u, 2156270441u, 3687322796u, 1014918098u, 132779355u, 3925029299u, 3864946949u, 497611789u, 1546454697u, 2481302717u, 2448187217u, 3628822177u, 1100105197u, 2627967188u, 3045253698u, 3861912155u, 4065856336u, 1383967132u, 2735574808u, 939688510u, 4111338367u, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = convert_binary_u32_f32(tmp_1[i]); }
  uint16_t tmp_2[dataLen] = {47923, 15085, 14530, 1433, 15000, 2132, 19430, 17303, 9861, 24915, 30175, 5816, 12581, 55490, 41941, 30320, 32606, 36087, 61868, 61735, 18079, 37547, 58152, 34225, 50802, 51361, 49897, 20130, 39144, 36355, 54139, 14044, 61126, 55666, 49103, 48383, 2591, 19517, 37415, 8606, 3660, 15751, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = tmp_2[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_2[i] = 0; }
}

void CodeBlock_0() {
  int avl2 = dataLen;
  int8_t* ptr_mask = data_mask;
  float16_t* ptr_load_0 = data_load_0;
  float32_t* ptr_load_1 = data_load_1;
  uint16_t* ptr_load_2 = data_load_2;
  int32_t* ptr_store_vreg_0 = data_store_vreg_0;
  float32_t* ptr_store_vreg_memory_1 = data_store_vreg_memory_1;
  uint16_t* ptr_store_vreg_memory_2 = data_store_vreg_memory_2;
  for (size_t vl; avl2 > 0; avl2 -= vl){
    vl = __riscv_vsetvl_e16mf2(avl2);
    vint8mf4_t mask_value= __riscv_vle8_v_i8mf4(ptr_mask, vl);
    vbool32_t vmask= __riscv_vmseq_vx_i8mf4_b32(mask_value, 1, vl);
    vuint32m1_t idx_0 = __riscv_vsll_vx_u32m1(__riscv_vid_v_u32m1(vl), 1, vl);
    vfloat16mf2_t vreg_memory_0 = __riscv_vloxei32_v_f16mf2(ptr_load_0, idx_0, vl);
    vint32m1_t vreg_0 = __riscv_vfwcvt_x_f_v_i32m1_rm_m(vmask, vreg_memory_0, __RISCV_FRM_RTZ, vl);
    __riscv_vse32_v_i32m1_m(vmask, ptr_store_vreg_0, vreg_0, vl);
    vfloat32m1_t vreg_memory_1 = __riscv_vlse32_v_f32m1_m(vmask, ptr_load_1, 4, vl);
    vreg_memory_1 = __riscv_vfsqrt_v_f32m1_m(vmask, vreg_memory_1, vl);
    vuint64m2_t idx_2 = __riscv_vsll_vx_u64m2(__riscv_vid_v_u64m2(vl), 2, vl);
    __riscv_vsoxei64_v_f32m1_m(vmask, ptr_store_vreg_memory_1, idx_2, vreg_memory_1, vl);
    vuint16mf2_t vreg_memory_2 = __riscv_vlse16_v_u16mf2_m(vmask, ptr_load_2, 2, vl);
    vreg_memory_2 = __riscv_vssrl_vv_u16mf2(vreg_memory_2, vreg_memory_2, __RISCV_VXRM_RNE, vl);
    __riscv_vse16_v_u16mf2_m(vmask, ptr_store_vreg_memory_2, vreg_memory_2, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_2 += vl;
    ptr_store_vreg_0 += vl;
    ptr_store_vreg_memory_1 += vl;
    ptr_store_vreg_memory_2 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_memory_1[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_2[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}