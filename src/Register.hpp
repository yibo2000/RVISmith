#ifndef REGISTER_HPP
#define REGISTER_HPP

#include "Type.hpp"

enum Source{
    Memory,     // load operation needed
    VectorReg,  // load operation not needed
    UnknownSrc
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

        VRegister():source(Source::UnknownSrc), valType(""), regName(""), declared(false), ended(false){
            for(size_t i=0;i<dataLen;++i){
                state.push_back(true);
            }
        };
        VRegister(std::string type, Source src):source(src), valType(type), declared(false), ended(false){ 
            setName(); 
            for(size_t i=0;i<dataLen;++i){
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
        // type (str) -> array of std::vector registers
        std::map<std::string, std::vector<VRegister *> > currentVRegs;

        RegTable():currentVRegs(){ VRegister::initializeReg(); }
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

class ScalarTable{
    public:
        size_t tableSize;
        static int name_number;
        std::vector<std::string> ScalarTypes;
        std::vector<std::string> ScalarVars;
        ScalarTable():tableSize(0){};
        ~ScalarTable(){};
        void AddScalar(std::string type, std::string var);
};
extern ScalarTable scalar_table;

#endif // REGISTER_HPP