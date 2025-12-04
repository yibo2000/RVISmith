#include "Operator.hpp"
#include "Utils.hpp"
#include <cstdio>

int main(){
    InitialSeed = 0x9192;
    initializeRNG(InitialSeed);
    OpDefs.setMaxNfield();
    std::cout << OpDefs.MaxNfield << std::endl;
    return 0;
}