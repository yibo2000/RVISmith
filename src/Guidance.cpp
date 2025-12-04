#include "Guidance.hpp"

std::string db_file = "coverage.bin";
FixedCovMap covmap(db_file);

// Fowler–Noll–Vo hash function for coverage record
// intrinsic name -> uint64_t 
uint64_t fnv1a_identifier(const std::string & str) {
    uint64_t prime = 1099511628211ULL;
    uint64_t offset = 14695981039346656037ULL;

    uint64_t hash = offset;
    for (char c : str) {
        hash ^= static_cast<unsigned char>(c);
        hash *= prime;
    }
    hash ^= str.length();
    hash *= prime;
    return hash;
}

// 1. init or load
// if this is the first time running the program (file does not exist), init, or load.
void FixedCovMap::init_or_load(){
    assert(filename_ != "");
    if (!std::filesystem::exists(filename_)) {
        create_and_init();
    }
    load_map_and_offsets();
}

// 2. update data
void FixedCovMap::add(uint64_t key, uint32_t delta /* = 1*/) {
    if (map_.find(key) != map_.end()) {
        map_[key].value += delta;
        dirty_keys_.insert(key); // label as dirty
    } else {
        // constant data volume means that unknown keys should not appear.
        std::cerr << "[Error] Key not found in fixed set: " << key << std::endl;
    }
}

uint32_t FixedCovMap::get(uint64_t key) {
    // if (map_.find(key) != map_.end()) return map_[key].value;
    if (key < global_op_table_size) return map_[key].value;
    return 0;
}

// A: The file does not exist. Create it and fill in the Key and initial Value (0).
void FixedCovMap::create_and_init() {
    // std::cout << "[Info] Creating new binary file..." << std::endl;
    std::ofstream out(filename_, std::ios::binary);
    
    std::vector<FileEntry> buffer;
    // initial_keys.reserve(global_op_table_size);
    buffer.reserve(global_op_table_size);
    
    for (size_t i = 0; i < global_op_table_size; ++i){
        // auto key = fnv1a_identifier(global_op_table[i].funcName);
        auto key = i;
        buffer.push_back({key, 0}); // init: 0
    }
    
    out.write(reinterpret_cast<const char*>(buffer.data()), buffer.size() * sizeof(FileEntry));
    out.close();
}

// B: Read a file and create an index of Key -> {Value, Offset}
void FixedCovMap::load_map_and_offsets() {
    std::ifstream in(filename_, std::ios::binary);
    if (!in.is_open()) return;

    FileEntry entry;
    // sizeof(FileEntry)
    while (in.read(reinterpret_cast<char*>(&entry), sizeof(FileEntry))) {
        // Calculate the current position of the Value in the file
        // Current position read - total structure size + key size = starting position of the Value
        std::streampos curr_pos = in.tellg();
        std::streampos val_offset = curr_pos - static_cast<std::streampos>(sizeof(FileEntry)) + static_cast<std::streampos>(sizeof(uint64_t)); // 偏移过 Key 的 8 字节

        map_[entry.key] = {entry.value, val_offset};
    }
    // std::cout << "[Info] Loaded " << map_.size() << " fixed keys." << std::endl;
}

// C: write back the update data
void FixedCovMap::flush_updates() {
    if (dirty_keys_.empty()) return;

    // Using r+ mode (read/write) will not clear the file (trunc)
    std::fstream fs(filename_, std::ios::binary | std::ios::in | std::ios::out);
    if (!fs.is_open()) {
        std::cerr << "[Error] Failed to open file for update." << std::endl;
        return;
    }

    // int update_count = 0;
    for (uint64_t key : dirty_keys_) {
        auto& entry = map_[key];
        
        fs.seekp(entry.file_offset_val); // 1. Locate the position of the value corresponding to the key in the file.
        fs.write(reinterpret_cast<const char*>(&entry.value), sizeof(uint32_t)); // 2. Write only 4 bytes of value
        //update_count++;
    }
    
    fs.close();
    // std::cout << "[Info] Flushed " << update_count << " updated entries." << std::endl;
    dirty_keys_.clear();
}

std::string FixedCovMap::get_coverage(){
    size_t covered = 0, total = map_.size();
    for(auto [key, entry]: map_){
        if(entry.value > 0) covered += 1;
    }

    std::ostringstream oss;
    double coverage = 0.0;
    if (total != 0) { coverage = static_cast<double>(covered) / total * 100.0; }
    
    oss << std::fixed << std::setprecision(4) << coverage 
        << "%(" << covered << "/" << total << ")";
    return oss.str();
}