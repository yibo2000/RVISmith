#include <stddef.h>
#include <stdio.h>
#include <riscv_vector.h>

void printvlmax(){
    printf("__riscv_vsetvlmax_e8mf8() = %d\n", __riscv_vsetvlmax_e8mf8());
    printf("__riscv_vsetvlmax_e8mf4() = %d\n", __riscv_vsetvlmax_e8mf4());
    printf("__riscv_vsetvlmax_e8mf2() = %d\n", __riscv_vsetvlmax_e8mf2());
    printf("__riscv_vsetvlmax_e8m1() = %d\n", __riscv_vsetvlmax_e8m1());
    printf("__riscv_vsetvlmax_e8m2() = %d\n", __riscv_vsetvlmax_e8m2());
    printf("__riscv_vsetvlmax_e8m4() = %d\n", __riscv_vsetvlmax_e8m4());
    printf("__riscv_vsetvlmax_e8m8() = %d\n", __riscv_vsetvlmax_e8m8());
    printf("__riscv_vsetvlmax_e16mf4() = %d\n", __riscv_vsetvlmax_e16mf4());
    printf("__riscv_vsetvlmax_e16mf2() = %d\n", __riscv_vsetvlmax_e16mf2());
    printf("__riscv_vsetvlmax_e16m1() = %d\n", __riscv_vsetvlmax_e16m1());
    printf("__riscv_vsetvlmax_e16m2() = %d\n", __riscv_vsetvlmax_e16m2());
    printf("__riscv_vsetvlmax_e16m4() = %d\n", __riscv_vsetvlmax_e16m4());
    printf("__riscv_vsetvlmax_e16m8() = %d\n", __riscv_vsetvlmax_e16m8());
    printf("__riscv_vsetvlmax_e32mf2() = %d\n", __riscv_vsetvlmax_e32mf2());
    printf("__riscv_vsetvlmax_e32m1() = %d\n", __riscv_vsetvlmax_e32m1());
    printf("__riscv_vsetvlmax_e32m2() = %d\n", __riscv_vsetvlmax_e32m2());
    printf("__riscv_vsetvlmax_e32m4() = %d\n", __riscv_vsetvlmax_e32m4());
    printf("__riscv_vsetvlmax_e32m8() = %d\n", __riscv_vsetvlmax_e32m8());
    printf("__riscv_vsetvlmax_e64m1() = %d\n", __riscv_vsetvlmax_e64m1());
    printf("__riscv_vsetvlmax_e64m2() = %d\n", __riscv_vsetvlmax_e64m2());
    printf("__riscv_vsetvlmax_e64m4() = %d\n", __riscv_vsetvlmax_e64m4());
    printf("__riscv_vsetvlmax_e64m8() = %d\n", __riscv_vsetvlmax_e64m8());
}

int main(){
    printvlmax();
    return 0;
}