set(LIB_NAME cadyacore)

set(LIB_SOURCES
    geometry/circle_utils.cpp
    geometry/intersection.cpp
    geometry/line_segment_utils.cpp
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


