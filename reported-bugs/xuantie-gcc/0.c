#include <riscv_vector.h>
_Float16 a[10];
void func(){
  int placeholder0 = 10;
  _Float16* ptr_a = a;
  for (size_t vl; placeholder0 > 0; placeholder0 -= vl){
    vl = __riscv_vsetvl_e16m1(placeholder0);
    vfloat16mf2_t va = __riscv_vle16_v_f16mf2(ptr_a, vl);
    vfloat16m1_t vb = __riscv_vlmul_ext_v_f16mf2_f16m1(va);
    ptr_a += vl;
  }
}