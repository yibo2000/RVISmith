#include <riscv_vector.h>
#define dataLen 1
float a[dataLen]; float b[dataLen];
int main(){
  for (int i = 0; i < dataLen; ++i) { a[i] = 1.0; }
  for (int i = 0; i < dataLen; ++i) { b[i] = 0; }
  int avl = dataLen;
  float* ptr_a = a; float* ptr_b = b;
  for (size_t vl; avl > 0; avl -= vl){
    vl = __riscv_vsetvl_e32m1(avl);
    vfloat32m1_t va = __riscv_vlse32_v_f32m1(ptr_a, 4, vl);
    va = __riscv_vfsqrt_v_f32m1_rm( va, __RISCV_FRM_RNE, vl);
    va = __riscv_vfredosum_vs_f32m1_f32m1(va, va, vl);
    __riscv_vse32_v_f32m1(ptr_b, va, vl);
    ptr_a += vl;
    ptr_b += vl;
  }
  __builtin_printf("success.\n");
  return 0;
}