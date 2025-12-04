#include <regex>
#include <functional>
#include <list>
#include "CodeGen.hpp"

unsigned int indentNum = 0; // indent
unsigned int blockNum = 0; // block name
unsigned int loopNum = 0; // for loop

unsigned int memLoadNum = 0; // for load
unsigned int memStoreNum = 0; // for store
unsigned int tmpNum = 0;

std::set <std::string> blockNames;

inline std::string newLoadVar() { return "load_" + std::to_string(memLoadNum++); }
// inline std::string newStoreVar() { return "mem_store_" + std::to_string(memStoreNum++); }
inline std::string newStoreVar(std::string regName) { return "store_" + regName; }

void emitHeader(std::ostream &os) {
    // headers
    os << "// --seed 0x" << std::hex << InitialSeed << " --data_length " << std::dec << dataLen 
    << " --sequence_length " << seqLen;
    // if(withPolicy) os << " --policy ";
    // if(withOverloaded) os << " --overloaded ";
    os << std::endl; 
    os << "// connect type: " << ConnectTypeStr << std::endl;
    if(SchedulingMode == SchedulingMODE::Random) os << "// scheduling mode: random ";
    if(SchedulingMode == SchedulingMODE::Unit) os << "// scheduling mode: unit ";
    if(SchedulingMode == SchedulingMODE::Allin) os << "// scheduling mode: allin ";
    os << std::endl;
    /*
    os << "#include <stdbool.h>\n";
    os << "#include <stdint.h>\n";
    os << "#include <stdlib.h>\n";
    os << "#include <stdio.h>\n";
    os << "#include <std::string.h>\n";
    os << "#include <stddef.h>\n";
    */
    os << "#include <riscv_vector.h>\n";
    os << "#include <vector>\n";
    // os << "int printf(const char *, ...);\n";
    os << "\n";
    // define
    os << "#define dataLen " << std::to_string(dataLen) << "\n";
    os << "#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & 0x03FF))\n";
    os << "#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & "
        "0x007FFFFF))\n";
    os << "#define isNaNF64UI( a ) (((~(a) & UINT64_C( 0x7FF0000000000000 )) == "
        "0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF )))\n";
    os << "typedef _Float16 float16_t;\n";
    os << "typedef float float32_t;\n";
    os << "typedef double float64_t;\n\n";

    os << "unsigned long long int seed = 0;\nvoid hash(unsigned long long int *seed, unsigned long long int const v) {\n"
        "\t*seed ^= v + 0x9e3779b9 + ((*seed)<<6) + ((*seed)>>2);\n"
        "}\n\n";

    // used functions
    os << "static inline float16_t convert_binary_u16_f16(uint16_t u16){\n"
        "\tunion { float16_t f16; uint16_t u16; } converter;\n"
        "\tconverter.u16 = u16;\n"
        "\tif(isNaNF16UI(converter.u16)) return 0;\n"
        "\treturn converter.f16;\n}\n";
    os << "static inline float32_t convert_binary_u32_f32(uint32_t u32){\n"
        "\tunion { float32_t f32; uint32_t u32; } converter;\n"
        "\tconverter.u32 = u32;\n"
        "\tif(isNaNF32UI(converter.u32)) return 0;\n"
        "\treturn converter.f32;\n}\n";
    os << "static inline float64_t convert_binary_u64_f64(uint64_t u64){\n"
        "\tunion { float64_t f64; uint64_t u64; } converter;\n"
        "\tconverter.u64 = u64;\n"
        "\tif(isNaNF64UI(converter.u64)) return 0;\n"
        "\treturn converter.f64;\n}\n";
    os << "static inline uint16_t convert_binary_f16_u16(float16_t f16){\n"
	    "\tunion { float16_t f16; uint16_t u16; } converter;\n"
	    "\tconverter.f16 = f16;\n"
        "\tif(isNaNF16UI(converter.u16)) return (uint16_t)-1;\n"
	    "\treturn converter.u16;\n}\n";
    os << "static inline uint32_t convert_binary_f32_u32(float32_t f32){\n"
	    "\tunion { float32_t f32; uint32_t u32; } converter;\n"
	    "\tconverter.f32 = f32;\n"
        "\tif(isNaNF32UI(converter.u32)) return (uint32_t)-1;\n"
	    "\treturn converter.u32;\n}\n";
    os << "static inline uint64_t convert_binary_f64_u64(float64_t f64){\n"
	    "\tunion { float64_t f64; uint64_t u64; } converter;\n"
	    "\tconverter.f64 = f64;\n"
        "\tif(isNaNF64UI(converter.u64)) return (uint64_t)-1;\n"
	    "\treturn converter.u64;\n}\n\n";
}

// code generation of main function
void MainBlock::codegen(std::ostream &os){
    indentNum = 0;
    os << "int main(){\n";

    indentNum ++;
    os << getIndent() + "init();\n";
    for( auto block: blockNames){
        os << getIndent() + block + "();\n";
    }
    os << getIndent() + "checksum();\n";
    os << getIndent() + "return 0;\n";
    indentNum --;
    os << "}\n";
}

// code generation of rvv intrinsic sequence
void CodeBlock::codegen(std::ostream &os){
    indentNum = 0;
    emitHeader(os);
    emitGlobalVars(os);
    os << "void " << blockName << "() {\n"; blockNames.insert(blockName); indentNum++;
    genLoopPrefix(os);
    genLoopMask(os);
    for(auto str: operationCode){ os << getIndent() + str; }
    genLoopSuffix(os);
    genPrint(os);
}

// definition of global variables
void CodeBlock::emitGlobalVars(std::ostream &os){
    indentNum = 0;
    // mask
    os << "uint8_t arr_mask[dataLen];\n";
    // vector
    for(auto& pair: memorys.globalLoadVars){
        os << pair.second.getMemDef();
    }
    for(auto& pair: memorys.globalStoreVars){
        os << pair.second.getMemDef();
    }
    // scalar
    for(size_t i = 0; i < scalar_table.tableSize; ++i){
        os << scalar_table.ScalarTypes[i] + " " + scalar_table.ScalarVars[i] + ";\n";
    }
    os << std::endl;

    // initialize
    os << "void init(){\n"; indentNum++;
    // initialize of mask
    if(OpDefs.MaxNfield == ""){
        os << getIndent() + "int8_t tmp_mask[dataLen] = {";
        for (size_t i=0; i<dataLen; ++i) {
            if(i == 0) { os << "1, "; } // the first vmask is 1
            else if(vmask[i] == false) os << "0, "; 
            else os << "1, "; 
        }
        os << "};\n";
        os << getIndent() + "for (int i = 0; i < dataLen; ++i) { arr_mask[i] = tmp_mask[i]; }\n";
    }else{
        os << getIndent() + "for (int i = 0; i < dataLen; ++i) { arr_mask[i] = 1; }\n";
    }

    // initialize of load value
    for(auto pair: memorys.globalLoadVars){
        std::string elementType = pair.second.elementType;
        std::string memName = pair.second.memName;
        assert( startsWith(elementType, "bool") == 0);
        if ( startsWith(elementType, "int") || startsWith(elementType, "uint") ){
            // int or uint
            if( pair.second.valueIsBool == true ) elementType = "bool";
            if( pair.second.valueIsBool == true && pair.second.allValueIsTrue == true) {
                os << getIndent() + "for (int i = 0; i < dataLen; ++i) { arr_" + memName + "[i] = 255; }\n";
            }else{
                os << getIndent() + "for (int i = 0; i < dataLen; ++i) { arr_" + memName + "[i] = " + pair.second.initValues[0] + "; }\n";
            }

        } else if ( startsWith(elementType, "float") ){
            // float
            int width = 0;
            if ( elementType == "float16_t" ) width = 16;
            else if ( elementType == "float32_t" ) width = 32;
            else if ( elementType == "float64_t" ) width = 64;
            assert ( width != 0);

            if (width == 16) 
                os << getIndent() + "for (int i = 0; i < dataLen; ++i) { arr_" + memName + "[i] = convert_binary_u16_f16(" + pair.second.initValues[0] + "); }\n";
            else if (width == 32) 
                os << getIndent() + "for (int i = 0; i < dataLen; ++i) { arr_" + memName + "[i] = convert_binary_u32_f32(" + pair.second.initValues[0] + "); }\n";
            else if (width == 64)
                os << getIndent() + "for (int i = 0; i < dataLen; ++i) { arr_" + memName + "[i] = convert_binary_u64_f64(" + pair.second.initValues[0] + "); }\n";
        }
    }

    // initialize of store value
    for(auto pair: memorys.globalStoreVars){
        std::string elementType = pair.second.elementType;
        std::string memName = pair.second.memName;
        // os << getIndent() + "for (int i = 0; i < dataLen; ++i) { arr_" + memName + "[i] = 0; }\n";
        pair.second.setInitValues();
        assert( startsWith(elementType, "bool") == 0);
        if ( startsWith(elementType, "int") || startsWith(elementType, "uint") ){
            // int or uint
            if( pair.second.valueIsBool == true ) elementType = "bool";
            if( pair.second.valueIsBool == true && pair.second.allValueIsTrue == true) {
                os << getIndent() + "for (int i = 0; i < dataLen; ++i) { arr_" + memName + "[i] = 255; }\n";
            }else{
                os << getIndent() + "for (int i = 0; i < dataLen; ++i) { arr_" + memName + "[i] = " + pair.second.initValues[0] + "; }\n";
            }

        } else if ( startsWith(elementType, "float") ){
            // float
            int width = 0;
            if ( elementType == "float16_t" ) width = 16;
            else if ( elementType == "float32_t" ) width = 32;
            else if ( elementType == "float64_t" ) width = 64;
            assert ( width != 0);

            if (width == 16) 
                os << getIndent() + "for (int i = 0; i < dataLen; ++i) { arr_" + memName + "[i] = convert_binary_u16_f16(" + pair.second.initValues[0] + "); }\n";
            else if (width == 32) 
                os << getIndent() + "for (int i = 0; i < dataLen; ++i) { arr_" + memName + "[i] = convert_binary_u32_f32(" + pair.second.initValues[0] + "); }\n";
            else if (width == 64)
                os << getIndent() + "for (int i = 0; i < dataLen; ++i) { arr_" + memName + "[i] = convert_binary_u64_f64(" + pair.second.initValues[0] + "); }\n";
        }
    }
    // initialize of scalars
    for(size_t i = 0; i < scalar_table.tableSize; ++i){
        os << getIndent() + scalar_table.ScalarVars[i] + " = 0;\n";
    }

    indentNum--; os << "}\n";
    os << std::endl;
}

// loop generation
void CodeBlock::genLoopPrefix(std::ostream &os){
    // avl = "avl" + std::to_string(loopNum++);
    avl = "avl"; std::string init_avl = "";
    if(OpDefs.MaxNfield != ""){
        init_avl = avl + " = " + std::to_string(dataLen) + " - " + std::to_string(dataLen) + " % " + nfield2n(OpDefs.MaxNfield);
    }else{
        init_avl = avl + " = dataLen";
    }

    if(OpDefs.MaxNfield != "") { 
        os << getIndent() + \
        "for (size_t ptr = 0, " << init_avl << "; " << avl << " > 0; ){\n"; 
        indentNum++;
        os << getIndent() + "size_t " + this->vlName + " = " + vsetvl( ConnectType.getRatio(), avl + " / " + nfield2n(OpDefs.MaxNfield)) + ";\n";
    } else { 
        os << getIndent() + "for (size_t ptr = 0, " << init_avl << "; " << avl << " > 0; ){\n"; 
        indentNum++;
        os << getIndent() + "size_t " + this->vlName + " = " + vsetvl( ConnectType.getRatio(), avl ) + ";\n";
    }
}

void CodeBlock::genLoopSuffix(std::ostream &os){

    if(OpDefs.MaxNfield != ""){
        os << getIndent() << "ptr += " + vlName + " * " + nfield2n(OpDefs.MaxNfield) << "; ";
        os << avl << " -= " + vlName + " * " + nfield2n(OpDefs.MaxNfield) + ";\n";
    }else{
        os << getIndent() << "ptr += " + vlName << "; ";
        os << avl << " -= " + vlName + ";\n";
    }
    
    indentNum--;
    os << getIndent() + "}\n"; // end of loop
    indentNum--;
    os << getIndent() + "}\n\n"; // end of function
}

void CodeBlock::genLoopMask(std::ostream &os){
    /*
    int ratio = VectorType(ConnectType).ratio;
    os << getIndent() + "vbool"+std::to_string(ratio)+"_t " + maskName + " = "; 
    os << "__riscv_vlm_v_b" + std::to_string(ratio) + "(&arr_mask[ptr], "+vlName+");\n";
    */
    
    std::string tmptype = ""; int ratio = ConnectType.getRatio();
    if(ratio == 64) tmptype = "8mf8";
    else if(ratio == 32) tmptype = "8mf4";
    else if(ratio == 16) tmptype = "8mf2";
    else if(ratio == 8) tmptype = "8m1";
    else if(ratio == 4) tmptype = "8m2";
    else if(ratio == 2) tmptype = "8m4";
    else if(ratio == 1) tmptype = "8m8";
    assert(tmptype != ""); 
    // load
    os << getIndent() + "vuint"+tmptype+"_t mask_value= __riscv_vle8_v_u"+tmptype+"(&arr_mask[ptr], vl);\n";
    os << getIndent() + "vbool"+std::to_string(ratio)+"_t "+maskName+"= __riscv_vmseq_vx_u"+tmptype+"_b"+std::to_string(ratio)+"(mask_value, 1, vl);\n"; 
}

// // print the memory for differential testing
void CodeBlock::genPrint(std::ostream &os){
    indentNum = 0;
    os << "void checksum(){\n";
    indentNum ++ ;
    os << getIndent() + "__builtin_printf(\"%llu\", seed);\n";
    // load
    // removed
    
    // store
    for ( auto& pair: memorys.globalStoreVars){
        if(pair.second.notNeedStore == true) continue;

        int width = 0;
        std::string elementType = pair.second.elementType;
        std::string memName = pair.second.memName;
        std::smatch matches;
        std::regex type_format("[a-z]+([0-9]+)_t");
        if( regex_search(elementType, matches, type_format) ){
            width = static_cast<int>( stoi(matches[1]) );
        }
        assert (width != 0);

        // for index store intrinsics
        std::string converted;
        if( memorys.storevar_link_final_vidx.find( memName ) == memorys.storevar_link_final_vidx.end() ) {
            converted = "arr_" + memName + "[i]";
        }else{
            // for index store intrinsics
            converted = "arr_" + memName + "[i]";
        }

        if( startsWith(elementType, "float") ) converted = "convert_binary_f" + std::to_string(width) + "_u" + std::to_string(width) + "(" + converted + ")";
        
        std::string length = pair.second.onlyZeroValid ? "1" : "dataLen";

        if(OpDefs.MaxNfield != ""){
            os << getIndent() + "for(int i=0; i<" + length + "; ++i) { hash(&seed, " + converted + "); }\n";
        }else{
            if( pair.second.stateIsMask == false ){
                os << getIndent() + "int8_t valid_" + memName + "[dataLen] = {";
                for (size_t i=0; i<dataLen; ++i) {
                    if(pair.second.state[i] == false) os << "0, "; 
                    else os << "1, "; 
                }
                os << "};\n";
            }
            if( pair.second.stateIsMask == false )
                os << getIndent() + "for(int i=0; i<" + length + "; ++i) { if(valid_" + memName + "[i]) hash(&seed, " + converted + "); } ";
            else
                os << getIndent() + "for(int i=0; i<" + length + "; ++i) { if(arr_mask[i]) hash(&seed, " + converted + "); } ";
            os << "\n";
        }
    }

    // scalar // always results in undefined behavior
    /*
    for(size_t i = 0; i < scalar_table.tableSize; ++i){
        std::string converted = scalar_table.ScalarVars[i];
        if(scalar_table.ScalarTypes[i] == "float") converted = "convert_binary_f32_u32(" + converted + ")";
        else if(scalar_table.ScalarTypes[i] == "double") converted = "convert_binary_f64_u64(" + converted + ")";
        os << getIndent() + "hash(&seed, " + converted + ");\n";
    }
    */

    os << getIndent() + "__builtin_printf(\"%llu\\n\", seed);\n";
    os << "}\n\n";
}

// std::vector register allocate
void CodeBlock::vregAllocateRandom(std::vector<BaseOperator > & Ops){
    for(size_t i = 0; i<Ops.size(); i++){
        for(auto & para: Ops[i].paras){
            Type etype = para.enumType();
            std::string type = para.getPtype();
            switch (etype){
                case Type::OneDVector:
                    assert( para.pvreg == nullptr );
                    if( Ops[i].commonRatio > 0 && Ops[i].ifWithoutMaskIntrin() == false ) para.pvreg = regtable.allocate_a_vreg_read( type ); 
                    else para.pvreg = regtable.allocate_a_vreg_read( type, true ); // not aligned, always new a register and use unmask load
                    assert( para.pvreg != nullptr );
                    break;
                case Type::VMASK: // mask
                case Type::VL:              
                default: break;
            }
        }
        Type retEtype = Ops[i].enumRetype();
        std::string rettype = Ops[i].getRetype();

        if (retEtype == Type::OneDVector) {
            assert ( Ops[i].retvreg == nullptr );
            if( Ops[i].commonRatio > 0 ) Ops[i].retvreg = regtable.allocate_a_vreg_write( rettype );
            else Ops[i].retvreg = regtable.allocate_a_vreg_write( rettype, true ); // not aligned, always new a register
            if( Ops[i].ifTailProducer() == true ){
                // tail element producer, remove from the register table
                assert ( regtable.endReg( rettype, Ops[i].retvreg->getRegName() ) == 0 );
            }
            assert ( Ops[i].retvreg != nullptr );
        }
    }
}

// insert load-store intrinsics to sequence after register allocation
void CodeBlock::insertLoadAndStoreIntrinsics(std::vector<BaseOperator > & Ops) {
    for(size_t i=0; i<Ops.size(); i++){
        std::vector<std::string> prefix, suffix;
        // get load intrinsics
        for (auto & para: Ops[i].paras){
            if(para.pvreg != nullptr){
                if( para.pvreg->declared == false){
                    std::vector<std::string> load; // a load intrinsic is needed
                    if( startsWith(para.getPtype(), "vbool") ){
                        if( startsWith( Ops[i].getName(), "__riscv_vcompress" ) == true \
                        && endsWith( Ops[i].getName(), "_tu" ) == false \
                        && (para.getPname() == "vs1" || para.getPname() == "mask") ){
                            // all value is non-agnostic
                            load = load_bool( para.getPtype(), para.pvreg->getRegName(), true ); 
                        }else{
                            load = load_bool( para.getPtype(), para.pvreg->getRegName() ); 
                        }
                    } else { 
                        // random select load intrinsics
                        std::string ptype = para.getPtype();
                        std::string loadVar = newLoadVar(); // globalLoadVars.insert( Parameter( vtmp.etype, loadVar) );
                        memorys.globalLoadVars[loadVar] = MemEntry(VectorType(ptype).etype, loadVar);
                        memorys.globalLoadVars[loadVar].setInitValues();
                        if(OpDefs.LoadIntrinsics[ptype].size() > 0){
                            BaseOperator* selected_load = nullptr;
                            if(cov_guide) selected_load = select_cov_guide(OpDefs.LoadIntrinsics[ptype]);
                            else selected_load = *select_random(OpDefs.LoadIntrinsics[ptype]);

                            // update covmap
                            if(cov_guide || cov_log) covmap.add(selected_load->opdata_id);
                            
                            if( Ops[i].commonRatio > 0 ){
                                load = selected_load->load_gen(ptype, para.pvreg->getRegName(), loadVar, Ops[i].ifWithoutMaskIntrin());
                            }else{
                                load = selected_load->load_gen(ptype, para.pvreg->getRegName(), loadVar, true);
                            }
                        }else{
                        // no load intrinsics in the .def
                        std::function<std::vector<std::string>(std::string, std::string, std::string, bool)> func_load;
                        int tmprandom = getRandomNumber<int>(0, 100) % 5;
                        if(tmprandom == 0 || Ops[i].commonRatio == 0) {
                            func_load = std::bind(&CodeBlock::load_vle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
                        }else if (tmprandom == 1){
                            func_load = std::bind(&CodeBlock::load_vlse, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
                        }else if (tmprandom == 2){
                            func_load = std::bind(&CodeBlock::load_vloxei, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
                        }else if (tmprandom == 3){
                            func_load = std::bind(&CodeBlock::load_vluxei, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
                        }else{
                            //default and tmp random == 4
                            func_load = std::bind(&CodeBlock::load_vle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
                        }
                        if( Ops[i].commonRatio > 0 ){
                            bool ifmask = (getRandomNumber<int>(0,99)%3 == 0); // mask : unmask = 1 : 2
                            load = func_load( ptype, para.pvreg->getRegName(), loadVar, ifmask && (!Ops[i].ifWithoutMaskIntrin()) ); 
                        } else {
                            load = func_load( ptype, para.pvreg->getRegName(), loadVar, false ); // always unmask
                        }
                        }
                    }
                    prefix.insert( prefix.end(), load.begin(), load.end() );
                    para.pvreg->declared = true;
                }
            }
        }
        // corner case: vrgather intrinsics
        // e.g., vfloat16mf4_t __riscv_vrgather_vv_f16mf4(vfloat16mf4_t vs2, vuint16mf4_t vs1, size_t vl);
        if(startsWith( Ops[i].getName(), "__riscv_vrgather" ) == true ){
            std::string vs1reg = "";
            for (auto para: Ops[i].paras){
                if((para.getPname() == "vs1" || para.getPname() == "index" || para.getPname() == "op2") && \
                (para.getPtype() != "size_t")){
                    assert(para.pvreg != nullptr);
                    vs1reg = para.pvreg->getRegName();
                    assert(vs1reg != "");
                    VectorType ret( para.getPtype() );
                    prefix.push_back( vs1reg + " = __riscv_vremu_vx_u" + std::to_string(ret.ewidth) + ret.emul + \
                    "(" + vs1reg + ", (" + ret.etype + ")(vl), vl);\n" );
                    break;
                }
            }
        }
        // get operation intrinsics
        OpInstruction.push_back( Ops[i].codegen() );
        
        // get store intrinsics
        if( Ops[i].retvreg != nullptr ){
            std::vector<std::string> store;
            if( startsWith(Ops[i].getRetype(), "vbool") ) { store = store_bool( Ops[i].getRetype(), Ops[i].retvreg->getRegName() ); }
            else { 
                bool onlyzero = Ops[i].ifTailProducer();
                std::string vtype = Ops[i].getRetype(); VectorType vtmp(vtype); // vector type to be stored
                std::string regName = Ops[i].retvreg->getRegName();

                // for store vars in memorys
                std::string storeVar = newStoreVar(regName); 
                memorys.globalStoreVars[storeVar] = MemEntry(vtmp.etype, storeVar);
                if(vtmp.nfield != "") memorys.globalStoreVars[storeVar].updateNfieldState(vmask, OpDefs.MaxNfield);
                else memorys.globalStoreVars[storeVar].setState(vmask);
                if(onlyzero){
                    memorys.globalStoreVars[storeVar].onlyZeroValid = true;
                    for(size_t i=0;i<dataLen;++i){
                        if(i==0) memorys.globalStoreVars[storeVar].state[i] = true;
                        else memorys.globalStoreVars[storeVar].state[i] = false;
                    }
                }

                if(OpDefs.StoreIntrinsics[vtype].size() > 0){
                    BaseOperator* selected_store = nullptr;
                    if(cov_guide) selected_store = select_cov_guide(OpDefs.StoreIntrinsics[vtype]);
                    else selected_store = *(select_random(OpDefs.StoreIntrinsics[vtype]));

                    // update covmap
                    if(cov_guide || cov_log) covmap.add(selected_store->opdata_id);
                    
                    if( Ops[i].commonRatio > 0 ){
                        store = selected_store->store_gen(vtype, regName, storeVar, Ops[i].ifWithoutMaskIntrin());
                    }else{
                        store = selected_store->store_gen(vtype, regName, storeVar, true);
                    }
                }else{

                    // random select store intrinsics
                    std::function<std::vector<std::string>(std::string, std::string, bool)> func_store;
                    int tmprandom = getRandomNumber<int>(0, 100) % 5;
                    if(tmprandom == 0 || Ops[i].commonRatio == 0) {
                        func_store = std::bind(&CodeBlock::store_vse, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                    }else if (tmprandom == 1){
                        func_store = std::bind(&CodeBlock::store_vsse, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                    }else if (tmprandom == 2){
                        func_store = std::bind(&CodeBlock::store_vsoxei, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                    }else if (tmprandom == 3){
                        func_store = std::bind(&CodeBlock::store_vsuxei, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                    }else{
                        //default and tmp random == 4
                        func_store = std::bind(&CodeBlock::store_vse, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                    }
                    if( Ops[i].commonRatio > 0 ){
                        bool ifmask = (getRandomNumber<int>(0,99)%3 == 0); // mask : unmask = 1 : 2
                        store = func_store( vtype, regName, ifmask && (!Ops[i].ifWithoutMaskIntrin()) );
                    } else {
                        store = func_store( vtype, regName, false ); // always unmask
                    }
                }

                // vreinterpret always encounter undefined behaviours
                //if( startsWith(Ops[i].getName(), "__riscv_vreinterpret") ||
                //startsWith(Ops[i].getName(), "__riscv_vlmul") || startsWith(Ops[i].getName(), "__riscv_vreinterpret") ){
                if( Ops[i].alwaysAgnostic() == true ){
                    store.clear();
                    memorys.globalStoreVars[newStoreVar(Ops[i].retvreg->getRegName())].notNeedStore = true;
                }
            }
            suffix.insert( suffix.end(), store.begin(), store.end() );
        }
        // update
        PrefixOp.push_back( prefix );
        SuffixOp.push_back( suffix );
    }
}

// given a selected sequence (load, store, operation)
// return a std::vector of std::string representing instructions after scheduling
void CodeBlock::instructionScheduling(unsigned int length, SchedulingMODE mode /*= SchedulingMODE::Allin*/){
    // instruction scheduling
    std::function<std::vector<std::string>(std::vector<std::vector<std::string>> &&, std::vector<std::vector<std::string>> &&, std::vector<std::string> &&, unsigned int)> func_scheduling;
    if(mode == SchedulingMODE::Allin){
        // operationCode = scheduling_allin(std::move(PrefixOp), std::move(SuffixOp), std::move(OpInstruction), OpNum);
        func_scheduling = scheduling_allin;
    }else if(mode == SchedulingMODE::Unit){
        // operationCode = scheduling_unit(std::move(PrefixOp), std::move(SuffixOp), std::move(OpInstruction), OpNum);
        func_scheduling = scheduling_unit;
    }else if(mode == SchedulingMODE::Random){
        // operationCode = scheduling_random(std::move(PrefixOp), std::move(SuffixOp), std::move(OpInstruction), OpNum);
        func_scheduling = scheduling_random;
    }else{
        std::cerr << "unimplemention error: instructionScheduling" << std::endl;
        exit(1);
    }
    operationCode = func_scheduling(std::move(PrefixOp), std::move(SuffixOp), std::move(OpInstruction), length);
}

// instruction scheduling unit by unit
// e.g. load-op-store, load-op-store, ....
std::vector<std::string> scheduling_unit( std::vector<std::vector<std::string>> && PrefixOp, std::vector<std::vector<std::string>> && SuffixOp,  
                                std::vector<std::string> && OpInstruction, size_t length){
    std::vector<std::string> res;
    for(size_t i=0; i<length; ++i){
        // load
        for(auto it = PrefixOp[i].begin(); it != PrefixOp[i].end(); it++){
            res.push_back(*it);
        }
        // operation
        res.push_back( OpInstruction[i] );
        // store
        for(auto it = SuffixOp[i].begin(); it != SuffixOp[i].end(); it++){
            res.push_back(*it);
        }
    }
    return res;
}

// instruction scheduling all at once
// e.g. load ... load, op ... op, store ... store
std::vector<std::string> scheduling_allin( std::vector<std::vector<std::string>> && PrefixOp, std::vector<std::vector<std::string>> && SuffixOp,  
                                std::vector<std::string> && OpInstruction, size_t length){
    std::vector<std::string> res;
    // load
    for(size_t i=0; i<length; ++i){
        for(auto it = PrefixOp[i].begin(); it != PrefixOp[i].end(); it++){
            res.push_back(*it);
        }
    }
    // operation
    for(size_t i=0; i<length; ++i) res.push_back( OpInstruction[i] );
    // store
    for(size_t i=0; i<length; ++i) { 
        for(auto it = SuffixOp[i].begin(); it != SuffixOp[i].end(); it++){
            res.push_back(*it);
        }
    }
    return res;
}

// instruction scheduling randomly
std::vector<std::string> scheduling_random( std::vector<std::vector<std::string>> && PrefixOp, std::vector<std::vector<std::string>> && SuffixOp,  
                                std::vector<std::string> && OpInstruction, size_t length){
    
    std::list<std::string> intrinsics; // list for insert
    std::list<std::string>::iterator ptr_start;
    std::list<std::string>::iterator ptr_end;
    std::list<std::string>::iterator ptr_lastop = intrinsics.begin();

    for(size_t i=0; i<length; ++i){
        ptr_lastop = insertRandomly(intrinsics, ++ptr_lastop, intrinsics.end(), OpInstruction[i] );

        ptr_start = intrinsics.begin();
        ptr_end = ptr_lastop;
        for(auto it = PrefixOp[i].begin(); it != PrefixOp[i].end(); it++){
            // if( ptr_start != ptr_end )
            ptr_start = insertRandomly(intrinsics, ptr_start, ptr_end, *it);
            ptr_start++;
        }

        ptr_start = ++ptr_lastop;
        ptr_end = intrinsics.end();
        for(auto it = SuffixOp[i].begin(); it != SuffixOp[i].end(); it++){
            ptr_start = insertRandomly(intrinsics, ptr_start, ptr_end, *it);
            ptr_start ++;
        }
        ptr_lastop--;
    }
    std::vector<std::string> res;
    for(auto s: intrinsics){
        res.push_back(s);
    }
    return res;
}

// load bool
std::vector<std::string> CodeBlock::load_bool(std::string type, std::string regName, bool allValueIsTrue /* = false*/){
    assert( startsWith(type, "vbool") == true );
    VectorType vtmp(type);
    int ratio = vtmp.ratio;

    if(allValueIsTrue == false){
        std::string loadVar = newLoadVar(); 
        memorys.globalLoadVars[loadVar] = MemEntry("uint8_t", loadVar);
        memorys.globalLoadVars[loadVar].valueIsBool = true;
        memorys.globalLoadVars[loadVar].setInitValues();
        std::string vmseqOp = "vbool" + std::to_string(ratio) + "_t " + regName + " = ";
        vmseqOp += "__riscv_vlm_v_b" + std::to_string(ratio) + "(&arr_" + loadVar + "[ptr], " + vlName + ");\n";
        return {vmseqOp};
    }else{
        // for vcompress vs1
        // allValueIsTrue == true
        std::string vmseqOp = "vbool" + std::to_string(ratio) + "_t " + regName + " = ";
        vmseqOp += "__riscv_vlm_v_b" + std::to_string(ratio) + "(std::vector<uint8_t>(("+vlName+" + 7) / 8, 255).data(), " + vlName + ");\n";
        return {vmseqOp};
    }
    return {};
}

// store bool
std::vector<std::string> CodeBlock::store_bool(std::string type, std::string regName){
    assert( startsWith(type, "vbool") == true );
    VectorType vtmp(type);
    int ratio = vtmp.ratio;
    std::vector<std::string> res; 

    std::string storeVar = newStoreVar(regName); // globalStoreVars.insert( Parameter( "int8_t", storeVar) );
    memorys.globalStoreVars[storeVar] = MemEntry("uint8_t", storeVar);
    memorys.globalStoreVars[storeVar].setState(vmask);

    // vuint8mf2_t zero = vmv_v_x_u8mf2(0, __riscv_vsetvlmax_e8mf2());
    // vuint8mf2_t vec_store = __riscv_vmerge_vxm_u8mf2(zero, 1, vec_value_4_0, vl);
    // vse8_v_u8mf2(placeholder4, vec_store, vl);
    std::string tmptype = "";
    if(ratio == 64) tmptype = "8mf8";
    else if(ratio == 32) tmptype = "8mf4";
    else if(ratio == 16) tmptype = "8mf2";
    else if(ratio == 8) tmptype = "8m1";
    else if(ratio == 4) tmptype = "8m2";
    else if(ratio == 2) tmptype = "8m4";
    else if(ratio == 1) tmptype = "8m8";
    assert(tmptype != "");
    res.push_back("vuint"+tmptype+"_t zero_"+std::to_string(tmpNum)+" = __riscv_vmv_v_x_u"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"());\n");
    res.push_back("vuint"+tmptype+"_t vstore_tmp_"+std::to_string(tmpNum)+" = __riscv_vmerge_vxm_u"+tmptype+"(zero_"+std::to_string(tmpNum) +", 1, "+ regName +", "+vlName+");\n");
    res.push_back("__riscv_vse8_v_u"+tmptype+"(&arr_"+storeVar+"[ptr], vstore_tmp_"+std::to_string(tmpNum)+", "+vlName+");\n");
    tmpNum++;
    /*
    std::string vmseqOp;
    regName = "__riscv_vmand(" + regName + ", vmask, " + vsetvl_max(ratio) + ")";
    if(withOverloaded){
        vmseqOp = "__riscv_vsm(&arr_" + storeVar + "[ptr], " + regName + ", " + vlName + ");\n";
    }else{
        vmseqOp = "__riscv_vsm_v_b" + std::to_string(ratio) + "(&arr_" + storeVar + "[ptr], " + regName + ", " + vlName + ");\n";
    }
    res.push_back(vmseqOp);
    */
    return res; 
}

// Vector Unit-Stride Load Intrinsics
// load intrinsic: vle, vlseg
std::vector<std::string> CodeBlock::load_vle(std::string type, std::string regName, std::string loadVar, bool mask /*= false*/ ){
    std::vector<std::string> res;
    assert( startsWith(type, "vbool") == false );
    VectorType vtmp(type);

    std::string intrinsic;
    std::string suffix = genPolicySuffix(mask);
    if(vtmp.nfield == ""){
        // vle
        if(withOverloaded == true && mask == true){
            // only mask vle intrinsics are overloaded
            intrinsic = "__riscv_vle" + std::to_string(vtmp.ewidth);
            if(withPolicy == false) suffix = "";
        }else{
            intrinsic = "__riscv_vle" + std::to_string(vtmp.ewidth) + "_v_" + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul;
        }
    }else{
        // vtmp.nfield: std::string, e.g., "x2"
        // vlseg
        if(withOverloaded == true && mask == true){
            // only mask vle intrinsics are overloaded
            intrinsic = "__riscv_vlseg";
            intrinsic += vtmp.nfield.c_str()[1];
            intrinsic += 'e' + std::to_string(vtmp.ewidth);
            if(withPolicy == false) suffix = "";
        }else{
            intrinsic = "__riscv_vlseg";
            intrinsic += vtmp.nfield.c_str()[1];
            intrinsic += 'e' + std::to_string(vtmp.ewidth) + "_v_" \
                        + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul + vtmp.nfield;
        }
    }
    intrinsic += suffix;

    std::string loadOp = type + " " + regName + " = " + intrinsic + "(";
    if(mask) loadOp += maskName + ", ";
    if(withPolicy){
        // add vd
        loadOp += "vd_" + loadVar + ", ";
        std::string tmptype = std::to_string(vtmp.ewidth) + vtmp.emul;
        std::string vlmax = vsetvl_max(vtmp.ratio);
        if(vtmp.nfield == ""){
            if( startsWith(vtmp.etype, "float") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vfmv_v_f_f"+tmptype+"(0, " + vlmax + ");\n");
            else if ( startsWith(vtmp.etype, "uint") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_u"+tmptype+"(0, " + vlmax + ");\n");
            else if ( startsWith(vtmp.etype, "int") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_i"+tmptype+"(0, " + vlmax + ");\n");
            else {
                std::cerr << "unimplementation error: unknown type" << std::endl;
                exit(1);
            }
        }else{
            int n = std::stoi( nfield2n(vtmp.nfield) );
            std::string create_vd;
            std::string para;
            if( startsWith(vtmp.etype, "float") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_f"+tmptype+vtmp.nfield;
                para = "__riscv_vfmv_v_f_f"+tmptype+"(0, " + vlmax + ")";
            }else if ( startsWith(vtmp.etype, "uint") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_u"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_u"+tmptype+"(0, " + vlmax + ")";
            }else if ( startsWith(vtmp.etype, "int") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_i"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_i"+tmptype+"(0, " + vlmax + ")";
            }else {
                std::cerr << "unimplementation error: unknown type" << std::endl;
                exit(1);
            }
            create_vd += "(";
            for(int x=0; x<n-1; ++x){
                create_vd += para + ", ";
            }
            create_vd += para + ");\n";
            res.push_back(create_vd);
        }
    }
    loadOp += "&arr_" + loadVar + "[ptr], " + vlName + ");\n";

    res.push_back(loadOp);
    return res;
}

// Vector Unit-Stride Store Intrinsics
// store intrinsic: vse, vsseg
// don't have policy variants
std::vector<std::string> CodeBlock::store_vse(std::string type, std::string regName, bool mask /*= false*/){
    std::vector<std::string> res;
    assert( startsWith(type, "vbool") == false );
    VectorType vtmp(type);
    
    std::string intrinsic;
    std::string suffix = genPolicySuffix(mask, false);
    if(vtmp.nfield == ""){
        // vse
        if(withOverloaded == true && withPolicy == false){
            intrinsic = "__riscv_vse" + std::to_string(vtmp.ewidth);
            suffix = "";
        }else{
            intrinsic = "__riscv_vse" + std::to_string(vtmp.ewidth) + "_v_" + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul;
        }
    }else{
        // vsseg
        if(withOverloaded == true && withPolicy == false){
            intrinsic = "__riscv_vsseg";
            intrinsic += vtmp.nfield.c_str()[1];
            intrinsic += 'e' + std::to_string(vtmp.ewidth);
            suffix = "";
        }else{
            intrinsic = "__riscv_vsseg";
            intrinsic += vtmp.nfield.c_str()[1];
            intrinsic += 'e' + std::to_string(vtmp.ewidth) + "_v_" \
                        + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul + vtmp.nfield;
        }
    }
    intrinsic += suffix;

    std::string storeOp = intrinsic + "(";
    if(mask) storeOp += maskName + ", ";
    std::string storeVar = newStoreVar(regName); 
    storeOp += "&arr_" + storeVar + "[ptr], " + regName + ", " + vlName + ");\n";

    res.push_back(storeOp);
    return res;
}


// Vector Strided Load Intrinsics
// load intrinsic: vlse, vlsseg
std::vector<std::string> CodeBlock::load_vlse(std::string type, std::string regName, std::string loadVar, bool mask /*= false*/ ){
    std::vector<std::string> res;
    assert( startsWith(type, "vbool") == false );
    VectorType vtmp(type);

    std::string intrinsic;
    std::string suffix = genPolicySuffix(mask);
    if(vtmp.nfield == ""){
        // vlse
        if(withOverloaded == true && mask == true){
            intrinsic = "__riscv_vlse" + std::to_string(vtmp.ewidth);
            if(withPolicy == false) suffix = "";
        }else{
            intrinsic = "__riscv_vlse" + std::to_string(vtmp.ewidth) + "_v_" + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul;
        }
    }else{
        // vlsseg
        if(withOverloaded == true && mask == true){
            intrinsic = "__riscv_vlsseg";
            intrinsic += vtmp.nfield.c_str()[1];
            intrinsic += 'e' + std::to_string(vtmp.ewidth);
            if(withPolicy == false) suffix = "";
        }else{
            intrinsic = "__riscv_vlsseg";
            intrinsic += vtmp.nfield.c_str()[1];
            intrinsic += 'e' + std::to_string(vtmp.ewidth) + "_v_" \
                        + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul + vtmp.nfield;
        }
    }
    intrinsic += suffix;

    std::string loadOp = type + " " + regName + " = " + intrinsic + "(";
    if(mask) loadOp += maskName + ", ";
    if(withPolicy){
        // add vd
        loadOp += "vd_" + loadVar + ", ";
        std::string tmptype = std::to_string(vtmp.ewidth) + vtmp.emul;
        std::string vlmax = vsetvl_max(vtmp.ratio);
        if(vtmp.nfield == ""){
            if( startsWith(vtmp.etype, "float") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vfmv_v_f_f"+tmptype+"(0, " + vlmax + ");\n");
            else if ( startsWith(vtmp.etype, "uint") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_u"+tmptype+"(0, " + vlmax + ");\n");
            else if ( startsWith(vtmp.etype, "int") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_i"+tmptype+"(0, " + vlmax + ");\n");
            else {
                std::cerr << "unimplementation error: unknown type" << std::endl;
                exit(1);
            }
        }else{
            int n = std::stoi( nfield2n(vtmp.nfield) );
            std::string create_vd;
            std::string para;
            if( startsWith(vtmp.etype, "float") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_f"+tmptype+vtmp.nfield;
                para = "__riscv_vfmv_v_f_f"+tmptype+"(0, " + vlmax + ")";
            }else if ( startsWith(vtmp.etype, "uint") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_u"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_u"+tmptype+"(0, " + vlmax + ")";
            }else if ( startsWith(vtmp.etype, "int") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_i"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_i"+tmptype+"(0, " + vlmax + ")";
            }else {
                std::cerr << "unimplementation error: unknown type" << std::endl;
                exit(1);
            }
            create_vd += "(";
            for(int x=0; x<n-1; ++x){
                create_vd += para + ", ";
            }
            create_vd += para + ");\n";
            res.push_back(create_vd);
        }
    }

    // one-element width is ptrdiff_t rs2 (equal to Unit-Stride)
    if(vtmp.nfield == ""){
        loadOp += "&arr_" + loadVar + "[ptr], " + std::to_string(bits2bytes(vtmp.ewidth)) + ", " + vlName + ");\n";
    }else{
        loadOp += "&arr_" + loadVar + "[ptr], " + std::to_string(bits2bytes(vtmp.ewidth)) + " * " + nfield2n(vtmp.nfield) + ", " + vlName + ");\n";
    }

    res.push_back(loadOp);
    return res;
}


// Vector Strided Store Intrinsics
// load intrinsic: vsse, vssseg
// don't have policy variants
std::vector<std::string> CodeBlock::store_vsse(std::string type, std::string regName, bool mask /*= false*/){
    std::vector<std::string> res;
    assert( startsWith(type, "vbool") == false );
    VectorType vtmp(type);

    std::string intrinsic;
    std::string suffix = genPolicySuffix(mask, false);
    if(vtmp.nfield == ""){
        // vsse
        if(withOverloaded==true && withPolicy == false){
            intrinsic = "__riscv_vsse" + std::to_string(vtmp.ewidth);
            suffix = "";
        }else{
            intrinsic = "__riscv_vsse" + std::to_string(vtmp.ewidth) + "_v_" + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul;
        }
    }else{
        // vssseg
        if(withOverloaded == true && withPolicy == false){
            intrinsic = "__riscv_vssseg";
            intrinsic += vtmp.nfield.c_str()[1];
            intrinsic += 'e' + std::to_string(vtmp.ewidth);
            suffix = "";
        }else{
            intrinsic = "__riscv_vssseg";
            intrinsic += vtmp.nfield.c_str()[1];
            intrinsic += 'e' + std::to_string(vtmp.ewidth) + "_v_" \
                    + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul + vtmp.nfield;
        }
        // if(mask) intrinsic += "_m";
    }
    intrinsic += suffix;

    std::string storeOp = intrinsic + "(";
    if(mask) storeOp += maskName + ", ";
    std::string storeVar = newStoreVar(regName); 

    // one-element byte is ptrdiff_t rs2 (equal to Unit-Stride)
    if(vtmp.nfield == ""){
        storeOp += "&arr_" + storeVar + "[ptr], " + std::to_string(bits2bytes(vtmp.ewidth)) + ", " + regName + ", " + vlName + ");\n";
    }else{
        storeOp += "&arr_" + storeVar + "[ptr], " + std::to_string(bits2bytes(vtmp.ewidth)) + " * " + nfield2n(vtmp.nfield) + ", " + regName + ", " + vlName + ");\n";
    }

    res.push_back(storeOp);
    return res;
}


// Vector Indexed Load Intrinsics
// load intrinsic: vloxei, vloxseg
std::vector<std::string> CodeBlock::load_vloxei(std::string type, std::string regName, std::string loadVar, bool mask /*= false*/ ){
    std::vector<std::string> res;
    assert( startsWith(type, "vbool") == false );
    // VectorType vtmp(type);
    VectorType vtmp = *dynamic_cast<VectorType *>(UsedTypes.getPtr(std::move(type)));
    // generate a std::vector named 'vidx' for indexes, where elements are in the range(0, min(255,dataLen-1))
    int maxValue = std::min( static_cast<int>((1<<8)-1), static_cast<int>(dataLen-1)); // range(0, min(2^8-1,dataLen-1))
    std::string idxType = genIdxType(vtmp.ratio);
    // vidxs.push_back( VIndex( idxType, maxValue ) );
    std::string idxName = VIndex( idxType, maxValue ).idxName;

    VectorType vidxtype = *dynamic_cast<VectorType *>(UsedTypes.getPtr(std::move(idxType)));
    //VectorType vidxtype(idxType); vidxtype.parse_vtype();
    // memorys.globalLoadVars[idxName] = MemEntry(vidxtype.etype, idxName);

    std::string intrinsic; std::string suffix = genPolicySuffix(mask);
    if(vtmp.nfield == ""){
        // vloxei
        if(withOverloaded == true){
            intrinsic = "__riscv_vloxei" + std::to_string(vidxtype.ewidth);
            if(withPolicy == false) suffix = "";
        }else{
            intrinsic = "__riscv_vloxei" + std::to_string(vidxtype.ewidth) + "_v_" + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul;
        }
    }else{
        // vloxseg
        if(withOverloaded == true){
            intrinsic = "__riscv_vloxseg";
            intrinsic += vtmp.nfield.c_str()[1] + std::string("ei") + std::to_string(vidxtype.ewidth);
            if(withPolicy == false) suffix = "";
        }else{
            intrinsic = "__riscv_vloxseg";
            intrinsic += vtmp.nfield.c_str()[1] + std::string("ei") + std::to_string(vidxtype.ewidth) + "_v_" \
                    + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul + vtmp.nfield;
        }
    }
    intrinsic += suffix;

    std::string loadOp = type + " " + regName + " = " + intrinsic + "(";
    if(mask) loadOp += maskName + ", ";
    if(withPolicy){
        // add vd
        loadOp += "vd_" + loadVar + ", ";
        std::string tmptype = std::to_string(vtmp.ewidth) + vtmp.emul;
        std::string vlmax = vsetvl_max(vtmp.ratio);
        if(vtmp.nfield == ""){
            if( startsWith(vtmp.etype, "float") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vfmv_v_f_f"+tmptype+"(0, " + vlmax + ");\n");
            else if ( startsWith(vtmp.etype, "uint") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_u"+tmptype+"(0, " + vlmax + ");\n");
            else if ( startsWith(vtmp.etype, "int") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_i"+tmptype+"(0, " + vlmax + ");\n");
            else {
                std::cerr << "unimplementation error: unknown type" << std::endl;
                exit(1);
            }
        }else{
            int n = std::stoi( nfield2n(vtmp.nfield) );
            std::string create_vd;
            std::string para;
            if( startsWith(vtmp.etype, "float") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_f"+tmptype+vtmp.nfield;
                para = "__riscv_vfmv_v_f_f"+tmptype+"(0, " + vlmax + ")";
            }else if ( startsWith(vtmp.etype, "uint") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_u"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_u"+tmptype+"(0, " + vlmax + ")";
            }else if ( startsWith(vtmp.etype, "int") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_i"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_i"+tmptype+"(0, " + vlmax + ")";
            }else {
                std::cerr << "unimplementation error: unknown type" << std::endl;
                exit(1);
            }
            create_vd += "(";
            for(int x=0; x<n-1; ++x){
                create_vd += para + ", ";
            }
            create_vd += para + ");\n";
            res.push_back(create_vd);
        }
    }
    loadOp += "&arr_" + loadVar + "[ptr], " + idxName + ", " + vlName + ");\n";

    // res.push_back(vidx_byte_statement);
    std::string vidx_statement = idxType + " " + idxName + " = __riscv_vsll_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(__riscv_vid_v_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + "(vl), " + std::to_string( bits2moven(vtmp.ewidth) ) + ", "+ vlName +");\n";
    res.push_back(vidx_statement);
    if(vtmp.nfield != ""){
        std::string vidx_statement2 = idxName + " = __riscv_vmul_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "( " + idxName + ", " + nfield2n(vtmp.nfield) + ", "+ vlName +");\n";
        res.push_back(vidx_statement2);
    }
    res.push_back(loadOp);
    return res;
}

// Vector Indexed Load Intrinsics
// load intrinsic: vluxei, vluxseg
std::vector<std::string> CodeBlock::load_vluxei(std::string type, std::string regName, std::string loadVar, bool mask /*= false*/ ){
    std::vector<std::string> res;
    assert( startsWith(type, "vbool") == false );
    VectorType vtmp(type);
    // generate a std::vector named 'vidx' for indexes, where elements are in the range(0, min(255,dataLen-1))
    int maxValue = std::min( static_cast<int>((1<<8)-1), static_cast<int>(dataLen-1)); // range(0, min(2^8-1,dataLen-1))
    std::string idxType = genIdxType(vtmp.ratio);
    // vidxs.push_back( VIndex( idxType, maxValue ) );
    std::string idxName = VIndex( idxType, maxValue ).idxName;
    VectorType vidxtype(idxType);
    // memorys.globalLoadVars[idxName] = MemEntry(vidxtype.etype, idxName);

    std::string intrinsic; std::string suffix = genPolicySuffix(mask);
    if(vtmp.nfield == ""){
        // vluxei
        if(withOverloaded == true){
            intrinsic = "__riscv_vluxei" + std::to_string(vidxtype.ewidth);
            if(withPolicy == false) suffix = "";
        }else{
            intrinsic = "__riscv_vluxei" + std::to_string(vidxtype.ewidth) + "_v_" + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul;
        }
    }else{
        // vluxseg
        if(withOverloaded == true){
            intrinsic = "__riscv_vluxseg";  // a compiler bug
            intrinsic += vtmp.nfield.c_str()[1] + std::string("ei") +  std::to_string(vidxtype.ewidth);
            if(withPolicy == false) suffix = "";
        }else{
            intrinsic = "__riscv_vluxseg";  // a compiler bug
            intrinsic += vtmp.nfield.c_str()[1] + std::string("ei") +  std::to_string(vidxtype.ewidth) + "_v_" \
                + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul + vtmp.nfield;
        }
    }
    intrinsic += suffix;

    std::string loadOp = type + " " + regName + " = " + intrinsic + "(";
    if(mask) loadOp += maskName + ", ";
    if(withPolicy){
        // add vd
        loadOp += "vd_" + loadVar + ", ";
        std::string tmptype = std::to_string(vtmp.ewidth) + vtmp.emul;
        std::string vlmax = vsetvl_max(vtmp.ratio);
        if(vtmp.nfield == ""){
            if( startsWith(vtmp.etype, "float") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vfmv_v_f_f"+tmptype+"(0, " + vlmax + ");\n");
            else if ( startsWith(vtmp.etype, "uint") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_u"+tmptype+"(0, " + vlmax + ");\n");
            else if ( startsWith(vtmp.etype, "int") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_i"+tmptype+"(0, " + vlmax + ");\n");
            else {
                std::cerr << "unimplementation error: unknown type" << std::endl;
                exit(1);
            }
        }else{
            int n = std::stoi( nfield2n(vtmp.nfield) );
            std::string create_vd;
            std::string para;
            if( startsWith(vtmp.etype, "float") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_f"+tmptype+vtmp.nfield;
                para = "__riscv_vfmv_v_f_f"+tmptype+"(0, " + vlmax + ")";
            }else if ( startsWith(vtmp.etype, "uint") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_u"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_u"+tmptype+"(0, " + vlmax + ")";
            }else if ( startsWith(vtmp.etype, "int") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_i"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_i"+tmptype+"(0, " + vlmax + ")";
            }else {
                std::cerr << "unimplementation error: unknown type" << std::endl;
                exit(1);
            }
            create_vd += "(";
            for(int x=0; x<n-1; ++x){
                create_vd += para + ", ";
            }
            create_vd += para + ");\n";
            res.push_back(create_vd);
        }
    }
    loadOp += "&arr_" + loadVar + "[ptr], " + idxName + ", " + vlName + ");\n";

    // res.push_back(vidx_byte_statement);
    std::string vidx_statement = idxType + " " + idxName + " = __riscv_vsll_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(__riscv_vid_v_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + "(vl), " + std::to_string( bits2moven(vtmp.ewidth) ) + ", "+ vlName +");\n";
    res.push_back(vidx_statement);
    if(vtmp.nfield != ""){
        std::string vidx_statement2 = idxName + " = __riscv_vmul_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "( " + idxName + ", " + nfield2n(vtmp.nfield) + ", "+ vlName +");\n";
        res.push_back(vidx_statement2);
    } 
    res.push_back(loadOp);
    return res;
}

// Vector Indexed Store Intrinsics
// load intrinsic: vsoxei, vsoxseg
std::vector<std::string> CodeBlock::store_vsoxei(std::string type, std::string regName, bool mask /*= false*/){
    std::vector<std::string> res;
    assert( startsWith(type, "vbool") == false );
    VectorType vtmp(type);
    // generate a std::vector named 'vidx' for indexes, where elements are in the range(0, min(255,dataLen-1))
    int maxValue = std::min( static_cast<int>((1<<8)-1), static_cast<int>(dataLen-1)); // range(0, min(2^8-1,dataLen-1))
    std::string idxType = genIdxType(vtmp.ratio);
    VIndex anindex = VIndex( idxType, maxValue, true );
    // vidxs.push_back( anindex );
    std::string idxName = VIndex( idxType, maxValue ).idxName;
    VectorType vidxtype(idxType);
    // memorys.globalLoadVars[idxName] = MemEntry(vidxtype.etype, idxName);

    std::string intrinsic; std::string suffix = genPolicySuffix(mask, false);
    if(vtmp.nfield == ""){
        // vsoxei
        if(withOverloaded == true && withPolicy == false){
            intrinsic = "__riscv_vsoxei" + std::to_string(vidxtype.ewidth);
            suffix = "";
        }else{
            intrinsic = "__riscv_vsoxei" + std::to_string(vidxtype.ewidth) + "_v_" + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul;
        }
    }else {
        // vsoxseg
        if(withOverloaded == true && withPolicy == false){
            intrinsic = "__riscv_vsoxseg";
            intrinsic += vtmp.nfield.c_str()[1] + std::string("ei") + std::to_string(vidxtype.ewidth);
            suffix = "";
        }else{
            intrinsic = "__riscv_vsoxseg";
            intrinsic += vtmp.nfield.c_str()[1] + std::string("ei") + std::to_string(vidxtype.ewidth) + "_v_" \
                + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul + vtmp.nfield;
        }
    }
    intrinsic += suffix;

    std::string storeOp = intrinsic + "(";
    if(mask) storeOp += maskName + ", ";
    std::string storeVar = newStoreVar(regName); 
    memorys.storevar_link_final_vidx[ storeVar ] = idxName;
    storeOp += "&arr_" + storeVar + "[ptr], " + idxName + ", " + regName + ", " + vlName + ");\n";

    //res.push_back(vidx_byte_statement);
    std::string vidx_statement = idxType + " " + idxName + " = __riscv_vsll_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(__riscv_vid_v_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + "(vl), " + std::to_string( bits2moven(vtmp.ewidth) ) + ", "+ vlName +");\n";
    res.push_back(vidx_statement);
    if(vtmp.nfield != ""){
        std::string vidx_statement2 = idxName + " = __riscv_vmul_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "( " + idxName + ", " + nfield2n(vtmp.nfield) + ", "+ vlName +");\n";
        res.push_back(vidx_statement2);
    }
    res.push_back(storeOp);
    return res;
}

// Vector Indexed Store Intrinsics
// load intrinsic: vsuxei, vsuxseg
// don't have a policy variant.
std::vector<std::string> CodeBlock::store_vsuxei(std::string type, std::string regName, bool mask /*= false*/){
    std::vector<std::string> res;
    assert( startsWith(type, "vbool") == false );
    VectorType vtmp(type);
    // generate a std::vector named 'vidx' for indexes, where elements are in the range(0, min(255,dataLen-1))
    int maxValue = std::min( static_cast<int>((1<<8)-1), static_cast<int>(dataLen-1)); // range(0, min(2^8-1,dataLen-1))
    std::string idxType = genIdxType(vtmp.ratio);
    VIndex anindex = VIndex( idxType, maxValue, true );
    // vidxs.push_back( anindex );
    std::string idxName = VIndex( idxType, maxValue ).idxName;
    VectorType vidxtype(idxType);
    // memorys.globalLoadVars[idxName] = MemEntry(vidxtype.etype, idxName);

    std::string intrinsic; std::string suffix = genPolicySuffix(mask, false);
    if(vtmp.nfield == ""){
        // vsuxei
        if(withOverloaded == true && withPolicy == false){
            intrinsic = "__riscv_vsuxei" + std::to_string(vidxtype.ewidth);
            suffix = "";
        }else{
            intrinsic = "__riscv_vsuxei" + std::to_string(vidxtype.ewidth) + "_v_" + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul;
        }
    }else{
        // vsuxseg
        std::string ei = std::string("ei");
        if(withOverloaded == true && withPolicy == false){
            intrinsic = "__riscv_vsuxseg";
            intrinsic += vtmp.nfield.c_str()[1] + ei + std::to_string(vidxtype.ewidth);
            suffix = "";
        }else{
            intrinsic = "__riscv_vsuxseg";
            intrinsic += vtmp.nfield.c_str()[1] + ei + std::to_string(vidxtype.ewidth) + "_v_" \
            + vtmp.etype.c_str()[0] + std::to_string(vtmp.ewidth) + vtmp.emul + vtmp.nfield;
        }
    }
    intrinsic += suffix;

    std::string storeOp = intrinsic + "(";
    if(mask) storeOp += maskName + ", ";
    std::string storeVar = newStoreVar(regName); 

    memorys.storevar_link_final_vidx[ storeVar ] = idxName;
    storeOp += "&arr_" + storeVar + "[ptr], " + idxName + ", " + regName + ", " + vlName + ");\n";

    //res.push_back(vidx_byte_statement);
    std::string vidx_statement = idxType + " " + idxName + " = __riscv_vsll_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(__riscv_vid_v_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + "(vl), " + std::to_string( bits2moven(vtmp.ewidth) ) + ", "+ vlName +");\n";
    res.push_back(vidx_statement);
    if(vtmp.nfield != ""){
        std::string vidx_statement2 = idxName + " = __riscv_vmul_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "( " + idxName + ", " + nfield2n(vtmp.nfield) + ", "+ vlName +");\n";
        res.push_back(vidx_statement2);
    }
    res.push_back(storeOp);
    return res;
}