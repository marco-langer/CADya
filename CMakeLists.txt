cmake_minimum_required(VERSION 3.18.4)

project(CPP_UTILS LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Check compiler requirements
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "10.2.1")
        message(FATAL_ERROR "Insufficient gcc version: 10.2.1 required")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "CLANG")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "11.0.1")
        message(FATAL_ERROR "Insufficient clang version: 11.0.1 required")
    endif()
endif()

find_package(fmt REQUIRED)
find_package(Eigen3 3.4 REQUIRED)
find_package(Boost REQUIRED)

# Options
option(WITH_TESTS "Enable building of tests" ON)
if(WITH_TESTS)
    find_package(Catch2 3 REQUIRED)
    message(STATUS "Building tests: Yes")
    enable_testing()
else()
    message(STATUS "Building tests: No")
endif()

add_subdirectory(src/lib)
if (WITH_TESTS)
  add_subdirectory(tests)
endif()
