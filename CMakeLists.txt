cmake_minimum_required(VERSION 3.18.4)

project(CADYA CXX)

include(GNUInstallDirs)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Options
option(WITH_TESTS "Enable building of tests" ON)
if(WITH_TESTS)
    message(STATUS "Building tests: Yes")
    enable_testing()
else()
    message(STATUS "Building tests: No")
endif()

find_package(fmt REQUIRED)
find_package(Catch2 3 REQUIRED)
find_package(Eigen3 3.4 REQUIRED)
find_package(Boost REQUIRED)

# Set Version
set(CADYA_VERSION_MAJOR "0")
set(CADYA_VERSION_MINOR "0")
set(CADYA_VERSION_PATCH "1")
set(CADYA_VERSION "${CADYA_VERSION_MAJOR}.${CADYA_VERSION_MINOR}.${CADYA_VERSION_PATCH}")

# Build type
set(DEFAULT_BUILD_TYPE "Debug")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}")
endif()
message(STATUS "Setting up build for CADya v${CADYA_VERSION} (${CMAKE_BUILD_TYPE})")

add_subdirectory(src)

if (WITH_TESTS)
  add_subdirectory(test)
endif()
