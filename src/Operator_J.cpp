/*
Compile fast, run slow (read from .jsonl).
JSON_INPUT is defined in Utils.hpp
set (JSON_INPUT = 1 and DEF_INPUT = 0) will run this file
*/

#include "Operator.hpp"

#if JSON_INPUT
void OpDEFS::initializeOpDefinitions(){
    using json = nlohmann::json;

    std::ifstream JsonlFile; JsonlFile.open(JsonlFilePath);
    if (JsonlFile.is_open() == false) {
        std::cerr << "Error: open jsonl file failed. Please check the path." << std::endl;
        exit(1);
    }

    std::cout << "Getting intrinsics under test ... " << std::endl;
    int lineCount = 0; std::string line;
    while (getline(JsonlFile, line)) {
        try {
            json j = json::parse(line);
            // std::cout << j.dump(4) << std::endl; // for debug
            this->push_back( new BaseOperator( std::move(j) ) );
            lineCount += 1;
            if( lineCount%1000 == 1 ) displayProgressBar(std::cout, double(lineCount)/double(totalLineNum) );
            if( lineCount == totalLineNum ) displayProgressBar(std::cout, 1.0);
            // if( lineCount == 10000) break; // for debug
        } catch (json::parse_error& e) { std::cerr << "Json parse error: " << e.what() << std::endl; }
    }
    JsonlFile.close();
}
#endif // #if JSON_INPUT
