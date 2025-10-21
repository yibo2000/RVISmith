#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <filesystem> // C++ 17 is required

#include "Operator.hpp"
#include "Utils.hpp"
#include "Register.hpp"
#include "CodeGen.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    // parse arguments
    parseArguments(argc, argv);

    // initialize
    // connect_type = "vfloat64m2_t";
    
    initializeRNG(InitialSeed);
    UsedTypes.initializeAllTypes();
    OpDefs.setUnifiedNfield();
    OpDefs.initializeOpDefinitions();
    OpDefs.organize(connect_type);
    cout << "Intrinsics under test collected. Start to generate rvv intrinsic code." << endl;

    /*for (auto it: OpDefs.IgnoredIntrinsics){
        it->printInfo();
    }*/
    // select a sequence
    cout<<"\nselect:\n";
    vector<BaseOperator > selected = OpDefs.selectOpSeq(seqLen);
    for(int i = 0; i<seqLen; i++){
        selected[i].printInfo();
    }
    
    CodeBlock codeblock(connect_type);
    codeblock.vregAllocateRandom(selected); // vector register allocate
    codeblock.insertLoadAndStoreIntrinsics(selected); // load-store
    MainBlock mainblock;
    ofstream CCodeFile; 
    std::filesystem::path CodeFilePath;

    // random
    SchedulingMode = SchedulingMODE::Random;
    CodeFilePath = std::filesystem::path(CodeDirPath) / std::filesystem::path("random.c");
    // given a selected sequence with allocated registers,
    // return a vector of string representing instructions after scheduling
    codeblock.instructionScheduling(seqLen, SchedulingMode);
    // output the code
    CCodeFile.open(CodeFilePath, ofstream::out | ofstream::trunc);
    codeblock.codegen(CCodeFile);
    mainblock.codegen(CCodeFile);
    CCodeFile.close();
    cout << "The rvv intrinsic code has been generated in: " << std::filesystem::absolute(CodeFilePath) << endl;

    // random
    SchedulingMode = SchedulingMODE::Allin;
    CodeFilePath = std::filesystem::path(CodeDirPath) / std::filesystem::path("allin.c");
    // given a selected sequence with allocated registers,
    // return a vector of string representing instructions after scheduling
    codeblock.instructionScheduling(seqLen, SchedulingMode);
    // output the code
    CCodeFile.open(CodeFilePath, ofstream::out | ofstream::trunc);
    codeblock.codegen(CCodeFile);
    mainblock.codegen(CCodeFile);
    CCodeFile.close();
    cout << "The rvv intrinsic code has been generated in: " << std::filesystem::absolute(CodeFilePath) << endl;

    // random
    SchedulingMode = SchedulingMODE::Unit;
    CodeFilePath = std::filesystem::path(CodeDirPath) / std::filesystem::path("unit.c");
    // given a selected sequence with allocated registers,
    // return a vector of string representing instructions after scheduling
    codeblock.instructionScheduling(seqLen, SchedulingMode);
    // output the code
    CCodeFile.open(CodeFilePath, ofstream::out | ofstream::trunc);
    codeblock.codegen(CCodeFile);
    mainblock.codegen(CCodeFile);
    CCodeFile.close();
    cout << "The rvv intrinsic code has been generated in: " << std::filesystem::absolute(CodeFilePath) << endl;

    return 0;
}
