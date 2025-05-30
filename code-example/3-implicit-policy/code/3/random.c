// --seed 0x83dee627 --data_length 9 --sequence_length 8 --root vint64m1_t --segment  --policy  --overloaded 
// scheduling mode: random 
#include <riscv_vector.h>

#define dataLen 9
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
int64_t data_load_1[dataLen];
float32_t data_load_2[dataLen];
float32_t data_load_3[dataLen];
int16_t data_load_4[dataLen];
int8_t data_load_5[dataLen];
uint64_t data_load_6[dataLen];
float16_t data_load_7[dataLen];
float32_t data_store_vreg_0[dataLen];
float16_t data_store_vreg_1[dataLen];
uint32_t data_store_vreg_memory_0[dataLen];
int64_t data_store_vreg_memory_1[dataLen];
int16_t data_store_vreg_memory_4[dataLen];
int8_t data_store_vreg_memory_5[dataLen];
uint64_t data_store_vreg_memory_6[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 1, 1, 1, 1, 0, 0, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint32_t tmp_0[dataLen] = {3019544112u, 4133180730u, 2531628129u, 2271321361u, 2754399463u, 3356349953u, 1872442511u, 1092757211u, 3373521978u, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  int64_t tmp_1[dataLen] = {5469760759649785349ll, -2139327202759960762ll, 6228978134059629237ll, 3496579375602809792ll, 3384230084656433425ll, 6888419742033772553ll, -7938519545735558854ll, -5649235081053159797ll, -4337081488467946037ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint32_t tmp_2[dataLen] = {2776347472u, 157536814u, 2772485592u, 4171979928u, 2417352428u, 2420051803u, 3302742863u, 1465713506u, 3009632384u, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = convert_binary_u32_f32(tmp_2[i]); }
  uint32_t tmp_3[dataLen] = {2192132997u, 2535612874u, 89826209u, 486434683u, 3495050922u, 2988431511u, 3158992959u, 3589463837u, 780009111u, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = convert_binary_u32_f32(tmp_3[i]); }
  int16_t tmp_4[dataLen] = {10376, 22102, -22464, -27211, -25482, 31586, -30498, -564, 29829, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = tmp_4[i]; }
  int8_t tmp_5[dataLen] = {-31, 11, 95, 74, -8, 121, 94, -97, 2, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = tmp_5[i]; }
  uint64_t tmp_6[dataLen] = {1495111053ull, 1410844852ull, 2570999817ull, 4207979568ull, 2435759691ull, 2652876665ull, 3616713591ull, 3007472520ull, 2364342431ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = tmp_6[i]; }
  uint16_t tmp_7[dataLen] = {14078, 36117, 52822, 33991, 53602, 47797, 31127, 13057, 3371, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = convert_binary_u16_f16(tmp_7[i]); }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_4[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_5[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_6[i] = 0; }
}

void CodeBlock_0() {
  int avl0 = dataLen;
  int8_t* ptr_mask = data_mask;
  uint32_t* ptr_load_0 = data_load_0;
  int64_t* ptr_load_1 = data_load_1;
  float32_t* ptr_load_2 = data_load_2;
  float32_t* ptr_load_3 = data_load_3;
  int16_t* ptr_load_4 = data_load_4;
  int8_t* ptr_load_5 = data_load_5;
  uint64_t* ptr_load_6 = data_load_6;
  float16_t* ptr_load_7 = data_load_7;
  float32_t* ptr_store_vreg_0 = data_store_vreg_0;
  float16_t* ptr_store_vreg_1 = data_store_vreg_1;
  uint32_t* ptr_store_vreg_memory_0 = data_store_vreg_memory_0;
  int64_t* ptr_store_vreg_memory_1 = data_store_vreg_memory_1;
  int16_t* ptr_store_vreg_memory_4 = data_store_vreg_memory_4;
  int8_t* ptr_store_vreg_memory_5 = data_store_vreg_memory_5;
  uint64_t* ptr_store_vreg_memory_6 = data_store_vreg_memory_6;
  for (size_t vl; avl0 > 0; avl0 -= vl){
    vl = __riscv_vsetvl_e64m1(avl0);
    vint8mf8_t mask_value= __riscv_vle8_v_i8mf8(ptr_mask, vl);
    vbool64_t vmask= __riscv_vmseq_vx_i8mf8_b64(mask_value, 1, vl);
    vfloat32mf2_t vd_load_2 = __riscv_vfmv_v_f_f32mf2(0, __riscv_vsetvlmax_e32mf2());
    vfloat16mf4_t vd_load_7 = __riscv_vfmv_v_f_f16mf4(0, __riscv_vsetvlmax_e16mf4());
    vuint64m1_t vd_load_6 = __riscv_vmv_v_x_u64m1(0, __riscv_vsetvlmax_e64m1());
    vfloat32mf2_t vreg_memory_2 = __riscv_vle32_v_f32mf2_tu(vd_load_2, ptr_load_2, vl);
    vuint32mf2_t vd_load_0 = __riscv_vmv_v_x_u32mf2(0, __riscv_vsetvlmax_e32mf2());
    vfloat32mf2_t vd_load_3 = __riscv_vfmv_v_f_f32mf2(0, __riscv_vsetvlmax_e32mf2());
    vint64m1_t vd_load_1 = __riscv_vmv_v_x_i64m1(0, __riscv_vsetvlmax_e64m1());
    vuint8mf8_t idx_0 = __riscv_vsll_vx_u8mf8(__riscv_vid_v_u8mf8(vl), 2, vl);
    vint64m1_t vreg_memory_1 = __riscv_vle64_mu(vmask, vd_load_1, ptr_load_1, vl);
    vint16mf4_t vd_load_4 = __riscv_vmv_v_x_i16mf4(0, __riscv_vsetvlmax_e16mf4());
    vuint64m1_t vreg_memory_6 = __riscv_vle64_v_u64m1_tu(vd_load_6, ptr_load_6, vl);
    vuint32mf2_t vreg_memory_0 = __riscv_vloxei8_tumu(vmask, vd_load_0, ptr_load_0, idx_0, vl);
    vreg_memory_0 = __riscv_vssrl_tu(vreg_memory_0, vreg_memory_0, 1911178248u, __RISCV_VXRM_RNE, vl);
    vfloat16mf4_t vreg_memory_7 = __riscv_vlse16_tum(vmask, vd_load_7, ptr_load_7, 2, vl);
    __riscv_vsse32_v_u32mf2_m(vmask, ptr_store_vreg_memory_0, 4, vreg_memory_0, vl);
    vreg_memory_1 = __riscv_vmulh_tum(vmask, vreg_memory_1, vreg_memory_1, vreg_memory_1, vl);
    __riscv_vse64_v_i64m1(ptr_store_vreg_memory_1, vreg_memory_1, vl);
    vuint8mf8_t idx_2 = __riscv_vsll_vx_u8mf8(__riscv_vid_v_u8mf8(vl), 1, vl);
    vint16mf4_t vreg_memory_4 = __riscv_vloxei8_tumu(vmask, vd_load_4, ptr_load_4, idx_2, vl);
    vuint8mf8_t idx_1 = __riscv_vsll_vx_u8mf8(__riscv_vid_v_u8mf8(vl), 2, vl);
    vfloat32mf2_t vreg_memory_3 = __riscv_vluxei8_tu(vd_load_3, ptr_load_3, idx_1, vl);
    vint8mf8_t vd_load_5 = __riscv_vmv_v_x_i8mf8(0, __riscv_vsetvlmax_e8mf8());
    vfloat32mf2_t vreg_0 = __riscv_vfslide1down_tumu(vmask, vreg_memory_2, vreg_memory_3, convert_binary_u32_f32(64578u), vl);
    __riscv_vse32_v_f32mf2(ptr_store_vreg_0, vreg_0, vl);
    vuint8mf8_t idx_3 = __riscv_vsll_vx_u8mf8(__riscv_vid_v_u8mf8(vl), 0, vl);
    vint8mf8_t vreg_memory_5 = __riscv_vluxei8_tumu(vmask, vd_load_5, ptr_load_5, idx_3, vl);
    vreg_memory_4 = __riscv_vwadd_vx_mu(vmask, vreg_memory_4, vreg_memory_5, -99, vl);
    __riscv_vse16_v_i16mf4(ptr_store_vreg_memory_4, vreg_memory_4, vl);
    vreg_memory_6 = __riscv_vwaddu_wv_tu(vreg_memory_6, vreg_memory_6, vreg_memory_0, vl);
    __riscv_vsse64_v_u64m1(ptr_store_vreg_memory_6, 8, vreg_memory_6, vl);
    vfloat16mf4_t vreg_1 = __riscv_vfdiv_mu(vmask, vreg_memory_7, vreg_memory_7, convert_binary_u16_f16(57677), __RISCV_FRM_RNE, vl);
    vuint32mf2_t idx_5 = __riscv_vsll_vx_u32mf2(__riscv_vid_v_u32mf2(vl), 1, vl);
    __riscv_vsoxei32_v_f16mf4(ptr_store_vreg_1, idx_5, vreg_1, vl);
    vreg_memory_5 = __riscv_vmacc_mu(vmask, vreg_memory_5, vreg_memory_5, vreg_memory_5, vl);
    vuint64m1_t idx_7 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 0, vl);
    __riscv_vsoxei64_v_i8mf8_m(vmask, ptr_store_vreg_memory_5, idx_7, vreg_memory_5, vl);
    vreg_memory_4 = __riscv_vnmsub_tum(vmask, vreg_memory_4, 27356, vreg_memory_4, vl);
    vuint32mf2_t idx_9 = __riscv_vsll_vx_u32mf2(__riscv_vid_v_u32mf2(vl), 1, vl);
    __riscv_vsuxei32_v_i16mf4(ptr_store_vreg_memory_4, idx_9, vreg_memory_4, vl);
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
    ptr_store_vreg_memory_0 += vl;
    ptr_store_vreg_memory_1 += vl;
    ptr_store_vreg_memory_4 += vl;
    ptr_store_vreg_memory_5 += vl;
    ptr_store_vreg_memory_6 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_0[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f16_u16(data_store_vreg_1[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_memory_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_4[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_5[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_memory_6[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

