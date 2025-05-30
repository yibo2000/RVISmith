// --seed 0x3a6e49e --data_length 4 --sequence_length 6 --root vint32m8_t --segment  --policy  --overloaded 
// scheduling mode: random 
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
uint32_t data_load_0[dataLen];
uint8_t data_load_1[dataLen];
uint8_t data_load_2[dataLen];
uint8_t data_load_3[dataLen];
uint32_t data_load_4[dataLen];
int32_t data_load_5[dataLen];
int8_t data_load_6[dataLen];
float16_t data_load_7[dataLen];
uint16_t data_store_vreg_0[dataLen];
uint32_t data_store_vreg_memory_0[dataLen];
uint8_t data_store_vreg_memory_1[dataLen];
int32_t data_store_vreg_memory_5[dataLen];
int8_t data_store_vreg_memory_6[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint32_t tmp_0[dataLen] = {2822940187u, 1690984765u, 2060079048u, 1216779335u, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  uint8_t tmp_1[dataLen] = {187, 178, 187, 36, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint8_t tmp_2[dataLen] = {149, 122, 53, 205, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = tmp_2[i]; }
  uint8_t tmp_3[dataLen] = {249, 144, 143, 138, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_3[i]; }
  uint32_t tmp_4[dataLen] = {1464265578u, 3087696061u, 1835128837u, 2487891754u, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = tmp_4[i]; }
  int32_t tmp_5[dataLen] = {684665913, 1570866637, -1416870806, 113203048, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = tmp_5[i]; }
  int8_t tmp_6[dataLen] = {-103, 101, 46, 77, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = tmp_6[i]; }
  uint16_t tmp_7[dataLen] = {56276, 59696, 56762, 11071, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = convert_binary_u16_f16(tmp_7[i]); }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_5[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_6[i] = 0; }
}

void CodeBlock_0() {
  int avl0 = dataLen;
  int8_t* ptr_mask = data_mask;
  uint32_t* ptr_load_0 = data_load_0;
  uint8_t* ptr_load_1 = data_load_1;
  uint8_t* ptr_load_2 = data_load_2;
  uint8_t* ptr_load_3 = data_load_3;
  uint32_t* ptr_load_4 = data_load_4;
  int32_t* ptr_load_5 = data_load_5;
  int8_t* ptr_load_6 = data_load_6;
  float16_t* ptr_load_7 = data_load_7;
  uint16_t* ptr_store_vreg_0 = data_store_vreg_0;
  uint32_t* ptr_store_vreg_memory_0 = data_store_vreg_memory_0;
  uint8_t* ptr_store_vreg_memory_1 = data_store_vreg_memory_1;
  int32_t* ptr_store_vreg_memory_5 = data_store_vreg_memory_5;
  int8_t* ptr_store_vreg_memory_6 = data_store_vreg_memory_6;
  for (size_t vl; avl0 > 0; avl0 -= vl){
    vl = __riscv_vsetvl_e32m8(avl0);
    vint8m2_t mask_value= __riscv_vle8_v_i8m2(ptr_mask, vl);
    vbool4_t vmask= __riscv_vmseq_vx_i8m2_b4(mask_value, 1, vl);
    vuint32m8_t vd_load_0 = __riscv_vmv_v_x_u32m8(0, __riscv_vsetvlmax_e32m8());
    vint32m8_t vd_load_5 = __riscv_vmv_v_x_i32m8(0, __riscv_vsetvlmax_e32m8());
    vint32m8_t vreg_memory_5 = __riscv_vle32_v_i32m8_tu(vd_load_5, ptr_load_5, vl);
    vuint16m4_t idx_0 = __riscv_vsll_vx_u16m4(__riscv_vid_v_u16m4(vl), 2, vl);
    vuint8m2_t vd_load_1 = __riscv_vmv_v_x_u8m2(0, __riscv_vsetvlmax_e8m2());
    vuint32m8_t vreg_memory_0 = __riscv_vluxei16_tu(vd_load_0, ptr_load_0, idx_0, vl);
    vuint32m8_t idx_1 = __riscv_vsll_vx_u32m8(__riscv_vid_v_u32m8(vl), 0, vl);
    vuint8m2_t vreg_memory_1 = __riscv_vloxei32_tu(vd_load_1, ptr_load_1, idx_1, vl);
    vreg_memory_0 = __riscv_vmulhu_tu(vreg_memory_0, vreg_memory_0, 2969655483u, vl);
    __riscv_vsse32_v_u32m8_m(vmask, ptr_store_vreg_memory_0, 4, vreg_memory_0, vl);
    vuint8m2_t vd_load_2 = __riscv_vmv_v_x_u8m2(0, __riscv_vsetvlmax_e8m2());
    vuint8mf2_t vd_load_3 = __riscv_vmv_v_x_u8mf2(0, __riscv_vsetvlmax_e8mf2());
    vuint32m8_t idx_2 = __riscv_vsll_vx_u32m8(__riscv_vid_v_u32m8(vl), 0, vl);
    vuint8mf2_t vreg_memory_3 = __riscv_vle8_v_u8mf2_tu(vd_load_3, ptr_load_3, vl);
    vuint8m2_t vreg_memory_2 = __riscv_vloxei32_tu(vd_load_2, ptr_load_2, idx_2, vl);
    vreg_memory_1 = __riscv_vnmsub_vx_u8m2_tu(vreg_memory_1, 168, vreg_memory_2, vl);
    vuint32m8_t vd_load_4 = __riscv_vmv_v_x_u32m8(0, __riscv_vsetvlmax_e32m8());
    vint8m2_t vload_tmp_0 = __riscv_vle8_v_i8m2(ptr_load_6, vl);
    vuint32m8_t vreg_memory_4 = __riscv_vlse32_v_u32m8_tu(vd_load_4, ptr_load_4, 4, vl);
    vuint32m8_t idx_4 = __riscv_vsll_vx_u32m8(__riscv_vid_v_u32m8(vl), 0, vl);
    __riscv_vsuxei32_v_u8m2(ptr_store_vreg_memory_1, idx_4, vreg_memory_1, vl);
    vbool4_t vreg_memory_6 = __riscv_vmseq_vx_i8m2_b4(vload_tmp_0, 1, vl);
    vfloat16m4_t vd_load_7 = __riscv_vfmv_v_f_f16m4(0, __riscv_vsetvlmax_e16m4());
    vuint16mf2_t vreg_0 = __riscv_vreinterpret_v_u8mf2_u16mf2(vreg_memory_3);
    vreg_memory_0 = __riscv_vmaxu_tu(vreg_memory_0, vreg_memory_4, 3994280981u, vl);
    __riscv_vse32_v_u32m8(ptr_store_vreg_memory_0, vreg_memory_0, vl);
    vreg_memory_5 = __riscv_vmulhsu_vv_i32m8(vreg_memory_5, vreg_memory_4, vl);
    vfloat16m4_t vreg_memory_7 = __riscv_vle16_mu(vmask, vd_load_7, ptr_load_7, vl);
    __riscv_vse32_v_i32m8(ptr_store_vreg_memory_5, vreg_memory_5, vl);
    vreg_memory_6 = __riscv_vmfgt_vv_f16m4_b4_mu(vmask, vreg_memory_6, vreg_memory_7, vreg_memory_7, vl);
    vint8m2_t zero_1 = __riscv_vmv_v_x_i8m2(0, __riscv_vsetvlmax_e8m2());
    vint8m2_t vstore_tmp_1 = __riscv_vmerge_vxm_i8m2(zero_1, 1, vreg_memory_6, vl);
    __riscv_vse8_v_i8m2(ptr_store_vreg_memory_6, vstore_tmp_1, vl);
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
    ptr_store_vreg_memory_0 += vl;
    ptr_store_vreg_memory_1 += vl;
    ptr_store_vreg_memory_5 += vl;
    ptr_store_vreg_memory_6 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_5[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_6[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

