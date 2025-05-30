#include <riscv_vector.h>
#define dataLen 230
int8_t data_mask[dataLen];
int16_t a[dataLen]; int16_t b[dataLen];
int main(){
  for (int i = 0; i < dataLen; ++i) { data_mask[i] = i%255; a[i] = i; b[i] = 0; }
  int avl = dataLen;
  int8_t* ptr_mask = data_mask;
  int16_t* ptr_a = a; int16_t* ptr_b = b;
  for (size_t vl; avl > 0; avl -= vl){
    vl = __riscv_vsetvl_e32m2(avl);
    vbool16_t vmask= __riscv_vmseq_vx_i8mf2_b16(__riscv_vle8_v_i8mf2(ptr_mask, vl), 1, vl);
    vint16m1_t va = __riscv_vlse16_v_i16m1(ptr_a, 2, vl);
    va = __riscv_vwadd_wx_i16m1_m(vmask, va, 92, vl);
    __riscv_vse16_v_i16m1(ptr_b, va, vl);
    ptr_mask += vl;
    ptr_a += vl; ptr_b += vl;
  }
  __builtin_printf("success");
  return 0;
}