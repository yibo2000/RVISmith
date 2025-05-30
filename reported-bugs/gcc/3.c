#include <riscv_vector.h>
void abort(void);
#define dataLen 10
int16_t a[dataLen]; int16_t b[dataLen];

int main(){
  for (int i = 0; i < dataLen; ++i) { a[i] = i * 5; }
  for (int i = 0; i < dataLen; ++i) { b[i] = 0; }
  int avl = dataLen;
  int16_t* ptr_a = a; int16_t* ptr_b = b;
  for (size_t vl; avl > 0; avl -= vl){
    vl = __riscv_vsetvl_e64m1(avl);
    vint16mf4_t va = __riscv_vle16_v_i16mf4(ptr_a, vl);
    va = __riscv_vasub_vx_i16mf4(va, 0, __RISCV_VXRM_RDN, vl); //round-down (truncate) 
    __riscv_vse16_v_i16mf4(ptr_b, va, vl);
    ptr_a += vl; ptr_b += vl;
  }
  for(int i=0; i<dataLen; ++i) { 
    //if(  (int)a[i]/2 != b[i]  ) abort();  
    __builtin_printf("%d ", b[i]); 
  } __builtin_printf("\n");
  return 0;
}