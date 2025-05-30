// --seed 0xdf5cc6a4 --data_length 6 --sequence_length 7 --root vuint8mf8_t --segment  --policy 
// scheduling mode: allin 
#include <riscv_vector.h>

#define dataLen 6
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
int16_t data_load_1[dataLen];
uint8_t data_load_10[dataLen];
float32_t data_load_11[dataLen];
float32_t data_load_12[dataLen];
uint16_t data_load_13[dataLen];
uint64_t data_load_2[dataLen];
uint8_t data_load_3[dataLen];
uint16_t data_load_4[dataLen];
int64_t data_load_5[dataLen];
int32_t data_load_6[dataLen];
int64_t data_load_7[dataLen];
uint8_t data_load_8[dataLen];
uint8_t data_load_9[dataLen];
uint64_t data_store_vreg_0[dataLen];
int64_t data_store_vreg_1[dataLen];
uint8_t data_store_vreg_2[dataLen];
int32_t data_store_vreg_memory_0[dataLen];
float32_t data_store_vreg_memory_12[dataLen];
uint16_t data_store_vreg_memory_4[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 1, 0, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  int32_t tmp_0[dataLen] = {1075907327, -1943384456, -948018755, 930138409, -1640556644, -333954523, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  int16_t tmp_1[dataLen] = {-24920, 29769, -4029, 12636, -12113, 29099, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint8_t tmp_2[dataLen] = {40, 88, 219, 245, 134, 42, };
  for (int i = 0; i < dataLen; ++i) { data_load_10[i] = tmp_2[i]; }
  uint32_t tmp_3[dataLen] = {3135582502u, 1475411765u, 4236127238u, 3401503948u, 3131825302u, 3143723212u, };
  for (int i = 0; i < dataLen; ++i) { data_load_11[i] = convert_binary_u32_f32(tmp_3[i]); }
  uint32_t tmp_4[dataLen] = {3079110886u, 318935231u, 807270632u, 4052268968u, 3625666556u, 1356949477u, };
  for (int i = 0; i < dataLen; ++i) { data_load_12[i] = convert_binary_u32_f32(tmp_4[i]); }
  uint16_t tmp_5[dataLen] = {51065, 5481, 31921, 8067, 59099, 40439, };
  for (int i = 0; i < dataLen; ++i) { data_load_13[i] = tmp_5[i]; }
  uint64_t tmp_6[dataLen] = {3056336210ull, 2699781578ull, 1217272705ull, 772797943ull, 96463908ull, 2119121269ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = tmp_6[i]; }
  uint8_t tmp_7[dataLen] = {82, 146, 43, 12, 124, 104, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_7[i]; }
  uint16_t tmp_8[dataLen] = {23879, 41871, 45509, 46996, 34368, 10695, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = tmp_8[i]; }
  int64_t tmp_9[dataLen] = {4029174387572040020ll, -2767674314040314071ll, -2169588104000557838ll, 1409788636377843417ll, 2400402827374132268ll, -9101920023966325702ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = tmp_9[i]; }
  int32_t tmp_10[dataLen] = {-328920485, 1822528735, -1655439218, -81298150, -1570023480, 225325034, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = tmp_10[i]; }
  int64_t tmp_11[dataLen] = {-5862352253217993690ll, 7641518665098808686ll, 3790175074179047480ll, 7618025927625325251ll, 3787175650509952815ll, 5028270455920433521ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = tmp_11[i]; }
  uint8_t tmp_12[dataLen] = {179, 13, 155, 122, 12, 214, };
  for (int i = 0; i < dataLen; ++i) { data_load_8[i] = tmp_12[i]; }
  uint8_t tmp_13[dataLen] = {23, 199, 196, 79, 120, 244, };
  for (int i = 0; i < dataLen; ++i) { data_load_9[i] = tmp_13[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_12[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_4[i] = 0; }
}

void CodeBlock_0() {
  int avl1 = dataLen;
  int8_t* ptr_mask = data_mask;
  int32_t* ptr_load_0 = data_load_0;
  int16_t* ptr_load_1 = data_load_1;
  uint8_t* ptr_load_10 = data_load_10;
  float32_t* ptr_load_11 = data_load_11;
  float32_t* ptr_load_12 = data_load_12;
  uint16_t* ptr_load_13 = data_load_13;
  uint64_t* ptr_load_2 = data_load_2;
  uint8_t* ptr_load_3 = data_load_3;
  uint16_t* ptr_load_4 = data_load_4;
  int64_t* ptr_load_5 = data_load_5;
  int32_t* ptr_load_6 = data_load_6;
  int64_t* ptr_load_7 = data_load_7;
  uint8_t* ptr_load_8 = data_load_8;
  uint8_t* ptr_load_9 = data_load_9;
  uint64_t* ptr_store_vreg_0 = data_store_vreg_0;
  int64_t* ptr_store_vreg_1 = data_store_vreg_1;
  uint8_t* ptr_store_vreg_2 = data_store_vreg_2;
  int32_t* ptr_store_vreg_memory_0 = data_store_vreg_memory_0;
  float32_t* ptr_store_vreg_memory_12 = data_store_vreg_memory_12;
  uint16_t* ptr_store_vreg_memory_4 = data_store_vreg_memory_4;
  for (size_t vl; avl1 > 0; avl1 -= vl){
    vl = __riscv_vsetvl_e8mf8(avl1);
    vint8mf8_t mask_value= __riscv_vle8_v_i8mf8(ptr_mask, vl);
    vbool64_t vmask= __riscv_vmseq_vx_i8mf8_b64(mask_value, 1, vl);
    vint32mf2_t vd_load_0 = __riscv_vmv_v_x_i32mf2(0, __riscv_vsetvlmax_e32mf2());
    vuint16mf4_t idx_0 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 2, vl);
    vint32mf2_t vreg_memory_0 = __riscv_vloxei16_v_i32mf2_tu(vd_load_0, ptr_load_0, idx_0, vl);
    vint16mf4_t vd_load_1 = __riscv_vmv_v_x_i16mf4(0, __riscv_vsetvlmax_e16mf4());
    vuint64m1_t idx_1 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 1, vl);
    vint16mf4_t vreg_memory_1 = __riscv_vluxei64_v_i16mf4_tu(vd_load_1, ptr_load_1, idx_1, vl);
    vuint64m1_t vd_load_2 = __riscv_vmv_v_x_u64m1(0, __riscv_vsetvlmax_e64m1());
    vuint64m1_t vreg_memory_2 = __riscv_vlse64_v_u64m1_mu(vmask, vd_load_2, ptr_load_2, 8, vl);
    vuint8mf8_t vd_load_3 = __riscv_vmv_v_x_u8mf8(0, __riscv_vsetvlmax_e8mf8());
    vuint8mf8_t vreg_memory_3 = __riscv_vlse8_v_u8mf8_tu(vd_load_3, ptr_load_3, 1, vl);
    vuint16mf4_t vd_load_4 = __riscv_vmv_v_x_u16mf4(0, __riscv_vsetvlmax_e16mf4());
    vuint16mf4_t vreg_memory_4 = __riscv_vle16_v_u16mf4_tu(vd_load_4, ptr_load_4, vl);
    vint64m1_t vd_load_5 = __riscv_vmv_v_x_i64m1(0, __riscv_vsetvlmax_e64m1());
    vuint64m1_t idx_4 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 3, vl);
    vint64m1_t vreg_memory_5 = __riscv_vloxei64_v_i64m1_tu(vd_load_5, ptr_load_5, idx_4, vl);
    vint32mf2_t vd_load_6 = __riscv_vmv_v_x_i32mf2(0, __riscv_vsetvlmax_e32mf2());
    vint32mf2_t vreg_memory_6 = __riscv_vlse32_v_i32mf2_tu(vd_load_6, ptr_load_6, 4, vl);
    vint64m1_t vd_load_7 = __riscv_vmv_v_x_i64m1(0, __riscv_vsetvlmax_e64m1());
    vuint16mf4_t idx_5 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 3, vl);
    vint64m1_t vreg_memory_7 = __riscv_vloxei16_v_i64m1_tum(vmask, vd_load_7, ptr_load_7, idx_5, vl);
    vuint8m1_t vd_load_8 = __riscv_vmv_v_x_u8m1(0, __riscv_vsetvlmax_e8m1());
    vuint8m1_t vreg_memory_8 = __riscv_vle8_v_u8m1_tu(vd_load_8, ptr_load_8, vl);
    vuint8mf8_t vd_load_9 = __riscv_vmv_v_x_u8mf8(0, __riscv_vsetvlmax_e8mf8());
    vuint8mf8_t vreg_memory_9 = __riscv_vle8_v_u8mf8_tu(vd_load_9, ptr_load_9, vl);
    vuint8m1_t vd_load_10 = __riscv_vmv_v_x_u8m1(0, __riscv_vsetvlmax_e8m1());
    vuint8m1_t vreg_memory_10 = __riscv_vle8_v_u8m1_tu(vd_load_10, ptr_load_10, vl);
    vfloat32mf2_t vd_load_11 = __riscv_vfmv_v_f_f32mf2(0, __riscv_vsetvlmax_e32mf2());
    vfloat32mf2_t vreg_memory_11 = __riscv_vle32_v_f32mf2_tu(vd_load_11, ptr_load_11, vl);
    vfloat32mf2_t vd_load_12 = __riscv_vfmv_v_f_f32mf2(0, __riscv_vsetvlmax_e32mf2());
    vfloat32mf2_t vreg_memory_12 = __riscv_vle32_v_f32mf2_tu(vd_load_12, ptr_load_12, vl);
    vuint16mf4_t vd_load_13 = __riscv_vmv_v_x_u16mf4(0, __riscv_vsetvlmax_e16mf4());
    vuint16mf4_t idx_8 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 1, vl);
    vuint16mf4_t vreg_memory_13 = __riscv_vloxei16_v_u16mf4_tu(vd_load_13, ptr_load_13, idx_8, vl);
    vreg_memory_13 = __riscv_vremu_vx_u16mf4(vreg_memory_13, (uint16_t)(vl), vl);
    vreg_memory_0 = __riscv_vwadd_vv_i32mf2_tum(vmask, vreg_memory_0, vreg_memory_1, vreg_memory_1, vl);
    vuint64m1_t vreg_0 = __riscv_vzext_vf8_u64m1_mu(vmask, vreg_memory_2, vreg_memory_3, vl);
    vreg_memory_4 = __riscv_vsaddu_vv_u16mf4_tum(vmask, vreg_memory_4, vreg_memory_4, vreg_memory_4, vl);
    vint64m1_t vreg_1 = __riscv_vwadd_wv_i64m1_tu(vreg_memory_5, vreg_memory_5, vreg_memory_6, vl);
    vreg_1 = __riscv_vmadd_vx_i64m1_tumu(vmask, vreg_1, 1417169801500566038ll, vreg_memory_7, vl);
    vuint8m1_t vreg_2 = __riscv_vredand_vs_u8mf8_u8m1_tum(vmask, vreg_memory_8, vreg_memory_9, vreg_memory_10, vl);
    vreg_memory_12 = __riscv_vrgatherei16_vv_f32mf2_tu(vreg_memory_11, vreg_memory_12, vreg_memory_13, vl);
    vuint64m1_t idx_3 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 2, vl);
    __riscv_vsuxei64_v_i32mf2_m(vmask, ptr_store_vreg_memory_0, idx_3, vreg_memory_0, vl);
    __riscv_vse64_v_u64m1(ptr_store_vreg_0, vreg_0, vl);
    __riscv_vse16_v_u16mf4(ptr_store_vreg_memory_4, vreg_memory_4, vl);
    __riscv_vse64_v_i64m1(ptr_store_vreg_1, vreg_1, vl);
    vuint64m1_t idx_7 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 3, vl);
    __riscv_vsoxei64_v_i64m1(ptr_store_vreg_1, idx_7, vreg_1, vl);
    __riscv_vse8_v_u8m1(ptr_store_vreg_2, vreg_2, vl);
    vuint32mf2_t idx_10 = __riscv_vsll_vx_u32mf2(__riscv_vid_v_u32mf2(vl), 2, vl);
    __riscv_vsoxei32_v_f32mf2(ptr_store_vreg_memory_12, idx_10, vreg_memory_12, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_10 += vl;
    ptr_load_11 += vl;
    ptr_load_12 += vl;
    ptr_load_13 += vl;
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
    ptr_store_vreg_memory_0 += vl;
    ptr_store_vreg_memory_12 += vl;
    ptr_store_vreg_memory_4 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_2[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_memory_12[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_4[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

