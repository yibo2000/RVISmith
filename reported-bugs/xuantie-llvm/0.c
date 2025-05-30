#include <riscv_vector.h>
#define dataLen 10
#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & 0x007FFFFF))
typedef _Float16 float16_t;
typedef float float32_t;
float32_t convert_binary_u32_f32(uint32_t u32){
  union { float32_t f32; uint32_t u32; } converter;
  converter.u32 = u32;
  if(isNaNF32UI(converter.u32)) return 0;
  return converter.f32;
}
float16_t a[dataLen]; float32_t b[dataLen]; float32_t c[dataLen]; uint8_t d[dataLen]; float16_t e[dataLen]; float32_t f[dataLen];

int main(){
  uint32_t tmp_1[10] = {540829794u, 2134250630u, 1216919773u, 2309110688u, 21457044u, 1960621478u, 4098792014u, 3080804647u, 460952409u, 2075577095u, };
  uint32_t tmp_2[10] = {1013721179u, 2119197348u, 742331465u, 4017533102u, 1126179803u, 236881090u, 1013561895u, 3202494434u, 1689715780u, 2447820075u, };
  uint8_t tmp_3[10] = {38, 160, 83, 92, 141, 61, 131, 125, 88, 107, };
  for (int i = 0; i < dataLen; ++i) { a[i] = i; b[i] = convert_binary_u32_f32(tmp_1[i]); c[i] = convert_binary_u32_f32(tmp_2[i]); d[i] = tmp_3[i]; }
  for (int i = 0; i < dataLen; ++i) { f[i] = 0; e[i] = 0;}
  int avl = dataLen;
  float16_t* ptr_a = a; float32_t* ptr_b = b; float32_t* ptr_c = c; uint8_t* ptr_d = d; float32_t* ptr_f = f; float16_t* ptr_e = e;
  for (size_t vl; avl > 0; avl -= vl){
    vl = __riscv_vsetvl_e16m2(avl);
    vfloat16m2_t va = __riscv_vle16_v_f16m2(ptr_a, vl);
    va = __riscv_vfrsub_vf_f16m2_rm( va, 53592.0, __RISCV_FRM_RDN, vl);
    __riscv_vse16_v_f16m2(ptr_e, va, vl);

    vfloat32m4_t vb = __riscv_vle32_v_f32m4(ptr_b, vl);
    vfloat32m1_t vc = __riscv_vle32_v_f32m1(ptr_c, vl);
    vfloat32m1_t vf = __riscv_vfredusum_vs_f32m4_f32m1(vb, vc, vl);
    __riscv_vse32_v_f32m1(ptr_f, vf, vl);

    vuint8m1_t vd = __riscv_vle8_v_u8m1(ptr_d, vl);
    vd = __riscv_vsaddu_vv_u8m1(vd, vd, vl);
    ptr_a += vl;ptr_b += vl;ptr_c += vl;ptr_d += vl;ptr_f += vl;ptr_e += vl;
  }
  union { float32_t f32; uint32_t u32; } converter; converter.f32 = f[0];
  __builtin_printf("%x \n", converter.u32);
  __builtin_printf("%f ", f[0]);
  return 0;
}