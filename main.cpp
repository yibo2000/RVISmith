#include "Operator.hpp"
#include "Utils.hpp"
#include "Register.hpp"
#include "CodeGen.hpp"
#include "Guidance.hpp"

int main(int argc, char *argv[]) {
    // parse arguments
    parseArguments(argc, argv);

    // initialize   
    if(print_cov) {
        covmap.init_or_load();
        std::cout << covmap.get_coverage() << std:: endl;
        exit(0);
    }
    if(cov_guide || cov_log) covmap.init_or_load(); 
    UsedTypes.initializeAllTypes();
    OpDefs.initializeOpDefinitions();
    OpDefs.selectOpSeq(seqLen);

    std::cout<<"select:\n";
    for(size_t i = 0; i<seqLen; i++){
        OpDefs.selectedOp[i].printInfo();
    }
    
    CodeBlock codeblock;
    codeblock.vregAllocateRandom(OpDefs.selectedOp); // vector register allocate
    codeblock.insertLoadAndStoreIntrinsics(OpDefs.selectedOp); // load-store
    MainBlock mainblock;
    std::ofstream CCodeFile; 
    std::filesystem::path CodeFilePath;

    CodeFilePath = std::filesystem::path(CodeDirPath) / std::filesystem::path("test.cpp");
    // given a selected sequence with allocated registers,
    // return a vector of string representing instructions after scheduling
    codeblock.instructionScheduling(seqLen, SchedulingMode);
    // output the code
    CCodeFile.open(CodeFilePath,std::ofstream::out | std::ofstream::trunc);
    codeblock.codegen(CCodeFile);
    mainblock.codegen(CCodeFile);
    CCodeFile.close();
    std::cout << "The rvv intrinsic code has been generated in: " << std::filesystem::absolute(CodeFilePath) << std::endl;
    
    if(cov_guide || cov_log) std::cout << covmap.get_coverage() << std:: endl;

    return 0;
}
