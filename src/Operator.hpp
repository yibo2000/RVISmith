#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <string>
#include <vector>
#include <fstream>
#include "Type.hpp"
#include "Utils.hpp"
#include "Register.hpp"

class Parameter{
    private:
        std::string __ptype__;
        std::string __pname__;
    public:
        // bool onlyzero;      // used for store operation, when onlyzero = true, only print element[0].
        VRegister* pvreg;   // for std::vector register type
        Parameter():__ptype__(""),__pname__(""),pvreg(nullptr){}
        Parameter(std::string type, std::string pname):__ptype__(type),__pname__(pname),pvreg(nullptr){}
        // Parameter(std::string type, std::string pname, bool zero):__ptype__(type),__pname__(pname),pvreg(nullptr),onlyzero(zero){}
        ~Parameter(){
            // if(pvreg != nullptr ) { delete pvreg; pvreg = nullptr; } // Segmentation fault
            // The points of `VRegister *` are managed uniformly (new and delete) by RegTable.
            // When more than one parameters share with the same register, deleting vregister points
            // in the parameter class will cause segmentation fault.
        }
        BaseType * getPtypePtr(UsedTYPES && UsedTypes){ return UsedTypes.TypeMap[__ptype__]; }
        std::string getPtype(){ return __ptype__; }
        std::string getPname(){ return __pname__; }
        Type enumType(){
            if(this->getPtype() == "unsigned int" && this->getPname() == "vxrm")    return Type::VXRM;
            if(this->getPtype() == "unsigned int" && this->getPname() == "frm")    return Type::FRM;
            if(this->getPtype() == "size_t" && this->getPname() == "vl")    return Type::VL;
            if(this->getPtype() == "size_t" && this->getPname() == "index")    return Type::Index;
            if(this->getPtype() == "ptrdiff_t")    return Type::Ptrdiff;
            if( startsWith( this->getPtype(), "vbool" ) && this->getPname() == "vm")    return Type::VMASK;
            return Type::UnknownType; 
        }
        Type enumType(UsedTYPES && UsedTypes){ 
            Type res = enumType();
            if(res == Type::UnknownType) return (this->getPtypePtr(std::move(UsedTypes)))->enumType(); 
            else return res;
        }
        bool operator < (const Parameter& para) const{
            return __pname__ < para.__pname__;
        } // used in set: codegen
};

class BaseOperator{
    private:
        std::string __retype__;
        std::string __name__; // instrinsic name

    public:
        std::vector<Parameter> paras;
        VRegister* retvreg;    // for return value type is std::vector register type
        BaseOperator():__retype__(""),__name__(""),retvreg(nullptr),nfield(""){};

#if JSON_INPUT
        BaseOperator(nlohmann::json && j):__retype__( j["retype"] ), __name__(j["intrinsic"]),retvreg(nullptr),nfield(""){
            // used when .jsonl files are input
            nfield = UsedTypes.TypeMap[__retype__]->getNfield();
            std::set<int> ratios;
            int r = UsedTypes.TypeMap[__retype__]->getRatio();
            if( r > 0) ratios.insert(r);
            for(int i=0; i<j["parameters"].size(); ++i){
                std::string tmp_type(j["parameters"][i]["ptype"]);
                std::string tmp_name(j["parameters"][i]["pname"]);
                Parameter para(tmp_type, tmp_name);
                // set nfield
                std::string pNfield = para.getPtypePtr(std::move(UsedTypes))->getNfield();
                assert( nfield == "" || pNfield == "" || pNfield == nfield );
                if(pNfield != "") nfield = pNfield;
                // set commonRatio
                int pr = UsedTypes.TypeMap[tmp_type]->getRatio();
                if(pr > 0)  ratios.insert( pr );
                paras.push_back( para );
            }
            // set commonRatio
            if(ratios.size() <= 0 ){
                // no vector type
                commonRatio = 0;
            }else if(ratios.size() == 1 ){
                commonRatio = *ratios.begin();
            }else if(ratios.size() > 1 ){
                commonRatio = 0;
            }
        }
#endif // #if JSON_INPUT

#if DEF_INPUT
        BaseOperator(std::string retype, std::string name, int pnum, std::vector<std::string> vptype_and_pname): \
        __retype__( retype ),__name__(name),retvreg(nullptr),nfield(""){
            // used when .def files are input
            assert( pnum * 2 == vptype_and_pname.size() );
            nfield = UsedTypes.TypeMap[__retype__]->getNfield();
            std::set<int> ratios;
            int r = UsedTypes.TypeMap[__retype__]->getRatio();
            if( r > 0) ratios.insert(r);
            for(int i = 0; i<vptype_and_pname.size(); i+=2) {
                Parameter para(vptype_and_pname[i], vptype_and_pname[i+1]);
                // set nfield
                std::string pNfield = para.getPtypePtr(std::move(UsedTypes))->getNfield();
                assert( nfield == "" || pNfield == "" || pNfield == nfield );
                if(pNfield != "") nfield = pNfield;
                // set commonRatio
                int pr = UsedTypes.TypeMap[vptype_and_pname[i]]->getRatio();
                if(pr > 0)  ratios.insert( pr );
                paras.push_back( para );
            }
            // set commonRatio
            if(ratios.size() <= 0 ){
                // no vector type
                commonRatio = 0;
            }else if(ratios.size() == 1 ){
                commonRatio = *ratios.begin();
            }else if(ratios.size() > 1 ){
                commonRatio = 0;
            }
        }
#endif // DEF_INPUT

        ~BaseOperator(){}
        std::string getRetype(){ return __retype__; }
        std::string getName(){ return __name__; } // return the instrinsic name
        BaseType * getRetypePtr(UsedTYPES && UsedTypes){ return UsedTypes.TypeMap[__retype__]; }
        Type enumRetype(UsedTYPES && UsedTypes){ return (this->getRetypePtr(std::move(UsedTypes)))->enumType(); }
        std::string getDefStr(); // return the definition std::string

        //bool ifUsedType (std::string queryType); // return whether the intrinsic uses the given type (parameter type or return type)
        bool ifUsedSegment (); // return whether the intrinsic uses the tuple type (e.g., vint8mf8x2_t)
        
        bool ifTailProducer(); // whether this intrinsic can produce tail elements
        bool ifReduction(); // whether this intrinsic is reduction operation
        bool ifWithoutMaskIntrin(); // whether this intrinsic cannot use data loaded by mask-intrinsics

        void printInfo(); // print the information of the intrinsic (for debug)
        std::string codegen(UsedTYPES && UsedTypes);

        std::string nfield; // if used tuple types, set as nfield of the corresponding type, else empty string
        void setNfiled();


        // ratio related
        bool ifUsedRatio (int ratio);
        // > 0: aligned ratio
        // = 0: non-aligned
        int commonRatio;
        int setRatio();

        bool alwaysAgnostic();
};

class OpDEFS{
    public:
        std::vector<BaseOperator* > UnderTestIntrinsics;
        OpDEFS():UnderTestIntrinsics(),UnifiedNfield(""){ ; };
        ~OpDEFS(){
            for(auto ptr: UnderTestIntrinsics){ if(ptr) { delete ptr; ptr = nullptr; } }
        }
        void insert(BaseOperator * ptr){ UnderTestIntrinsics.push_back(ptr); }
        void push_back(BaseOperator * ptr){ UnderTestIntrinsics.push_back(ptr); }
        void extend(std::vector<BaseOperator * > v) { UnderTestIntrinsics.insert( UnderTestIntrinsics.end(), v.begin(), v.end() ); }

        std::vector<BaseOperator* > LoadIntrinsics;
        std::vector<BaseOperator* > StoreIntrinsics;
        std::vector<BaseOperator* > OpIntrinsics;
        std::vector<BaseOperator* > SetvlIntrinsics;
        std::vector<BaseOperator* > IgnoredIntrinsics;

        std::string UnifiedNfield; // xn, the only one nfield used in intrinsics after organization (--segment)
        void setUnifiedNfield();
        void organize(std::string usedType, bool ifClear = true);
        void organize(std::vector<std::string> usedTypes);
        void clearPool();

        std::vector<BaseOperator > selectOpSeq(int size);
        void initializeOpDefinitions();
};

extern OpDEFS OpDefs;

#endif // OPERATOR_HPP
