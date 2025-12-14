#include "Operator.hpp"
#include <regex>

OpDEFS OpDefs;
int VIndex::number = 0;

void BaseOperator::OpInit(size_t pnum, const char* const raw_args[MAX_ARG_TOKENS]){
    // used when .def files are input
    nfield = UsedTypes.TypeMap[__retype__]->getNfield();
    int r = UsedTypes.TypeMap[__retype__]->getRatio();
    std::set<int> ratios;
    if(r > 0) ratios.insert(r);
    
    const char* const* it = raw_args;
    const char* const* end = raw_args + pnum * 2;
    while (it != end) {
        const char* type_str = *it; ++it;
        if (it == end) exit(1);
        const char* name_str = *it; ++it;
        Parameter para(type_str, name_str); paras.push_back( para );

        // set nfield
        std::string pNfield = para.getPtypePtr()->getNfield();
        assert( nfield == "" || pNfield == "" || pNfield == nfield );
        if(pNfield != "") nfield = pNfield;
        // set commonRatio
        int pr = UsedTypes.TypeMap[std::string(type_str)]->getRatio();
        if(pr > 0)  ratios.insert( pr );
    }
    // set commonRatio
    int tmp_ratio = 0;
    if(ratios.size() <= 0 ){ tmp_ratio = 0; // no vector type
    }else if(ratios.size() == 1 ){ tmp_ratio = *ratios.begin();
    }else if(ratios.size() > 1 ){ tmp_ratio = 0;
    }
    assert(tmp_ratio == this->commonRatio); // double check
    this->commonRatio = tmp_ratio;
}

std::string BaseOperator::getDefStr(){ 
    std::string res = __retype__ + " " + __name__ + "("; 
    for (auto it = paras.begin(); it != paras.end(); ){
        res += it->getPtype() + " " + it->getPname();
        if(++it != paras.end()) res += ", ";
    }
    res += ");";
    return res;
}

bool BaseOperator::ifUsedSegment(){
    return this->nfield != "";
}

// whether this intrinsic is reduction operation
bool BaseOperator::ifReduction(){
    if( startsWith(this->getName(), "__riscv_vred") || startsWith(this->getName(), "__riscv_vwred")
    || startsWith(this->getName(), "__riscv_vfred") || startsWith(this->getName(), "__riscv_vfwred")){
        return true;
    }
    return false;
}
bool ifReduction(const std::string& s){
    if( startsWith(s, "__riscv_vred") || startsWith(s, "__riscv_vwred")
    || startsWith(s, "__riscv_vfred") || startsWith(s, "__riscv_vfwred")){
        return true;
    }
    return false;
}

// whether this intrinsic can produce tail elements
bool BaseOperator::ifTailProducer(){
    if( endsWith(this->getName(), "_tu") || endsWith(this->getName(), "_tum") || endsWith(this->getName(), "_tumu")) return false;
    /*
    Tail producer instructions:
    vmv.s.x, vfmv.s.f,
    all reduction instructions
    */
    if( this->ifReduction() ){
        return true;
    }
    if( startsWith(this->getName(), "__riscv_vmv_s_x") || startsWith(this->getName(), "__riscv_vfmv_s_f")){
        return true;
    }
    // Reinterpret between vector boolean types and LMUL=1 (m1) vector integer types
    if( this->alwaysAgnostic() ){
        return true;
    }
    return false;
}

// whether this intrinsic should load with unmask intrinsics
bool BaseOperator::ifWithoutMaskIntrin(){
    if(this->ifTailProducer()) return true;
    if(this->ifReduction()) return true;

    if( startsWith(this->getName(), "__riscv_vcompress") ) return true;
    if( this->getName().find("slide") != std::string::npos ) return true;
    if( this->getName().find("vrgather") != std::string::npos ) return true;

    if( this->getName().find("vcpop") != std::string::npos ) return true;
    if( this->getName().find("vfirst") != std::string::npos ) return true;
    if( this->getName().find("vmsif") != std::string::npos ) return true;
    if( this->getName().find("vmsbf") != std::string::npos ) return true;
    if( this->getName().find("vmsof") != std::string::npos ) return true;
    if( this->getName().find("viota") != std::string::npos ) return true;
    return false;
}


void BaseOperator::printInfo(){ 
    std::cout << this->getDefStr() << std::endl; 
    //std::cout << this->getDefStr() << ": commonRatio=" << commonRatio << ", nfield=" << nfield << std::endl; 
}

void OpDEFS::initializeOpDefinitions(){
	// const auto& res = getOpDefinitions();
    // this->UnderTestIntrinsics = res;
    this->organize();
}

void OpDEFS::organize(){
    // this->OpIntrinsics = {};
    // this->IgnoredIntrinsics = {};

    int ratio = 0; ratio = ConnectType.getRatio();
    if( ratio <= 0 ){
        std::cerr << "Error: used type " << ConnectType.getType() << " is not a valid vector type." << std::endl;
        exit(1);
    }
    assert( ratio > 0 );

    std::vector<std::string> load_prefix = {"vle", "vlm", "vlse", "vloxei", "vluxei", "vlseg", "vlsseg", "vloxseg", "vluxseg"};
    // std::vector<std::string> ignored = {"__riscv_vlm_v_", "__riscv_vsm_v_", "ff_v_" /*Fault-Only-First Loads Intrinsics*/};
    for(auto& s: load_prefix) s = "__riscv_"+s;

    //for(auto ptr: UnderTestIntrinsics){
    for (size_t i = 0; i < global_op_table_size; ++i){
        // std::unique_ptr<BaseOperator> ptr = std::make_unique<BaseOperator>(global_op_table[i]);
        const OpData & current_data = global_op_table[i];

        bool pushed = false; 
        // setvl intrinsics
        if( startsWith( current_data.funcName, "__riscv_vsetvl" ) == true ){
            pushed = true; continue;
        }

        // ignored intrinsics
        // for( auto ignore: ignored ){ if( ptr->getName().find(ignore) != std::string::npos ) { IgnoredIntrinsics.push_back(ptr); pushed = true; break; } }
        
        // if( usedType != "" && ptr->ifUsedType(usedType) == false ) continue; // not used the given type, continue
        // not use any vector types in the same ratio, continue
        if( current_data.ratio > 0 && current_data.ratio != ratio ) continue;
        // if( ifSegment == false && ptr->ifUsedSegment()==true) continue; // when segment intrinsics are not under test, continue

        // for intrinsics with n-field types
        // if(UnifiedNfield != "" && ptr->nfield != "" && UnifiedNfield != ptr->nfield){
            // ignore intrinsics without the same n-field
            // IgnoredIntrinsics.push_back(ptr); pushed = true;
        // }

        // for ratio non-aligned intrinsics
        if( current_data.ratio == 0 ){
            // for ratio non-aligned intrinsics
            // reduction operation, only select the vs2 type and vmask type (if exists) are connect type (to align the type)
            if ( ifReduction(current_data.funcName) ){
                pushed = true; 
                for (size_t i = 0; i < current_data.pNum; i+=2){
                    if( UsedTypes.getPtr(current_data.args[i])->getRatio() == ratio && \
                    (std::string(current_data.args[i+1]) == "vs2" || std::string(current_data.args[i+1]) == "vector" ) ){
                        // select
                        BaseOperator* tmp = new BaseOperator(current_data);
                        tmp->intrinsic_type = OperatorType::Operation; tmp->opdata_id = i;
                        OpIntrinsics.push_back(tmp);
                        break;
                    }
                }
            }
            // __riscv_vset: select in return type
            if ( std::string(current_data.funcName).find( "__riscv_vset" ) != std::string::npos ){
                pushed = true;
                if( UsedTypes.getPtr(std::string(current_data.retType))->getRatio() == ratio ){
                    BaseOperator* tmp = new BaseOperator(current_data);
                    tmp->intrinsic_type = OperatorType::Operation; tmp->opdata_id = i;
                    OpIntrinsics.push_back(tmp); // select
                }
            }
            // __riscv_vget: select in parameter list
            if ( std::string(current_data.funcName).find( "__riscv_vget" ) != std::string::npos ){
                pushed = true;
                for (size_t i = 0; i < current_data.pNum; i+=2){
                    if( UsedTypes.getPtr(current_data.args[i])->getRatio() == ratio ){
                        // select
                        BaseOperator* tmp = new BaseOperator(current_data);
                        tmp->intrinsic_type = OperatorType::Operation; tmp->opdata_id = i;
                        OpIntrinsics.push_back(tmp);
                        break;
                    }
                }
            }
            // __riscv_vreinterpret, __riscv_vlmul_ext, __riscv_vundefined: always agnostic
            // __riscv_vlmul_trunc: fine, no undefined behavior
            // __riscv_vcreate: fine, no undefined behavior
        }

        // store intrinsics
        if( std::string(current_data.retType) == "void" && startsWith(current_data.funcName, "__riscv_vs") && pushed == false ) { 
            BaseOperator* tmp = new BaseOperator(current_data);
            tmp->intrinsic_type = OperatorType::Store; tmp->opdata_id = i;
            for(auto para: tmp->paras){
                if(para.getPname() == "vs3"){
                    StoreIntrinsics[para.getPtype()].push_back(tmp); pushed = true;
                    break;
                }
            }
        }
        
        // load intrinsics
        // corner case: __riscv_vlmul, is not load operation
        if( std::string(current_data.funcName).find( "__riscv_vlmul" ) != std::string::npos && pushed == false ) { 
            BaseOperator* tmp = new BaseOperator(current_data);
            tmp->intrinsic_type = OperatorType::Operation; tmp->opdata_id = i;
            OpIntrinsics.push_back(tmp); pushed = true; 
        }
        for ( auto it = load_prefix.begin(); it != load_prefix.end() && pushed == false ; it++){
            if( startsWith( std::string(current_data.funcName), *it ) == true ){
                BaseOperator* tmp = new BaseOperator(current_data);
                tmp->intrinsic_type = OperatorType::Load; tmp->opdata_id = i;
                LoadIntrinsics[tmp->getRetype()].push_back(tmp);
                pushed = true;
            }
        }
        // operation intrinsics
        if(pushed == false) {
            BaseOperator* tmp = new BaseOperator(current_data);
            tmp->intrinsic_type = OperatorType::Operation; tmp->opdata_id = i;
            OpIntrinsics.push_back(tmp);
        }
    }
}

void OpDEFS::selectOpSeq(int size){
    if (OpIntrinsics.size()<=0) {
        std::cerr<< "Please organize the intrinsics under test before select." <<std::endl;
        exit(1);
    }
    this->selectedOp.clear();
    for (int i=0; i<size; ++i) {
        if(cov_guide) { 
            BaseOperator* selected_op = nullptr;
            selected_op = select_cov_guide(this->OpIntrinsics);
            selectedOp.push_back(* selected_op); 
            // update covmap
            if(cov_guide || cov_log) covmap.add(selected_op->opdata_id);
        } else { 
            BaseOperator* selected_op = nullptr;
            selected_op = (*select_random(this->OpIntrinsics));
            selectedOp.push_back(* selected_op); 
            // update covmap
            if(cov_guide || cov_log) covmap.add(selected_op->opdata_id);
        }
    }

    this->setMaxNfield();
}

std::string BaseOperator::codegen(){
    assert(this->intrinsic_type == OperatorType::Operation);
    std::string res("");

    if ( this->enumRetype() != Type::OneDVector ){
        // return scalar: TBD
        // return res;
        std::string var_type = this->getRetype(); std::string var_name = "scalar_" + std::to_string(ScalarTable::name_number++);
        scalar_table.AddScalar( this->getRetype(), var_name);
        res += var_name + " = " + this->getName() + "(";
    } else {
        // return vector
        assert( retvreg!=nullptr );
        if( retvreg->declared == false ){
            // to avoid statements like "int a = a + 1;" (uninitialized value used)
            res += this->getRetype() + " " + retvreg->getRegName() + " = " + this->getName() + "(";
            retvreg->declared = true;
        }else{
            res += retvreg->getRegName() + " = " + this->getName() + "(";
        }
    }

    // parameters
    for (size_t i=0; i<paras.size(); ++i){
        if(paras[i].pvreg != nullptr){
            res += paras[i].pvreg->getRegName();
        }else{
            if( paras[i].enumType() == Type::VL ) res += "vl";
            else if( paras[i].enumType() == Type::VMASK ) { res += "vmask"; }
            else if( paras[i].enumType() == Type::FRM ) { res += *select_random(__RISCV_FRM); }
            else if( paras[i].enumType() == Type::VXRM ) { res += *select_random(__RISCV_VXRM); }
            else if( paras[i].enumType() == Type::Index ) { /*TBD*/ res += "0"; }
            else{ 
                // scalar
                assert( paras[i].enumType() == Type::Scalar );
                res += paras[i].getPtypePtr()->getScalar();
                // corner case: vrgather intrinsics
                // e.g., vfloat16m4_t __riscv_vrgather_tu(vfloat16m4_t vd, vfloat16m4_t vs2, size_t vs1, size_t vl);
                if(startsWith( this->getName(), "__riscv_vrgather" ) == true && \
                (paras[i].getPname() == "vs1" || paras[i].getPname() == "index") && \
                paras[i].getPtype() == "size_t" ){
                    res += "%vl";
                }
            }
        }
        if(i<paras.size()-1) res += ", ";
    }

    res += ");\n";
    return res;
}

// use after sequence selection, set MaxNfield to the max nfield in the selected sequence
// if all selected intrinsics do not use segment types, set MaxNfield to ""
void OpDEFS::setMaxNfield(){
    std::set<std::string> lst;
    for(auto op: this->selectedOp){
        if(op.nfield != ""){
            lst.insert( op.nfield );
        }
    }
    if(lst.empty() == true) this->MaxNfield = "";
    else this->MaxNfield = *lst.rbegin();
}

bool BaseOperator::alwaysAgnostic(){
    if( this->getName().find("__riscv_vundefined") != std::string::npos ){
        return true;
    }
    if( this->getName().find("__riscv_vreinterpret") != std::string::npos ){
        return true;
    }
    if( this->getName().find("__riscv_vlmul_ext") != std::string::npos ){
        return true;
    }
    return false;
}

// whether all std::vector types used in this intrinsic have the same ratio (if false, only unit-stride load and store)
// > 0: aligned ratio
// = 0: non-aligned
/*
int BaseOperator::setRatio(){
    std::vector<std::string> vtypes;
    if(enumRetype() == Type::OneDVector) vtypes.push_back(this->getRetype());
    for( auto para: paras ){
        if(para.enumType() == Type::VMASK || para.enumType() == Type::OneDVector){
            vtypes.push_back(para.getPtype());
        }
    }
    if(vtypes.size() == 0){
        this->commonRatio = 0; // no vector type
        return 0;
    }
    int ratio = VectorType(vtypes[0]).ratio;
    for( auto vtype: vtypes ){
        int tmp_ratio = VectorType(vtype).ratio;
        assert(ratio > 0 && tmp_ratio > 0);
        if(ratio != tmp_ratio) {
            this->commonRatio = 0;
            return 0;
        }
    }
    this->commonRatio = ratio;
    return ratio;
}*/

std::string vsetvl(int ratio, std::string avl){
    // ensure ratio is one of the allowed values
    // ratio in [1, 2, 4, 8, 16, 32, 64]
    assert(ratio == 1 || ratio == 2 || ratio == 4 || ratio == 8 || ratio == 16 || ratio == 32 || ratio == 64);

    std::vector<std::string> suffix_lst = {};
    std::string suffux = "";
    switch (ratio){
        case 1:
            suffix_lst = {"e8m8"};
            suffux = *select_random(suffix_lst);
            return "__riscv_vsetvl_" + suffux + "(" + avl + ")";
        case 2:
            suffix_lst = {"e16m8", "e8m4"};
            suffux = *select_random(suffix_lst);
            return "__riscv_vsetvl_" + suffux + "(" + avl + ")";
        case 4:
            suffix_lst = {"e32m8", "e16m4", "e8m2"};
            suffux = *select_random(suffix_lst);
            return "__riscv_vsetvl_" + suffux + "(" + avl + ")";
        case 8:
            suffix_lst = {"e64m8", "e32m4", "e16m2", "e8m1"};
            suffux = *select_random(suffix_lst);
            return "__riscv_vsetvl_" + suffux + "(" + avl + ")";
        case 16:
            suffix_lst = {"e64m4", "e32m2", "e16m1", "e8mf2"};
            suffux = *select_random(suffix_lst);
            return "__riscv_vsetvl_" + suffux + "(" + avl + ")";
        case 32:
            suffix_lst = {"e64m2", "e32m1", "e16mf2", "e8mf4"};
            suffux = *select_random(suffix_lst);
            return "__riscv_vsetvl_" + suffux + "(" + avl + ")";
        case 64:
            suffix_lst = {"e64m1", "e32mf2", "e16mf4", "e8mf8"};
            suffux = *select_random(suffix_lst);
            return "__riscv_vsetvl_" + suffux + "(" + avl + ")";
        default:
            throw std::invalid_argument("Invalid ratio for vsetvl");
    }
}

std::string vsetvl_max(int ratio){
    // ensure ratio is one of the allowed values
    // ratio in [1, 2, 4, 8, 16, 32, 64]
    assert(ratio == 1 || ratio == 2 || ratio == 4 || ratio == 8 || ratio == 16 || ratio == 32 || ratio == 64);

    std::vector<std::string> suffix_lst = {};
    std::string suffux = "";
    switch (ratio){
        case 1:
            suffix_lst = {"e8m8"};
            suffux = *select_random(suffix_lst);
            return "__riscv_vsetvlmax_" + suffux + "()";
        case 2:
            suffix_lst = {"e16m8", "e8m4"};
            suffux = *select_random(suffix_lst);
            return "__riscv_vsetvlmax_" + suffux + "()";
        case 4:
            suffix_lst = {"e32m8", "e16m4", "e8m2"};
            suffux = *select_random(suffix_lst);
            return "__riscv_vsetvlmax_" + suffux + "()";
        case 8:
            suffix_lst = {"e64m8", "e32m4", "e16m2", "e8m1"};
            suffux = *select_random(suffix_lst);
            return "__riscv_vsetvlmax_" + suffux + "()";
        case 16:
            suffix_lst = {"e64m4", "e32m2", "e16m1", "e8mf2"};
            suffux = *select_random(suffix_lst);
            return "__riscv_vsetvlmax_" + suffux + "()";
        case 32:
            suffix_lst = {"e64m2", "e32m1", "e16mf2", "e8mf4"};
            suffux = *select_random(suffix_lst);
            return "__riscv_vsetvlmax_" + suffux + "()";
        case 64:
            suffix_lst = {"e64m1", "e32mf2", "e16mf4", "e8mf8"};
            suffux = *select_random(suffix_lst);
            return "__riscv_vsetvlmax_" + suffux + "()";
        default:
            throw std::invalid_argument("Invalid ratio for vsetvl_max");
    }
}

std::vector<std::string> BaseOperator::load_gen(std::string type, std::string regName, std::string loadVar, bool allMaskIsTrue /* = false*/){
    assert(this->intrinsic_type == OperatorType::Load);
    assert(type == this->getRetype());
    assert( startsWith(type, "vbool") == false ); // should use CodeBlock::load_bool
    std::vector<std::string> res; VectorType vtmp(type);

    std::string loadOp = type + " " + regName + " = " + this->getName() + "(";
    for (size_t i=0; i<(this->paras.size()); ++i){
        if(paras[i].enumType() == Type::VMASK){
            // for vmask: vbool[]_t vm
            if(allMaskIsTrue) { 
                std::string vmask = "__riscv_vlm_v_b" + std::to_string(vtmp.getRatio()) + "(std::vector<uint8_t>((vl + 7) / 8, 255).data(), vl)";
                loadOp += vmask; 
            } else { 
                loadOp += "vmask"; // 'std::string maskName' in CodeBlock 
            }
        }else if(paras[i].enumType() == Type::Scalar && paras[i].getPtypePtr()->ifConstPointer() == true){
            // for pointer to data
            loadOp += "&arr_" + loadVar + "[ptr]";
        }else if(paras[i].enumType() == Type::VL){
            // for size_t vl
            loadOp += "vl";
        }else if(paras[i].enumType() == Type::Ptrdiff){
            // for 'ptrdiff_t rs2' in Vector Strided Load Intrinsics
            // one-element width is ptrdiff_t rs2 (equal to Unit-Stride)
            loadOp += std::to_string(bits2bytes(vtmp.ewidth));
            if(vtmp.nfield != "") loadOp +=  " * " + nfield2n(vtmp.nfield);
        }else if(paras[i].enumType() == Type::OneDVector){
            if(paras[i].getPname() == "vd"){
                // for vd in policy intrinsics
                std::string tmptype = std::to_string(vtmp.ewidth) + vtmp.emul;
                std::string vlmax = vsetvl_max(vtmp.ratio);
                if(vtmp.nfield == ""){
                    if( startsWith(vtmp.etype, "float") )
                        loadOp += "__riscv_vfmv_v_f_f"+tmptype+"(0, " + vlmax + ")";
                    else if ( startsWith(vtmp.etype, "uint") )
                        loadOp += "__riscv_vmv_v_x_u"+tmptype+"(0, " + vlmax + ")";
                    else if ( startsWith(vtmp.etype, "int") )
                        loadOp += "__riscv_vmv_v_x_i"+tmptype+"(0, " + vlmax + ")";
                    else {
                        std::cerr << "unimplementation error: unknown element type: " << vtmp.etype << std::endl;
                        exit(1);
                    }
                }else{
                    int n = std::stoi( nfield2n(vtmp.nfield) );
                    std::string create_vd;
                    std::string para;
                    if( startsWith(vtmp.etype, "float") ){
                        create_vd = "__riscv_vcreate_v_f"+tmptype+vtmp.nfield;
                        para = "__riscv_vfmv_v_f_f"+tmptype+"(0, " + vlmax + ")";
                    }else if ( startsWith(vtmp.etype, "uint") ){
                        create_vd = "__riscv_vcreate_v_u"+tmptype+vtmp.nfield;
                        para = "__riscv_vmv_v_x_u"+tmptype+"(0, " + vlmax + ")";
                    }else if ( startsWith(vtmp.etype, "int") ){
                        create_vd = "__riscv_vcreate_v_i"+tmptype+vtmp.nfield;
                        para = "__riscv_vmv_v_x_i"+tmptype+"(0, " + vlmax + ")";
                    }else {
                        std::cerr << "unimplementation error: unknown element type: " << vtmp.etype << std::endl;
                        exit(1);
                    }
                    create_vd += "(";
                    for(int x=0; x<n-1; ++x){
                        create_vd += para + ", ";
                    }
                    create_vd += para + ")";
                    loadOp += create_vd;
                }
                // end vd
            }else if(paras[i].getPname() == "rs2" && (startsWith(this->getName(), "__riscv_vlux") || startsWith(this->getName(), "__riscv_vlox"))){
                // for vidx in Vector Indexed Load Intrinsics
                int maxValue = std::min( static_cast<int>((1<<8)-1), static_cast<int>(dataLen-1));
                std::string idxType = paras[i].getPtype();
                std::string idxName = VIndex( idxType, maxValue ).idxName;
                VectorType vidxtype(idxType);

                std::string vidx_statement = idxType + " " + idxName + " = __riscv_vsll_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                            "(__riscv_vid_v_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + "(vl), " + std::to_string( bits2moven(vtmp.ewidth) ) + ", vl);\n";
                res.push_back(vidx_statement);
                if(vtmp.nfield != ""){
                    std::string vidx_statement2 = idxName + " = __riscv_vmul_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                            "( " + idxName + ", " + nfield2n(vtmp.nfield) + ", vl);\n";
                    res.push_back(vidx_statement2);
                };
                loadOp += idxName;
            }else{
                std::cerr << "unimplementation error: unknown OneDVector type in the parameter of the load intrinsic: " << this->getDefStr() << std::endl;
                exit(1);
            }
        }else if(paras[i].getPtype() == "size_t *" && paras[i].getPname() == "new_vl"){
            // Fault-Only-First Loads Intrinsics
            loadOp += "&vl";
        }else{
            std::cerr << "unimplementation error: unknown parameter of the load intrinsic: " << this->getDefStr() << std::endl;
            exit(1);
        }

        if(i<paras.size()-1) loadOp += ", ";
    }
    loadOp += ");\n"; res.push_back(loadOp);
    return res;
}

std::vector<std::string> BaseOperator::store_gen(std::string type, std::string regName, std::string storeVar, bool allMaskIsTrue /* = false*/){
    assert(this->intrinsic_type == OperatorType::Store);
    assert( startsWith(type, "vbool") == false ); // should use CodeBlock::store_bool
    std::vector<std::string> res; VectorType vtmp(type);

    std::string storeOp = this->getName() + "(";
    for (size_t i=0; i<(this->paras.size()); ++i){
        if(paras[i].enumType() == Type::VMASK){ 
            if(allMaskIsTrue) { 
                std::string vmask = "__riscv_vlm_v_b" + std::to_string(vtmp.getRatio()) + "(std::vector<uint8_t>((vl + 7) / 8, 255).data(), vl)";
                storeOp += vmask; 
            } else { 
                storeOp += "vmask"; // 'std::string maskName' in CodeBlock 
            }
        } else if( paras[i].enumType() == Type::Scalar && paras[i].getPname() == "rs1" ){ storeOp += "&arr_" + storeVar + "[ptr]"; 
        } else if(paras[i].enumType() == Type::Ptrdiff) { 
            // for 'ptrdiff_t rs2' in Vector Strided Store Intrinsics
            // one-element width is ptrdiff_t rs2 (equal to Unit-Stride)
            storeOp += std::to_string(bits2bytes(vtmp.ewidth));
            if(vtmp.nfield != "") storeOp +=  " * " + nfield2n(vtmp.nfield); 
        } else if(paras[i].getPtype() == "size_t *" && paras[i].getPname() == "new_vl"){
            // Fault-Only-First Store Intrinsics
            storeOp += "&vl";
        } else if(paras[i].enumType() == Type::VL) { storeOp += "vl"; 
        } else if(paras[i].enumType() == Type::OneDVector){

            if(paras[i].getPname() == "vs3"){
                // the vector to be stored
                assert(type == paras[i].getPtype());
                storeOp += regName;
            }else if((paras[i].getPname() == "rs2" || paras[i].getPname() == "vs2") 
                && (startsWith(this->getName(), "__riscv_vsux") || startsWith(this->getName(), "__riscv_vsox"))){
                // for vidx in Vector Indexed Store Intrinsics
                int maxValue = std::min( static_cast<int>((1<<8)-1), static_cast<int>(dataLen-1)); // range(0, min(2^8-1,dataLen-1))
                std::string idxType = paras[i].getPtype();
                std::string idxName = VIndex( idxType, maxValue ).idxName;
                VectorType vidxtype(idxType);

                std::string vidx_statement = idxType + " " + idxName + " = __riscv_vsll_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                "(__riscv_vid_v_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + "(vl), " + std::to_string( bits2moven(vtmp.ewidth) ) + ", vl);\n";
                res.push_back(vidx_statement);
                if(vtmp.nfield != ""){
                    std::string vidx_statement2 = idxName + " = __riscv_vmul_vx_u" + std::to_string(vidxtype.ewidth) + vidxtype.emul + \
                            "( " + idxName + ", " + nfield2n(vtmp.nfield) + ", vl);\n";
                    res.push_back(vidx_statement2);
                }
                storeOp += idxName;

            }else{
                std::cerr << "unimplementation error: unknown OneDVector type in the parameter of the store intrinsic: " << this->getDefStr() << std::endl;
                exit(1);
            }


        } else {
            std::cerr << "unimplementation error: unknown parameter of the store intrinsic: " << this->getDefStr() << std::endl;
            exit(1);
        }

        if(i<paras.size()-1) storeOp += ", ";
    }
    storeOp += ");\n"; res.push_back(storeOp);
    return res;
}

BaseOperator* select_cov_guide(std::vector<BaseOperator* >& candidate){
    std::vector<BaseOperator *> uncovered_idx;
    for(auto ptr: candidate){
        assert(ptr->opdata_id < global_op_table_size);
        if(covmap.get(ptr->opdata_id) == 0) uncovered_idx.push_back(ptr);
    }

    if(uncovered_idx.size() == 0) return *select_random(candidate);
    else{
        auto res = *select_random(uncovered_idx);
        return res;
    }
    return nullptr;
}