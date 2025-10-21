#include "Type.hpp"

UsedTYPES UsedTypes;

constexpr unsigned int str2int(const char* str, int h = 0){
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}
std::string getAScalarRandom(std::string type){
    std::string res;

    uint16_t tmp16; uint32_t tmp32; uint64_t tmp64;
    int tmp; // for mask
    switch ( str2int(type.c_str()) ){
    // bool
    case str2int("bool"):
        return std::to_string( getRandomNumber<int>(0, 100) % 2 ); break;
    // mask
    case str2int("mask"):
        tmp = getRandomNumber<int>(0, 100) % 5;
        // true : false = 4 : 1
        if (tmp == 0) return std::to_string(0);
        else return std::to_string(1);
        break;
    // int
    case str2int("int8_t"):
        return std::to_string( getRandomNumber<int8_t> (static_cast<int8_t>(0x80), static_cast<int8_t>(0x7f)) ); break;
    case str2int("int16_t"):
        return std::to_string( getRandomNumber<int16_t> (static_cast<int16_t>(0x8000), static_cast<int16_t>(0x7fff)) ); break;
    case str2int("int32_t"):
    case str2int("long"):
    case str2int("ptrdiff_t"):
        return std::to_string( getRandomNumber<int32_t> (static_cast<int32_t>(0x80000000), static_cast<int32_t>(0x7fffffff)) ); break;
    case str2int("int64_t"):
    case str2int("long long"):
        return std::to_string( getRandomNumber<int64_t> (static_cast<int64_t>(0x8000000000000000), static_cast<int64_t>(0x7fffffffffffffff)) ) + "ll"; break;
    // unsigned int
    case str2int("uint8_t"):
        return std::to_string( getRandomNumber<uint8_t> (static_cast<uint8_t>(0), static_cast<uint8_t>(0xff)) ); break;
    case str2int("uint16_t"):
        return std::to_string( getRandomNumber<uint16_t> (static_cast<uint16_t>(0), static_cast<uint16_t>(0xffff)) ); break;
    case str2int("uint32_t"):
    case str2int("unsigned long"):
    case str2int("unsigned int"):
    case str2int("size_t"):
        return std::to_string( getRandomNumber<uint32_t> (static_cast<uint32_t>(0), static_cast<uint32_t>(0xffffffff)) ) + "u"; break;
    case str2int("uint64_t"):
    case str2int("unsigned long long"):
        return std::to_string( getRandomNumber<uint64_t> (static_cast<uint64_t>(0), static_cast<uint64_t>(0xffffffff)) ) + "ull"; break;
    // float
    case str2int("_Float16"):
    case str2int("float16_t"):
        tmp16 = getRandomNumber<uint16_t> (static_cast<uint16_t>(0), static_cast<uint16_t>(0xffff));
        return "convert_binary_u16_f16(" + std::to_string(tmp16) + ")"; break;
    case str2int("float"):
    case str2int("float32_t"):
        tmp32 = getRandomNumber<uint32_t> (static_cast<uint32_t>(0), static_cast<uint32_t>(0xffff));
        return "convert_binary_u32_f32(" + std::to_string(tmp32) + "u)"; break;
    case str2int("double"):
    case str2int("float64_t"):
        tmp64 = getRandomNumber<uint64_t> (static_cast<uint64_t>(0), static_cast<uint64_t>(0xffff));
        return "convert_binary_u64_f64(" + std::to_string(tmp64) + "ull)"; break;
    // other
    default :
        throw std::invalid_argument("unimplemented scalar type encountered: " + type);
        break;
    }
    return res;
}

std::string GeneralType::getScalar(){
    // const and point vars can be used only in load/store operations, but
    // load/store operations have no need to call this function.
    assert (this->isConst == false && this->isPoint == false);
    return getAScalarRandom( this->type );
}

void UsedTYPES::printTypeMap(){
    std::cout<<TypeMap.size()<<std::endl;
    for(auto it = TypeMap.cbegin(); it != TypeMap.cend(); ++it){
        std::cout << it->first << " " << it->second->getType() << "\n";
    }
}

#if JSON_INPUT
void UsedTYPES::initializeAllTypes(){
    using json = nlohmann::json;

    std::ifstream JsonlFile; JsonlFile.open(JsonlFilePath);
    if (JsonlFile.is_open() == false) {
        std::cerr << "Error: open jsonl file failed. Please check the path." << std::endl;
        exit(1);
    }

    std::cout << "Extracting data types ..." << std::endl;
    totalLineNum = 0; std::string line;
    std::set<std::string> typeStrings;

    while (getline(JsonlFile, line)) {
        try {
            json j = json::parse(line); totalLineNum += 1;
            std::string retype(j["retype"]); typeStrings.insert(retype);

            for(int i=0; i<j["parameters"].size(); ++i){
                std::string tmp_type(j["parameters"][i]["ptype"]);
                std::string tmp_name(j["parameters"][i]["pname"]);
                typeStrings.insert(tmp_type);
            }
        } catch (json::parse_error& e) { std::cerr << "Json parse error: " << e.what() << std::endl; }
    }

    for (auto s: typeStrings){
        BaseType* ptr = nullptr; if(s=="") continue;

        if(s == "void") { ptr = new BaseType(s); this->insert(std::move(s), ptr); }
        else if(s[0] == 'v') { ptr = new VectorType(s); this->insert(std::move(s), ptr); }
        else { ptr = new GeneralType(s); this->insert(std::move(s), ptr); }
    }

    std::cout << "Data types finished." << std::endl;
    JsonlFile.close();
}
#endif // JSON_INPUT

#if DEF_INPUT

void UsedTYPES::initializeAllTypes(){

    #define BASETYPE(TYPE_STR) {                    \
    BaseType* ptr = new BaseType(#TYPE_STR);        \
    this->insert( std::string(#TYPE_STR), ptr );      \
    }
    #define VECTORTYPE(TYPE_STR) {                  \
    BaseType* ptr = new VectorType(#TYPE_STR);    \
    this->insert( std::string(#TYPE_STR), ptr );      \
    }
    #define GENERALTYPE(TYPE_STR) {                 \
    BaseType* ptr = new GeneralType(#TYPE_STR);  \
    this->insert( std::string(#TYPE_STR), ptr );      \
    }

    #include "Types.def"
    #undef BASETYPE 
    #undef VECTORTYPE 
    #undef GENERALTYPE

}

#endif // DEF_INPUT

void VectorType::parse_vtype(){
    // e.g., vfloat32m4_t, vuint32mf2x8_t, vbool4_t
    #include <regex>
    std::regex vnum_format("v([a-z]+)([0-9]+)(m[f0-9]+)([x1-8]*)_t");
    std::regex vbool_format("vbool([0-9]+)_t");
    std::smatch matches;
    if( regex_search(type, matches, vnum_format) ){
        etype = static_cast<std::string>(matches[1]) + static_cast<std::string>(matches[2]) + "_t";
        ewidth = static_cast<int>( stoi(matches[2]) );
        emul = static_cast<std::string>(matches[3]);
        nfield = static_cast<std::string>(matches[4]);

        if(emul == "mf8") ratio = ewidth*8;
        else if (emul == "mf4") ratio = ewidth*4;
        else if (emul == "mf2") ratio = ewidth*2;
        else if (emul == "m1") ratio = ewidth;
        else if (emul == "m2") ratio = ewidth/2;
        else if (emul == "m4") ratio = ewidth/4;
        else if (emul == "m8") ratio = ewidth/8;
    }
    std::smatch matches2;
    if( regex_search(type, matches2, vbool_format) ){
        etype = "bool";
        ewidth = static_cast<int>( stoi(matches2[1]) );
        emul = "m1";
        ratio = ewidth;
    }
}
