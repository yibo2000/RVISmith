// --seed 0x485b2201 --data_length 10 --sequence_length 8 --root vint16m2_t --segment  --policy 
// scheduling mode: unit 
#include <riscv_vector.h>

#define dataLen 10
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
float16_t data_load_1[dataLen];
int32_t data_load_10[dataLen];
float32_t data_load_11[dataLen];
float16_t data_load_2[dataLen];
int8_t data_load_3[dataLen];
int8_t data_load_4[dataLen];
float64_t data_load_5[dataLen];
uint32_t data_load_6[dataLen];
float64_t data_load_7[dataLen];
float64_t data_load_8[dataLen];
uint64_t data_load_9[dataLen];
float32_t data_store_vreg_0[dataLen];
float32_t data_store_vreg_memory_0[dataLen];
int32_t data_store_vreg_memory_10[dataLen];
int8_t data_store_vreg_memory_3[dataLen];
int8_t data_store_vreg_memory_4[dataLen];
float64_t data_store_vreg_memory_5[dataLen];
float64_t data_store_vreg_memory_7[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint32_t tmp_0[dataLen] = {1858722470u, 3040496520u, 3834523213u, 2458602341u, 3429596995u, 1410082589u, 892538184u, 338541411u, 2264585413u, 2380189549u, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = convert_binary_u32_f32(tmp_0[i]); }
  uint16_t tmp_1[dataLen] = {29243, 55486, 23972, 24762, 51649, 41555, 30934, 48413, 9786, 33982, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = convert_binary_u16_f16(tmp_1[i]); }
  int32_t tmp_2[dataLen] = {-1045572677, 232987473, 678126797, -1644972305, -87834100, -2147481355, 386137073, -1775832914, 1229358193, -456119601, };
  for (int i = 0; i < dataLen; ++i) { data_load_10[i] = tmp_2[i]; }
  uint32_t tmp_3[dataLen] = {3900257759u, 1287889255u, 93878327u, 2220780021u, 2822330112u, 915857253u, 1444706753u, 1568507514u, 3867010432u, 1628803942u, };
  for (int i = 0; i < dataLen; ++i) { data_load_11[i] = convert_binary_u32_f32(tmp_3[i]); }
  uint16_t tmp_4[dataLen] = {43759, 32813, 37887, 11746, 43486, 64990, 38565, 58937, 8650, 40567, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = convert_binary_u16_f16(tmp_4[i]); }
  int8_t tmp_5[dataLen] = {-97, -17, 67, -127, 45, -82, -10, -53, 65, 117, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_5[i]; }
  int8_t tmp_6[dataLen] = {75, -89, -31, 73, 72, -89, 38, -75, -17, 110, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = tmp_6[i]; }
  uint64_t tmp_7[dataLen] = {330775714ull, 346752844ull, 2767396217ull, 2295125344ull, 2225639378ull, 3031393787ull, 3021296950ull, 3101322296ull, 1126327239ull, 4272947130ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = convert_binary_u64_f64(tmp_7[i]); }
  uint32_t tmp_8[dataLen] = {2474333152u, 3925155745u, 2599807017u, 941712530u, 1884356042u, 355156431u, 318350815u, 2191013682u, 665769590u, 567240277u, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = tmp_8[i]; }
  uint64_t tmp_9[dataLen] = {2533326010ull, 3074599901ull, 1901035554ull, 1614642000ull, 1424460166ull, 2153555990ull, 2559470178ull, 4190572493ull, 1519805637ull, 1383303777ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = convert_binary_u64_f64(tmp_9[i]); }
  uint64_t tmp_10[dataLen] = {3485827548ull, 499337136ull, 24053046ull, 2411640170ull, 374127361ull, 2604681241ull, 948340569ull, 324669996ull, 648189156ull, 3923985509ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_8[i] = convert_binary_u64_f64(tmp_10[i]); }
  uint64_t tmp_11[dataLen] = {3956586603ull, 1540727624ull, 2259455571ull, 1680605264ull, 3144485224ull, 1762908828ull, 3311749499ull, 2954828632ull, 3666986930ull, 98195854ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_9[i] = tmp_11[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_10[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_3[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_4[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_5[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_7[i] = 0; }
}

void CodeBlock_0() {
  int avl2 = dataLen;
  int8_t* ptr_mask = data_mask;
  float32_t* ptr_load_0 = data_load_0;
  float16_t* ptr_load_1 = data_load_1;
  int32_t* ptr_load_10 = data_load_10;
  float32_t* ptr_load_11 = data_load_11;
  float16_t* ptr_load_2 = data_load_2;
  int8_t* ptr_load_3 = data_load_3;
  int8_t* ptr_load_4 = data_load_4;
  float64_t* ptr_load_5 = data_load_5;
  uint32_t* ptr_load_6 = data_load_6;
  float64_t* ptr_load_7 = data_load_7;
  float64_t* ptr_load_8 = data_load_8;
  uint64_t* ptr_load_9 = data_load_9;
  float32_t* ptr_store_vreg_0 = data_store_vreg_0;
  float32_t* ptr_store_vreg_memory_0 = data_store_vreg_memory_0;
  int32_t* ptr_store_vreg_memory_10 = data_store_vreg_memory_10;
  int8_t* ptr_store_vreg_memory_3 = data_store_vreg_memory_3;
  int8_t* ptr_store_vreg_memory_4 = data_store_vreg_memory_4;
  float64_t* ptr_store_vreg_memory_5 = data_store_vreg_memory_5;
  float64_t* ptr_store_vreg_memory_7 = data_store_vreg_memory_7;
  for (size_t vl; avl2 > 0; avl2 -= vl){
    vl = __riscv_vsetvl_e16m2(avl2);
    vint8m1_t mask_value= __riscv_vle8_v_i8m1(ptr_mask, vl);
    vbool8_t vmask= __riscv_vmseq_vx_i8m1_b8(mask_value, 1, vl);
    vfloat32m4_t vd_load_0 = __riscv_vfmv_v_f_f32m4(0, __riscv_vsetvlmax_e32m4());
    vfloat32m4_t vreg_memory_0 = __riscv_vle32_v_f32m4_tu(vd_load_0, ptr_load_0, vl);
    vfloat16m2_t vd_load_1 = __riscv_vfmv_v_f_f16m2(0, __riscv_vsetvlmax_e16m2());
    vfloat16m2_t vreg_memory_1 = __riscv_vle16_v_f16m2_tu(vd_load_1, ptr_load_1, vl);
    vfloat16m2_t vd_load_2 = __riscv_vfmv_v_f_f16m2(0, __riscv_vsetvlmax_e16m2());
    vfloat16m2_t vreg_memory_2 = __riscv_vle16_v_f16m2_tumu(vmask, vd_load_2, ptr_load_2, vl);
    vreg_memory_0 = __riscv_vfwsub_vv_f32m4_tumu(vmask, vreg_memory_0, vreg_memory_1, vreg_memory_2, vl);
    __riscv_vsse32_v_f32m4(ptr_store_vreg_memory_0, 4, vreg_memory_0, vl);
    vint8m1_t vd_load_3 = __riscv_vmv_v_x_i8m1(0, __riscv_vsetvlmax_e8m1());
    vint8m1_t vreg_memory_3 = __riscv_vle8_v_i8m1_tu(vd_load_3, ptr_load_3, vl);
    vint8m1_t vload_tmp_0 = __riscv_vle8_v_i8m1(ptr_load_4, vl);
    vbool8_t vreg_memory_4 = __riscv_vmseq_vx_i8m1_b8(vload_tmp_0, 1, vl);
    vreg_memory_3 = __riscv_vadc_vxm_i8m1_tu(vreg_memory_3, vreg_memory_3, 50, vreg_memory_4, vl);
    __riscv_vse8_v_i8m1(ptr_store_vreg_memory_3, vreg_memory_3, vl);
    vfloat64m8_t vd_load_5 = __riscv_vfmv_v_f_f64m8(0, __riscv_vsetvlmax_e64m8());
    vfloat64m8_t vreg_memory_5 = __riscv_vlse64_v_f64m8_mu(vmask, vd_load_5, ptr_load_5, 8, vl);
    vreg_memory_4 = __riscv_vmfgt_vv_f64m8_b8_mu(vmask, vreg_memory_4, vreg_memory_5, vreg_memory_5, vl);
    vint8m1_t zero_1 = __riscv_vmv_v_x_i8m1(0, __riscv_vsetvlmax_e8m1());
    vint8m1_t vstore_tmp_1 = __riscv_vmerge_vxm_i8m1(zero_1, 1, vreg_memory_4, vl);
    __riscv_vse8_v_i8m1(ptr_store_vreg_memory_4, vstore_tmp_1, vl);
    vuint32m4_t vd_load_6 = __riscv_vmv_v_x_u32m4(0, __riscv_vsetvlmax_e32m4());
    vuint8m1_t idx_0 = __riscv_vsll_vx_u8m1(__riscv_vid_v_u8m1(vl), 2, vl);
    vuint32m4_t vreg_memory_6 = __riscv_vluxei8_v_u32m4_tumu(vmask, vd_load_6, ptr_load_6, idx_0, vl);
    vreg_memory_0 = __riscv_vfcvt_f_xu_v_f32m4_rm_mu(vmask, vreg_memory_0, vreg_memory_6, __RISCV_FRM_RDN, vl);
    vuint16m2_t idx_2 = __riscv_vsll_vx_u16m2(__riscv_vid_v_u16m2(vl), 2, vl);
    __riscv_vsuxei16_v_f32m4(ptr_store_vreg_memory_0, idx_2, vreg_memory_0, vl);
    vfloat64m8_t vd_load_7 = __riscv_vfmv_v_f_f64m8(0, __riscv_vsetvlmax_e64m8());
    vfloat64m8_t vreg_memory_7 = __riscv_vlse64_v_f64m8_tu(vd_load_7, ptr_load_7, 8, vl);
    vreg_memory_5 = __riscv_vfadd_vv_f64m8_rm_tum(vmask, vreg_memory_5, vreg_memory_5, vreg_memory_7, __RISCV_FRM_RDN, vl);
    vuint8m1_t idx_4 = __riscv_vsll_vx_u8m1(__riscv_vid_v_u8m1(vl), 3, vl);
    __riscv_vsoxei8_v_f64m8(ptr_store_vreg_memory_5, idx_4, vreg_memory_5, vl);
    vfloat64m8_t vd_load_8 = __riscv_vfmv_v_f_f64m8(0, __riscv_vsetvlmax_e64m8());
    vfloat64m8_t vreg_memory_8 = __riscv_vle64_v_f64m8_tumu(vmask, vd_load_8, ptr_load_8, vl);
    vuint64m8_t vd_load_9 = __riscv_vmv_v_x_u64m8(0, __riscv_vsetvlmax_e64m8());
    vuint16m2_t idx_5 = __riscv_vsll_vx_u16m2(__riscv_vid_v_u16m2(vl), 3, vl);
    vuint64m8_t vreg_memory_9 = __riscv_vloxei16_v_u64m8_tumu(vmask, vd_load_9, ptr_load_9, idx_5, vl);
    vreg_memory_7 = __riscv_vfcvt_f_xu_v_f64m8_tum(vmask, vreg_memory_8, vreg_memory_9, vl);
    vuint64m8_t idx_7 = __riscv_vsll_vx_u64m8(__riscv_vid_v_u64m8(vl), 3, vl);
    __riscv_vsoxei64_v_f64m8(ptr_store_vreg_memory_7, idx_7, vreg_memory_7, vl);
    vint32m4_t vd_load_10 = __riscv_vmv_v_x_i32m4(0, __riscv_vsetvlmax_e32m4());
    vint32m4_t vreg_memory_10 = __riscv_vle32_v_i32m4_tu(vd_load_10, ptr_load_10, vl);
    vreg_memory_10 = __riscv_vnmsac_vv_i32m4_tumu(vmask, vreg_memory_10, vreg_memory_10, vreg_memory_10, vl);
    vuint32m4_t idx_9 = __riscv_vsll_vx_u32m4(__riscv_vid_v_u32m4(vl), 2, vl);
    __riscv_vsuxei32_v_i32m4(ptr_store_vreg_memory_10, idx_9, vreg_memory_10, vl);
    vfloat32m4_t vd_load_11 = __riscv_vfmv_v_f_f32m4(0, __riscv_vsetvlmax_e32m4());
    vfloat32m4_t vreg_memory_11 = __riscv_vle32_v_f32m4_tu(vd_load_11, ptr_load_11, vl);
    vfloat32m4_t vreg_0 = __riscv_vfmadd_vf_f32m4_mu(vmask, vreg_memory_0, convert_binary_u32_f32(36068u), vreg_memory_11, vl);
    __riscv_vsse32_v_f32m4_m(vmask, ptr_store_vreg_0, 4, vreg_0, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_10 += vl;
    ptr_load_11 += vl;
    ptr_load_2 += vl;
    ptr_load_3 += vl;
    ptr_load_4 += vl;
    ptr_load_5 += vl;
    ptr_load_6 += vl;
    ptr_load_7 += vl;
    ptr_load_8 += vl;
    ptr_load_9 += vl;
    ptr_store_vreg_0 += vl;
    ptr_store_vreg_memory_0 += vl;
    ptr_store_vreg_memory_10 += vl;
    ptr_store_vreg_memory_3 += vl;
    ptr_store_vreg_memory_4 += vl;
    ptr_store_vreg_memory_5 += vl;
    ptr_store_vreg_memory_7 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_0[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_memory_0[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_10[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_3[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_4[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_memory_5[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_memory_7[i])); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

