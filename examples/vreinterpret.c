#include <stddef.h>
#include <stdio.h>
#include <riscv_vector.h>

#define ARRAY_SIZE 9

// Reinterpret between different type under the same SEW/LMUL
// vuint8mf8_t __riscv_vreinterpret_v_i8mf8_u8mf8(vint8mf8_t src);
int8_t src1[ARRAY_SIZE] = {1, 14, 35, 68, 10, 0, -12, -79, 10, }; 
uint8_t dst1[ARRAY_SIZE];

// Reinterpret between different SEW under the same LMUL
// vint16mf4_t __riscv_vreinterpret_v_i8mf4_i16mf4(vint8mf4_t src);
int8_t src2[ARRAY_SIZE] = {1, 14, 35, 68, 10, 0, -12, -79, 10, }; 
int16_t dst2[ARRAY_SIZE] = {-1, -1, -1, -1, -1, -1, -1, -1, -1,};

// Reinterpret between vector boolean types and LMUL=1 (m1) vector integer types
// vbool64_t __riscv_vreinterpret_v_i8m1_b64(vint8m1_t src);

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
        vl = __riscv_vsetvl_e8mf8 (tbd);
        vint8mf8_t vec_src1 = __riscv_vle8_v_i8mf8(ptr_src1, vl);
        vuint8mf8_t vec_dst1 = __riscv_vreinterpret_v_i8mf8_u8mf8(vec_src1);
        __riscv_vse8_v_u8mf8 (ptr_dst1, vec_dst1, vl);
        ptr_src1 += vl;
        ptr_dst1 += vl;
    }
    MyPrint(dst1);


    tbd = ARRAY_SIZE;
    int8_t* ptr_src2 = src2;
    int16_t* ptr_dst2 = dst2;
    for (size_t vl; tbd > 0; ){
        // vl = 3;
        vl = __riscv_vsetvl_e8mf4 (tbd);
        printf("%d\n", vl);
        vint8mf4_t vec_src2 = __riscv_vle8_v_i8mf4(ptr_src2, vl);
        vint16mf4_t vec_dst2 = __riscv_vreinterpret_v_i8mf4_i16mf4(vec_src2);
        __riscv_vse16_v_i16mf4 (ptr_dst2, vec_dst2, vl);
        printf("%d\n", vl);
        ptr_src2 += vl;
        ptr_dst2 += vl;
        tbd -= vl;
    }
    MyPrint2(dst2);
    return 0;
}