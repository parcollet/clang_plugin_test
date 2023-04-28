cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(pfn VERSION 0.1.0 LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Type of build" FORCE)
endif()

# CXX options
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Load LLVM/Clang cmake
set(LLVM_CONFIG llvm-config CACHE STRING "llvm-config")
execute_process(COMMAND ${LLVM_CONFIG} --prefix OUTPUT_VARIABLE LLVM_ROOT_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)

list(APPEND CMAKE_PREFIX_PATH "${LLVM_ROOT_DIR}/lib/cmake/clang/")

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

MESSAGE(STATUS "LLVM_ROOT_DIR : ${LLVM_ROOT_DIR}")
MESSAGE(STATUS "LLVM_INCLUDE_DIR : ${LLVM_INCLUDE_DIR}")
MESSAGE(STATUS "LLVM_LIBRARY_DIR : ${LLVM_LIBRARY_DIR}")
MESSAGE(STATUS "LLVM_ENABLE_RTTI : ${LLVM_ENABLE_RTTI}")
MESSAGE(STATUS "CLANG_INCLUDE_DIR : ${CLANG_INCLUDE_DIR}")

# Building
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

# Add library
add_llvm_library(pfn MODULE PrintFunctionNames.cpp PLUGIN_TOOL clang)

#target_link_libraries(pfn PRIVATE -L${LLVM_ROOT_DIR}/lib -lclangFormat)

#add_library(pfn  SHARED PrintFunctionNames.cpp )

enable_testing()
add_test(NAME t1 COMMAND ${CLANG_INSTALL_PREFIX}/bin/clang++ -fplugin=./pfn.so -c ${CMAKE_SOURCE_DIR}/test/ess.cpp)
