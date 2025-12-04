add_library(Utils Utils.cpp)
target_link_libraries(Utils softfloat)

add_library(Type Type.cpp)
add_dependencies(Type RunMergeDoc)
target_link_libraries(Type Utils)
add_library(Register Register.cpp)
add_library(Memory Memory.cpp)
target_link_libraries(Memory Type)

add_library(Guidance Guidance.cpp)
add_dependencies(Guidance RunMergeDoc)

add_library(Operator Operator.cpp)
add_dependencies(Operator RunMergeDoc)
add_library(CodeGen CodeGen.cpp)
target_link_libraries(CodeGen Memory Operator)