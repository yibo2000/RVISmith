cmake_minimum_required(VERSION 3.0)
project(RVISmith VERSION 2.0.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# creating files in the ./def before compilation
set(SCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/scripts/MergeDoc.py")
set(DOC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/rvv-doc/rvv-intrinsic-doc-1.0-rc2/")
# or selecting a specific part
# set(DOC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/rvv-doc/rvv-intrinsic-doc-1.0-rc2/explicit_intrinsic_funcs")
# set(DOC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/rvv-doc/rvv-intrinsic-doc-1.0-rc2/explicit_intrinsic_funcs_policy_variants")
# set(DOC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/rvv-doc/rvv-intrinsic-doc-1.0-rc2/implicit_intrinsic_funcs")
# set(DOC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/rvv-doc/rvv-intrinsic-doc-1.0-rc2/implicit_intrinsic_funcs_policy_variants")
find_package(Python3 REQUIRED COMPONENTS Interpreter)
add_custom_target(RunMergeDoc
    COMMAND Python3::Interpreter "${SCRIPT_PATH}" "${DOC_DIR}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "using scripts/MergeDoc.py to create *.def files..."
    VERBATIM
)

# Set global C++ compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

set(SRC ${CMAKE_CURRENT_LIST_DIR}/src)
set(SOFTFLOAT ${CMAKE_CURRENT_LIST_DIR}/extern/riscv-softfloat-standalone)

include_directories(${SRC})
include_directories(${SOFTFLOAT})
include_directories(${SOFTFLOAT}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/extern)
include_directories(${CMAKE_CURRENT_LIST_DIR}/def)

add_custom_target(CovClean ALL
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_BINARY_DIR}/coverage.bin"
    COMMENT "Deleting coverage information..."
    VERBATIM
)
add_subdirectory(extern)
add_subdirectory(src)
add_executable(rvismith main.cpp)
add_dependencies(rvismith RunMergeDoc)
target_link_libraries(rvismith Utils Operator Guidance Register Memory CodeGen)

install(TARGETS rvismith DESTINATION bin)
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_LIST_DIR}/License.txt")
set(CPACK_PACKAGE_NAME "rvismith")
set(CPACK_PACKAGE_VERSION "2.0.0")
set(CPACK_GENERATOR "TGZ")
include(CPack)
