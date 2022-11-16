set(LIB_NAME cadyacore)

set(LIB_SOURCES
    geometry/circle.cpp
    geometry/circle_utils.cpp
    geometry/coordinate_utils.cpp
    geometry/intersection.cpp
    geometry/line.cpp
    geometry/line_segment.cpp
    geometry/line_segment_utils.cpp
    geometry/line_utils.cpp
    geometry/trigonometry.cpp
)

add_library(${LIB_NAME} SHARED ${LIB_SOURCES})

target_include_directories(${LIB_NAME} PRIVATE .)

set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${LIB_NAME} PROPERTY CXX_EXTENSIONS OFF)

target_compile_options(${LIB_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -pedantic -Wundef -Wpointer-arith -Wno-long-long
        -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused
        -Woverloaded-virtual -Wconversion -Wsign-conversion -Wdouble-promotion
        -Wformat=2 -flto -O2>
    $<$<CXX_COMPILER_ID:GNU>:
        -Wduplicated-branches -Wduplicated-cond -Wlogical-op -Wuseless-cast>
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /WX>)

target_link_libraries (${LIB_NAME} Eigen3::Eigen)

