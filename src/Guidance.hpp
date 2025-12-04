#ifndef GUIDANCE_HPP
#define GUIDANCE_HPP

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <unordered_set>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <filesystem> // C++ 17 is required

#include "OpData.hpp"

extern std::string db_file;

// Fowler–Noll–Vo hash function for coverage record
// intrinsic name -> uint64_t 
uint64_t fnv1a_identifier(const std::string & str);

struct FileEntry {
    uint64_t key;
    uint32_t value;
};

class FixedCovMap {
private:
    std::string filename_;
    
    // Key -> { Value, FileOffset }
    struct RuntimeEntry {
        uint32_t value;
        std::streampos file_offset_val; // Value offset in file
    };
    std::unordered_map<uint64_t, RuntimeEntry> map_;
    
    // Record the keys modified during this run to avoid traversing the entire Map.
    std::unordered_set<uint64_t> dirty_keys_;

public:
    FixedCovMap(const std::string& filename) : filename_(filename) { }

    ~FixedCovMap() {
        flush_updates();
    }
    // std::vector<uint64_t> initial_keys;

    // 1. init or load
    // if this is the first time running the program (file does not exist), init, or load.
    void init_or_load();

    // 2. update data
    void add(uint64_t key, uint32_t delta = 1);

    uint32_t get(uint64_t key);
    std::string get_coverage();

private:
    // A: The file does not exist. Create it and fill in the Key and initial Value (0).
    void create_and_init();

    // B: Read a file and create an index of Key -> {Value, Offset}
    void load_map_and_offsets();

    // C: write back the update data
    void flush_updates();
};

extern FixedCovMap covmap;

#endif // GUIDANCE