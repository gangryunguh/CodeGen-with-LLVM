cmake_minimum_required(VERSION 3.10)
project(Toy01)

set(CMAKE_CXX_STANDARD 11)

#set (CMAKE_PREFIX_PATH "/Users/uh/LLVM/6.0/llvm/cmake-build-debug")
set (CMAKE_PREFIX_PATH "/Users/uh/LLVM/llvm-project-10.0.0/llvm/cmake-build-debug")
#set (CMAKE_PREFIX_PATH "/Users/uh/hare/llvm/cmake-build-debug")
find_package(LLVM REQUIRED CONFIG)

# The version number
set (TOY01_VERSION_MAJOR 1)
set (TOY01_VERSION_MINOR 0)

# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(Toy01 toy01.cpp)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
target_link_libraries(Toy01 ${llvm_libs})
