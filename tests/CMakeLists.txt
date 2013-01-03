cmake_minimum_required(VERSION 2.6)
project(delabismo-test)

set(CMAKE_BUILD_TYPE Debug)
add_definitions(-std=c++0x)

link_libraries(
    delabismo 
    
    gtest_main
    pthread
)

# Enable debugging
set(CMAKE_BUILD_TYPE Debug)

# Enable profiling
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pg" )
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -pg" )

# Add tests here
add_subdirectory(EntityTests)
add_subdirectory(KeyboardMouseTest)
