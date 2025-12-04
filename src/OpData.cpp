#include "OpData.hpp"

/*
const std::vector<BaseOperator*> & getOpDefinitions(){
    static const RawOpDef raw_defs[] = {
        #define OPDEF(RETYPE, NAME, PNUM, ...) \
            { #RETYPE, #NAME, (size_t)PNUM, { __VA_ARGS__ } },

        #include "Intrinsic.def"
        #undef OPDEF
    };

    static const std::vector<BaseOperator* > res = []() {
        std::vector<BaseOperator*> tmp;
        tmp.reserve(sizeof(raw_defs) / sizeof(RawOpDef));

        for (const auto& def : raw_defs) {
            BaseOperator* ptr = new BaseOperator(
                def.retType, 
                def.funcName, 
                def.pNum, 
                def.args
            );
            tmp.push_back(ptr);
        }
        return tmp;
    }();
    return res;
}
*/