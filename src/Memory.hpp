#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "Type.hpp"
#include "Utils.hpp"
using namespace std;

// one memory entry
class MemEntry{
    public:
        std::string elementType;
        std::string memName;
        std::vector<bool> state;
        bool notNeedStore;
        bool valueIsBool; // whether the value is bool
        bool allValueIsTrue; // for vcompress
        bool stateIsMask; // whether the state is equal to vmask (for store intrinsics)
        bool onlyZeroValid;
        unsigned int length;
        MemEntry():elementType(""),memName(""),length(0),onlyZeroValid(false),valueIsBool(false),allValueIsTrue(false),notNeedStore(false){ 
            for(int i=0;i<dataLen;++i) state.push_back(true);
            stateIsMask = true; 
        };
        MemEntry(std::string type, std::string name, unsigned int len = dataLen): \
        elementType(type),memName(name),length(dataLen),onlyZeroValid(false),valueIsBool(false),allValueIsTrue(false),notNeedStore(false){
            for(int i=0;i<dataLen;++i){
                state.push_back(true);
            }
            stateIsMask = true;
        }

        // for init load values
        std::vector<std::string> initValues;
        void setInitValues();

        // set the state of memory
        // state[i] = newState[i]
        void setState(std::vector<bool> newState);

        // update the state of memory
        // state[i] = state[i] & newState[i]
        void updateState(std::vector<bool> newState);

        // update the state of memory with idx vector (for Vector Indexed Store Intrinsics)
        // state[idx[i]] = state[idx[i]] & newState[i]
        // void updateIndexedState(std::vector<bool> newState, std::vector<int> idx);
        void updateNfieldState(std::vector<bool> newState, std::string nfield);

        // get the definition (as global vars in the generated code)
        std::string getMemDef();

        // pointer statement used before the loop
        std::string getLoopPrefix();
        // pointer update statement used after the loop
        // std::string getLoopSuffix();
};

// allocated memory
class Memorys{
    public:
        // key: name
        // value: memory entry
        std::map<std::string, MemEntry> globalLoadVars; // for global var definition
        std::map<std::string, MemEntry> globalStoreVars; // for global var definition
        Memorys(){};
        // for vsoxei and vsuxei
        // key: type of StoreVar
        // value: vidx of the final store intrinsic
        // to print the correct value
        std::map<std::string, std::string> storevar_link_final_vidx;
};

#endif // MEMORY_HPP