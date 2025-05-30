#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short int __int16_t;
typedef short unsigned int __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long int __int64_t;
typedef long unsigned int __uint64_t;
typedef signed char __int_least8_t;
typedef unsigned char __uint_least8_t;
typedef short int __int_least16_t;
typedef short unsigned int __uint_least16_t;
typedef int __int_least32_t;
typedef unsigned int __uint_least32_t;
typedef long int __int_least64_t;
typedef long unsigned int __uint_least64_t;
typedef long int __intmax_t;
typedef long unsigned int __uintmax_t;
typedef long int __intptr_t;
typedef long unsigned int __uintptr_t;
typedef __int8_t int8_t ;
typedef __uint8_t uint8_t ;
typedef __int16_t int16_t ;
typedef __uint16_t uint16_t ;
typedef __int32_t int32_t ;
typedef __uint32_t uint32_t ;
typedef __int64_t int64_t ;
typedef __uint64_t uint64_t ;
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
typedef __intptr_t intptr_t;
typedef __uintptr_t uintptr_t;
typedef __int_least8_t int_least8_t;
typedef __uint_least8_t uint_least8_t;
typedef __int_least16_t int_least16_t;
typedef __uint_least16_t uint_least16_t;
typedef __int_least32_t int_least32_t;
typedef __uint_least32_t uint_least32_t;
typedef __int_least64_t int_least64_t;
typedef __uint_least64_t uint_least64_t;
  typedef int int_fast8_t;
  typedef unsigned int uint_fast8_t;
  typedef int int_fast16_t;
  typedef unsigned int uint_fast16_t;
  typedef int int_fast32_t;
  typedef unsigned int uint_fast32_t;
  typedef long int int_fast64_t;
  typedef long unsigned int uint_fast64_t;
#pragma GCC diagnostic pop
typedef long int ptrdiff_t;
typedef long unsigned int size_t;
typedef int wchar_t;
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
} max_align_t;
  typedef __typeof__(nullptr) nullptr_t;
#pragma riscv intrinsic "vector"
typedef _Float16 float16_t;
float16_t a[4]; float16_t b[4];
void initialize(){
  uint16_t tmp_0[4] = {43883, 3213, 238, 275, };
  for (int i = 0; i < 4; ++i) {
    union { float16_t f16; uint16_t u16; } converter;
    converter.u16 = tmp_0[i];
    a[i] = converter.f16;
  }
  for (int i = 0; i < 4; ++i) { b[i] = 0; }
}
void compute(){
  int avl = 4;
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
  for(int i=0; i<4; ++i) { __builtin_printf("%lf ", (double)(b[i])); } __builtin_printf("\n");
  return 0;
}
