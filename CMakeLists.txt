cmake_minimum_required(VERSION 3.10.2)
project(vox-to-schematic)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -O3")
include_directories(include)
file(GLOB SOURCES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.cpp")

add_executable(V2S ${SOURCES})

target_compile_definitions(V2S PUBLIC) 
find_library(LIBZ_LIBRARY libz.a HINTS "/usr/local/lib")
target_link_libraries(V2S PUBLIC ${LIBZ_LIBRARY}) 
