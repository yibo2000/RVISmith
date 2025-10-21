#include "Operator.hpp"
#include <regex>

OpDEFS OpDefs;

std::string BaseOperator::getDefStr(){ 
    std::string res = __retype__ + " " + __name__ + "("; 
    for (auto it = paras.begin(); it != paras.end(); ){
        res += it->getPtype() + " " + it->getPname();
        if(++it != paras.end()) res += ", ";
    }
    res += ");";
    return res;
}

/*
bool BaseOperator::ifUsedType (std::string queryType){
    if (this->getRetype() == queryType) return true;
    for (auto it = paras.begin(); it != paras.end(); ++it){
        if(it->getPtype() == queryType) return true;
    }
    return false;
}*/

bool BaseOperator::ifUsedRatio(int ratio){
    if ( this->getRetypePtr( std::move(UsedTypes) )->getRatio() == ratio ) return true;
    for (auto it = paras.begin(); it != paras.end(); ++it){
        if( UsedTypes.getPtr(std::move( it->getPtype() ))->getRatio() == ratio) return true;
    }
    return false;
}

bool BaseOperator::ifUsedSegment(){
    /*
    std::regex vseg_format("v[a-z]+[0-9]+m[f0-9]+x[1-8]+_t");
    std::smatch matches;
    std::string rettype = this->getRetype();
    if( regex_search(rettype, matches, vseg_format) ) {
        // return type is tuple type
        // std::cout << rettype << std::endl;
        return true;
    }
    for (auto it = paras.begin(); it != paras.end(); ++it){
        std::string paratype = it->getPtype();
        if( regex_search(paratype, matches, vseg_format) ){
            // parameter type is tuple type
            // std::cout << paratype << std::endl;
            return true;
        }
    }
    return false;
    */
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

void OpDEFS::organize(std::string usedType, bool ifClear /* = true */){
    if(ifClear) this->clearPool();
    std::vector<std::string> load_prefix = {"vle", "vlm", "vlse", "vloxei", "vluxei", "vlseg", "vlsseg", "vloxseg", "vluxseg"};
    std::vector<std::string> ignored = {"__riscv_vlm_v_", "__riscv_vsm_v_", "ff_v_" /*Fault-Only-First Loads Intrinsics*/};
    for(auto& s: load_prefix) s = "__riscv_"+s;

    // ratio based
    int ratio = UsedTypes.getPtr(std::move(usedType))->getRatio();
    assert( ratio > 0 );
    for(auto ptr: UnderTestIntrinsics){
        bool pushed = false; 
        // setvl intrinsics
        if( startsWith( ptr->getName(), "__riscv_vsetvl" ) == true ){
            SetvlIntrinsics.push_back(ptr);
            pushed = true;
        }

        // ignored intrinsics
        for( auto ignore: ignored ){ if( ptr->getName().find(ignore) != std::string::npos ) { IgnoredIntrinsics.push_back(ptr); pushed = true; break; } }
        
        //if( usedType != "" && ptr->ifUsedType(usedType) == false ) continue; // not used the given type, continue
        // not use any vector types in the same ratio, continue
        if( ptr->commonRatio > 0 && ptr->commonRatio != ratio ) continue;
        if( ifSegment == false && ptr->ifUsedSegment()==true) continue; // when segment intrinsics are not under test, continue

        // for intrinsics with n-field types
        if(UnifiedNfield != "" && ptr->nfield != "" && UnifiedNfield != ptr->nfield){
            // ignore intrinsics without the same n-field
            IgnoredIntrinsics.push_back(ptr); pushed = true;
        }

        // for ratio non-aligned intrinsics
        if( ptr->commonRatio == 0 ){
            // for ratio non-aligned intrinsics
            // reduction operation, only select the vs2 type and vmask type (if exists) are connect type (to align the type)
            if ( ptr->ifReduction() ){
                pushed = true;
                for (auto para: ptr->paras){
                    if( UsedTypes.getPtr(std::move(para.getPtype()))->getRatio() == ratio && \
                    (para.getPname() == "vs2" || para.getPname() == "vector" ) ){
                        // select
                        OpIntrinsics.push_back(ptr);
                        break;
                    }
                }
            }

            // __riscv_vreinterpret, __riscv_vlmul_ext, __riscv_vundefined: always agnostic
            // __riscv_vlmul_trunc: fine, no undefined behavior
            // __riscv_vset: select in return type
            if ( ptr->getName().find( "__riscv_vset" ) != std::string::npos ){
                pushed = true;
                if( UsedTypes.getPtr(std::move(ptr->getRetype()))->getRatio() == ratio ){
                    OpIntrinsics.push_back(ptr); // select
                }
            }
            // __riscv_vget: select in parameter list
            if ( ptr->getName().find( "__riscv_vget" ) != std::string::npos ){
                pushed = true;
                for (auto para: ptr->paras){
                    if( UsedTypes.getPtr(std::move(para.getPtype()))->getRatio() == ratio ){
                        // select
                        OpIntrinsics.push_back(ptr);
                        break;
                    }
                }
            }
            // __riscv_vcreate: no undefined behavior
        }

        // store intrinsics
        if( ptr->getRetype() == "void" && startsWith(ptr->getName(), "__riscv_vs") && pushed == false ) { StoreIntrinsics.push_back(ptr); pushed = true; }
        
        // load intrinsics
        // corner case: __riscv_vlmul, is not load operation
        if( ptr->getName().find( "__riscv_vlmul" ) != std::string::npos && pushed == false ) { OpIntrinsics.push_back(ptr); pushed = true; }
        for ( auto it = load_prefix.begin(); it != load_prefix.end() && pushed == false ; it++){
            if( startsWith( ptr->getName(), *it ) == true ){
                LoadIntrinsics.push_back(ptr);
                pushed = true;
            }
        }
        // operation intrinsics
        if(pushed == false) OpIntrinsics.push_back(ptr);
    }
    std::cout.precision(6);
    std::cout << "Intrinsic support ratio: " << static_cast<double>(UnderTestIntrinsics.size() - IgnoredIntrinsics.size())*100.0/UnderTestIntrinsics.size() << \
    "%("<<(UnderTestIntrinsics.size() - IgnoredIntrinsics.size())<<"/"<<UnderTestIntrinsics.size()<<")" << std::endl;
}

void OpDEFS::organize(std::vector<std::string> usedTypes){
    this->clearPool();
    for (auto str: usedTypes) this->organize(str, false);
}

void OpDEFS::clearPool(){
    LoadIntrinsics.clear(); StoreIntrinsics.clear(); OpIntrinsics.clear();
    SetvlIntrinsics.clear(); IgnoredIntrinsics.clear();
}

std::vector<BaseOperator > OpDEFS::selectOpSeq(int size){
    if (OpIntrinsics.size()<=0) {
        std::cerr<< "Please organize the intrinsics under test before select." <<std::endl;
        return std::vector<BaseOperator >();
    }
    std::vector<BaseOperator > res;
    for (int i=0; i<size; ++i) res.push_back( *(*select_random(this->OpIntrinsics)) );
    return res;
}

std::string BaseOperator::codegen(UsedTYPES && UsedTypes){
    std::string res("");

    // return scalar: TBD
    if ( this->enumRetype(std::move(UsedTypes)) != Type::OneDVector ){
        return res;
    }

    assert( retvreg!=nullptr );
    if( retvreg->declared == false ){
        // to avoid statements like "int a = a + 1;" (uninitialized value used)
        // TBD
        res += this->getRetype() + " " + retvreg->getRegName() + " = " + this->getName() + "(";
        retvreg->declared = true;
    }else{
        res += retvreg->getRegName() + " = " + this->getName() + "(";
    }

    // parameters
    for (int i=0; i<paras.size(); ++i){
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
                assert( paras[i].enumType(std::move(UsedTypes)) == Type::Scalar );
                res += paras[i].getPtypePtr( std::move(UsedTypes) )->getScalar();
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

void BaseOperator::setNfiled(){
    nfield = getRetypePtr(std::move(UsedTypes))->getNfield();
    for(auto para: paras){
        std::string pNfield = para.getPtypePtr(std::move(UsedTypes))->getNfield();
        /*if(( nfield == "" || pNfield == "" || pNfield == nfield ) == false) {
            std::cerr << this->getDefStr() << std::endl;
            std::cerr << nfield << std::endl;
            std::cerr << pNfield << std::endl;
        }*/
        assert( nfield == "" || pNfield == "" || pNfield == nfield );
        if(pNfield != "") nfield = pNfield;
    }
}

void OpDEFS::setUnifiedNfield(){
    std::vector<std::string> nfields = {"x2", "x3", "x4", "x5", "x6", "x7", "x8"};
    this->UnifiedNfield = *(select_random(nfields));
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
int BaseOperator::setRatio(){
    std::vector<std::string> vtypes;
    if(enumRetype(std::move(UsedTypes)) == Type::OneDVector) vtypes.push_back(this->getRetype());
    for( auto para: paras ){
        if(para.enumType(std::move(UsedTypes)) == Type::VMASK || para.enumType(std::move(UsedTypes)) == Type::OneDVector)
            vtypes.push_back(para.getPtype());
    }
    if(vtypes.size() == 0){
        this->commonRatio = 0;
        return 0;
    }
    int ratio = VectorType(vtypes[0]).ratio;
    for( auto vtype: vtypes ){
        int tmp_ratio = VectorType(vtype).ratio;
        if(ratio != tmp_ratio) {
            this->commonRatio = 0;
            return 0;
        }
    }
    this->commonRatio = ratio;
    return ratio;
}