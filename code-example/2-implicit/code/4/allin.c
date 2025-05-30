// --seed 0x94f55d93 --data_length 5 --sequence_length 10 --root vint32m1_t --segment  --overloaded 
// scheduling mode: allin 
#include <riscv_vector.h>

#define dataLen 5
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
uint16_t data_load_1[dataLen];
uint16_t data_load_10[dataLen];
uint8_t data_load_11[dataLen];
uint32_t data_load_12[dataLen];
float16_t data_load_2[dataLen];
float64_t data_load_3[dataLen];
float32_t data_load_4[dataLen];
float32_t data_load_5[dataLen];
uint64_t data_load_6[dataLen];
uint64_t data_load_7[dataLen];
uint64_t data_load_8[dataLen];
int8_t data_load_9[dataLen];
uint32_t data_store_vreg_0[dataLen];
float64_t data_store_vreg_1[dataLen];
uint64_t data_store_vreg_2[dataLen];
uint16_t data_store_vreg_3[dataLen];
int8_t data_store_vreg_4[dataLen];
uint8_t data_store_vreg_5[dataLen];
uint8_t data_store_vreg_memory_11[dataLen];
uint64_t data_store_vreg_memory_7[dataLen];
int8_t data_store_vreg_memory_9[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 0, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint32_t tmp_0[dataLen] = {2799961323u, 83049832u, 2881210992u, 3031382802u, 283870185u, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  uint16_t tmp_1[dataLen] = {41006, 3898, 59144, 40026, 23926, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint16_t tmp_2[dataLen] = {27595, 18436, 58038, 36691, 55665, };
  for (int i = 0; i < dataLen; ++i) { data_load_10[i] = tmp_2[i]; }
  uint8_t tmp_3[dataLen] = {239, 233, 56, 89, 14, };
  for (int i = 0; i < dataLen; ++i) { data_load_11[i] = tmp_3[i]; }
  uint32_t tmp_4[dataLen] = {2630466674u, 2347495474u, 284027046u, 3035238493u, 2676368697u, };
  for (int i = 0; i < dataLen; ++i) { data_load_12[i] = tmp_4[i]; }
  uint16_t tmp_5[dataLen] = {36091, 61811, 4003, 17554, 29522, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = convert_binary_u16_f16(tmp_5[i]); }
  uint64_t tmp_6[dataLen] = {3818853872ull, 1996704920ull, 4224061978ull, 2249725729ull, 3611040642ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = convert_binary_u64_f64(tmp_6[i]); }
  uint32_t tmp_7[dataLen] = {1504282266u, 3457444190u, 1487110971u, 1766870759u, 1247975971u, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = convert_binary_u32_f32(tmp_7[i]); }
  uint32_t tmp_8[dataLen] = {3444397971u, 2754134680u, 139763848u, 2013285002u, 1569352138u, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = convert_binary_u32_f32(tmp_8[i]); }
  uint64_t tmp_9[dataLen] = {1251367104ull, 977632484ull, 1467274467ull, 1363378750ull, 3712986641ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = tmp_9[i]; }
  uint64_t tmp_10[dataLen] = {705020634ull, 2335993862ull, 1152654298ull, 3442395399ull, 14981656ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = tmp_10[i]; }
  uint64_t tmp_11[dataLen] = {1907327004ull, 2032948052ull, 4181605308ull, 2513917746ull, 1420983859ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_8[i] = tmp_11[i]; }
  int8_t tmp_12[dataLen] = {97, 57, 19, -70, -67, };
  for (int i = 0; i < dataLen; ++i) { data_load_9[i] = tmp_12[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_4[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_5[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_11[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_7[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_9[i] = 0; }
}

void CodeBlock_0() {
  int avl1 = dataLen;
  int8_t* ptr_mask = data_mask;
  uint32_t* ptr_load_0 = data_load_0;
  uint16_t* ptr_load_1 = data_load_1;
  uint16_t* ptr_load_10 = data_load_10;
  uint8_t* ptr_load_11 = data_load_11;
  uint32_t* ptr_load_12 = data_load_12;
  float16_t* ptr_load_2 = data_load_2;
  float64_t* ptr_load_3 = data_load_3;
  float32_t* ptr_load_4 = data_load_4;
  float32_t* ptr_load_5 = data_load_5;
  uint64_t* ptr_load_6 = data_load_6;
  uint64_t* ptr_load_7 = data_load_7;
  uint64_t* ptr_load_8 = data_load_8;
  int8_t* ptr_load_9 = data_load_9;
  uint32_t* ptr_store_vreg_0 = data_store_vreg_0;
  float64_t* ptr_store_vreg_1 = data_store_vreg_1;
  uint64_t* ptr_store_vreg_2 = data_store_vreg_2;
  uint16_t* ptr_store_vreg_3 = data_store_vreg_3;
  int8_t* ptr_store_vreg_4 = data_store_vreg_4;
  uint8_t* ptr_store_vreg_5 = data_store_vreg_5;
  uint8_t* ptr_store_vreg_memory_11 = data_store_vreg_memory_11;
  uint64_t* ptr_store_vreg_memory_7 = data_store_vreg_memory_7;
  int8_t* ptr_store_vreg_memory_9 = data_store_vreg_memory_9;
  for (size_t vl; avl1 > 0; avl1 -= vl){
    vl = __riscv_vsetvl_e32m1(avl1);
    vint8mf4_t mask_value= __riscv_vle8_v_i8mf4(ptr_mask, vl);
    vbool32_t vmask= __riscv_vmseq_vx_i8mf4_b32(mask_value, 1, vl);
    vuint32m1_t vreg_memory_0 = __riscv_vle32_v_u32m1(ptr_load_0, vl);
    vuint16mf2_t vreg_memory_1 = __riscv_vlse16_v_u16mf2(ptr_load_1, 2, vl);
    vreg_memory_1 = __riscv_vremu_vx_u16mf2(vreg_memory_1, (uint16_t)(vl), vl);
    vfloat16mf2_t vreg_memory_2 = __riscv_vle16(vmask, ptr_load_2, vl);
    vfloat64m2_t vreg_memory_3 = __riscv_vlse64_v_f64m2(ptr_load_3, 8, vl);
    vuint8mf4_t idx_0 = __riscv_vsll_vx_u8mf4(__riscv_vid_v_u8mf4(vl), 2, vl);
    vfloat32m1_t vreg_memory_4 = __riscv_vluxei8(vmask, ptr_load_4, idx_0, vl);
    vuint64m2_t idx_1 = __riscv_vsll_vx_u64m2(__riscv_vid_v_u64m2(vl), 2, vl);
    vfloat32m1_t vreg_memory_5 = __riscv_vluxei64(ptr_load_5, idx_1, vl);
    vuint32m1_t idx_2 = __riscv_vsll_vx_u32m1(__riscv_vid_v_u32m1(vl), 3, vl);
    vuint64m2_t vreg_memory_6 = __riscv_vluxei32(ptr_load_6, idx_2, vl);
    vuint64m2_t vreg_memory_7 = __riscv_vle64(vmask, ptr_load_7, vl);
    vuint64m2_t vreg_memory_8 = __riscv_vle64(vmask, ptr_load_8, vl);
    vint8mf4_t vreg_memory_9 = __riscv_vle8_v_i8mf4(ptr_load_9, vl);
    vuint16m2_t vreg_memory_10 = __riscv_vle16_v_u16m2(ptr_load_10, vl);
    vuint8mf4_t idx_5 = __riscv_vsll_vx_u8mf4(__riscv_vid_v_u8mf4(vl), 0, vl);
    vuint8mf4_t vreg_memory_11 = __riscv_vluxei8(vmask, ptr_load_11, idx_5, vl);
    vuint32m1_t vreg_memory_12 = __riscv_vle32_v_u32m1(ptr_load_12, vl);
    vuint32m1_t vreg_0 = __riscv_vrgatherei16(vmask, vreg_memory_0, vreg_memory_1, vl);
        vfloat64m2_t vreg_1 = __riscv_vfwmacc(vreg_memory_3, vreg_memory_4, vreg_memory_5, __RISCV_FRM_RDN, vl);
    vreg_memory_7 = __riscv_vmadd(vreg_memory_6, 4194866888ull, vreg_memory_7, vl);
    vuint64m2_t vreg_2 = __riscv_vmul(vreg_memory_8, vreg_memory_7, vl);
    vreg_memory_9 = __riscv_vxor(vmask, vreg_memory_9, -62, vl);
    vuint16m1_t vreg_3 = __riscv_vlmul_trunc_u16m1(vreg_memory_10);
    vbool32_t vreg_4 = __riscv_vmfle(vreg_memory_3, convert_binary_u64_f64(37472ull), vl);
    vreg_memory_11 = __riscv_vremu(vreg_memory_11, vreg_memory_11, vl);
    vuint8m1_t vreg_5 = __riscv_vreinterpret_u8m1(vreg_memory_12);
    __riscv_vse32(ptr_store_vreg_0, vreg_0, vl);
    __riscv_vse64(vmask, ptr_store_vreg_1, vreg_1, vl);
    __riscv_vse64(ptr_store_vreg_memory_7, vreg_memory_7, vl);
    vuint64m2_t idx_4 = __riscv_vsll_vx_u64m2(__riscv_vid_v_u64m2(vl), 3, vl);
    __riscv_vsoxei64(vmask, ptr_store_vreg_2, idx_4, vreg_2, vl);
    __riscv_vse8(ptr_store_vreg_memory_9, vreg_memory_9, vl);
    __riscv_vse16(ptr_store_vreg_3, vreg_3, vl);
    vint8mf4_t zero_0 = __riscv_vmv_v_x_i8mf4(0, __riscv_vsetvlmax_e8mf4());
    vint8mf4_t vstore_tmp_0 = __riscv_vmerge_vxm_i8mf4(zero_0, 1, vreg_4, vl);
    __riscv_vse8_v_i8mf4(ptr_store_vreg_4, vstore_tmp_0, vl);
    __riscv_vse8(ptr_store_vreg_memory_11, vreg_memory_11, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_10 += vl;
    ptr_load_11 += vl;
    ptr_load_12 += vl;
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
    ptr_store_vreg_5 += vl;
    ptr_store_vreg_memory_11 += vl;
    ptr_store_vreg_memory_7 += vl;
    ptr_store_vreg_memory_9 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_1[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_2[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_3[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_4[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_11[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_memory_7[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_9[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

