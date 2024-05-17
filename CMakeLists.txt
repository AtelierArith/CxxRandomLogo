cmake_minimum_required(VERSION 3.24)
project(CxxRandomLogo)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

add_library(myproject_compiler_flags INTERFACE)
target_compile_features(myproject_compiler_flags INTERFACE cxx_std_17)

add_subdirectory(src) # affine fern

add_executable(CxxRandomLogo main.cpp)
target_link_libraries(CxxRandomLogo PUBLIC ifs myproject_compiler_flags)
