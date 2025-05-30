#include <riscv_vector.h>
#define dataLen 3000
int8_t mask[dataLen];
uint8_t a[dataLen]; uint8_t b[dataLen]; uint8_t c[dataLen];
uint8_t u8_in[dataLen]; _Float16 f16_in[dataLen]; int64_t i64_in[dataLen];
int8_t i8_out[dataLen]; uint8_t u8_out[dataLen]; int16_t i16_out[dataLen]; float f32_out[dataLen]; int64_t i64_out[dataLen];

int main(){
  int8_t tmp_mask[32] = {1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, };
  for (int i = 0; i < dataLen; ++i) { mask[i] = tmp_mask[i%32]; }
  for (int i = 0; i < dataLen; ++i) { a[i] = i%255; b[i] = i%255; f16_in[i] = i; u8_in[i] = i%255; i64_in[i] = i; }
  for (int i = 0; i < dataLen; ++i) { c[i] = 0; i8_out[i] = 0;i16_out[i] = 0;f32_out[i] = 0; u8_out[i] = 0; i64_out[i] = 0;}
  int8_t* ptr_mask = mask;
  uint8_t* ptr_a = a; uint8_t* ptr_b = b; uint8_t* ptr_c = c;

  _Float16* ptr_f16_in = f16_in; uint8_t* ptr_u8_in = u8_in; int64_t* ptr_i64_in = i64_in;
  int8_t* ptr_i8_out = i8_out; int16_t* ptr_i16_out = i16_out; float* ptr_f32_out = f32_out;
  uint8_t* ptr_u8_out = u8_out; int64_t* ptr_i64_out = i64_out;
  int avl = 128;
  for (size_t vl; avl > 0; avl -= vl){
    vl = __riscv_vsetvl_e64m8(avl);
    vint8m1_t mask_value= __riscv_vle8_v_i8m1(ptr_mask, vl);
    vbool8_t vmask= __riscv_vmseq_vx_i8m1_b8(mask_value, 1, vl);
    vuint8m1_t va = __riscv_vle8_v_u8m1(ptr_a, vl);
    vuint8m1_t vb = __riscv_vluxei8_v_u8m1(ptr_b, \
                    __riscv_vsll_vx_u8m1(__riscv_vid_v_u8m1(vl), 0, vl), vl);
    vuint8m1_t vc = __riscv_vadd_vv_u8m1_m(vmask, va, vb, vl);
    __riscv_vse8_v_u8m1(ptr_c, vc, vl);
    
///*
    vfloat16m2_t vreg_memory_2 = __riscv_vle16_v_f16m2_m(vmask, ptr_f16_in, vl);
    vbool8_t vreg_1 = __riscv_vmflt_vv_f16m2_b8(vreg_memory_2, vreg_memory_2, vl);
    vint8m1_t vstore_tmp_0 = __riscv_vmerge_vxm_i8m1(__riscv_vmv_v_x_i8m1(0, __riscv_vsetvlmax_e8m1()), 1, vreg_1, vl);
    __riscv_vse8_v_i8m1(ptr_i8_out, vstore_tmp_0, vl);
    vuint8m1_t vreg_memory_3 = __riscv_vle8_v_u8m1(ptr_u8_in, vl);
    vreg_memory_3 = __riscv_vmacc_vv_u8m1_m(vmask, vreg_memory_3, vreg_memory_3, va, vl);
    __riscv_vsoxei64_v_u8m1(ptr_u8_out, __riscv_vsll_vx_u64m8(__riscv_vid_v_u64m8(vl), 0, vl), vreg_memory_3, vl);
    vint16m2_t vreg_2 = __riscv_vmv_s_x_i16m2(-29277, vl);
    __riscv_vse16_v_i16m2(ptr_i16_out, vreg_2, vl);
    vfloat32m4_t vreg_3 = __riscv_vfmv_s_f_f32m4(1.0, vl);
    __riscv_vsoxei64_v_f32m4(ptr_f32_out, __riscv_vsll_vx_u64m8(__riscv_vid_v_u64m8(vl), 2, vl), vreg_3, vl);
    vint64m8_t vreg_memory_6 = __riscv_vluxei32_v_i64m8(ptr_i64_in, __riscv_vsll_vx_u32m4(__riscv_vid_v_u32m4(vl), 3, vl), vl);
    vreg_memory_6 = __riscv_vnmsub_vx_i64m8(vreg_memory_6, 7181326ll, vreg_memory_6, vl);
    __riscv_vsoxei64_v_i64m8(ptr_i64_out, __riscv_vsll_vx_u64m8(__riscv_vid_v_u64m8(vl), 3, vl), vreg_memory_6, vl);
    ptr_f16_in += vl; ptr_u8_in += vl; ptr_i64_in += vl;
    ptr_i8_out += vl; ptr_i16_out += vl; ptr_f32_out += vl; ptr_u8_out += vl; ptr_i64_out += vl;
//*/
    ptr_mask += vl; ptr_a += vl; ptr_b += vl; ptr_c += vl;
  }
  int count = 0;
  for (int i = 0; i < 128; ++i)  if(mask[i]) count+=c[i];
  __builtin_printf("%d\n", count);
  return 0;
}