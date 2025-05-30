// --seed 0x86233c47 --data_length 8 --sequence_length 4 --root vint16mf4_t --segment  --overloaded 
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
float64_t data_load_1[dataLen];
uint32_t data_load_2[dataLen];
int8_t data_load_3[dataLen];
int32_t data_load_4[dataLen];
int8_t data_store_vreg_0[dataLen];
float64_t data_store_vreg_memory_0[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 1, 0, 0, 1, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint64_t tmp_0[dataLen] = {2799149556ull, 3899717980ull, 3131573042ull, 320463214ull, 27719459ull, 551860994ull, 2155507999ull, 3620526082ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = convert_binary_u64_f64(tmp_0[i]); }
  uint64_t tmp_1[dataLen] = {1604443712ull, 1764093457ull, 1518792618ull, 2908500655ull, 1194429231ull, 2189789858ull, 343698958ull, 1644795677ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = convert_binary_u64_f64(tmp_1[i]); }
  uint32_t tmp_2[dataLen] = {1535056950u, 1623164111u, 1549207591u, 1231300731u, 149309978u, 1398167017u, 1952591055u, 3544688510u, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = tmp_2[i]; }
  int8_t tmp_3[dataLen] = {-37, -14, 57, -10, -12, -58, -60, -33, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_3[i]; }
  int32_t tmp_4[dataLen] = {846000498, 182430660, 598077819, 246789035, -1673339124, 782295024, -1644252399, 1756066026, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = tmp_4[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_0[i] = 0; }
}

void CodeBlock_0() {
  int avl1 = dataLen;
  int8_t* ptr_mask = data_mask;
  float64_t* ptr_load_0 = data_load_0;
  float64_t* ptr_load_1 = data_load_1;
  uint32_t* ptr_load_2 = data_load_2;
  int8_t* ptr_load_3 = data_load_3;
  int32_t* ptr_load_4 = data_load_4;
  int8_t* ptr_store_vreg_0 = data_store_vreg_0;
  float64_t* ptr_store_vreg_memory_0 = data_store_vreg_memory_0;
  for (size_t vl; avl1 > 0; avl1 -= vl){
    vl = __riscv_vsetvl_e16mf4(avl1);
    vint8mf8_t mask_value= __riscv_vle8_v_i8mf8(ptr_mask, vl);
    vbool64_t vmask= __riscv_vmseq_vx_i8mf8_b64(mask_value, 1, vl);
    vfloat64m1_t vreg_memory_0 = __riscv_vle64_v_f64m1(ptr_load_0, vl);
    vfloat64m1_t vreg_memory_1 = __riscv_vle64_v_f64m1(ptr_load_1, vl);
    vuint8mf8_t idx_0 = __riscv_vsll_vx_u8mf8(__riscv_vid_v_u8mf8(vl), 2, vl);
    vuint32mf2_t vreg_memory_2 = __riscv_vloxei8(ptr_load_2, idx_0, vl);
    vint8mf8_t vload_tmp_1 = __riscv_vle8_v_i8mf8(ptr_load_3, vl);
    vbool64_t vreg_memory_3 = __riscv_vmseq_vx_i8mf8_b64(vload_tmp_1, 1, vl);
    vint32mf2_t vreg_memory_4 = __riscv_vle32(vmask, ptr_load_4, vl);
    vreg_memory_0 = __riscv_vfsub(vreg_memory_0, convert_binary_u64_f64(39721ull), __RISCV_FRM_RDN, vl);
    vbool64_t vreg_0 = __riscv_vmflt(vreg_memory_1, vreg_memory_1, vl);
    vreg_0 = __riscv_vmadc(vreg_memory_2, vreg_memory_2, vreg_memory_3, vl);
    vreg_0 = __riscv_vmsge(vreg_memory_4, -1507799501, vl);
    __riscv_vsse64(ptr_store_vreg_memory_0, 8, vreg_memory_0, vl);
    vint8mf8_t zero_0 = __riscv_vmv_v_x_i8mf8(0, __riscv_vsetvlmax_e8mf8());
    vint8mf8_t vstore_tmp_0 = __riscv_vmerge_vxm_i8mf8(zero_0, 1, vreg_0, vl);
    __riscv_vse8_v_i8mf8(ptr_store_vreg_0, vstore_tmp_0, vl);
    vint8mf8_t zero_2 = __riscv_vmv_v_x_i8mf8(0, __riscv_vsetvlmax_e8mf8());
    vint8mf8_t vstore_tmp_2 = __riscv_vmerge_vxm_i8mf8(zero_2, 1, vreg_0, vl);
    __riscv_vse8_v_i8mf8(ptr_store_vreg_0, vstore_tmp_2, vl);
    vint8mf8_t zero_3 = __riscv_vmv_v_x_i8mf8(0, __riscv_vsetvlmax_e8mf8());
    vint8mf8_t vstore_tmp_3 = __riscv_vmerge_vxm_i8mf8(zero_3, 1, vreg_0, vl);
    __riscv_vse8_v_i8mf8(ptr_store_vreg_0, vstore_tmp_3, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_2 += vl;
    ptr_load_3 += vl;
    ptr_load_4 += vl;
    ptr_store_vreg_0 += vl;
    ptr_store_vreg_memory_0 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_memory_0[i])); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

