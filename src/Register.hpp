#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "Type.hpp"
#include "Utils.hpp"

#ifndef MEM_MAX
#define MEM_MAX 8
#endif

#ifndef VREG_MAX
#define VREG_MAX 64
#endif

#ifndef VL_MAX
#define VL_MAX 1
#endif

#ifndef MASK_MAX
#define MASK_MAX 1
#endif

enum Source{
    Memory,     // load operation needed
    VectorReg,  // load operation not needed
    Unknown
};

class VRegister{
    // std::vector register
    private:
        int source;
        std::string valType;
        std::string regName; // core
        void setName();
    public:
        bool declared;
        bool ended;
        static unsigned int mNum; // current number of memory-source register
        static unsigned int vNum; // current number of std::vector-register-source register
        static void initializeReg();

        VRegister():source(Source::Unknown), regName(""), valType(""), declared(false), ended(false){
            for(int i=0;i<dataLen;++i){
                state.push_back(true);
            }
        };
        VRegister(std::string type, Source src):valType(type), source(src), declared(false), ended(false){ 
            setName(); 
            for(int i=0;i<dataLen;++i){
                state.push_back(true);
            }
        };
        ~VRegister(){};
        int getSource(){ return source; }
        std::string getRegName(){ return regName; }
        std::string getValeType(){ return valType; }
        BaseType * getValeTypePtr(UsedTYPES && UsedTypes){ return UsedTypes.TypeMap[valType]; }

        std::vector<bool> state;
        // set the state of register
        // state[i] = newState[i]
        void setState(std::vector<bool> newState);
        // update the state of register
        // state[i] = state[i] & newState[i]
        void updateState(std::vector<bool> newState);
};

class RegTable{
    public:
        static unsigned int mNum_max; // max number of memory-source register
        static unsigned int vNum_max; // max number of std::vector-register-source register
        static unsigned int vlNum_max; // max number of vl register
        static unsigned int maskNum_Max; // max number of mask register (bool)
        static void initializeRegTable();

        // type (str) -> array of std::vector registers
        std::map<std::string, std::vector<VRegister *> > currentVRegs;

        RegTable():currentVRegs(){ VRegister::initializeReg(); RegTable::initializeRegTable(); }
        ~RegTable(){
            for(auto it = currentVRegs.begin(); it != currentVRegs.end(); it++){
                for(auto vrptr = it->second.begin(); vrptr != it->second.end(); vrptr++){
                    if(*vrptr) {delete *vrptr; *vrptr = nullptr; } // delete point of VRegister
                }
            }
        }
        VRegister * insertReg(std::string type, Source src); // insert a new register entry to table
        bool endReg(std::string type, std::string regName); // remove a register from the table
        VRegister * select_vreg_random( std::string type );
        VRegister * allocate_a_vreg_read( std::string type, bool alwaysNew = false); // when alwaysNew = true, allocate a new register, else random allocation
        VRegister * allocate_a_vreg_write( std::string type, bool alwaysNew = false); // when alwaysNew = true, allocate a new register, else random allocation
        void print_info();
};

#endif // REGISTER_HPP