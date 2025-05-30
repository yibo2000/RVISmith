#include <riscv_vector.h>
#define dataLen 100
typedef _Float16 float16_t;
int8_t mask[dataLen];
uint16_t u16_in[dataLen]; float16_t f16_in[dataLen]; int8_t i8_in[dataLen];
float16_t f16_out[dataLen]; uint16_t u16_out[dataLen]; uint32_t u32_out[dataLen]; int8_t i8_out[dataLen];

int main(){
  for (int i = 0; i < dataLen; ++i) { mask[i] = i%2; }
  for (int i = 0; i < dataLen; ++i) { mask[i] = i%2; u16_in[i] = i; f16_in[i] = 2+i; i8_in[i] = i%128; }
  for (int i = 0; i < dataLen; ++i) { f16_out[i] = 0; u16_out[i] = 0; u32_out[i] = 0; i8_out[i] = 0; }
  int avl = dataLen;
  int8_t* ptr_mask = mask;
  int8_t* ptr_i8_in = i8_in; uint16_t* ptr_u16_in = u16_in; float16_t* ptr_f16_in = f16_in;
  int8_t* ptr_i8_out = i8_out; float16_t* ptr_f16_out = f16_out; uint16_t* ptr_u16_out = u16_out; uint32_t* ptr_u32_out = u32_out;
  for (size_t vl; avl > 0; avl -= vl){
    vl = __riscv_vsetvl_e32m8(avl);
    vbool4_t vmask= __riscv_vmseq_vx_i8m2_b4(__riscv_vle8_v_i8m2(ptr_mask, vl), 1, vl);
    vuint16m4_t vu16m4 = __riscv_vloxei16_v_u16m4(ptr_u16_in, __riscv_vsll_vx_u16m4(__riscv_vid_v_u16m4(vl), 1, vl), vl);
    vu16m4 = __riscv_vrgather_vx_u16m4(vu16m4, 10u%vl, vl);
    __riscv_vsoxei8_v_u16m4(ptr_u16_out, __riscv_vsll_vx_u8m2(__riscv_vid_v_u8m2(vl), 1, vl), vu16m4, vl);
    vfloat16m4_t vf16_in = __riscv_vle16_v_f16m4(ptr_f16_in, vl);
///*
    __riscv_vsuxei32_v_u16m4(ptr_u16_out, __riscv_vsll_vx_u32m8(__riscv_vid_v_u32m8(vl), 1, vl), __riscv_vxor_vx_u16m4(vu16m4, 123, vl), vl);
    vint8m2_t vi8m2 = __riscv_vle8_v_i8m2_m(vmask, ptr_i8_in, vl);
    vi8m2 = __riscv_vdiv_vv_i8m2(vi8m2, vi8m2, vl);
    __riscv_vsoxei8_v_i8m2(ptr_i8_out, __riscv_vsll_vx_u8m2(__riscv_vid_v_u8m2(vl), 0, vl), vi8m2, vl);
    __riscv_vse16_v_u16m4(ptr_u16_out, __riscv_vmv_s_x_u16m4(100, vl), vl);
    __riscv_vsuxei16_v_u32m8(ptr_u32_out, __riscv_vsll_vx_u16m4(__riscv_vid_v_u16m4(vl), 2, vl), __riscv_vmv_s_x_u32m8(200, vl), vl);
//*/
    vfloat16m4_t vf16_out = __riscv_vfmsub_vv_f16m4_rm(vf16_in, vf16_in, vf16_in, __RISCV_FRM_RNE, vl);
    __riscv_vse16_v_f16m4(ptr_f16_out, vf16_out, vl);
    ptr_mask += vl;
    ptr_i8_in += vl; ptr_u16_in += vl; ptr_f16_in += vl;
    ptr_i8_out += vl; ptr_f16_out += vl; ptr_u16_out += vl; ptr_u32_out += vl;
  }
  for(int i=0; i<dataLen; ++i) { __builtin_printf("%.2f ", (float)f16_out[i]); } __builtin_printf("\n");
  return 0;
}