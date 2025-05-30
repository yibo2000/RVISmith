#include <riscv_vector.h>

#define dataLen 100
uint32_t a[dataLen];
uint32_t b[dataLen];

int main(){
  for (int i=0; i<dataLen; ++i){ a[i]=i; b[i]=i; }
  int avl1 = 100 - 100 % 7;
  uint32_t* ptr_a = a; uint32_t* ptr_b = b;
  for (size_t vl; avl1 > 0; avl1 -= vl * 7){
    vl = __riscv_vsetvl_e32m1(avl1 / 7);
    vuint32m1_t va = __riscv_vle32_v_u32m1(ptr_a, vl);
    vuint32m1x7_t vb = __riscv_vlseg7e32_v_u32m1x7(ptr_b, vl);
    vb = __riscv_vset_v_u32m1_u32m1x7(vb, 0, va);
    ptr_a += vl * 7; ptr_b += vl * 7;
  }
  return 0;
}