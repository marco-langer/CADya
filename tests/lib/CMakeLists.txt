set(TEST_NAME cadya_lib_tests)

set(TEST_SOURCES
    geometry/angle_test.cpp
    geometry/circle_test.cpp
    geometry/circle_utils_test.cpp
    geometry/coordinate_utils_test.cpp
    geometry/intersection_test.cpp
    geometry/line_segment_utils_test.cpp
    geometry/line_test.cpp
    geometry/line_utils_test.cpp
    geometry/trigonometry_test.cpp
)

add_executable(${TEST_NAME} ${TEST_SOURCES})

set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${TEST_NAME} PROPERTY CXX_EXTENSIONS OFF)

target_compile_options(${TEST_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -pedantic -Wundef -Wpointer-arith -Wno-long-long
        -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused
        -Woverloaded-virtual -Wconversion -Wsign-conversion -Wdouble-promotion
        -Wformat=2 -flto -O2>
    $<$<CXX_COMPILER_ID:GNU>:
        -Wduplicated-branches -Wduplicated-cond -Wlogical-op -Wuseless-cast>
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /WX>)

target_include_directories(${TEST_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../../src/lib)

target_link_libraries(${TEST_NAME} Catch2::Catch2WithMain fmt::fmt cadyacore)

include(CTest)
include(Catch)
catch_discover_tests(${TEST_NAME})



