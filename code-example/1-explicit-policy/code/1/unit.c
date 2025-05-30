// --seed 0xda747f61 --data_length 3 --sequence_length 6 --root vbool64_t --segment  --policy 
// scheduling mode: unit 
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
uint32_t data_load_0[dataLen];
uint32_t data_load_1[dataLen];
uint64_t data_load_10[dataLen];
uint32_t data_load_2[dataLen];
uint64_t data_load_3[dataLen];
float64_t data_load_4[dataLen];
float32_t data_load_5[dataLen];
float16_t data_load_6[dataLen];
int32_t data_load_7[dataLen];
int64_t data_load_8[dataLen];
uint64_t data_load_9[dataLen];
uint32_t data_store_vreg_0[dataLen];
uint64_t data_store_vreg_1[dataLen];
float64_t data_store_vreg_2[dataLen];
uint64_t data_store_vreg_memory_10[dataLen];
float32_t data_store_vreg_memory_5[dataLen];
int32_t data_store_vreg_memory_7[dataLen];

void initialize(){
  int8_t tmp_mask[dataLen] = {1, 1, 0, };
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }
  uint32_t tmp_0[dataLen] = {330985145u, 2824289935u, 3920794187u, };
  for (int i = 0; i < dataLen; ++i) { data_load_0[i] = tmp_0[i]; }
  uint32_t tmp_1[dataLen] = {687050761u, 1509897877u, 2910084671u, };
  for (int i = 0; i < dataLen; ++i) { data_load_1[i] = tmp_1[i]; }
  uint64_t tmp_2[dataLen] = {2377397902ull, 647698731ull, 3804589561ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_10[i] = tmp_2[i]; }
  uint32_t tmp_3[dataLen] = {3303667963u, 71528972u, 590531390u, };
  for (int i = 0; i < dataLen; ++i) { data_load_2[i] = tmp_3[i]; }
  uint64_t tmp_4[dataLen] = {1073932113ull, 3977955547ull, 2211107939ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_3[i] = tmp_4[i]; }
  uint64_t tmp_5[dataLen] = {3491784159ull, 1618814493ull, 2197681479ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_4[i] = convert_binary_u64_f64(tmp_5[i]); }
  uint32_t tmp_6[dataLen] = {1712830885u, 11098348u, 974292666u, };
  for (int i = 0; i < dataLen; ++i) { data_load_5[i] = convert_binary_u32_f32(tmp_6[i]); }
  uint16_t tmp_7[dataLen] = {3542, 61355, 26172, };
  for (int i = 0; i < dataLen; ++i) { data_load_6[i] = convert_binary_u16_f16(tmp_7[i]); }
  int32_t tmp_8[dataLen] = {-134444999, -808254918, -1650843967, };
  for (int i = 0; i < dataLen; ++i) { data_load_7[i] = tmp_8[i]; }
  int64_t tmp_9[dataLen] = {5096174056844057629ll, -4536805970625544528ll, -7813417628015271779ll, };
  for (int i = 0; i < dataLen; ++i) { data_load_8[i] = tmp_9[i]; }
  uint64_t tmp_10[dataLen] = {2853767920ull, 3855198871ull, 4170569911ull, };
  for (int i = 0; i < dataLen; ++i) { data_load_9[i] = tmp_10[i]; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_0[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_1[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_2[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_10[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_5[i] = 0; }
  for (int i = 0; i < dataLen; ++i) { data_store_vreg_memory_7[i] = 0; }
}

void CodeBlock_0() {
  int avl2 = dataLen;
  int8_t* ptr_mask = data_mask;
  uint32_t* ptr_load_0 = data_load_0;
  uint32_t* ptr_load_1 = data_load_1;
  uint64_t* ptr_load_10 = data_load_10;
  uint32_t* ptr_load_2 = data_load_2;
  uint64_t* ptr_load_3 = data_load_3;
  float64_t* ptr_load_4 = data_load_4;
  float32_t* ptr_load_5 = data_load_5;
  float16_t* ptr_load_6 = data_load_6;
  int32_t* ptr_load_7 = data_load_7;
  int64_t* ptr_load_8 = data_load_8;
  uint64_t* ptr_load_9 = data_load_9;
  uint32_t* ptr_store_vreg_0 = data_store_vreg_0;
  uint64_t* ptr_store_vreg_1 = data_store_vreg_1;
  float64_t* ptr_store_vreg_2 = data_store_vreg_2;
  uint64_t* ptr_store_vreg_memory_10 = data_store_vreg_memory_10;
  float32_t* ptr_store_vreg_memory_5 = data_store_vreg_memory_5;
  int32_t* ptr_store_vreg_memory_7 = data_store_vreg_memory_7;
  for (size_t vl; avl2 > 0; avl2 -= vl){
    vl = __riscv_vsetvl_e64m1(avl2);
    vint8mf8_t mask_value= __riscv_vle8_v_i8mf8(ptr_mask, vl);
    vbool64_t vmask= __riscv_vmseq_vx_i8mf8_b64(mask_value, 1, vl);
    vuint32mf2_t vd_load_0 = __riscv_vmv_v_x_u32mf2(0, __riscv_vsetvlmax_e32mf2());
    vuint16mf4_t idx_0 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 2, vl);
    vuint32mf2_t vreg_memory_0 = __riscv_vluxei16_v_u32mf2_tu(vd_load_0, ptr_load_0, idx_0, vl);
    vuint32mf2_t vd_load_1 = __riscv_vmv_v_x_u32mf2(0, __riscv_vsetvlmax_e32mf2());
    vuint32mf2_t vreg_memory_1 = __riscv_vle32_v_u32mf2_tu(vd_load_1, ptr_load_1, vl);
    vuint32mf2_t vd_load_2 = __riscv_vmv_v_x_u32mf2(0, __riscv_vsetvlmax_e32mf2());
    vuint32mf2_t vreg_memory_2 = __riscv_vle32_v_u32mf2_tu(vd_load_2, ptr_load_2, vl);
    vreg_memory_2 = __riscv_vremu_vx_u32mf2(vreg_memory_2, (uint32_t)(vl), vl);
    vuint32mf2_t vreg_0 = __riscv_vrgather_vv_u32mf2_tu(vreg_memory_0, vreg_memory_1, vreg_memory_2, vl);
    vuint64m1_t idx_2 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 2, vl);
    __riscv_vsuxei64_v_u32mf2(ptr_store_vreg_0, idx_2, vreg_0, vl);
    vuint64m1_t vd_load_3 = __riscv_vmv_v_x_u64m1(0, __riscv_vsetvlmax_e64m1());
    vuint32mf2_t idx_3 = __riscv_vsll_vx_u32mf2(__riscv_vid_v_u32mf2(vl), 3, vl);
    vuint64m1_t vreg_memory_3 = __riscv_vloxei32_v_u64m1_tu(vd_load_3, ptr_load_3, idx_3, vl);
    vfloat64m1_t vd_load_4 = __riscv_vfmv_v_f_f64m1(0, __riscv_vsetvlmax_e64m1());
    vfloat64m1_t vreg_memory_4 = __riscv_vle64_v_f64m1_tu(vd_load_4, ptr_load_4, vl);
    vuint64m1_t vreg_1 = __riscv_vfcvt_rtz_xu_f_v_u64m1_mu(vmask, vreg_memory_3, vreg_memory_4, vl);
    vuint32mf2_t idx_5 = __riscv_vsll_vx_u32mf2(__riscv_vid_v_u32mf2(vl), 3, vl);
    __riscv_vsoxei32_v_u64m1_m(vmask, ptr_store_vreg_1, idx_5, vreg_1, vl);
    vfloat32mf2_t vd_load_5 = __riscv_vfmv_v_f_f32mf2(0, __riscv_vsetvlmax_e32mf2());
    vfloat32mf2_t vreg_memory_5 = __riscv_vle32_v_f32mf2_tu(vd_load_5, ptr_load_5, vl);
    vfloat16mf4_t vd_load_6 = __riscv_vfmv_v_f_f16mf4(0, __riscv_vsetvlmax_e16mf4());
    vfloat16mf4_t vreg_memory_6 = __riscv_vle16_v_f16mf4_tumu(vmask, vd_load_6, ptr_load_6, vl);
    vreg_memory_5 = __riscv_vfwsub_vv_f32mf2_tum(vmask, vreg_memory_5, vreg_memory_6, vreg_memory_6, vl);
    vuint64m1_t idx_7 = __riscv_vsll_vx_u64m1(__riscv_vid_v_u64m1(vl), 2, vl);
    __riscv_vsoxei64_v_f32mf2(ptr_store_vreg_memory_5, idx_7, vreg_memory_5, vl);
    vint32mf2_t vd_load_7 = __riscv_vmv_v_x_i32mf2(0, __riscv_vsetvlmax_e32mf2());
    vint32mf2_t vreg_memory_7 = __riscv_vlse32_v_i32mf2_tu(vd_load_7, ptr_load_7, 4, vl);
    vint64m1_t vd_load_8 = __riscv_vmv_v_x_i64m1(0, __riscv_vsetvlmax_e64m1());
    vint64m1_t vreg_memory_8 = __riscv_vlse64_v_i64m1_tu(vd_load_8, ptr_load_8, 8, vl);
    vreg_memory_7 = __riscv_vnsra_wx_i32mf2_tumu(vmask, vreg_memory_7, vreg_memory_8, 2351171486u, vl);
    vuint16mf4_t idx_9 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 2, vl);
    __riscv_vsoxei16_v_i32mf2(ptr_store_vreg_memory_7, idx_9, vreg_memory_7, vl);
    vuint64m1_t vd_load_9 = __riscv_vmv_v_x_u64m1(0, __riscv_vsetvlmax_e64m1());
    vuint16mf4_t idx_10 = __riscv_vsll_vx_u16mf4(__riscv_vid_v_u16mf4(vl), 3, vl);
    vuint64m1_t vreg_memory_9 = __riscv_vloxei16_v_u64m1_tu(vd_load_9, ptr_load_9, idx_10, vl);
    vuint64m1_t vd_load_10 = __riscv_vmv_v_x_u64m1(0, __riscv_vsetvlmax_e64m1());
    vuint64m1_t vreg_memory_10 = __riscv_vlse64_v_u64m1_tu(vd_load_10, ptr_load_10, 8, vl);
    vreg_memory_10 = __riscv_vrgather_vx_u64m1_tumu(vmask, vreg_memory_9, vreg_memory_10, 2217265774u%vl, vl);
    __riscv_vse64_v_u64m1(ptr_store_vreg_memory_10, vreg_memory_10, vl);
    vfloat64m1_t vreg_2 = __riscv_vfrdiv_vf_f64m1_rm_mu(vmask, vreg_memory_4, vreg_memory_4, convert_binary_u64_f64(40805ull), __RISCV_FRM_RUP, vl);
    __riscv_vsse64_v_f64m1(ptr_store_vreg_2, 8, vreg_2, vl);
    ptr_mask += vl;
    ptr_load_0 += vl;
    ptr_load_1 += vl;
    ptr_load_10 += vl;
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
    ptr_store_vreg_memory_10 += vl;
    ptr_store_vreg_memory_5 += vl;
    ptr_store_vreg_memory_7 += vl;
  }
}

void printInfo(){
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_0[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_1[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", convert_binary_f64_u64(data_store_vreg_2[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%lx ", data_store_vreg_memory_10[i]); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", convert_binary_f32_u32(data_store_vreg_memory_5[i])); else __builtin_printf("* "); } __builtin_printf("\n");
  for(int i=0; i<dataLen; ++i) { if(data_mask[i]) __builtin_printf("%x ", data_store_vreg_memory_7[i]); else __builtin_printf("* "); } __builtin_printf("\n");
}

int main(){
  initialize();
  CodeBlock_0();
  printInfo();
  return 0;
}

