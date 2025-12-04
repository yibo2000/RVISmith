#ifndef OPDATA_HPP
#define OPDATA_HPP
#include <cstddef>

// max number of parameters setting: 12
constexpr size_t MAX_ARG_TOKENS = 12 * 2;
struct OpData {
    const char* retType;    // 8 bytes
    const char* funcName;   // 8 bytes
    int ratio;           // 8 bytes
    size_t pNum;            // 8 bytes
    const char* args[MAX_ARG_TOKENS];

    bool operator==(const OpData& other) const {
        auto safe_cmp = [](const char* s1, const char* s2) {
            if (s1 == s2) return true;
            if (!s1 || !s2) return false;
            return std::string_view(s1) == std::string_view(s2);
        };
        
        if (ratio != other.ratio || pNum != other.pNum) return false;
        if (!safe_cmp(retType, other.retType)) return false;
        if (!safe_cmp(funcName, other.funcName)) return false;
        for (size_t i = 0; i < pNum; ++i) {
            if (!safe_cmp(args[i], other.args[i])) return false;
        }
        return true;
    }
};

constexpr OpData global_op_table[] = {
    #define OPDEF(RETYPE, NAME, RATIO, PNUM, ...) \
        { #RETYPE, #NAME, (int)RATIO, (size_t)PNUM, { __VA_ARGS__ } },
    #include "Intrinsic.def"
    #undef OPDEF
};
constexpr size_t global_op_table_size = sizeof(global_op_table) / sizeof(OpData);

#endif