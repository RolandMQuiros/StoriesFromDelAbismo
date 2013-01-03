cmake_minimum_required(VERSION 2.6)
project(cavenoir)

################################################################################
# Del Abismo Library
################################################################################

# Add DelAbismo library sources
add_subdirectory(da)

# Add DelAbismo include path
set(DA_INC ${PROJECT_SOURCE_DIR}/da/include)
set(DA_SRC ${PROJECT_SOURCE_DIR}/da/src)
include_directories(${DA_INC})

# Add path to DelAbismo library
set(DA_LIB ${PROJECT_SOURCE_DIR}/lib)
link_directories(${DA_LIB})

set(GAME_SRC ${PROJECT_SOURCE_DIR}/src)
include_directories(${GAME_SRC})

################################################################################
# Unit Tests
################################################################################
# Link to Google Test
enable_testing()

# Recursively handle test case files
add_subdirectory(tests)