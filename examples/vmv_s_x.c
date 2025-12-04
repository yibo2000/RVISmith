#include <stddef.h>
#include <stdio.h>
#include <riscv_vector.h>

#define ARRAY_SIZE 9

// __riscv_vfmv_s_f
// vint8mf8_t __riscv_vmv_s_x_i8mf8(int8_t rs1, size_t vl);
int8_t src1[ARRAY_SIZE] = {1, 14, 35, 68, 10, 0, -12, -79, 10, }; 
int8_t dst1[ARRAY_SIZE] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,};

// Reinterpret between different SEW under the same LMUL
// vint16mf4_t __riscv_vreinterpret_v_i8mf4_i16mf4(vint8mf4_t src);
int8_t src2[ARRAY_SIZE] = {1, 14, 35, 68, 10, 0, -12, -79, 10, }; 
int16_t dst2[ARRAY_SIZE] = {-1, -1, -1, -1, -1, -1, -1, -1, -1,};

void MyPrint(char* arr){
    for (int i=0; i<ARRAY_SIZE; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

void MyPrint2(int16_t * arr){
    for (int i=0; i<ARRAY_SIZE; ++i)
        printf("%x ", arr[i]);
    printf("\n");
}

int main(){
    int tbd = ARRAY_SIZE;
    int8_t* ptr_src1 = src1;
    uint8_t* ptr_dst1 = dst1;
    for (size_t vl; tbd > 0; tbd -= vl){
        vl = __riscv_vsetvl_e8mf4 (tbd);
        vint8mf4_t ld = __riscv_vle8_v_i8mf4(ptr_src1, vl);
        vint8mf4_t vec_src1 = __riscv_vmv_s_x_i8mf4_tu(ld, 8, vl);
        __riscv_vse8_v_i8mf4 (ptr_dst1, vec_src1, vl);
        ptr_src1 += vl;
        ptr_dst1 += vl;
    }
    MyPrint(dst1);

    return 0;
}