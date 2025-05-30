#include <riscv_vector.h>
#define dataLen 4
typedef _Float16 float16_t;
float16_t a[dataLen]; float16_t b[dataLen];

void initialize(){
  uint16_t tmp_0[dataLen] = {43883, 3213, 238, 275, };
  for (int i = 0; i < dataLen; ++i) { 
    union { float16_t f16; uint16_t u16; } converter;
    converter.u16 = tmp_0[i];
    a[i] = converter.f16; 
  }
  for (int i = 0; i < dataLen; ++i) { b[i] = 0; }
}

void compute(){
  int avl = dataLen;
  float16_t* ptr_a = a; float16_t* ptr_b = b;
  for (size_t vl; avl > 0; avl -= vl){
    vl = __riscv_vsetvl_e16m1(avl);
    vfloat16m1_t va = __riscv_vle16_v_f16m1(ptr_a, vl);
    va = __riscv_vfnmadd_vv_f16m1_rm(va, va, va, __RISCV_FRM_RDN, vl);
    va = __riscv_vfmsac_vv_f16m1(va, va, va, vl);
    __riscv_vse16_v_f16m1(ptr_b, va, vl);
    ptr_a += vl; ptr_b += vl;
  }
}

int main(){
  initialize();
  compute();
  for(int i=0; i<dataLen; ++i) { __builtin_printf("%lf ", (double)(b[i])); } __builtin_printf("\n");
  return 0;
}