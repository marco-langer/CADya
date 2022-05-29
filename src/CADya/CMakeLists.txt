find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)

set(APP_NAME CADya)

set(APP_SOURCES
    main.cpp
    widgets/mainwindow.cpp
    widgets/glcanvas.cpp
)

add_executable(${APP_NAME} ${APP_SOURCES})

set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${APP_NAME} PROPERTY CXX_EXTENSIONS OFF)
set_property(TARGET ${APP_NAME} PROPERTY AUTOMOC ON)

target_compile_options(${APP_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -Wpedantic -Wundef -Wpointer-arith -Wno-long-long
        -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused
        -Woverloaded-virtual -Wconversion -Wsign-conversion -Wdouble-promotion
        -Wformat=2>
    $<$<CXX_COMPILER_ID:GNU>:
        -Wduplicated-branches -Wduplicated-cond -Wlogical-op -Wuseless-cast>
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /WX>)

target_include_directories(${APP_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(${APP_NAME}
  PRIVATE
    Qt5::Widgets
    Qt5::OpenGL
    fmt::fmt
)
