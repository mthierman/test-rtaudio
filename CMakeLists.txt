cmake_minimum_required(VERSION 3.31)

project(template-cmake)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

add_library(config INTERFACE)

add_library(config::config ALIAS config)

target_compile_features(config INTERFACE c_std_17 cxx_std_23)

target_compile_definitions(config INTERFACE UNICODE WIN32_LEAN_AND_MEAN NOMINMAX GDIPVER=0x0110)

# https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options
target_compile_options(
    config
    INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:
        /W4
        /WX
        /utf-8
        /bigobj
        /diagnostics:caret
        /permissive-
        /Zc:__cplusplus,enumTypes,templateScope,throwingNew,preprocessor
        >
        $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_FRONTEND_VARIANT:MSVC>>:
        /W4
        /WX
        -Wno-braced-scalar-init
        >
        $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_FRONTEND_VARIANT:GNU>>:
        -Wall
        -Werror
        -Wno-braced-scalar-init
        >
)

# https://learn.microsoft.com/en-us/cpp/build/reference/linker-options
target_link_options(
    config
    INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:
        /WX
        >
        $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_FRONTEND_VARIANT:MSVC>>:
        /WX
        >
        $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_FRONTEND_VARIANT:GNU>>:
        -Wl,/WX
        >
)

if(PROJECT_IS_TOP_LEVEL)
    add_subdirectory("exe")
endif()
