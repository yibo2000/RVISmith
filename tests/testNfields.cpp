#include "Operator.hpp"
#include "Utils.hpp"
#include <cstdio>

int main(){
    InitialSeed = 0x9192;
    initializeRNG(InitialSeed);
    OpDefs.setUnifiedNfield();
    std::cout << OpDefs.UnifiedNfield << std::endl;
    return 0;
}