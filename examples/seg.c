#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <riscv_vector.h>

#define ARRAY_SIZE 11

float a_array[ARRAY_SIZE] = {
1.18869953,  1.55298864, -0.17365574, -1.86193886,
-1.52391526, -0.36566814,  0.70753702,  0.73992422,
-0.13493693,  1.09563677, 1.03797902
};
 
float b_array[ARRAY_SIZE] = {
1.19655525,  0.23393777, -0.11629651, -0.54508896,
-1.2424749, -1.54835913,  0.86935212,  0.12946646,
0.81831905, -0.42723697, -0.89793257
};

float c_array_ref[ARRAY_SIZE] = {
2.38525478, 1.78692641, -0.28995225, -2.40702783,
-2.76639016, -1.91402727, 1.57688914, 0.86939068,
0.68338213, 0.66839979, 0.14004644
};
float c_array_vec[ARRAY_SIZE];

void add(const float *a, const float *b, float *c, size_t length)
{
    for (int i = 0; i < length; i++) {
        c[i] = a[i] + b[i];
    }
}

void add_vec(const float *a, const float *b, float *c, size_t length)
{
    while (length > 0) {
        size_t vl = __riscv_vsetvl_e32m4(length); // vl = 16
        // vl = 16, but vlmax for `vfloat32m2_t` is 8.
        vfloat32m2x2_t va_x2 = __riscv_vlseg2e32_v_f32m2x2(a, vl);
        vfloat32m2_t va_0 = __riscv_vget_v_f32m2x2_f32m2(va_x2, 0);
        vfloat32m2_t va_1 = __riscv_vget_v_f32m2x2_f32m2(va_x2, 1);

        vfloat32m2x2_t vb_x2 = __riscv_vlseg2e32_v_f32m2x2(b, vl);
        vfloat32m2_t vb_0 = __riscv_vget_v_f32m2x2_f32m2(vb_x2, 0);
        vfloat32m2_t vb_1 = __riscv_vget_v_f32m2x2_f32m2(vb_x2, 1);

        vfloat32m2_t vc_0 = __riscv_vfadd_vv_f32m2(va_0, vb_0, vl); // c = a + b
        vfloat32m2_t vc_1 = __riscv_vfadd_vv_f32m2(va_1, vb_1, vl); // c = a + b
        vfloat32m2x2_t vc_x2 = __riscv_vcreate_v_f32m2x2(vc_0, vc_1);
        __riscv_vsseg2e32_v_f32m2x2(c, vc_x2, vl); // store 8 elements

        a += vl;
        b += vl;
        c += vl;
        length -= vl;
    }
}

int main(){
    add_vec(a_array, b_array, c_array_vec, ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (fabsf(c_array_ref[i] - c_array_vec[i]) > 1e-6) {
            printf("index[%d] failed, %f!=%f\n", i, c_array_ref[i], c_array_vec[i]);
        } else {
            printf("index[%d] successed, %f=%f\n", i, c_array_ref[i], c_array_vec[i]);
        }
    }
    return 0;
}