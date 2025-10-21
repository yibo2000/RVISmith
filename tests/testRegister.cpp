#include "Register.hpp"
#include <cassert>

int main(){
    RegTable regTable;
    regTable.insertReg("vint64m1x5_t", Source::Memory);
    regTable.insertReg("vint64m1x5_t", Source::VectorReg);
    regTable.insertReg("vfloat16m1_t", Source::Memory);
    regTable.insertReg("vfloat16m1_t", Source::Memory);
    regTable.insertReg("vint8mf4_t", Source::Memory);
    regTable.print_info();

    // assert: TBD
    return 0;
}