#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <regex>
#include <iostream>
#include <vector>
#include <random>
#include <unistd.h>
#include <cmath>
#include "softfloat.h"
#include "json.hpp" // JSON for Modern C++ version 3.11.3, in the `extern` directory

#ifndef DEF_INPUT
// set to 0: .jsonl is input, compile fast, run slow
// set to 1: .def is input, compile slow, run fast
#define DEF_INPUT 1
#endif // DEF_INPUT

#ifndef JSON_INPUT
#define JSON_INPUT (1-DEF_INPUT)
#endif

extern std::string JsonlFilePath;
extern std::string CodeDirPath;
extern int totalLineNum;
extern bool ifSegment;

extern unsigned int dataLen;
extern unsigned int seqLen;
extern std::string connect_type; // selected in UsedTYPES::initializeAllTypes()

enum Type{
    Void,
    Scalar,
    OneDVector,
    VXRM,       // unsigned int vxrm
    FRM,        // unsigned int frm
    VL,         // size_t vl
    Index,      // size_t index
    Ptrdiff,    // ptrdiff_t
    VMASK,      // mask, vbool[0-9]+_t vm
    UnknownType
};

enum SchedulingMODE{
    Unit,
    Allin,
    Random
};
extern SchedulingMODE SchedulingMode;

// for generating load-store intrinsics
/*
enum NamingScheme{
    Non_overloaded,
    Non_overloaded_with_policy,
    Overloaded,
    Overloaded_with_policy
};
extern NamingScheme namingscheme;
*/
extern bool withPolicy;
extern bool withOverloaded;

extern std::vector<std::string> PolicySuffixes;
extern std::vector<std::string> PolicySuffixes_mask;
extern std::vector<std::string> __RISCV_VXRM;
extern std::vector<std::string> __RISCV_FRM;

// generate the intrinsic suffix
std::string genPolicySuffix(bool mask, bool policy = withPolicy);

void parseArguments(int argc, char **argv);

// given a std::string, replace all the substrings to a new std::string
std::string replaceSubstring(std::string str, const std::string& oldSubstring, const std::string& newSubstring);

// return whether a std::string starts with another std::string
bool startsWith(const std::string& str, const std::string& prefix);

// return whether a std::string ends with another std::string
bool endsWith(const std::string& str, const std::string& suffix);

// removes any leading, and trailing whitespaces of the given std::string
std::string strip(const std::string& str);

// merge continuous spaces into one space, and
// remove any leading, and trailing whitespaces and quotes of the given std::string
std::string strClean(const std::string& str);

// print usage of RVISmith
inline void printUsage(std::ostream &out, std::string filename){
    out << "Usage: " << filename << " [OPTION...]" <<  std::endl;
    out << "-s <seed, default = 0xdeadbeef>" << std::endl;
    out << "-l <data_length, default = 10>" << std::endl;
    out << "-j <json_path, default = \"../rvv-doc/parsed.jsonl\">" << std::endl;
    out << "-o <output_path, default = \"1.c\">" << std::endl;
    out << "-h" << std::endl;
}

// progress bar
void displayProgressBar(std::ostream& os, float progress);


// random
extern uint32_t InitialSeed;
extern std::mt19937 rng;
void initializeRNG(uint32_t seed = InitialSeed);
template <typename T, typename T2>
T getRandomNumber(T2 minValue, T2 maxValue, uint64_t *raw = nullptr) {
    static_assert(std::is_integral<T>::value,
                "non integral type should be handeled explicitly");
    T ret = std::uniform_int_distribution<T>(minValue, maxValue)(rng);
    if (raw != nullptr)
    *raw = ret;
    return ret;
}
template <>
float16_t getRandomNumber(int minValue, int maxValue, uint64_t *raw);
template <>
float32_t getRandomNumber(int minValue, int maxValue, uint64_t *raw);
template <>
float64_t getRandomNumber(int minValue, int maxValue, uint64_t *raw);

#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & 0x03FF))
#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & 0x007FFFFF))
#define isNaNF64UI( a ) (((~(a) & UINT64_C( 0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF )))

inline float16_t converter_binary_u16_f16(uint16_t u16){
    union { float16_t f16; uint16_t u16; } converter;
    converter.u16 = u16;
    return converter.f16;
}

inline float32_t converter_binary_u32_f32(uint32_t u32){
    union { float32_t f32; uint32_t u32; } converter;
    converter.u32 = u32;
    return converter.f32;
}

inline float64_t converter_binary_u64_f64(uint64_t u64){
    union { float64_t f64; uint32_t u64; } converter;
    converter.u64 = u64;
    return converter.f64;
}

// for select
// select the iterator point to the element of given index
template <typename S> typename S::iterator select_idx(S &s, size_t idx) {
    idx %= s.size();
    typename S::iterator it = std::begin(s);
    std::advance(it, idx);
    return it;
}
// randomly select an element
template <typename S> typename S::iterator select_random(S &s) {
    size_t n = getRandomNumber<int>(0, (int)s.size() - 1);
    n %= s.size();
    typename S::iterator it = std::begin(s);
    std::advance(it, n);
    return it;
}

std::string mul2str(float mul); // e.g., 1/8 to "mf8"

std::string genIdxType(int ratio); // given ratio, return the type of 'rs2' used in indexed load-store intrinsics


// insert an element into a std::vector (or any container supporting random-access iterators) 
// at a random position between two iterators [start, end]
template<typename T, typename Container>
typename Container::iterator insertRandomly(Container & container, \
                            typename Container::iterator it_start, typename Container::iterator it_end, const T& value) {
    // Calculate the distance between the iterators
    int distance = std::distance(it_start, it_end);

    if(distance < 0){
        std::cerr << " randomly insert error: start is less than end." << std::endl;
        exit(1);
    }

    // Set up a random number generator
    std::uniform_int_distribution<> dis(0, distance);

    // Generate a random index and move the iterator to that position
    auto random_it = it_start;
    std::advance(random_it, dis(rng));

    // Insert the element at the random position
    return container.insert(random_it, value);
}

// given the value of bits, return the value of bytes
// e.g., 32 bits --> 4 bytes
int bits2bytes(int bits);

// given the value of bits, return the move of digits for `vsll_vx`
// e.g., 32 bits --> 4 bytes --> 2 move
int bits2moven(int bits);

std::string nfield2n(std::string nfield);

#endif // UTILS_HPP