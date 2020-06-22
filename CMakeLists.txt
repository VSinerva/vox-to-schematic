cmake_minimum_required(VERSION 3.10.2)
project(vox-to-schematic)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON )

include_directories(include)
file(GLOB SOURCES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.cpp")

add_executable(V2S ${SOURCES})

set(MY_DEBUG_OPTIONS "-std=c++17 -O3 -g -o")

target_compile_definitions(V2S PUBLIC) 
find_library(LIBZ_LIBRARY libz.a.a HINTS "/usr/local/lib")
target_link_libraries(V2S PUBLIC ${LIBZ_LIBRARY}) 
add_compile_options("$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
