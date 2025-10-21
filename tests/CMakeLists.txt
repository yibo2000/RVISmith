add_executable(testRegister testRegister.cpp)
target_link_libraries(testRegister Utils Operator Register)

add_executable(testNfields testNfields.cpp)
target_link_libraries(testNfields Utils Operator)