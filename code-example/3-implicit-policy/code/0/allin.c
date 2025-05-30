// --seed 0xe53cafbd --data_length 6 --sequence_length 10 --root vuint64m2_t --segment  --policy  --overloaded 
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
uint8_t data_load_0[dataLen];
int16_t data_load_1[dataLen];
float32_t data_load_10[dataLen];
int64_t data_load_11[dataLen];
int64_t data_load_12[dataLen];
float32_t data_load_2[dataLen];
float64_t data_load_3[dataLen];
int8_t data_load_4[dataLen];
uint16_t data_load_5[dataLen];
uint16_t data_load_6[dataLen];
uint64_t data_load_7[dataLen];
uint64_t data_load_8[dataLen];
float16_t data_load_9[dataLen];
int16_t data_store_vreg_0[dataLen];
int16_t data_store_vreg_1[dataLen];
float16_t data_store_vreg_2[dataLen];
uint8_t data_store_vreg_memory_0[dataLen];
int64_t data_store_vreg_memory_12[dataLen];
float32_t data_store_vreg_memory_2[dataLen];
float64_t data_store_vreg_memory_3[dataLen];
uint16_t data_store_vreg_memory_5[dataLen];
uint64_t data_store_vreg_memory_7[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 0, 0, 0, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint8_t tmp_0[dataLen] = {89, 28, 44, 14, 107, 131, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  int16_t tmp_1[dataLen] = {15659, -20400, -25650, 11323, -28171, 29014, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint32_t tmp_2[dataLen] = {2040608777u, 3529669845u, 2584560298u, 2632481739u, 2461885254u, 502157554u, };
  for (int i = 0; i < dataLen; ++i) { data_load_10[i] = convert_binary_u32_f32(tmp_2[i]); }
  int64_t tmp_3[dataLen] = {-1553719165307782522ll, -6352585011120739771ll, 8313778516583102486ll, -8875834552832812326ll, 5304959708955946625ll, -438160657924954744ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_11[i] = tmp_3[i]; }
  int64_t tmp_4[dataLen] = {9213851635266998007ll, -1193698323340465565ll, -5121862032932708010ll, 8703728135344935517ll, -7319809660624770220ll, -6099847823151012903ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_12[i] = tmp_4[i]; }
  uint32_t tmp_5[dataLen] = {300797579u, 3947607601u, 1107536023u, 2477632164u, 825201373u, 3688368545u, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = convert_binary_u32_f32(tmp_5[i]); }
  uint64_t tmp_6[dataLen] = {2308612875ull, 2268031105ull, 1862753194ull, 2527231268ull, 1538588785ull, 415379486ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = convert_binary_u64_f64(tmp_6[i]); }
  int8_t tmp_7[dataLen] = {-87, -30, -65, 70, -119, 57, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = tmp_7[i]; }
  uint16_t tmp_8[dataLen] = {59978, 24924, 32997, 5790, 2143, 26279, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = tmp_8[i]; }
  uint16_t tmp_9[dataLen] = {59193, 53104, 25685, 42000, 60383, 26012, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = tmp_9[i]; }
  uint64_t tmp_10[dataLen] = {3646435608ull, 2910224313ull, 726854865ull, 3460674501ull, 4101867212ull, 754254638ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = tmp_10[i]; }
  uint64_t tmp_11[dataLen] = {889315513ull, 2534550295ull, 965548563ull, 2698420974ull, 2940182681ull, 3803776500ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_8[i] = tmp_11[i]; }
  uint16_t tmp_12[dataLen] = {6042, 20410, 19408, 40946, 47349, 23513, };
  for (int i = 0; i < dataLen; ++i) { data_load_9[i] = convert_binary_u16_f16(tmp_12[i]); }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_12[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_5[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_7[i] = 0; }
}

void CodeBlock_0() {
  int avl1 = dataLen;
  int8_t* ptr_mask = data_mask;
  uint8_t* ptr_load_0 = data_load_0;
  int16_t* ptr_load_1 = data_load_1;
  float32_t* ptr_load_10 = data_load_10;
  int64_t* ptr_load_11 = data_load_11;
  int64_t* ptr_load_12 = data_load_12;
  float32_t* ptr_load_2 = data_load_2;
  float64_t* ptr_load_3 = data_load_3;
  int8_t* ptr_load_4 = data_load_4;
  uint16_t* ptr_load_5 = data_load_5;
  uint16_t* ptr_load_6 = data_load_6;
  uint64_t* ptr_load_7 = data_load_7;
  uint64_t* ptr_load_8 = data_load_8;
  float16_t* ptr_load_9 = data_load_9;
  int16_t* ptr_store_vreg_0 = data_store_vreg_0;
  int16_t* ptr_store_vreg_1 = data_store_vreg_1;
  float16_t* ptr_store_vreg_2 = data_store_vreg_2;
  uint8_t* ptr_store_vreg_memory_0 = data_store_vreg_memory_0;
  int64_t* ptr_store_vreg_memory_12 = data_store_vreg_memory_12;
  float32_t* ptr_store_vreg_memory_2 = data_store_vreg_memory_2;
  float64_t* ptr_store_vreg_memory_3 = data_store_vreg_memory_3;
  uint16_t* ptr_store_vreg_memory_5 = data_store_vreg_memory_5;
  uint64_t* ptr_store_vreg_memory_7 = data_store_vreg_memory_7;
  for (size_t vl; avl1 > 0; avl1 -= vl){
    vl = __riscv_vsetvl_e64m2(avl1);
    vint8mf4_t mask_value= __riscv_vle8_v_i8mf4(ptr_mask, vl);
    vbool32_t vmask= __riscv_vmseq_vx_i8mf4_b32(mask_value, 1, vl);
    vuint8mf4_t vd_load_0 = __riscv_vmv_v_x_u8mf4(0, __riscv_vsetvlmax_e8mf4());
    vuint8mf4_t vreg_memory_0 = __riscv_vle8_tum(vmask, vd_load_0, ptr_load_0, vl);
    vint16mf2_t vd_load_1 = __riscv_vmv_v_x_i16mf2(0, __riscv_vsetvlmax_e16mf2());
    vint16mf2_t vreg_memory_1 = __riscv_vle16_mu(vmask, vd_load_1, ptr_load_1, vl);
    vfloat32m1_t vd_load_2 = __riscv_vfmv_v_f_f32m1(0, __riscv_vsetvlmax_e32m1());
    vfloat32m1_t vreg_memory_2 = __riscv_vle32_v_f32m1_tu(vd_load_2, ptr_load_2, vl);
    vfloat64m2_t vd_load_3 = __riscv_vfmv_v_f_f64m2(0, __riscv_vsetvlmax_e64m2());
    vfloat64m2_t vreg_memory_3 = __riscv_vlse64_v_f64m2_tu(vd_load_3, ptr_load_3, 8, vl);
    vint8mf4_t vload_tmp_0 = __riscv_vle8_v_i8mf4(ptr_load_4, vl);
    vbool32_t vreg_memory_4 = __riscv_vmseq_vx_i8mf4_b32(vload_tmp_0, 1, vl);
    vuint16mf2_t vd_load_5 = __riscv_vmv_v_x_u16mf2(0, __riscv_vsetvlmax_e16mf2());
    vuint16mf2_t vreg_memory_5 = __riscv_vle16_v_u16mf2_tu(vd_load_5, ptr_load_5, vl);
    vuint16mf2_t vd_load_6 = __riscv_vmv_v_x_u16mf2(0, __riscv_vsetvlmax_e16mf2());
    vuint16mf2_t vreg_memory_6 = __riscv_vlse16_v_u16mf2_tu(vd_load_6, ptr_load_6, 2, vl);
    vuint64m2_t vd_load_7 = __riscv_vmv_v_x_u64m2(0, __riscv_vsetvlmax_e64m2());
    vuint64m2_t idx_8 = __riscv_vsll_vx_u64m2(__riscv_vid_v_u64m2(vl), 3, vl);
    vuint64m2_t vreg_memory_7 = __riscv_vluxei64_tum(vmask, vd_load_7, ptr_load_7, idx_8, vl);
    vuint64m2_t vd_load_8 = __riscv_vmv_v_x_u64m2(0, __riscv_vsetvlmax_e64m2());
    vuint16mf2_t idx_9 = __riscv_vsll_vx_u16mf2(__riscv_vid_v_u16mf2(vl), 3, vl);
    vuint64m2_t vreg_memory_8 = __riscv_vloxei16_tu(vd_load_8, ptr_load_8, idx_9, vl);
    vfloat16mf2_t vd_load_9 = __riscv_vfmv_v_f_f16mf2(0, __riscv_vsetvlmax_e16mf2());
    vfloat16mf2_t vreg_memory_9 = __riscv_vle16_tum(vmask, vd_load_9, ptr_load_9, vl);
    vfloat32m1_t vd_load_10 = __riscv_vfmv_v_f_f32m1(0, __riscv_vsetvlmax_e32m1());
    vfloat32m1_t vreg_memory_10 = __riscv_vlse32_tumu(vmask, vd_load_10, ptr_load_10, 4, vl);
    vint64m2_t vd_load_11 = __riscv_vmv_v_x_i64m2(0, __riscv_vsetvlmax_e64m2());
    vuint32m1_t idx_10 = __riscv_vsll_vx_u32m1(__riscv_vid_v_u32m1(vl), 3, vl);
    vint64m2_t vreg_memory_11 = __riscv_vluxei32_tu(vd_load_11, ptr_load_11, idx_10, vl);
    vint64m2_t vd_load_12 = __riscv_vmv_v_x_i64m2(0, __riscv_vsetvlmax_e64m2());
    vint64m2_t vreg_memory_12 = __riscv_vle64_mu(vmask, vd_load_12, ptr_load_12, vl);
    vreg_memory_0 = __riscv_vremu_mu(vmask, vreg_memory_0, vreg_memory_0, vreg_memory_0, vl);
    vint16mf2_t vreg_0 = __riscv_vfncvt_x_mu(vmask, vreg_memory_1, vreg_memory_2, __RISCV_FRM_RNE, vl);
    vreg_memory_2 = __riscv_vfnmsub_tumu(vmask, vreg_memory_2, convert_binary_u32_f32(31972u), vreg_memory_2, vl);
    vreg_memory_3 = __riscv_vfnmsac_tum(vmask, vreg_memory_3, convert_binary_u64_f64(62130ull), vreg_memory_3, __RISCV_FRM_RUP, vl);
    vint16mf2_t vreg_1 = __riscv_vsbc_tu(vreg_0, vreg_0, -10579, vreg_memory_4, vl);
    vreg_memory_5 = __riscv_vslide1down_mu(vmask, vreg_memory_5, vreg_memory_6, 12933, vl);
    vreg_memory_7 = __riscv_vssrl_tu(vreg_memory_7, vreg_memory_7, vreg_memory_8, __RISCV_VXRM_ROD, vl);
    vfloat16mf2_t vreg_2 = __riscv_vfcvt_f_tu(vreg_memory_9, vreg_memory_5, __RISCV_FRM_RNE, vl);
    vreg_memory_2 = __riscv_vfsgnj_tu(vreg_memory_10, vreg_memory_10, convert_binary_u32_f32(57291u), vl);
    vreg_memory_12 = __riscv_vneg_tum(vmask, vreg_memory_11, vreg_memory_12, vl);
    vuint16mf2_t idx_1 = __riscv_vsll_vx_u16mf2(__riscv_vid_v_u16mf2(vl), 0, vl);
    __riscv_vsoxei16_v_u8mf4_m(vmask, ptr_store_vreg_memory_0, idx_1, vreg_memory_0, vl);
    __riscv_vsse16_v_i16mf2_m(vmask, ptr_store_vreg_0, 2, vreg_0, vl);
    vuint16mf2_t idx_3 = __riscv_vsll_vx_u16mf2(__riscv_vid_v_u16mf2(vl), 2, vl);
    __riscv_vsuxei16_v_f32m1_m(vmask, ptr_store_vreg_memory_2, idx_3, vreg_memory_2, vl);
    vuint64m2_t idx_5 = __riscv_vsll_vx_u64m2(__riscv_vid_v_u64m2(vl), 3, vl);
    __riscv_vsuxei64_v_f64m2(ptr_store_vreg_memory_3, idx_5, vreg_memory_3, vl);
    __riscv_vse16_v_i16mf2_m(vmask, ptr_store_vreg_1, vreg_1, vl);
    vuint16mf2_t idx_7 = __riscv_vsll_vx_u16mf2(__riscv_vid_v_u16mf2(vl), 1, vl);
    __riscv_vsuxei16_v_u16mf2(ptr_store_vreg_memory_5, idx_7, vreg_memory_5, vl);
    __riscv_vse64_v_u64m2(ptr_store_vreg_memory_7, vreg_memory_7, vl);
    __riscv_vse16_v_f16mf2_m(vmask, ptr_store_vreg_2, vreg_2, vl);
    __riscv_vsse32_v_f32m1(ptr_store_vreg_memory_2, 4, vreg_memory_2, vl);
    __riscv_vse64_v_i64m2(ptr_store_vreg_memory_12, vreg_memory_12, vl);
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
    ptr_store_vreg_memory_0 += vl;
    ptr_store_vreg_memory_12 += vl;
    ptr_store_vreg_memory_2 += vl;
    ptr_store_vreg_memory_3 += vl;
    ptr_store_vreg_memory_5 += vl;
    ptr_store_vreg_memory_7 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_2[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_memory_12[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_memory_2[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_memory_3[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_5[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_memory_7[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

