#ifndef TYPE_HPP
#define TYPE_HPP

#include <cstring>
#include <string>
#include <cassert>
#include <fstream>
#include <set>
#include <map>
#include <stdexcept>
#include "Utils.hpp"


class BaseType{
    public:
        std::string type;
        BaseType():type(""){};
        BaseType(std::string __type__):type(__type__){}; // for void
        ~BaseType(){};
        std::string getType() { return type; }
        virtual Type enumType() { return Type::Void; }
        virtual std::string getScalar() { throw std::runtime_error("get scalar in void type."); /* should never be called */ }
        virtual void printInfo() { std::cout << "BaseType: " + type << std::endl; }
        virtual std::string getNfield(){ return ""; }
        virtual int getRatio(){ return 0; }
};

// general types can be used in both rvv intrinsics and C code without rvv
// typically, general types are not start with the char 'v'
class GeneralType : public BaseType{
    public:
        bool isPoint; // e.g., input 'double' is false, input 'double *' is true.
        bool isConst;
        GeneralType():isPoint(false),isConst(false),BaseType(""){};
        GeneralType(std::string __type__):BaseType(__type__){
            // type = strip(__type__);
            if ( endsWith(type, "*") ){ isPoint = true; } else { isPoint = false; }
            if ( startsWith(type, "const") ){ isConst = true; } else { isConst = false; }

            if (isPoint) { type = type.substr( 0, type.length() - strlen("*")); /*type = replaceSubstring(type, "*", "");*/ }
            if (isConst) { type = type.substr( strlen("const"), type.length() - strlen("const")); /*type = replaceSubstring(type, "const", "");*/ }

            type = strClean(type);
        }
        // bool isPoint(){ return endsWith(type, "*"); }
        // bool isConst(){ return startsWith(type, "const"); }
        ~GeneralType(){};
        virtual Type enumType()  { return Type::Scalar; }
        virtual std::string getScalar();
        virtual void printInfo() { std::cout << "GeneralType: " + type << std::endl; }
        virtual std::string getNfield(){ return ""; }
        virtual int getRatio(){ return 0; }
};

std::string getAScalarRandom(std::string type); // given a std::string of scalar type, return a std::string representing the value.

// std::vector types can be used in only rvv intrinsics
// typically, std::vector types are start with the char 'v' (except the void type)
class VectorType : public GeneralType{
    public:
        std::string etype; // element type, e.g. float64_t
        std::string emul; // element mul, 1/8, 1/4, 1/2, 1, 2, 4, 8
        std::string nfield; // xn
        int ewidth; // element width
        int ratio; // ewidth / lmul
        
        VectorType():GeneralType(""){};
        VectorType(std::string __type__):GeneralType(__type__),etype(""),emul(""),nfield(""),ewidth(0){
            assert( startsWith(type, "v") && type != "void");
            this->parse_vtype();
        };
        void parse_vtype();
        ~VectorType(){};
        virtual Type enumType()  { return Type::OneDVector; }
        virtual void printInfo() { std::cout << "VectorType: " + type << std::endl; std::cout << "etype=" + etype <<
         ", emul="+emul<<", nfield="+nfield<<", ewidth="+std::to_string(ewidth)<<std::endl; }
        virtual std::string getNfield(){ return nfield; }
        virtual int getRatio(){ return ratio; }
};

class UsedTYPES{
    // all types used
    public:
        std::map<std::string, BaseType *> TypeMap;
        UsedTYPES():TypeMap(){}
        ~UsedTYPES(){
            for(auto it = TypeMap.begin(); it != TypeMap.end(); ++it){
                if(it->second) { delete(it->second); it->second = nullptr; }
            }
        }
        void insert(std::string && s, BaseType * t){
            TypeMap.insert( {s, t } );
        }
        BaseType * getPtr(std::string && s){
            return TypeMap[s];
        }
        void printTypeMap();
        void initializeAllTypes();
};

extern UsedTYPES UsedTypes; // global, all types that used in rvv definition

#endif // TYPE_HPP
