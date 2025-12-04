#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <set>
#include <fstream>
#include "Register.hpp"
#include "OpData.hpp"
#include "Guidance.hpp"

class Parameter{
    private:
        std::string __ptype__;
        std::string __pname__;
    public:
        // bool onlyzero;      // used for store operation, when onlyzero = true, only print element[0].
        VRegister* pvreg;   // for std::vector register type
        Parameter():__ptype__(""),__pname__(""),pvreg(nullptr){}
        Parameter(const char* type, const char* pname):__ptype__(type),__pname__(pname),pvreg(nullptr){}
        Parameter(std::string type, std::string pname):__ptype__(type),__pname__(pname),pvreg(nullptr){}
        // Parameter(std::string type, std::string pname, bool zero):__ptype__(type),__pname__(pname),pvreg(nullptr),onlyzero(zero){}
        ~Parameter(){
            // if(pvreg != nullptr ) { delete pvreg; pvreg = nullptr; } // Segmentation fault
            // The points of `VRegister *` are managed uniformly (new and delete) by RegTable.
            // When more than one parameters share with the same register, deleting vregister points
            // in the parameter class will cause segmentation fault.
        }
        BaseType * getPtypePtr(){ return UsedTypes.TypeMap[__ptype__]; }
        std::string getPtype(){ return __ptype__; }
        std::string getPname(){ return __pname__; }
        Type enumType(){
            if(this->getPtype() == "unsigned int" && this->getPname() == "vxrm")    return Type::VXRM;
            if(this->getPtype() == "unsigned int" && this->getPname() == "frm")    return Type::FRM;
            if(this->getPtype() == "size_t" && this->getPname() == "vl")    return Type::VL;
            if(this->getPtype() == "size_t" && this->getPname() == "index")    return Type::Index;
            if(this->getPtype() == "ptrdiff_t")    return Type::Ptrdiff;
            if( startsWith( this->getPtype(), "vbool" ) && this->getPname() == "vm")    return Type::VMASK;

            auto PtypePtr = this->getPtypePtr();
            if (PtypePtr != nullptr) return PtypePtr->enumType();
            return Type::UnknownType; 
        }
        bool operator < (const Parameter& para) const{
            return __pname__ < para.__pname__;
        }
};

enum OperatorType{
    Load,
    Operation,
    Store,
    Others,
    UnknownOP
};

class BaseOperator{
    private:
        std::string __retype__;
        std::string __name__; // instrinsic name

    public:
        std::vector<Parameter> paras;
        VRegister* retvreg;    // for return value type is std::vector register type
        std::string nfield; // if used tuple types, set as nfield of the corresponding type, else empty string
        int commonRatio; // > 0: aligned ratio; = 0: non-aligned
        OperatorType intrinsic_type;
        BaseOperator():__retype__(""),__name__(""),retvreg(nullptr),nfield(""),commonRatio(0), intrinsic_type(OperatorType::UnknownOP),opdata_id(SIZE_MAX){};
        BaseOperator(const OpData & opdata):__retype__(opdata.retType),__name__(opdata.funcName),retvreg(nullptr),nfield(""), \
        commonRatio(opdata.ratio),intrinsic_type(OperatorType::UnknownOP),opdata_id(SIZE_MAX){
            this->OpInit(opdata.pNum, opdata.args);
        }
        BaseOperator(std::string retype, std::string name, size_t ratio, size_t pnum, std::initializer_list<const char*> raw_args): \
        __retype__( retype ),__name__(name),retvreg(nullptr),nfield(""),commonRatio(ratio),intrinsic_type(OperatorType::UnknownOP),opdata_id(SIZE_MAX){
            const char* args[MAX_ARG_TOKENS] = { nullptr };
            size_t idx = 0;
            for (auto it = raw_args.begin(); it != raw_args.end() && idx < MAX_ARG_TOKENS; ++it, ++idx) {
                args[idx] = *it;
            }
            this->OpInit(pnum, args);
        }
        ~BaseOperator(){}
        void OpInit(size_t pnum, const char* const raw_args[MAX_ARG_TOKENS]);
        std::string getRetype(){ return __retype__; }
        std::string getName(){ return __name__; } // return the instrinsic name
        BaseType * getRetypePtr(){ 
            if (UsedTypes.TypeMap.find(__retype__) == UsedTypes.TypeMap.end()) {
                std::cerr << "Error: type " << __retype__ << " not found in UsedTypes." << std::endl;
                exit(1);
            }
            return UsedTypes.TypeMap[__retype__]; 
        }
        Type enumRetype(){ return (this->getRetypePtr())->enumType(); }
        std::string getDefStr(); // return the definition std::string

        bool ifUsedSegment (); // return whether the intrinsic uses the tuple type (e.g., vint8mf8x2_t)
        bool ifTailProducer(); // whether this intrinsic can produce tail elements
        bool ifReduction(); // whether this intrinsic is reduction operation
        bool ifWithoutMaskIntrin(); // whether this intrinsic cannot use data loaded by mask-intrinsics

        void printInfo(); // print the information of the intrinsic (for debug)
        bool alwaysAgnostic();
        
        std::string codegen(); // for operation intrinsics
        // for load intrinsics
        // type: vector type after load; regName: vector var name after load; loadVar: global data
        std::vector<std::string> load_gen(std::string type, std::string regName, std::string loadVar, bool allMaskIsTrue = false);
        // for store intrinsics
        std::vector<std::string> store_gen(std::string type, std::string regName, std::string storeVar, bool allMaskIsTrue = false);

        // for coverage guidance (hash)
        uint64_t opdata_id;
};

// for index load/store intrinsics
class VIndex{
    public:
        std::string idxType; 
        std::string idxName;
        int maxValue;
        static int number;
        std::vector<int> vals;
        VIndex():idxType(""),idxName("idx_"+std::to_string(number++)),maxValue(0){ 
            for(size_t i = 0; i < dataLen; ++i) vals.push_back(0); 
        };
        VIndex(std::string type, int maxV, bool conservative = false):idxType(type),idxName("idx_"+std::to_string(number++)),maxValue(maxV){
            int start = 0;
            int end = maxValue;
            for(size_t i=0;i<dataLen;++i) {
                if(conservative) vals.push_back( i % 256 );
                else vals.push_back( getRandomNumber<int>(start, end) );
            }
        };
};

class OpDEFS{
    public:
        // std::vector<BaseOperator* > UnderTestIntrinsics;
        OpDEFS(){};
        ~OpDEFS(){
            for (auto& [key, opsVector] : LoadIntrinsics) {
                for (auto& ptr : opsVector) { if (ptr) {  delete ptr; ptr = nullptr; } }
            }
            for (auto& [key, opsVector] : StoreIntrinsics) {
                for (auto& ptr : opsVector) { if (ptr) {  delete ptr; ptr = nullptr; } }
            }
            for(auto ptr: OpIntrinsics){ if(ptr) { delete ptr; ptr = nullptr; } }
            for(auto ptr: SetvlIntrinsics){ if(ptr) { delete ptr; ptr = nullptr; } }
            for(auto ptr: IgnoredIntrinsics){ if(ptr) { delete ptr; ptr = nullptr; } }
        }

        void initializeOpDefinitions();

        std::unordered_map<std::string, std::vector<BaseOperator* >> LoadIntrinsics; // key: vector type (ret); value: load intrinsics
        std::unordered_map<std::string, std::vector<BaseOperator* >> StoreIntrinsics; // key: vector type (vs3); value: store intrinsics
        std::vector<BaseOperator* > OpIntrinsics;
        std::vector<BaseOperator* > SetvlIntrinsics;
        std::vector<BaseOperator* > IgnoredIntrinsics;


        std::string MaxNfield;
        void setMaxNfield();
        void organize();

        void selectOpSeq(int size);
        std::vector<BaseOperator> selectedOp;
};

extern OpDEFS OpDefs;

extern bool ifReduction(const std::string& s);
extern std::string vsetvl(int ratio, std::string avl = "avl");
extern std::string vsetvl_max(int ratio);

BaseOperator* select_cov_guide(std::vector<BaseOperator* >& candidate);

#endif // OPERATOR_HPP
