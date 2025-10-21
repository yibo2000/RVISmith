#ifndef CODEGEN_HPP
#define CODEGEN_HPP

#include <string>
#include <vector>
#include <set>
#include "Register.hpp"
#include "Operator.hpp"
#include "Utils.hpp"
#include "Memory.hpp"

extern unsigned int indentNum; // indent
// inline std::string getIndent() { return std::string(indentNum, '\t'); }
inline std::string getIndent() { return std::string(indentNum*2, ' '); }
extern unsigned int blockNum; // block name
extern unsigned int loopNum; // for loop

class VIndex{
    public:
        std::string idxType; 
        std::string idxName;
        int maxValue;
        static int number;
        vector<int> vals;
        VIndex():idxType(""),idxName("idx_"+std::to_string(number++)),maxValue(0){ 
            for(int i=0;i<dataLen;++i) vals.push_back(0); 
        };
        VIndex(std::string type, int maxV, bool conservative = false):idxType(type),idxName("idx_"+std::to_string(number++)),maxValue(maxV){
            int start = 0;
            int end = maxValue;
            for(int i=0;i<dataLen;++i) {
                if(conservative) vals.push_back( i % 256 );
                else vals.push_back( getRandomNumber<int>(start, end) );
            }
        };
};

class CodeBlock{
    public:
        std::string connect_type;
        std::string blockName;
        std::string vlName;  // for size_t vl
        std::string maskName; // for mask
        std::string avl; // loop var
        bool hasNfieldOp;

        RegTable regtable;  // manage the std::vector registers
        Memorys memorys;

        std::vector<bool> vmask;

        // code after instruction scheduling
        std::vector<std::string> operationCode;

        // code before instruction scheduling
        std::vector<std::vector<std::string>> PrefixOp;    // load and other operation
        std::vector<std::vector<std::string>> SuffixOp;    // store and other operation
        std::vector<std::string> OpInstruction;

        CodeBlock(){ initializeCodeBlock(); };
        CodeBlock(std::string type):connect_type(type){ initializeCodeBlock(); };
        void initializeCodeBlock() { 
            operationCode.clear();
            blockName = "CodeBlock_" + std::to_string(blockNum++);
            vlName = "vl";
            maskName = "vmask";
            hasNfieldOp = false;
            for(int i=0;i<dataLen;++i){
                std::string val = getAScalarRandom("mask");
                if(val == to_string(0)) { vmask.push_back(false); }
                else if(val == to_string(1)) { vmask.push_back(true); }
                else{
                    assert("invalid value");
                    exit(1);
                }
            }
            PrefixOp.clear();
            SuffixOp.clear();
            OpInstruction.clear();
        }

        void emitGlobalVars(std::ostream &os);

        // std::vector register allocate
        void vregAllocateRandom(std::vector<BaseOperator > & Ops);

        // insert load-store intrinsics to sequence after register allocation
        void insertLoadAndStoreIntrinsics(std::vector<BaseOperator > & Ops);

        // given a selected sequence (load, store, operation)
        // return a std::vector of std::string representing instructions after scheduling
        void instructionScheduling(unsigned int length, SchedulingMODE mode = SchedulingMode);

        // set vl
        std::string vsetvl(int ewidth, std::string emul, std::string avl);
        std::string vsetvlmax(int ewidth, std::string emul, std::string avl);

        // loop generation
        void genLoopPrefix(std::ostream &os);
        void genLoopSuffix(std::ostream &os);
        void genLoopMask(std::ostream &os);

        // bool load and store
        std::vector<std::string> load_bool(std::string type, std::string regName, bool allValueIsTrue = false);
        std::vector<std::string> store_bool(std::string type, std::string regName);

        // load and store
        // Vector Unit-Stride Load and Store Intrinsics
        std::vector<std::string> load_vle(std::string type, std::string regName, bool mask = false);
        std::vector<std::string> store_vse(std::string type, std::string regName, bool mask = false, bool onlyzero = false);
        // Vector Strided Load and store Intrinsics
        std::vector<std::string> load_vlse(std::string type, std::string regName, bool mask = false);
        std::vector<std::string> store_vsse(std::string type, std::string regName, bool mask = false, bool onlyzero = false);
        // Vector Indexed Load and Store Intrinsics
        std::vector<std::string> load_vloxei(std::string type, std::string regName, bool mask = false);
        std::vector<std::string> load_vluxei(std::string type, std::string regName, bool mask = false);
        std::vector<std::string> store_vsoxei(std::string type, std::string regName, bool mask = false, bool onlyzero = false);
        std::vector<std::string> store_vsuxei(std::string type, std::string regName, bool mask = false, bool onlyzero = false);

        // Unit-stride Fault-Only-First Loads Intrinsics
        // TBD, not supported

        // print the memory for differential testing
        void genPrint(std::ostream &os);

        // code generation
        void codegen(std::ostream &os);
};

class MainBlock{
    public:
        void codegen(std::ostream &os);
};

void emitHeader(std::ostream &os);
std::vector<std::string> scheduling_unit( std::vector<std::vector<std::string>> && PrefixOp, std::vector<std::vector<std::string>> && SuffixOp,  
                                std::vector<std::string> && OpInstruction, unsigned int length);
std::vector<std::string> scheduling_allin( std::vector<std::vector<std::string>> && PrefixOp, std::vector<std::vector<std::string>> && SuffixOp,  
                                std::vector<std::string> && OpInstruction, unsigned int length);
std::vector<std::string> scheduling_random( std::vector<std::vector<std::string>> && PrefixOp, std::vector<std::vector<std::string>> && SuffixOp,  
                                std::vector<std::string> && OpInstruction, unsigned int length);

#endif // CODEGEN_HPP