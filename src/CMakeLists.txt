add_library(Utils Utils.cpp)
target_link_libraries(Utils softfloat)

add_library(Type Type.cpp)
target_link_libraries(Type Utils)

add_library(Register Register.cpp)
target_link_libraries(Register Type Utils)

add_library(Memory Memory.cpp)
target_link_libraries(Memory Type Utils)

add_library(Operator Operator.cpp)
target_link_libraries(Operator Type Utils Register)
add_library(Operator_J Operator_J.cpp)
target_link_libraries(Operator_J Type Utils Register)
add_library(Operator_D Operator_D.cpp)
target_link_libraries(Operator_D Type Utils Register)

add_library(CodeGen CodeGen.cpp)
target_link_libraries(CodeGen Operator Type Utils Register Memory)