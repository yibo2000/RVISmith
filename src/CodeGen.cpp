#include <regex>
#include <functional>
#include <list>
#include "CodeGen.hpp"

int VIndex::number = 0;

unsigned int indentNum = 0; // indent
unsigned int blockNum = 0; // block name
unsigned int loopNum = 0; // for loop
unsigned int tmpNum = 0;

unsigned int memLoadNum = 0; // for load
unsigned int memStoreNum = 0; // for store
std::set <std::string> blockNames;

inline std::string newLoadVar() { return "load_" + std::to_string(memLoadNum++); }
// inline std::string newStoreVar() { return "mem_store_" + std::to_string(memStoreNum++); }
inline std::string newStoreVar(std::string regName) { return "store_" + regName; }

void emitHeader(std::ostream &os) {
    // headers
    os << "// --seed 0x" << hex << InitialSeed << " --data_length " << dec << dataLen 
    << " --sequence_length " << seqLen << " --root " << connect_type;
    if(ifSegment) os << " --segment ";
    if(withPolicy) os << " --policy ";
    if(withOverloaded) os << " --overloaded ";
    os << std::endl;
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
    os << "typedef double float64_t;\n";
    os << "\n";
    // used functions, inline have bugs when -O0
    os << "float16_t convert_binary_u16_f16(uint16_t u16){\n"
        "  union { float16_t f16; uint16_t u16; } converter;\n"
        "  converter.u16 = u16;\n"
        "  if(isNaNF16UI(converter.u16)) return 0;\n"
        "  return converter.f16;\n}\n";
    os << "float32_t convert_binary_u32_f32(uint32_t u32){\n"
        "  union { float32_t f32; uint32_t u32; } converter;\n"
        "  converter.u32 = u32;\n"
        "  if(isNaNF32UI(converter.u32)) return 0;\n"
        "  return converter.f32;\n}\n";
    os << "float64_t convert_binary_u64_f64(uint64_t u64){\n"
        "  union { float64_t f64; uint64_t u64; } converter;\n"
        "  converter.u64 = u64;\n"
        "  if(isNaNF64UI(converter.u64)) return 0;\n"
        "  return converter.f64;\n}\n";
    os << "uint16_t convert_binary_f16_u16(float16_t f16){\n"
	    "  union { float16_t f16; uint16_t u16; } converter;\n"
	    "  converter.f16 = f16;\n"
        "  if(isNaNF16UI(converter.u16)) return -1;"
	    "  return converter.u16;\n}\n";
    os << "uint32_t convert_binary_f32_u32(float32_t f32){\n"
	    "  union { float32_t f32; uint32_t u32; } converter;\n"
	    "  converter.f32 = f32;\n"
        "  if(isNaNF32UI(converter.u32)) return -1;"
	    "  return converter.u32;\n}\n";
    os << "uint64_t convert_binary_f64_u64(float64_t f64){\n"
	    "  union { float64_t f64; uint64_t u64; } converter;\n"
	    "  converter.f64 = f64;\n"
        "  if(isNaNF64UI(converter.u64)) return -1;"
	    "  return converter.u64;\n}\n\n";
}

// code generation of main function
void MainBlock::codegen(std::ostream &os){
    indentNum = 0;
    os << "int main(){\n";

    indentNum ++;
    os << getIndent() + "initialize();\n";
    for( auto block: blockNames){
        os << getIndent() + block + "();\n";
    }
    os << getIndent() + "printInfo();\n";
    os << getIndent() + "return 0;\n";
    indentNum --;
    os << "}\n" << std::endl;
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
    os << "int8_t data_mask[dataLen];\n";
    // vidx
    /*
    for(auto vidx: vidxs){
        VectorType vidxtype = *dynamic_cast<VectorType *>(UsedTypes.getPtr(std::move(vidx.idxType)));
        os << "uint" + std::to_string(vidxtype.ewidth) + "_t data_"+vidx.idxName+"[dataLen];\n";
    }
    */
    for(auto& pair: memorys.globalLoadVars){
        os << pair.second.getMemDef();
    }
    for(auto& pair: memorys.globalStoreVars){
        os << pair.second.getMemDef();
    }
    os << std::endl;

    // initialize
    os << "void initialize(){\n"; indentNum++;
    // initialize of mask
    os << getIndent() + "int8_t tmp_mask[dataLen] = {";
    for ( int i=0; i<dataLen; ++i) {
        if(vmask[i] == false) os << "0, "; 
        else os << "1, "; 
    }
    os << "};\n";
    os << getIndent() + "for (int i = 0; i < dataLen; ++i) { data_mask[i] = tmp_mask[i]; }\n";

    // initialize of vidx (for indexed load and store intrinsics)
    /*
    for(auto vidx: vidxs){
        VectorType vidxtype = *dynamic_cast<VectorType *>(UsedTypes.getPtr(std::move(vidx.idxType)));
        os << getIndent() + "uint" + std::to_string(vidxtype.ewidth) + "_t tmp_"+vidx.idxName+"[dataLen] = {";
        for ( int i=0; i<dataLen; ++i) { os << std::to_string( vidx.vals[i] ) + ", "; }
        os << "};\n";
        os << getIndent() + "for (int i = 0; i < dataLen; ++i) { data_"+vidx.idxName+"[i] = tmp_"+vidx.idxName+"[i]; }\n";
    }
    */

    // initialize of other value
    int tmp = 0;
    for(auto pair: memorys.globalLoadVars){
        std::string elementType = pair.second.elementType;
        std::string memName = pair.second.memName;
        assert( startsWith(elementType, "bool") == 0);
        if ( startsWith(elementType, "int") || startsWith(elementType, "uint") ){
            // int or uint
            os << getIndent() + elementType + " tmp_" + std::to_string(tmp) + "[dataLen] = {";
            if( pair.second.valueIsBool == true ) elementType = "bool";
            if( pair.second.valueIsBool == true && pair.second.allValueIsTrue == true) {
                for ( int i=0; i<dataLen; ++i) { os << "1, "; } // for vcompress vs1
            }else{
                for ( int i=0; i<dataLen; ++i) { os << pair.second.initValues[i] + ", "; }
            }
            os << "};\n";
            os << getIndent() + "for (int i = 0; i < dataLen; ++i) { data_" + memName + "[i] = tmp_" + std::to_string(tmp++) + "[i]; }\n";
        } else if ( startsWith(elementType, "float") ){
            // float
            int width = 0;
            if ( elementType == "float16_t" ) width = 16;
            else if ( elementType == "float32_t" ) width = 32;
            else if ( elementType == "float64_t" ) width = 64;
            assert ( width != 0);

            os << getIndent() + "uint" + std::to_string(width) + "_t tmp_" + std::to_string(tmp) + "[dataLen] = {";
            for ( int i=0; i<dataLen; ++i) { os << pair.second.initValues[i] + ", "; }
            os << "};\n";
            if (width == 16) 
                os << getIndent() + "for (int i = 0; i < dataLen; ++i) { data_" + memName + "[i] = convert_binary_u16_f16(tmp_" + std::to_string(tmp++) + "[i]); }\n";
            else if (width == 32) 
                os << getIndent() + "for (int i = 0; i < dataLen; ++i) { data_" + memName + "[i] = convert_binary_u32_f32(tmp_" + std::to_string(tmp++) + "[i]); }\n";
            else if (width == 64)
                os << getIndent() + "for (int i = 0; i < dataLen; ++i) { data_" + memName + "[i] = convert_binary_u64_f64(tmp_" + std::to_string(tmp++) + "[i]); }\n";
        }
    }
    for(auto pair: memorys.globalStoreVars){
        std::string elementType = pair.second.elementType;
        std::string memName = pair.second.memName;
        os << getIndent() + "for (int i = 0; i < dataLen; ++i) { data_" + memName + "[i] = 0; }\n";
    }
    indentNum--; os << "}\n";
    os << std::endl;
}

// loop generation
void CodeBlock::genLoopPrefix(std::ostream &os){
    avl = "avl" + std::to_string(loopNum++);
    if(hasNfieldOp){
        os << getIndent() + "int " + avl + " = " + std::to_string(dataLen) \
        << " - " << std::to_string(dataLen) << " % " << nfield2n(OpDefs.UnifiedNfield) + ";\n"; // loop var
    }else{
        os << getIndent() + "int " + avl + " = dataLen;\n"; // loop var
    }

    os << getIndent() + "int8_t* ptr_mask = data_mask;\n"; // mask
    /*
    for(auto vidx: vidxs){
        VectorType vidxtype = *dynamic_cast<VectorType *>(UsedTypes.getPtr(std::move(vidx.idxType)));
        os << getIndent() + vidxtype.etype +"* ptr_"+vidx.idxName+" = data_"+vidx.idxName+";\n"; // vidx
    }*/
    for(auto& pair: memorys.globalLoadVars){
        os << getIndent() + pair.second.getLoopPrefix();
    }
    for(auto& pair: memorys.globalStoreVars){
        os << getIndent() + pair.second.getLoopPrefix();
    }

    if(hasNfieldOp) { 
        os << getIndent() + \
        "for (size_t " + vlName + "; " << avl << " > 0; " << avl << " -= " + vlName + " * " + nfield2n(OpDefs.UnifiedNfield) + "){\n"; 
        indentNum++;
        os << getIndent() + vsetvl( VectorType(connect_type).ewidth, VectorType(connect_type).emul, avl + " / " + nfield2n(OpDefs.UnifiedNfield));
    } else { 
        os << getIndent() + "for (size_t " + vlName + "; " << avl << " > 0; " << avl << " -= " + vlName + "){\n"; 
        indentNum++;
        os << getIndent() + vsetvl( VectorType(connect_type).ewidth, VectorType(connect_type).emul, avl );
    }
}

void CodeBlock::genLoopSuffix(std::ostream &os){
    /*
    if(hasNfieldOp){
        os << getIndent() + "ptr_mask += "+ vlName + " * " + nfield2n(OpDefs.UnifiedNfield) + ";\n";
    }else{
        os << getIndent() + "ptr_mask += " +vlName+ ";\n";
    }
    */
    os << getIndent() + "ptr_mask += " +vlName+ ";\n";
    /*
    for(auto& vidx: vidxs){
        VectorType vidxtype = *dynamic_cast<VectorType *>(UsedTypes.getPtr(std::move(vidx.idxType)));
        if(hasNfieldOp) { os << getIndent() + "ptr_" + vidx.idxName + " += "+ vlName + " * " + nfield2n(OpDefs.UnifiedNfield) + ";\n"; }
        else { os << getIndent() + "ptr_" + vidx.idxName + " += "+ vlName +";\n"; }
    }
    */
    for(auto& pair: memorys.globalLoadVars){
        // os << getIndent() + pair.second.getLoopSuffix();
        if(hasNfieldOp) { os << getIndent() + "ptr_" + pair.second.memName + " += "+ vlName + " * " + nfield2n(OpDefs.UnifiedNfield) + ";\n"; }
        else { os << getIndent() + "ptr_" + pair.second.memName + " += "+ vlName +";\n"; }
    }
    for(auto& pair: memorys.globalStoreVars){
        // os << getIndent() + pair.second.getLoopSuffix();
        if(pair.second.stateIsMask == false) { os << getIndent() + "ptr_" + pair.second.memName + " += "+ vlName + " * " + nfield2n(OpDefs.UnifiedNfield) + ";\n"; }
        else { os << getIndent() + "ptr_" + pair.second.memName + " += "+ vlName +";\n"; }
        // if(hasNfieldOp) { os << getIndent() + "ptr_" + pair.second.memName + " += "+ vlName + " * " + nfield2n(OpDefs.UnifiedNfield) + ";\n"; }
    }
    indentNum--;
    os << getIndent() + "}\n"; // end of loop
    indentNum--;
    os << getIndent() + "}\n\n"; // end of function
}

void CodeBlock::genLoopMask(std::ostream &os){
    int ratio = VectorType(connect_type).ratio;
    std::string tmptype = "";
    if(ratio == 64) tmptype = "8mf8";
    else if(ratio == 32) tmptype = "8mf4";
    else if(ratio == 16) tmptype = "8mf2";
    else if(ratio == 8) tmptype = "8m1";
    else if(ratio == 4) tmptype = "8m2";
    else if(ratio == 2) tmptype = "8m4";
    else if(ratio == 1) tmptype = "8m8";
    assert(tmptype != "");
    // load
    os << getIndent() + "vint"+tmptype+"_t mask_value= __riscv_vle8_v_i"+tmptype+"(ptr_mask, "+vlName+");\n";
    // get mask
    os << getIndent() + "vbool"+std::to_string(ratio)+"_t "+maskName+"= __riscv_vmseq_vx_i"+tmptype+"_b"+std::to_string(ratio)+"(mask_value, 1, "+vlName+");\n"; 
}

// // print the memory for differential testing
void CodeBlock::genPrint(std::ostream &os){
    indentNum = 0;
    os << "void printInfo(){\n";
    indentNum ++ ;
    // load
    // removed

    // store
    for ( auto& pair: memorys.globalStoreVars){
        if(pair.second.notNeedStore == true) continue;

        int width = 0;
        std::string elementType = pair.second.elementType;
        std::string memName = pair.second.memName;
        smatch matches;
        std::regex type_format("[a-z]+([0-9]+)_t");
        if( regex_search(elementType, matches, type_format) ){
            width = static_cast<int>( stoi(matches[1]) );
        }
        assert (width != 0);

        // for index store intrinsics
        std::string converted;
        if( memorys.storevar_link_final_vidx.find( memName ) == memorys.storevar_link_final_vidx.end() ) {
            converted = "data_" + memName + "[i]";
        }else{
            // for index store intrinsics
            converted = "data_" + memName + "[i]";
        }

        if( startsWith(elementType, "float") ) converted = "convert_binary_f" + std::to_string(width) + "_u" + std::to_string(width) + "(" + converted + ")";

        if( pair.second.stateIsMask == false ){
            os << getIndent() + "int8_t valid_" + memName + "[dataLen] = {";
            for ( int i=0; i<dataLen; ++i) {
                if(pair.second.state[i] == false) os << "0, "; 
                else os << "1, "; 
            }
            os << "};\n";
        }
        std::string length = pair.second.onlyZeroValid ? "1" : "dataLen";
        if(width == 64) {
            if( pair.second.stateIsMask == false )
                os << getIndent() + "for(int i=0; i<" + length + "; ++i) { if(valid_" + memName + "[i]) __builtin_printf(\"%lx \", " + converted + "); else __builtin_printf(\"* \"); } ";
            else
                os << getIndent() + "for(int i=0; i<" + length + "; ++i) { if(data_mask[i]) __builtin_printf(\"%lx \", " + converted + "); else __builtin_printf(\"* \"); } ";
        } else {
            if( pair.second.stateIsMask == false )
                os << getIndent() + "for(int i=0; i<" + length + "; ++i) { if(valid_" + memName + "[i]) __builtin_printf(\"%x \", " + converted + "); else __builtin_printf(\"* \"); } ";
            else
                os << getIndent() + "for(int i=0; i<" + length + "; ++i) { if(data_mask[i]) __builtin_printf(\"%x \", " + converted + "); else __builtin_printf(\"* \"); } ";
        }
        os << "__builtin_printf(\"\\n\");\n";
    }
    os << "}\n\n";
}

// std::vector register allocate
void CodeBlock::vregAllocateRandom(std::vector<BaseOperator > & Ops){
    for(int i = 0; i<Ops.size(); i++){
        for(auto & para: Ops[i].paras){
            Type etype = para.enumType(std::move(UsedTypes));
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
        Type retEtype = Ops[i].enumRetype(std::move(UsedTypes));
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
        if(Ops[i].nfield != "" && ifSegment) {
            hasNfieldOp = true;
        }
    }
}

// insert load-store intrinsics to sequence after register allocation
void CodeBlock::insertLoadAndStoreIntrinsics(std::vector<BaseOperator > & Ops) {
    size_t OpNum = Ops.size();
    for(int i=0; i<Ops.size(); i++){
        std::vector<std::string> prefix, suffix;
        // get load intrinsics
        for (auto & para: Ops[i].paras){
            if(para.pvreg != nullptr){
                if( para.pvreg->declared == false){
                    std::vector<std::string> load; // a load intrinsic is needed
                    if( startsWith(para.getPtype(), "vbool") ){ 
                        // all value is non-agnostic
                        if( startsWith( Ops[i].getName(), "__riscv_vcompress" ) == true \
                        && endsWith( Ops[i].getName(), "_tu" ) == false \
                        && (para.getPname() == "vs1" || para.getPname() == "mask") ){
                            load = load_bool( para.getPtype(), para.pvreg->getRegName(), true ); 
                        }else{
                            load = load_bool( para.getPtype(), para.pvreg->getRegName() ); 
                        }
                    } else { 
                        // random select load intrinsics
                        std::function<std::vector<std::string>(std::string, std::string, bool)> func_load;
                        int tmprandom = getRandomNumber<int>(0, 100) % 5;
                        if(tmprandom == 0 || Ops[i].commonRatio == 0) {
                            func_load = std::bind(&CodeBlock::load_vle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                        }else if (tmprandom == 1){
                            func_load = std::bind(&CodeBlock::load_vlse, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                        }else if (tmprandom == 2){
                            func_load = std::bind(&CodeBlock::load_vloxei, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                        }else if (tmprandom == 3){
                            func_load = std::bind(&CodeBlock::load_vluxei, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                        }else{
                            //default and tmp random == 4
                            func_load = std::bind(&CodeBlock::load_vle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                        }
                        // load = func_load( para.getPtype(), para.pvreg->getRegName(), false ); 
                        if( Ops[i].commonRatio > 0 ){
                            bool ifmask = (getRandomNumber<int>(0,99)%3 == 0); // mask : unmask = 1 : 2
                            load = func_load( para.getPtype(), para.pvreg->getRegName(), ifmask && (!Ops[i].ifWithoutMaskIntrin()) ); 
                        } else {
                            load = func_load( para.getPtype(), para.pvreg->getRegName(), false ); // always unmask
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
            string vs1reg = "";
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
        OpInstruction.push_back( Ops[i].codegen(std::move(UsedTypes)) );
        
        // get store intrinsics
        if( Ops[i].retvreg != nullptr ){
            std::vector<std::string> store;
            if( startsWith(Ops[i].getRetype(), "vbool") ) { store = store_bool( Ops[i].getRetype(), Ops[i].retvreg->getRegName() ); }
            else { 
                // random select store intrinsics
                std::function<std::vector<std::string>(std::string, std::string, bool, bool)> func_store;
                int tmprandom = getRandomNumber<int>(0, 100) % 5;
                if(tmprandom == 0 || Ops[i].commonRatio == 0) {
                    func_store = std::bind(&CodeBlock::store_vse, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
                }else if (tmprandom == 1){
                    func_store = std::bind(&CodeBlock::store_vsse, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
                }else if (tmprandom == 2){
                    func_store = std::bind(&CodeBlock::store_vsoxei, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
                }else if (tmprandom == 3){
                    func_store = std::bind(&CodeBlock::store_vsuxei, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
                }else{
                    //default and tmp random == 4
                    func_store = std::bind(&CodeBlock::store_vse, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
                }
                if( Ops[i].commonRatio > 0 ){
                    bool ifmask = (getRandomNumber<int>(0,99)%3 == 0); // mask : unmask = 1 : 2
                    store = func_store( Ops[i].getRetype(), Ops[i].retvreg->getRegName(), ifmask && (!Ops[i].ifWithoutMaskIntrin()), Ops[i].ifTailProducer() );
                    // store = store_vse( Ops[i].getRetype(), Ops[i].retvreg->getRegName(), ifmask && (!Ops[i].ifWithoutMaskIntrin()), Ops[i].ifTailProducer() );
                } else {
                    store = func_store( Ops[i].getRetype(), Ops[i].retvreg->getRegName(), false, Ops[i].ifTailProducer() ); // always unmask
                    // store = store_vse( Ops[i].getRetype(), Ops[i].retvreg->getRegName(), false, Ops[i].ifTailProducer() ); // always unmask
                }
                // vreinterpret always encounter undefined behaviours
                //if( startsWith(Ops[i].getName(), "__riscv_vreinterpret") || \
                //startsWith(Ops[i].getName(), "__riscv_vlmul") || startsWith(Ops[i].getName(), "__riscv_vreinterpret") ){
                if( Ops[i].alwaysAgnostic() == true ){
                    store.clear();
                    std::string storeVar = newStoreVar(Ops[i].retvreg->getRegName());
                    memorys.globalStoreVars[storeVar].notNeedStore = true;
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
                                std::vector<std::string> && OpInstruction, unsigned int length){
    std::vector<std::string> res;
    for(int i=0; i<length; ++i){
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
                                std::vector<std::string> && OpInstruction, unsigned int length){
    std::vector<std::string> res;
    // load
    for(int i=0; i<length; ++i){
        for(auto it = PrefixOp[i].begin(); it != PrefixOp[i].end(); it++){
            res.push_back(*it);
        }
    }
    // operation
    for(int i=0; i<length; ++i) res.push_back( OpInstruction[i] );
    // store
    for(int i=0; i<length; ++i) { 
        for(auto it = SuffixOp[i].begin(); it != SuffixOp[i].end(); it++){
            res.push_back(*it);
        }
    }
    return res;
}

// instruction scheduling randomly
std::vector<std::string> scheduling_random( std::vector<std::vector<std::string>> && PrefixOp, std::vector<std::vector<std::string>> && SuffixOp,  
                                std::vector<std::string> && OpInstruction, unsigned int length){
    
    list<std::string> intrinsics; // list for insert
    list<std::string>::iterator ptr_start;
    list<std::string>::iterator ptr_end;
    list<std::string>::iterator ptr_lastop = intrinsics.begin();

    for(int i=0; i<length; ++i){
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

// set vl
std::string CodeBlock::vsetvl(int ewidth, std::string emul, std::string avl){
    if(ewidth < 8){
        // vbool1_t vbool2_t vbool4_t
        switch (ewidth){
        case 1: // vbool1_t
            return this->vlName + " = __riscv_vsetvl_e8m8(" + avl + ");\n";
            break;
        case 2: // vbool2_t
            return this->vlName + " = __riscv_vsetvl_e16m8(" + avl + ");\n";
            break;
        case 4: // vbool4_t
            return this->vlName + " = __riscv_vsetvl_e32m8(" + avl + ");\n";
            break;
        default:
            break;
        }
    }
    return /*"size_t " + */ this->vlName + 
        " = __riscv_vsetvl_e" + std::to_string(ewidth) + emul + "(" + avl + ");\n";
}
std::string CodeBlock::vsetvlmax(int ewidth, std::string emul, std::string avl){
    if(ewidth < 8){
        // vbool1_t vbool2_t vbool4_t
        switch (ewidth){
        case 1: // vbool1_t
            return this->vlName + " = __riscv_vsetvlmax_e8m8(" + avl + ");\n";
            break;
        case 2: // vbool2_t
            return this->vlName + " = __riscv_vsetvlmax_e16m8(" + avl + ");\n";
            break;
        case 4: // vbool4_t
            return this->vlName + " = __riscv_vsetvlmax_e32m8(" + avl + ");\n";
            break;
        default:
            break;
        }
    }
    return /*"size_t " + */ this->vlName + 
        " = __riscv_vsetvlmax_e" + std::to_string(ewidth) + emul + "(" + avl + ");\n";
}

// load bool
std::vector<std::string> CodeBlock::load_bool(std::string type, std::string regName, bool allValueIsTrue /* = false*/){
    assert( startsWith(type, "vbool") == true );
    std::vector<std::string> res;
    VectorType vtmp(type);
    int ratio = vtmp.ratio;

    std::string tmptype = "";
    if(ratio == 64) tmptype = "8mf8";
    else if(ratio == 32) tmptype = "8mf4";
    else if(ratio == 16) tmptype = "8mf2";
    else if(ratio == 8) tmptype = "8m1";
    else if(ratio == 4) tmptype = "8m2";
    else if(ratio == 2) tmptype = "8m4";
    else if(ratio == 1) tmptype = "8m8";
    assert(tmptype != "");

    std::string loadVar = newLoadVar(); 
    // globalLoadVars.insert( Parameter( "int8_t", loadVar) );
    memorys.globalLoadVars[loadVar] = MemEntry("int8_t", loadVar);
    memorys.globalLoadVars[loadVar].valueIsBool = true;
    if(allValueIsTrue){
        // for vcompress vs1
        memorys.globalLoadVars[loadVar].allValueIsTrue = true;
    }
    memorys.globalLoadVars[loadVar].setInitValues();
    // load: {ptr_load_var} to {vload_tmp_i}
    std::string loadOp = "vint"+tmptype+"_t vload_tmp_" + std::to_string(tmpNum);
    loadOp += " = __riscv_vle8_v_i" + tmptype + "(ptr_" + loadVar + ", " + vlName + ");\n";
    res.push_back(loadOp);
    // vbool_t {regName} = vmseq ( {vload_tmp_i} )
    std::string vmseqOp = "vbool"+std::to_string(ratio)+"_t "+regName;
    vmseqOp += " = __riscv_vmseq_vx_i"+tmptype+"_b"+std::to_string(ratio)+"(vload_tmp_" + std::to_string(tmpNum++) + ", 1, "+vlName+");\n";
    res.push_back(vmseqOp);
    return res; 
}

// store bool
std::vector<std::string> CodeBlock::store_bool(std::string type, std::string regName){
    assert( startsWith(type, "vbool") == true );
    std::vector<std::string> res;
    VectorType vtmp(type);
    int ratio = vtmp.ratio;

    std::string tmptype = "";
    if(ratio == 64) tmptype = "8mf8";
    else if(ratio == 32) tmptype = "8mf4";
    else if(ratio == 16) tmptype = "8mf2";
    else if(ratio == 8) tmptype = "8m1";
    else if(ratio == 4) tmptype = "8m2";
    else if(ratio == 2) tmptype = "8m4";
    else if(ratio == 1) tmptype = "8m8";
    assert(tmptype != "");

    std::string storeVar = newStoreVar(regName); // globalStoreVars.insert( Parameter( "int8_t", storeVar) );
    memorys.globalStoreVars[storeVar] = MemEntry("int8_t", storeVar);
    memorys.globalStoreVars[storeVar].setState(vmask);
    /*
    vint8mf2_t zero = vmv_v_x_i8mf2(0, __riscv_vsetvlmax_e8mf2());
    vint8mf2_t vec_store = __riscv_vmerge_vxm_i8mf2(zero, 1, vec_value_4_0, vl);
    vse8_v_i8mf2(placeholder4, vec_store, vl);
    */
    res.push_back("vint"+tmptype+"_t zero_"+std::to_string(tmpNum)+" = __riscv_vmv_v_x_i"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"());\n");
    res.push_back("vint"+tmptype+"_t vstore_tmp_"+std::to_string(tmpNum)+" = __riscv_vmerge_vxm_i"+tmptype+"(zero_"+std::to_string(tmpNum) +", 1, "+ regName +", "+vlName+");\n");
    res.push_back("__riscv_vse8_v_i"+tmptype+"(ptr_"+storeVar+", vstore_tmp_"+std::to_string(tmpNum)+", "+vlName+");\n");
    tmpNum++;
    return res; 
}

// Vector Unit-Stride Load Intrinsics
// load intrinsic: vle, vlseg
std::vector<std::string> CodeBlock::load_vle(std::string type, std::string regName, bool mask /*= false*/ ){
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
    std::string loadVar = newLoadVar(); // globalLoadVars.insert( Parameter( vtmp.etype, loadVar) );
    memorys.globalLoadVars[loadVar] = MemEntry(vtmp.etype, loadVar);
    memorys.globalLoadVars[loadVar].setInitValues();
    if(withPolicy){
        // add vd
        loadOp += "vd_" + loadVar + ", ";
        std::string tmptype = std::to_string(vtmp.ewidth) + vtmp.emul;
        if(vtmp.nfield == ""){
            if( startsWith(vtmp.etype, "float") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vfmv_v_f_f"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"());\n");
            else if ( startsWith(vtmp.etype, "uint") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_u"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"());\n");
            else if ( startsWith(vtmp.etype, "int") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_i"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"());\n");
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
                para = "__riscv_vfmv_v_f_f"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"())";
            }else if ( startsWith(vtmp.etype, "uint") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_u"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_u"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"())";
            }else if ( startsWith(vtmp.etype, "int") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_i"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_i"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"())";
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
    loadOp += "ptr_" + loadVar + ", " + vlName + ");\n";

    res.push_back(loadOp);
    return res;
}

// Vector Unit-Stride Store Intrinsics
// store intrinsic: vse, vsseg
// don't have policy variants
std::vector<std::string> CodeBlock::store_vse(std::string type, std::string regName, bool mask /*= false*/, bool onlyzero /*= false*/){
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
    memorys.globalStoreVars[storeVar] = MemEntry(vtmp.etype, storeVar);
    if(vtmp.nfield != "") memorys.globalStoreVars[storeVar].updateNfieldState(vmask, vtmp.nfield);
    else memorys.globalStoreVars[storeVar].setState(vmask);
    if(onlyzero){
        memorys.globalStoreVars[storeVar].onlyZeroValid = true;
        for(int i=0;i<dataLen;++i){
            if(i==0) memorys.globalStoreVars[storeVar].state[i] = true;
            else memorys.globalStoreVars[storeVar].state[i] = false;
        }
    }
    storeOp += "ptr_" + storeVar + ", " + regName + ", " + vlName + ");\n";

    res.push_back(storeOp);
    return res;
}


// Vector Strided Load Intrinsics
// load intrinsic: vlse, vlsseg
std::vector<std::string> CodeBlock::load_vlse(std::string type, std::string regName, bool mask /*= false*/ ){
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
    std::string loadVar = newLoadVar(); // globalLoadVars.insert( Parameter( vtmp.etype, loadVar) );
    memorys.globalLoadVars[loadVar] = MemEntry(vtmp.etype, loadVar);
    memorys.globalLoadVars[loadVar].setInitValues();
    if(withPolicy){
        // add vd
        loadOp += "vd_" + loadVar + ", ";
        std::string tmptype = std::to_string(vtmp.ewidth) + vtmp.emul;
        if(vtmp.nfield == ""){
            if( startsWith(vtmp.etype, "float") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vfmv_v_f_f"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"());\n");
            else if ( startsWith(vtmp.etype, "uint") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_u"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"());\n");
            else if ( startsWith(vtmp.etype, "int") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_i"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"());\n");
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
                para = "__riscv_vfmv_v_f_f"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"())";
            }else if ( startsWith(vtmp.etype, "uint") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_u"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_u"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"())";
            }else if ( startsWith(vtmp.etype, "int") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_i"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_i"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"())";
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
        loadOp += "ptr_" + loadVar + ", " + to_string(bits2bytes(vtmp.ewidth)) + ", " + vlName + ");\n";
    }else{
        loadOp += "ptr_" + loadVar + ", " + to_string(bits2bytes(vtmp.ewidth)) + " * " + nfield2n(OpDefs.UnifiedNfield) + ", " + vlName + ");\n";
    }

    res.push_back(loadOp);
    return res;
}


// Vector Strided Store Intrinsics
// load intrinsic: vsse, vssseg
// don't have policy variants
std::vector<std::string> CodeBlock::store_vsse(std::string type, std::string regName, bool mask /*= false*/, bool onlyzero /*= false*/){
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
    memorys.globalStoreVars[storeVar] = MemEntry(vtmp.etype, storeVar);
    if(vtmp.nfield != "") memorys.globalStoreVars[storeVar].updateNfieldState(vmask, vtmp.nfield);
    else memorys.globalStoreVars[storeVar].setState(vmask);
    if(onlyzero){
        memorys.globalStoreVars[storeVar].onlyZeroValid = true;
        for(int i=0;i<dataLen;++i){
            if(i==0) memorys.globalStoreVars[storeVar].state[i] = true;
            else memorys.globalStoreVars[storeVar].state[i] = false;
        }
    }

    // one-element byte is ptrdiff_t rs2 (equal to Unit-Stride)
    if(vtmp.nfield == ""){
        storeOp += "ptr_" + storeVar + ", " + to_string(bits2bytes(vtmp.ewidth)) + ", " + regName + ", " + vlName + ");\n";
    }else{
        storeOp += "ptr_" + storeVar + ", " + to_string(bits2bytes(vtmp.ewidth)) + " * " + nfield2n(OpDefs.UnifiedNfield) + ", " + regName + ", " + vlName + ");\n";
    }

    res.push_back(storeOp);
    return res;
}


// Vector Indexed Load Intrinsics
// load intrinsic: vloxei, vloxseg
std::vector<std::string> CodeBlock::load_vloxei(std::string type, std::string regName, bool mask /*= false*/ ){
    std::vector<std::string> res;
    assert( startsWith(type, "vbool") == false );
    // VectorType vtmp(type);
    VectorType vtmp = *dynamic_cast<VectorType *>(UsedTypes.getPtr(std::move(type)));
    // generate a std::vector named 'vidx' for indexes, where elements are in the range(0, min(255,dataLen-1))
    int maxValue = min( static_cast<int>((1<<8)-1), static_cast<int>(dataLen-1)); // range(0, min(2^8-1,dataLen-1))
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
    std::string loadVar = newLoadVar(); // globalLoadVars.insert( Parameter( vtmp.etype, loadVar) );
    memorys.globalLoadVars[loadVar] = MemEntry(vtmp.etype, loadVar);
    memorys.globalLoadVars[loadVar].setInitValues();
    if(withPolicy){
        // add vd
        loadOp += "vd_" + loadVar + ", ";
        std::string tmptype = std::to_string(vtmp.ewidth) + vtmp.emul;
        if(vtmp.nfield == ""){
            if( startsWith(vtmp.etype, "float") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vfmv_v_f_f"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"());\n");
            else if ( startsWith(vtmp.etype, "uint") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_u"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"());\n");
            else if ( startsWith(vtmp.etype, "int") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_i"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"());\n");
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
                para = "__riscv_vfmv_v_f_f"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"())";
            }else if ( startsWith(vtmp.etype, "uint") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_u"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_u"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"())";
            }else if ( startsWith(vtmp.etype, "int") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_i"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_i"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"())";
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
    loadOp += "ptr_" + loadVar + ", " + idxName + ", " + vlName + ");\n";

    // std::string vidx_byte_statement = idxType + " byte_" + idxName + " = __riscv_vremu_vx_u" + \
                std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(__riscv_vle" + std::to_string(vidxtype.ewidth) + "_v_u"+std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(ptr_" + idxName + ", "+ vlName +"), (uint" + std::to_string(vidxtype.ewidth) + "_t)("+ vlName +"), "+ vlName +");\n";
    // std::string vidx_statement = idxType + " " + idxName + " = __riscv_vsll_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(byte_" + idxName + ", " + std::to_string( bits2moven(vtmp.ewidth) ) + ", "+ vlName +");\n";

    // res.push_back(vidx_byte_statement);
    std::string vidx_statement = idxType + " " + idxName + " = __riscv_vsll_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(__riscv_vid_v_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + "(vl), " + std::to_string( bits2moven(vtmp.ewidth) ) + ", "+ vlName +");\n";
    res.push_back(vidx_statement);
    if(vtmp.nfield != ""){
        std::string vidx_statement2 = idxName + " = __riscv_vmul_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "( " + idxName + ", " + nfield2n(OpDefs.UnifiedNfield) + ", "+ vlName +");\n";
        res.push_back(vidx_statement2);
    }
    res.push_back(loadOp);
    return res;
}

// Vector Indexed Load Intrinsics
// load intrinsic: vluxei, vluxseg
std::vector<std::string> CodeBlock::load_vluxei(std::string type, std::string regName, bool mask /*= false*/ ){
    std::vector<std::string> res;
    assert( startsWith(type, "vbool") == false );
    VectorType vtmp(type);
    // generate a std::vector named 'vidx' for indexes, where elements are in the range(0, min(255,dataLen-1))
    int maxValue = min( static_cast<int>((1<<8)-1), static_cast<int>(dataLen-1)); // range(0, min(2^8-1,dataLen-1))
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
    std::string loadVar = newLoadVar(); // globalLoadVars.insert( Parameter( vtmp.etype, loadVar) );
    memorys.globalLoadVars[loadVar] = MemEntry(vtmp.etype, loadVar);
    memorys.globalLoadVars[loadVar].setInitValues();
    if(withPolicy){
        // add vd
        loadOp += "vd_" + loadVar + ", ";
        std::string tmptype = std::to_string(vtmp.ewidth) + vtmp.emul;
        if(vtmp.nfield == ""){
            if( startsWith(vtmp.etype, "float") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vfmv_v_f_f"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"());\n");
            else if ( startsWith(vtmp.etype, "uint") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_u"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"());\n");
            else if ( startsWith(vtmp.etype, "int") )
                res.push_back( type + " vd_" + loadVar + " = __riscv_vmv_v_x_i"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"());\n");
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
                para = "__riscv_vfmv_v_f_f"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"())";
            }else if ( startsWith(vtmp.etype, "uint") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_u"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_u"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"())";
            }else if ( startsWith(vtmp.etype, "int") ){
                create_vd = type + " vd_" + loadVar + " = __riscv_vcreate_v_i"+tmptype+vtmp.nfield;
                para = "__riscv_vmv_v_x_i"+tmptype+"(0, __riscv_vsetvlmax_e"+tmptype+"())";
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
    loadOp += "ptr_" + loadVar + ", " + idxName + ", " + vlName + ");\n";

    //std::string vidx_byte_statement = idxType + " byte_" + idxName + " = __riscv_vremu_vx_u" + \
                std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(__riscv_vle" + std::to_string(vidxtype.ewidth) + "_v_u"+std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(ptr_" + idxName + ", "+ vlName +"), (uint" + std::to_string(vidxtype.ewidth) + "_t)("+ vlName +"), "+ vlName +");\n";
    //std::string vidx_statement = idxType + " " + idxName + " = __riscv_vsll_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(byte_" + idxName + ", " + std::to_string( bits2moven(vtmp.ewidth) ) + ", "+ vlName +");\n";

    //res.push_back(vidx_byte_statement);
    std::string vidx_statement = idxType + " " + idxName + " = __riscv_vsll_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(__riscv_vid_v_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + "(vl), " + std::to_string( bits2moven(vtmp.ewidth) ) + ", "+ vlName +");\n";
    res.push_back(vidx_statement);
    if(vtmp.nfield != ""){
        std::string vidx_statement2 = idxName + " = __riscv_vmul_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "( " + idxName + ", " + nfield2n(OpDefs.UnifiedNfield) + ", "+ vlName +");\n";
        res.push_back(vidx_statement2);
    } 
    res.push_back(loadOp);
    return res;
}

// Vector Indexed Store Intrinsics
// load intrinsic: vsoxei, vsoxseg
std::vector<std::string> CodeBlock::store_vsoxei(std::string type, std::string regName, bool mask /*= false*/, bool onlyzero /*= false*/){
    std::vector<std::string> res;
    assert( startsWith(type, "vbool") == false );
    VectorType vtmp(type);
    // generate a std::vector named 'vidx' for indexes, where elements are in the range(0, min(255,dataLen-1))
    int maxValue = min( static_cast<int>((1<<8)-1), static_cast<int>(dataLen-1)); // range(0, min(2^8-1,dataLen-1))
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
    memorys.globalStoreVars[storeVar] = MemEntry(vtmp.etype, storeVar);
    if(vtmp.nfield != "") memorys.globalStoreVars[storeVar].updateNfieldState(vmask, vtmp.nfield);
    else memorys.globalStoreVars[storeVar].setState(vmask);
    // memorys.globalStoreVars[storeVar].updateIndexedState(vmask, anindex.vals);
    // memorys.globalStoreVars[storeVar].stateIsMask = false;
    if(onlyzero){
        memorys.globalStoreVars[storeVar].onlyZeroValid = true;
        for(int i=0;i<dataLen;++i){
            if(i==0) memorys.globalStoreVars[storeVar].state[i] = true;
            else memorys.globalStoreVars[storeVar].state[i] = false;
        }
    }

    memorys.storevar_link_final_vidx[ storeVar ] = idxName;
    storeOp += "ptr_" + storeVar + ", " + idxName + ", " + regName + ", " + vlName + ");\n";

    //std::string vidx_byte_statement = idxType + " byte_" + idxName + " = __riscv_vremu_vx_u" + \
                std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(__riscv_vle" + std::to_string(vidxtype.ewidth) + "_v_u"+std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(ptr_" + idxName + ", "+ vlName +"), (uint" + std::to_string(vidxtype.ewidth) + "_t)("+ vlName +"), "+ vlName +");\n";
    //std::string vidx_statement = idxType + " " + idxName + " = __riscv_vsll_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(byte_" + idxName + ", " + std::to_string( bits2moven(vtmp.ewidth) ) + ", "+ vlName +");\n";

    //res.push_back(vidx_byte_statement);
    std::string vidx_statement = idxType + " " + idxName + " = __riscv_vsll_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(__riscv_vid_v_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + "(vl), " + std::to_string( bits2moven(vtmp.ewidth) ) + ", "+ vlName +");\n";
    res.push_back(vidx_statement);
    if(vtmp.nfield != ""){
        std::string vidx_statement2 = idxName + " = __riscv_vmul_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "( " + idxName + ", " + nfield2n(OpDefs.UnifiedNfield) + ", "+ vlName +");\n";
        res.push_back(vidx_statement2);
    }
    res.push_back(storeOp);
    return res;
}

// Vector Indexed Store Intrinsics
// load intrinsic: vsuxei, vsuxseg
// don't have a policy variant.
std::vector<std::string> CodeBlock::store_vsuxei(std::string type, std::string regName, bool mask /*= false*/, bool onlyzero /*= false*/){
    std::vector<std::string> res;
    assert( startsWith(type, "vbool") == false );
    VectorType vtmp(type);
    // generate a std::vector named 'vidx' for indexes, where elements are in the range(0, min(255,dataLen-1))
    int maxValue = min( static_cast<int>((1<<8)-1), static_cast<int>(dataLen-1)); // range(0, min(2^8-1,dataLen-1))
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
    memorys.globalStoreVars[storeVar] = MemEntry(vtmp.etype, storeVar);
    if(vtmp.nfield != "") memorys.globalStoreVars[storeVar].updateNfieldState(vmask, vtmp.nfield);
    else memorys.globalStoreVars[storeVar].setState(vmask);
    // memorys.globalStoreVars[storeVar].updateIndexedState(vmask, anindex.vals);
    // memorys.globalStoreVars[storeVar].stateIsMask = false;
    if(onlyzero){
        memorys.globalStoreVars[storeVar].onlyZeroValid = true;
        for(int i=0;i<dataLen;++i){
            if(i==0) memorys.globalStoreVars[storeVar].state[i] = true;
            else memorys.globalStoreVars[storeVar].state[i] = false;
        }
    }

    memorys.storevar_link_final_vidx[ storeVar ] = idxName;
    storeOp += "ptr_" + storeVar + ", " + idxName + ", " + regName + ", " + vlName + ");\n";

    //std::string vidx_byte_statement = idxType + " byte_" + idxName + " = __riscv_vremu_vx_u" + \
                std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(__riscv_vle" + std::to_string(vidxtype.ewidth) + "_v_u"+std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(ptr_" + idxName + ", "+ vlName +"), (uint" + std::to_string(vidxtype.ewidth) + "_t)("+ vlName +"), "+ vlName +");\n";
    //std::string vidx_statement = idxType + " " + idxName + " = __riscv_vsll_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(byte_" + idxName + ", " + std::to_string( bits2moven(vtmp.ewidth) ) + ", "+ vlName +");\n";

    //res.push_back(vidx_byte_statement);
    std::string vidx_statement = idxType + " " + idxName + " = __riscv_vsll_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(__riscv_vid_v_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + "(vl), " + std::to_string( bits2moven(vtmp.ewidth) ) + ", "+ vlName +");\n";
    res.push_back(vidx_statement);
    if(vtmp.nfield != ""){
        std::string vidx_statement2 = idxName + " = __riscv_vmul_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "( " + idxName + ", " + nfield2n(OpDefs.UnifiedNfield) + ", "+ vlName +");\n";
        res.push_back(vidx_statement2);
    }
    res.push_back(storeOp);
    return res;
}