// --seed 0xdeadbeef --data_length 10 --sequence_length 10
// connect type: vfloat16mf2_t
// scheduling mode: unit 
#include <riscv_vector.h>
#include <vector>

#define dataLen 10
#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & 0x03FF))
#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & 0x007FFFFF))
#define isNaNF64UI( a ) (((~(a) & UINT64_C( 0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF )))
typedef _Float16 float16_t;
typedef float float32_t;
typedef double float64_t;

unsigned long long int seed = 0;
void hash(unsigned long long int *seed, unsigned long long int const v) {
	*seed ^= v + 0x9e3779b9 + ((*seed)<<6) + ((*seed)>>2);
}

static inline float16_t convert_binary_u16_f16(uint16_t u16){
	union { float16_t f16; uint16_t u16; } converter;
	converter.u16 = u16;
	if(isNaNF16UI(converter.u16)) return 0;
	return converter.f16;
}
static inline float32_t convert_binary_u32_f32(uint32_t u32){
	union { float32_t f32; uint32_t u32; } converter;
	converter.u32 = u32;
	if(isNaNF32UI(converter.u32)) return 0;
	return converter.f32;
}
static inline float64_t convert_binary_u64_f64(uint64_t u64){
	union { float64_t f64; uint64_t u64; } converter;
	converter.u64 = u64;
	if(isNaNF64UI(converter.u64)) return 0;
	return converter.f64;
}
static inline uint16_t convert_binary_f16_u16(float16_t f16){
	union { float16_t f16; uint16_t u16; } converter;
	converter.f16 = f16;
	if(isNaNF16UI(converter.u16)) return (uint16_t)-1;
	return converter.u16;
}
static inline uint32_t convert_binary_f32_u32(float32_t f32){
	union { float32_t f32; uint32_t u32; } converter;
	converter.f32 = f32;
	if(isNaNF32UI(converter.u32)) return (uint32_t)-1;
	return converter.u32;
}
static inline uint64_t convert_binary_f64_u64(float64_t f64){
	union { float64_t f64; uint64_t u64; } converter;
	converter.f64 = f64;
	if(isNaNF64UI(converter.u64)) return (uint64_t)-1;
	return converter.u64;
}

uint8_t arr_mask[dataLen];
uint8_t arr_load_0[dataLen];
float64_t arr_load_1[dataLen];
int16_t arr_load_10[dataLen];
uint8_t arr_load_11[dataLen];
float32_t arr_load_12[dataLen];
int32_t arr_load_13[dataLen];
float64_t arr_load_2[dataLen];
float64_t arr_load_3[dataLen];
float64_t arr_load_4[dataLen];
float64_t arr_load_5[dataLen];
uint64_t arr_load_6[dataLen];
float32_t arr_load_7[dataLen];
int32_t arr_load_8[dataLen];
int16_t arr_load_9[dataLen];
uint8_t arr_store_vreg_0[dataLen];
float64_t arr_store_vreg_1[dataLen];
int16_t arr_store_vreg_2[dataLen];
int32_t arr_store_vreg_memory_13[dataLen];
float64_t arr_store_vreg_memory_2[dataLen];
float64_t arr_store_vreg_memory_4[dataLen];
uint64_t arr_store_vreg_memory_6[dataLen];
float32_t arr_store_vreg_memory_7[dataLen];
int16_t arr_store_vreg_memory_9[dataLen];

void init(){
	int8_t tmp_mask[dataLen] = {1, 1, 0, 1, 1, 0, 1, 1, 1, 1, };
	for (int i = 0; i < dataLen; ++i) { arr_mask[i] = tmp_mask[i]; }
	for (int i = 0; i < dataLen; ++i) { arr_load_0[i] = 12; }
	for (int i = 0; i < dataLen; ++i) { arr_load_1[i] = convert_binary_u64_f64(1426382866ull); }
	for (int i = 0; i < dataLen; ++i) { arr_load_10[i] = 1602; }
	for (int i = 0; i < dataLen; ++i) { arr_load_11[i] = 220; }
	for (int i = 0; i < dataLen; ++i) { arr_load_12[i] = convert_binary_u32_f32(2432830040u); }
	for (int i = 0; i < dataLen; ++i) { arr_load_13[i] = -582830563; }
	for (int i = 0; i < dataLen; ++i) { arr_load_2[i] = convert_binary_u64_f64(3592728916ull); }
	for (int i = 0; i < dataLen; ++i) { arr_load_3[i] = convert_binary_u64_f64(3454356601ull); }
	for (int i = 0; i < dataLen; ++i) { arr_load_4[i] = convert_binary_u64_f64(1398958096ull); }
	for (int i = 0; i < dataLen; ++i) { arr_load_5[i] = convert_binary_u64_f64(2790716594ull); }
	for (int i = 0; i < dataLen; ++i) { arr_load_6[i] = 2367101932ull; }
	for (int i = 0; i < dataLen; ++i) { arr_load_7[i] = convert_binary_u32_f32(4225202605u); }
	for (int i = 0; i < dataLen; ++i) { arr_load_8[i] = 1002527417; }
	for (int i = 0; i < dataLen; ++i) { arr_load_9[i] = 28852; }
	for (int i = 0; i < dataLen; ++i) { arr_store_vreg_0[i] = 134; }
	for (int i = 0; i < dataLen; ++i) { arr_store_vreg_1[i] = convert_binary_u64_f64(4002661540ull); }
	for (int i = 0; i < dataLen; ++i) { arr_store_vreg_2[i] = -14300; }
	for (int i = 0; i < dataLen; ++i) { arr_store_vreg_memory_13[i] = 1429446929; }
	for (int i = 0; i < dataLen; ++i) { arr_store_vreg_memory_2[i] = convert_binary_u64_f64(343262935ull); }
	for (int i = 0; i < dataLen; ++i) { arr_store_vreg_memory_4[i] = convert_binary_u64_f64(3137003815ull); }
	for (int i = 0; i < dataLen; ++i) { arr_store_vreg_memory_6[i] = 3905071948ull; }
	for (int i = 0; i < dataLen; ++i) { arr_store_vreg_memory_7[i] = convert_binary_u32_f32(1715557044u); }
	for (int i = 0; i < dataLen; ++i) { arr_store_vreg_memory_9[i] = -5771; }
}

void test() {
	for (size_t ptr = 0, avl = dataLen; avl > 0; ){
		size_t vl = __riscv_vsetvl_e16mf2(avl);
		vuint8mf4_t mask_value= __riscv_vle8_v_u8mf4(&arr_mask[ptr], vl);
		vbool32_t vmask= __riscv_vmseq_vx_u8mf4_b32(mask_value, 1, vl);
		vuint32m1_t idx_0 = __riscv_vsll_vx_u32m1(__riscv_vid_v_u32m1(vl), 0, vl);
		vuint8mf4_t vreg_memory_0 = __riscv_vluxei32_v_u8mf4_tum(vmask, __riscv_vmv_v_x_u8mf4(0, __riscv_vsetvlmax_e16mf2()), &arr_load_0[ptr], idx_0, vl);
		vbool32_t vreg_0 = __riscv_vmsltu(vreg_memory_0, 243, vl);
		vuint8mf4_t zero_0 = __riscv_vmv_v_x_u8mf4(0, __riscv_vsetvlmax_e8mf4());
		vuint8mf4_t vstore_tmp_0 = __riscv_vmerge_vxm_u8mf4(zero_0, 1, vreg_0, vl);
		__riscv_vse8_v_u8mf4(&arr_store_vreg_0[ptr], vstore_tmp_0, vl);
		vuint8mf4_t idx_1 = __riscv_vsll_vx_u8mf4(__riscv_vid_v_u8mf4(vl), 3, vl);
		vfloat64m2_t vreg_memory_1 = __riscv_vloxei8_tumu(vmask, __riscv_vfmv_v_f_f64m2(0, __riscv_vsetvlmax_e16mf2()), &arr_load_1[ptr], idx_1, vl);
		vuint64m2_t idx_2 = __riscv_vsll_vx_u64m2(__riscv_vid_v_u64m2(vl), 3, vl);
		vfloat64m2_t vreg_memory_2 = __riscv_vluxei64_v_f64m2_tum(vmask, __riscv_vfmv_v_f_f64m2(0, __riscv_vsetvlmax_e32m1()), &arr_load_2[ptr], idx_2, vl);
		vreg_memory_2 = __riscv_vfmsac(vreg_memory_1, vreg_memory_1, vreg_memory_2, vl);
		__riscv_vse64(vmask, &arr_store_vreg_memory_2[ptr], vreg_memory_2, vl);
		vfloat64m1_t vd_load_3 = __riscv_vfmv_v_f_f64m1(0, __riscv_vsetvlmax_e64m1());
		vfloat64m1_t vreg_memory_3 = __riscv_vle64_v_f64m1_tu(vd_load_3, &arr_load_3[ptr], vl);
		vuint8mf4_t idx_3 = __riscv_vsll_vx_u8mf4(__riscv_vid_v_u8mf4(vl), 3, vl);
		vfloat64m2_t vreg_memory_4 = __riscv_vloxei8_v_f64m2_tumu(__riscv_vlm_v_b32(std::vector<uint8_t>((vl + 7) / 8, 255).data(), vl), __riscv_vfmv_v_f_f64m2(0, __riscv_vsetvlmax_e8mf4()), &arr_load_4[ptr], idx_3, vl);
		vfloat64m1_t vd_load_5 = __riscv_vfmv_v_f_f64m1(0, __riscv_vsetvlmax_e32mf2());
		vfloat64m1_t vreg_memory_5 = __riscv_vle64_v_f64m1_tu(vd_load_5, &arr_load_5[ptr], vl);
		vfloat64m1_t vreg_1 = __riscv_vfredusum_vs_f64m2_f64m1_tu(vreg_memory_3, vreg_memory_4, vreg_memory_5, vl);
		__riscv_vse64_v_f64m1(&arr_store_vreg_1[ptr], vreg_1, vl);
		vuint8mf4_t idx_4 = __riscv_vsll_vx_u8mf4(__riscv_vid_v_u8mf4(vl), 3, vl);
		vuint64m2_t vreg_memory_6 = __riscv_vluxei8_mu(vmask, __riscv_vmv_v_x_u64m2(0, __riscv_vsetvlmax_e32m1()), &arr_load_6[ptr], idx_4, vl);
		vreg_memory_6 = __riscv_vand_tum(vmask, vreg_memory_6, vreg_memory_6, 2960760473ull, vl);
		vuint8mf4_t idx_5 = __riscv_vsll_vx_u8mf4(__riscv_vid_v_u8mf4(vl), 3, vl);
		__riscv_vsoxei8(&arr_store_vreg_memory_6[ptr], idx_5, vreg_memory_6, vl);
		vuint64m2_t idx_6 = __riscv_vsll_vx_u64m2(__riscv_vid_v_u64m2(vl), 2, vl);
		vfloat32m1_t vreg_memory_7 = __riscv_vloxei64_mu(vmask, __riscv_vfmv_v_f_f32m1(0, __riscv_vsetvlmax_e64m2()), &arr_load_7[ptr], idx_6, vl);
		vreg_memory_7 = __riscv_vfmsub_tum(vmask, vreg_memory_7, convert_binary_u32_f32(37392u), vreg_memory_7, __RISCV_FRM_RUP, vl);
		vuint16mf2_t idx_7 = __riscv_vsll_vx_u16mf2(__riscv_vid_v_u16mf2(vl), 2, vl);
		__riscv_vsuxei16(&arr_store_vreg_memory_7[ptr], idx_7, vreg_memory_7, vl);
		vuint8mf4_t idx_8 = __riscv_vsll_vx_u8mf4(__riscv_vid_v_u8mf4(vl), 2, vl);
		vint32m1_t vreg_memory_8 = __riscv_vloxei8_v_i32m1_m(vmask, &arr_load_8[ptr], idx_8, vl);
		vint16mf2_t vreg_2 = __riscv_vncvt_x(vreg_memory_8, vl);
		__riscv_vse16(vmask, &arr_store_vreg_2[ptr], vreg_2, vl);
		vuint64m2_t idx_9 = __riscv_vsll_vx_u64m2(__riscv_vid_v_u64m2(vl), 1, vl);
		vint16mf2_t vreg_memory_9 = __riscv_vluxei64_mu(__riscv_vlm_v_b32(std::vector<uint8_t>((vl + 7) / 8, 255).data(), vl), __riscv_vmv_v_x_i16mf2(0, __riscv_vsetvlmax_e8mf4()), &arr_load_9[ptr], idx_9, vl);
		vuint8mf4_t idx_10 = __riscv_vsll_vx_u8mf4(__riscv_vid_v_u8mf4(vl), 1, vl);
		vint16mf2_t vreg_memory_10 = __riscv_vloxei8_v_i16mf2(&arr_load_10[ptr], idx_10, vl);
		vbool32_t vreg_memory_11 = __riscv_vlm_v_b32(&arr_load_11[ptr], vl);
		vreg_memory_9 = __riscv_vcompress_tu(vreg_memory_9, vreg_memory_10, vreg_memory_11, vl);
		__riscv_vsse16_v_i16mf2(&arr_store_vreg_memory_9[ptr], 2, vreg_memory_9, vl);
		vreg_memory_4 = __riscv_vfsgnjn_vv_f64m2(vreg_memory_2, vreg_memory_2, vl);
		vuint8mf4_t idx_11 = __riscv_vsll_vx_u8mf4(__riscv_vid_v_u8mf4(vl), 3, vl);
		__riscv_vsoxei8(vmask, &arr_store_vreg_memory_4[ptr], idx_11, vreg_memory_4, vl);
		vuint64m2_t idx_12 = __riscv_vsll_vx_u64m2(__riscv_vid_v_u64m2(vl), 2, vl);
		vfloat32m1_t vreg_memory_12 = __riscv_vluxei64_tu(__riscv_vfmv_v_f_f32m1(0, __riscv_vsetvlmax_e16mf2()), &arr_load_12[ptr], idx_12, vl);
		vreg_memory_7 = __riscv_vfslide1up(vmask, vreg_memory_12, convert_binary_u32_f32(43917u), vl);
		vuint8mf4_t idx_13 = __riscv_vsll_vx_u8mf4(__riscv_vid_v_u8mf4(vl), 2, vl);
		__riscv_vsuxei8_v_f32m1(&arr_store_vreg_memory_7[ptr], idx_13, vreg_memory_7, vl);
		vint32m1_t vreg_memory_13 = __riscv_vlse32_tumu(vmask, __riscv_vmv_v_x_i32m1(0, __riscv_vsetvlmax_e8mf4()), &arr_load_13[ptr], 4, vl);
		vreg_memory_13 = __riscv_vsadd_vx_i32m1_mu(vmask, vreg_memory_13, vreg_memory_13, 1319961238, vl);
		vuint16mf2_t idx_14 = __riscv_vsll_vx_u16mf2(__riscv_vid_v_u16mf2(vl), 2, vl);
		__riscv_vsoxei16_v_i32m1(&arr_store_vreg_memory_13[ptr], idx_14, vreg_memory_13, vl);
		ptr += vl; avl -= vl;
	}
}

void checksum(){
	__builtin_printf("%llu", seed);
	for(int i=0; i<dataLen; ++i) { if(arr_mask[i]) hash(&seed, arr_store_vreg_0[i]); } 
	for(int i=0; i<dataLen; ++i) { if(arr_mask[i]) hash(&seed, convert_binary_f64_u64(arr_store_vreg_1[i])); } 
	for(int i=0; i<dataLen; ++i) { if(arr_mask[i]) hash(&seed, arr_store_vreg_2[i]); } 
	for(int i=0; i<dataLen; ++i) { if(arr_mask[i]) hash(&seed, arr_store_vreg_memory_13[i]); } 
	for(int i=0; i<dataLen; ++i) { if(arr_mask[i]) hash(&seed, convert_binary_f64_u64(arr_store_vreg_memory_2[i])); } 
	for(int i=0; i<dataLen; ++i) { if(arr_mask[i]) hash(&seed, convert_binary_f64_u64(arr_store_vreg_memory_4[i])); } 
	for(int i=0; i<dataLen; ++i) { if(arr_mask[i]) hash(&seed, arr_store_vreg_memory_6[i]); } 
	for(int i=0; i<dataLen; ++i) { if(arr_mask[i]) hash(&seed, convert_binary_f32_u32(arr_store_vreg_memory_7[i])); } 
	for(int i=0; i<dataLen; ++i) { if(arr_mask[i]) hash(&seed, arr_store_vreg_memory_9[i]); } 
	__builtin_printf("%llu\n", seed);
}

int main(){
	init();
	test();
	checksum();
	return 0;
}
