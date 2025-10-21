#include "Memory.hpp"

void MemEntry::setInitValues(){
    assert( startsWith(elementType, "bool") == 0);
    if ( startsWith(elementType, "int") || startsWith(elementType, "uint") ){
        for ( int i=0; i<dataLen; ++i){
            this->initValues.push_back(getAScalarRandom(elementType));
        }
    }else{
        // float
        int width = 0;
        if ( elementType == "float16_t" ) width = 16;
        else if ( elementType == "float32_t" ) width = 32;
        else if ( elementType == "float64_t" ) width = 64;
        assert ( width != 0);
        for ( int i=0; i<dataLen; ++i){
            this->initValues.push_back(getAScalarRandom( "uint" + std::to_string(width) + "_t" ));
        }
    }
}

// set the state of memory
// state[i] = newState[i]
void MemEntry::setState(std::vector<bool> newState){
    assert( newState.size() >= dataLen );
    this->state.clear();
    for(int i=0; i<dataLen; ++i){
        this->state.push_back(newState[i]);
    }
}

// update the state of memory
// state[i] = state[i] & newState[i]
void MemEntry::updateState(std::vector<bool> newState){
    assert( newState.size() >= dataLen );
    assert( state.size() >= dataLen );
    for(int i=0; i<dataLen; ++i){
        state[i] = state[i] && newState[i];
    }
    stateIsMask = false;
}

// update the state of memory with idx vector (for Vector Indexed Store Intrinsics)
// state[idx[i]] = state[idx[i]] & newState[i]
/*
void MemEntry::updateIndexedState(std::vector<bool> newState, std::vector<int> idx){
    assert( newState.size() >= dataLen );
    assert( state.size() >= dataLen );
    assert( idx.size() >= dataLen );
    for(int i=0; i<dataLen; ++i){
        state[idx[i]] = state[idx[i]] && newState[i];
    }
    stateIsMask = false;
}
*/
void MemEntry::updateNfieldState(std::vector<bool> newState, std::string nfield){
    assert( newState.size() >= dataLen );
    assert( state.size() >= dataLen );
    int n = std::stoi( nfield2n(nfield) );
    int ptr_state = 0; int ptr_newState = 0;
    for( ; ptr_state<dataLen; ){
        for (int k=0; k<n && ptr_state+k<dataLen ; ++k){
            state[ptr_state+k] = newState[ptr_newState];
        }
        ptr_state += n;
        ptr_newState += 1;
    }
    stateIsMask = false;
}

// get the definition (as global vars in the generated code)
std::string MemEntry::getMemDef(){
    return elementType + " data_" + memName + "[dataLen];\n";
}

// pointer statement used before the loop
std::string MemEntry::getLoopPrefix(){
    return elementType + "* ptr_" + memName + " = data_" + memName + ";\n";
}

// pointer update statement used after the loop
// std::string MemEntry::getLoopSuffix(){
    // return "ptr_" + memName + " += "+ vlName +";\n";
//}