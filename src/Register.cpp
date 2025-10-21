#include "Register.hpp"

// initialize of std::vector register
unsigned int VRegister::mNum = 0;
unsigned int VRegister::vNum = 0;
void VRegister::initializeReg(){
    mNum = 0; vNum = 0;
}
// initialize of std::vector register table 
unsigned int RegTable::mNum_max = MEM_MAX; // max number of memory-source register
unsigned int RegTable::vNum_max = VREG_MAX; // max number of std::vector-register-source register
unsigned int RegTable::vlNum_max = VL_MAX; // max number of vl register
unsigned int RegTable::maskNum_Max = MASK_MAX; // max number of mask register (bool)
void RegTable::initializeRegTable(){
    mNum_max = MEM_MAX;
    vNum_max = VREG_MAX;
    vlNum_max = VL_MAX;
    maskNum_Max = MASK_MAX;
}

// set the register name
void VRegister::setName(){
    switch (source){
    case Source::Memory:
        regName = "vreg_memory_" + std::to_string(mNum++);
        break;
    case Source::VectorReg:
        regName = "vreg_" + std::to_string(vNum++);
        break;
    default:
        std::cerr << "Unknown source: " << source << std::endl;
        break;
    };
}

std::vector<bool> state;
// set the state of register
// state[i] = newState[i]
void VRegister::setState(std::vector<bool> newState){
    assert( newState.size() >= dataLen );
    this->state.clear();
    for(int i=0; i<dataLen; ++i){
        this->state.push_back(newState[i]);
    }
}
// update the state of register
// state[i] = state[i] & newState[i]
void VRegister::updateState(std::vector<bool> newState){
    assert( newState.size() >= dataLen );
    assert( state.size() >= dataLen );
    for(int i=0; i<dataLen; ++i){
        state[i] = state[i] && newState[i];
    }
}


VRegister * RegTable::insertReg(std::string type, Source src){
    auto ptr = currentVRegs.find(type);
    VRegister * res = nullptr; 
    if( ptr == currentVRegs.end() ){
        // first appearance of a type
        currentVRegs[type] = std::vector<VRegister *>();
        res = new VRegister(type, src);
        currentVRegs[type].push_back( res );
    }else{
        res = new VRegister(type, src);
        ptr->second.push_back( res );
    }
    assert (res != nullptr);
    return res;
}

VRegister * RegTable::select_vreg_random( std::string type ){
    if( currentVRegs.find(type) == currentVRegs.end() ) return nullptr;
    std::vector<int> idx_not_ended;
    for( int i=0; i<currentVRegs[type].size(); ++i){
        // add not ended index into the std::vector
        if( currentVRegs[type][i]->ended == false ){
            idx_not_ended.push_back( i );
        }
    }
    if( idx_not_ended.size() == 0) return nullptr; // all reg are ended
    int idx_select = *select_random( idx_not_ended );
    return currentVRegs[type][idx_select];
}

void RegTable::print_info(){
    for(auto it = currentVRegs.begin(); it!=currentVRegs.end(); ++it){
        std::cout<< it->first << ": " << std::endl;
        for(auto vrptr = it->second.begin(); vrptr != it->second.end(); vrptr++){
            std::cout<< (*vrptr)->getRegName() << "; ";
        }
        std::cout<<std::endl;
    }
}

VRegister * RegTable::allocate_a_vreg_read(std::string type, bool alwaysNew /* = false*/){
    // determine the source
    Source src = Source::Unknown;
    auto ptr = currentVRegs.find(type);
    if( ptr == currentVRegs.end() || alwaysNew){
        // first appearance of a type, allocate a new register and load from memory
        src = Source::Memory;
    }else{
        // use an old reg : new Memory = 3 : 1 
        int tmp = getRandomNumber<int>(0, 100);
        VRegister * ptr = nullptr;
        switch ( tmp%4 ) {
        case 0: // use an old reg
        case 1: // use an old reg
        case 2: // use an old reg
            ptr = select_vreg_random(type);
            if (ptr != nullptr) return ptr;
            else{
                src = Source::Memory; break;
            }
        case 3: // new Memory (load from memory)
            src = Source::Memory; break;
        default:
            break;
        }
    }

    // allocate a new register
    assert (src != Source::Unknown);
    VRegister * res = nullptr;
    switch (src){
        case Source::VectorReg:
        case Source::Memory:
            res = insertReg(type, src);
            break;
        default:
            break;
    }
    assert (res != nullptr);
    return res;
}

VRegister * RegTable::allocate_a_vreg_write(std::string type, bool alwaysNew /* = false*/){
    // determine the source
    Source src = Source::Unknown;
    auto ptr = currentVRegs.find(type);
    if( ptr == currentVRegs.end() || alwaysNew){
        // first appearance of a type, allocate a new register
        src = Source::VectorReg;
    }else{
        // use an old reg : new VectorReg : new Memory = 3 : 1 
        int tmp = getRandomNumber<int>(0, 100);
        VRegister * ptr = nullptr;
        switch ( tmp%4 ) {
        case 0: // use an old reg
        case 1: // use an old reg
        case 2: // use an old reg
            ptr = select_vreg_random(type);
            if(ptr != nullptr)  return ptr;
            else{
                src = Source::VectorReg; break;
            }
        case 3: // new VectorReg (not load from memory)
            src = Source::VectorReg; break;
        default:
            break;
        }
        // src = (tmp%2 == 0) ? Source::Memory : Source::VectorReg;
    }

    // allocate a new register
    assert (src != Source::Unknown);
    VRegister * res = nullptr;
    switch (src){
        case Source::VectorReg:
        case Source::Memory:
            res = insertReg(type, src);
            break;
        default:
            break;
    }
    assert (res != nullptr);
    return res;
}

// do not use the reg to allocate (in select_vreg_random)
bool RegTable::endReg(std::string type, std::string regName){
    auto ptr = currentVRegs.find(type);
    if( ptr == currentVRegs.end() ){
        // don't find the type in map, remove failed
        return 1; // don't find the type in map, remove failed
    }else{
        for (auto it = ptr->second.begin(); it != ptr->second.end(); ++it){
            if( (*it)->getRegName() == regName ){
                // if(*it) {delete *it; *it = nullptr; } // delete point of the VRegister
                // ptr->second.erase(it); // remove the reg entry
                (*it)->ended = true;
                return 0;
            }
        }
    }
    return 1;
}
