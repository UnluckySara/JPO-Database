# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(DataBase VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PROJECT_NAME DatabaseMovieManager)

# Add source files
set(SOURCES
    src/main.cpp
    src/DataBase.cpp
    src/Menu.cpp
)

set(HEADERS
    include/DataBase.hpp
    include/Menu.hpp
)

# Add an executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC {CMAKE_SOURCE_DIR} include)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -g -Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()