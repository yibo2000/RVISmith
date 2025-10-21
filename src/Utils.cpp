#include "Utils.hpp"
#include "cxxopts.hpp"

// default
std::string JsonlFilePath;
std::string CodeDirPath;
std::string connect_type;
unsigned int dataLen = 10;
unsigned int seqLen = 10;
int totalLineNum = 0;
bool ifSegment = false;

uint32_t InitialSeed = 0xdeadbeef;
std::mt19937 rng;
SchedulingMODE SchedulingMode = SchedulingMODE::Allin;

std::vector<std::string> PolicySuffixes = {"_tu" };
std::vector<std::string> PolicySuffixes_mask = {"_tum", "_mu", "_tumu"};

std::vector<std::string> __RISCV_VXRM = {"__RISCV_VXRM_RNU", "__RISCV_VXRM_RNE", "__RISCV_VXRM_RDN", "__RISCV_VXRM_ROD"};
std::vector<std::string> __RISCV_FRM = {"__RISCV_FRM_RNE", "__RISCV_FRM_RTZ", "__RISCV_FRM_RDN", "__RISCV_FRM_RUP", "__RISCV_FRM_RMM"};

bool withPolicy = false;
bool withOverloaded = false;

void parseArguments(int argc, char **argv) {
    std::string filename = argv[0]; JsonlFilePath.assign("../rvv-doc/parsed.jsonl");
    if (argc < 1) { printUsage(std::cerr, filename); exit(1); }

    cxxopts::Options options("RVISmith", "One line description of RVISmith");

    options.add_options()
        ("s,seed", "Seed", cxxopts::value<uint32_t>()->default_value("0xdeadbeef")) // uint32_t InitialSeed
        ("l,data_length", "Data length", cxxopts::value<unsigned int>()->default_value( "10" )) // unsigned int dataLen
        ("n,sequence_length", "Sequence length", cxxopts::value<unsigned int>()->default_value( "10" )) // unsigned int dataLen
        ("r,root", "Root (connect type)", cxxopts::value<std::string>()->default_value("vint8mf8_t")) // std::string connect_type
        //("j,json_path", "Jsonl file path", cxxopts::value<std::string>()->default_value("../rvv-doc/parsed.jsonl")) // std::string JsonlFilePath
        ("o,output", "Output path", cxxopts::value<std::string>()->default_value("./")) // std::string CodeDirPath
        //("mode", "Instruction scheduling mode {unit,allin,random}", cxxopts::value<std::string>()->default_value("allin"))// instruction scheduling mode
        ("segment", "Whether segment load-store intrinsics are included (default: false)")
        ("policy", "Whether load-store intrinsics with policy suffixes are included (default: false)")
        ("overloaded", "Whether overloaded load-store intrinsics are included (default: false)")
        ("h,help", "Print usage")
    ;
    auto result = options.parse(argc, argv);
    if (result.count("help")){
      std::cout << options.help() << std::endl;
      exit(0);
    }

    /*
    if (result["mode"].as<std::string>() == "random"){
        SchedulingMode = SchedulingMODE::Random;
    }else if (result["mode"].as<std::string>() == "unit"){
        SchedulingMode = SchedulingMODE::Unit;
    }else if (result["mode"].as<std::string>() == "allin"){
        SchedulingMode = SchedulingMODE::Allin;
    }else{
        std::cerr << "Argument `mode` is set error, the value should be in  {unit,allin,random}." << std::endl;
        std::cerr << options.help() << std::endl;
        exit(1);
    }*/

    if ( result.count("segment") ){
        ifSegment = true;
    } else { ifSegment = false; }

    if ( result.count("policy") ){
        withPolicy = true;
    } else { withPolicy = false; }

    if ( result.count("overloaded") ){
        withOverloaded = true;
    } else { withOverloaded = false; }

    InitialSeed = result["seed"].as<uint32_t>();
    dataLen = result["data_length"].as<unsigned int>();
    seqLen = result["sequence_length"].as<unsigned int>();
    connect_type = result["root"].as<std::string>();
    JsonlFilePath = std::string("../rvv-doc/parsed.jsonl");
    CodeDirPath = result["output"].as<std::string>();

    std::vector<std::string> vector_type_list = {"vint64m1_t", "vint64m2_t", "vint64m4_t", "vint64m8_t", \
    "vint32m1_t", "vint32m2_t", "vint32m4_t", "vint32m8_t", "vint32mf2_t", \
    "vint16m1_t", "vint16m2_t", "vint16m4_t", "vint16m8_t", "vint16mf2_t", "vint16mf4_t", \
    "vint8m1_t", "vint8m2_t", "vint8m4_t", "vint8m8_t", "vint8mf2_t", "vint8mf4_t", "vint8mf8_t", \
    "vuint64m1_t", "vuint64m2_t", "vuint64m4_t", "vuint64m8_t", \
    "vuint32m1_t", "vuint32m2_t", "vuint32m4_t", "vuint32m8_t", "vuint32mf2_t", \
    "vuint16m1_t", "vuint16m2_t", "vuint16m4_t", "vuint16m8_t", "vuint16mf2_t", "vuint16mf4_t", \
    "vuint8m1_t", "vuint8m2_t", "vuint8m4_t", "vuint8m8_t", "vuint8mf2_t", "vuint8mf4_t" ,"vuint8mf8_t", \
    "vfloat64m1_t", "vfloat64m2_t", "vfloat64m4_t", "vfloat64m8_t", \
    "vfloat32m1_t", "vfloat32m2_t", "vfloat32m4_t", "vfloat32m8_t", "vfloat32mf2_t", \
    "vfloat16m1_t", "vfloat16m2_t", "vfloat16m4_t", "vfloat16m8_t", "vfloat16mf2_t", "vfloat16mf4_t", \
    "vbool1_t", "vbool2_t", "vbool4_t", "vbool8_t", "vbool16_t", "vbool32_t", "vbool64_t"};
    if( std::find(vector_type_list.begin(), vector_type_list.end(), connect_type) == vector_type_list.end() ){
        // unknown connect_type
        std::cerr << "unknown connect_type: " << connect_type << ", use default vint8mf8_t" << std::endl;
        connect_type = std::string("vint8mf8_t");
    }
}

// given a std::string, replace all the substrings to a new std::string
std::string replaceSubstring(std::string str, const std::string& oldSubstring, const std::string& newSubstring) {
    size_t pos = 0;

    // Loop to find and replace all occurrences
    while ((pos = str.find(oldSubstring, pos)) != std::string::npos) {
        str.replace(pos, oldSubstring.length(), newSubstring);
        pos += newSubstring.length(); // Move past the replaced substring
    }

    return str;
}

// return whether a std::string starts with another std::string
bool startsWith(const std::string& str, const std::string& prefix) {
    return str.find(prefix) == 0;  // Return true if prefix is found at the start (index 0)
}

// return whether a std::string ends with another std::string
bool endsWith(const std::string& str, const std::string& suffix) {
    if (suffix.length() > str.length()) return false;
    return str.substr(str.length() - suffix.length()) == suffix;
}

// removes any leading, and trailing whitespaces of the given std::string
std::string strip(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v"); // Find the first non-whitespace character from the start

    if (start == std::string::npos) { return ""; }
    size_t end = str.find_last_not_of(" \t\n\r\f\v"); // Find the last non-whitespace character from the end
    return str.substr(start, end - start + 1); // Return the substring without leading and trailing whitespace
}

// merge continuous spaces into one space, and
// remove any leading, and trailing whitespaces and quotes of the given std::string
std::string strClean(const std::string& str) {
    std::regex quota_regex("[\"\']");
    std::string res = regex_replace( strip(str), quota_regex, ""); // remove quota marks
    std::regex space_regex(" +");
    return regex_replace( strip(res), space_regex, " "); // remove duplicate spaces
}

// progress bar
void displayProgressBar(std::ostream& os, float progress) {
    int barWidth = 70; // Width of the progress bar
    os << "[";
    int pos = barWidth * progress;
    
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) os << "=";
        else if (i == pos) os << ">";
        else os << " ";
    }
    
    os << "] " << int(progress * 100.0) << " %\r";
    if(progress < 1.0) os.flush();
    else os << std::endl;
}


void initializeRNG(uint32_t seed) { rng = std::mt19937(seed); }

// Simple linear transformation from generator 'rng'
template <>
float16_t getRandomNumber(int minValue, int maxValue, uint64_t *raw) {
    uint64_t x = getRandomNumber<uint64_t>(minValue, maxValue, nullptr);
    float16_t ret = ui64_to_f16(x);
    if (raw != nullptr) *raw = ret.v;
    return ret;
}
template <>
float32_t getRandomNumber(int minValue, int maxValue, uint64_t *raw) {
    uint64_t x = getRandomNumber<uint64_t>(minValue, maxValue, nullptr);
    float32_t ret = ui64_to_f32(x);
    if (raw != nullptr) *raw = ret.v;
    return ret;
}
template <>
float64_t getRandomNumber(int minValue, int maxValue, uint64_t *raw) {
    uint64_t x = getRandomNumber<uint64_t>(minValue, maxValue, nullptr);
    float64_t ret = ui64_to_f64(x);
    if (raw != nullptr)  *raw = ret.v;
    return ret;
}

std::string mul2str(float mul){
    if( mul == static_cast<float>(1.0/8.0) ) return "mf8";
    else if( mul == static_cast<float>(1.0/4.0) ) return "mf4";
    else if( mul == static_cast<float>(1.0/2.0) ) return "mf2";
    else if( mul == static_cast<float>(1.0) ) return "m1";
    else if( mul == static_cast<float>(2.0) ) return "m2";
    else if( mul == static_cast<float>(4.0) ) return "m4";
    else if( mul == static_cast<float>(8.0) ) return "m8";

    std::cerr << "unimplementation in mul2str: mul = " << mul << std::endl;
    exit(1); // undefined
}

// given ratio, return the type of 'rs2' used in indexed load-store intrinsics
std::string genIdxType(int ratio){
    // ratio = sew / lmul
    // sew in [8, 16, 32, 64]
    // ratio in [1, 2, 4, 8, 16, 32, 64]
    // 1/8 <= lmul <= 8
    assert ( ratio >= 1 && ratio <= 64 );

    std::vector<int> sews;
    if(ratio == 1) sews = {8};
    else if(ratio == 2) sews = {8, 16};
    else if(ratio == 4) sews = {8, 16, 32};
    else sews = {8, 16, 32, 64};

    int sew = *select_random(sews);
    float lmul = static_cast<float>(sew * 1.0) / static_cast<float>(ratio);
    assert( lmul <=static_cast<float>(8.0) && lmul >= static_cast<float>(1.0/8.0) );
    return "vuint" + std::to_string(sew) + mul2str(lmul) + "_t";
}

// generate the intrinsic suffix
std::string genPolicySuffix(bool mask, bool policy /*= withPolicy*/){
    if(policy){
        if(mask) return *select_random(PolicySuffixes_mask);
        else return *select_random(PolicySuffixes);
    }else{
        // without policy suffixes
        if(mask) return "_m";
        else return "";
    }
    return "";
}

// given the value of bits, return the value of bytes
// e.g., 32 bits --> 4 bytes
int bits2bytes(int bits){
    assert(bits >= 0);
    return bits / 8;
}

// given the value of bits, return the move of digits for `vsll_vx`
// e.g., 32 bits --> 4 bytes --> 2 move
int bits2moven(int bits){
    int bytes = bits2bytes(bits);
    return static_cast<int>(log2( static_cast<double>(bytes)));
}

std::string nfield2n(std::string nfield){
    assert( nfield.c_str()[1] >= '1' && nfield.c_str()[1] <= '9' );
    return std::string( 1, nfield.c_str()[1] );
}