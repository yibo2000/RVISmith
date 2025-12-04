#include "Utils.hpp"
#include "cxxopts.hpp"

// default
std::string CodeDirPath;
std::string ConnectTypeStr;
size_t dataLen = 10;
size_t seqLen = 10;
bool ifSegment = true;
bool CoverageGuided = true;
bool cov_guide = false;
bool cov_log = false;
bool print_cov = false;

uint32_t InitialSeed = 0xdeadbeef;
std::mt19937 rng;
SchedulingMODE SchedulingMode;

std::vector<std::string> PolicySuffixes = {"_tu" };
std::vector<std::string> PolicySuffixes_mask = {"_tum", "_mu", "_tumu"};

std::vector<std::string> __RISCV_VXRM = {"__RISCV_VXRM_RNU", "__RISCV_VXRM_RNE", "__RISCV_VXRM_RDN", "__RISCV_VXRM_ROD"};
std::vector<std::string> __RISCV_FRM = {"__RISCV_FRM_RNE", "__RISCV_FRM_RTZ", "__RISCV_FRM_RDN", "__RISCV_FRM_RUP", "__RISCV_FRM_RMM"};

bool withPolicy = false;
bool withOverloaded = false;

void parseArguments(int argc, char **argv) {
    std::string filename = argv[0];
    if (argc < 1) { printUsage(std::cerr, filename); exit(1); }

    cxxopts::Options options("RVISmith", "One line description of RVISmith");

    options.add_options()
        ("s,seed", "Seed", cxxopts::value<uint32_t>()->default_value("0xdeadbeef")) // uint32_t InitialSeed
        ("l,data_length", "Data length", cxxopts::value<unsigned int>()->default_value( "10" )) // unsigned int dataLen
        ("n,sequence_length", "Sequence length", cxxopts::value<unsigned int>()->default_value( "10" )) // unsigned int dataLen
        ("o,output", "Output path", cxxopts::value<std::string>()->default_value("./")) // std::string CodeDirPath
        ("log-coverage", "Save the coverage information to 'coverage.bin' (default: false)")
        ("cov-guidance", "Enable coverage guidance and save the coverage information to 'coverage.bin' (default: false)")
        ("cov-clean", "Clean the coverage data in 'coverage.bin' (default: false)")
        ("print-cov", "Print the coverage information in 'coverage.bin' (default: false)")
        //("overloaded", "Whether overloaded load-store intrinsics are included (default: false)")
        ("h,help", "Print usage")
    ;
    
    cxxopts::ParseResult result;
    try{
        result = options.parse(argc, argv);
    }
    catch(const std::exception& e) {
        std::cerr << "Exception: " << e.what() << ";\n";
        printUsage(std::cerr, filename);
        exit(1);
    }
    
    if (result.count("help")){
        std::cout << options.help() << std::endl;
        exit(0);
    }

    if ( result.count("print-cov") ) { print_cov = true; } else { print_cov = false; }
    if ( result.count("log-coverage") ){ cov_log = true; } else { cov_log = false; }
    if ( result.count("cov-guidance") ){ cov_guide = true; } else { cov_guide = false; }
    if ( result.count("cov-clean") ){
        deleteFile("coverage.bin");
        exit(0);
    }
    //if ( result.count("overloaded") ){ withOverloaded = true; } else { withOverloaded = false; }

    InitialSeed = result["seed"].as<uint32_t>(); 
    initializeRNG(InitialSeed);
    dataLen = result["data_length"].as<unsigned int>();
    seqLen = result["sequence_length"].as<unsigned int>();
    CodeDirPath = result["output"].as<std::string>();

    std::vector<SchedulingMODE> mode_list = {SchedulingMODE::Allin, SchedulingMODE::Unit, SchedulingMODE::Random};
    SchedulingMode = *select_random(mode_list);

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
    ConnectTypeStr = *select_random(vector_type_list);

    withPolicy = (getRandomNumber<int>(0, 100) % 2) == 0;
    withOverloaded = (getRandomNumber<int>(0, 100) % 2) == 0;
}

bool deleteFile(const std::string& filename) {
    if (!std::filesystem::exists(filename)) {
        std::cout << "File not exist: " << filename << std::endl;
        return false;
    }
    std::error_code ec;
    if (std::filesystem::remove(filename, ec)) {
        std::cout << "Remove: " << filename << std::endl;
        return true;
    } else {
        std::cout << "Fail: " << ec.message() << std::endl;
        return false;
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

// removes any leading, and trailing whitespaces of the given std::string
std::string strip(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v"); // Find the first non-whitespace character from the start

    if (start == std::string::npos) { return ""; }
    size_t end = str.find_last_not_of(" \t\n\r\f\v"); // Find the last non-whitespace character from the end
    return str.substr(start, end - start + 1); // Return the substring without leading and trailing whitespace
}

// merge continuous spaces into one space, and
// remove any leading, and trailing whitespaces and quotes of the given std::string
std::string strClean(const std::string & str) {
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
    assert( nfield != "" );
    assert( nfield.c_str()[1] >= '1' && nfield.c_str()[1] <= '9' );
    return std::string( 1, nfield.c_str()[1] );
}