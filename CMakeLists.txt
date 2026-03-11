cmake_minimum_required(VERSION 3.16)

project(gymzip LANGUAGES CXX)

if(NOT WIN32)
    message(FATAL_ERROR "This project uses Win32 API and can only be built on Windows.")
endif()

add_library(gymzip SHARED
    gymunzip.cpp
    unzip.cpp
    src/zip.cpp
    Source.def
)

target_include_directories(gymzip
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(gymzip PRIVATE cxx_std_11)

if(MSVC)
    target_compile_options(gymzip PRIVATE /W3)
else()
    target_compile_options(gymzip PRIVATE -Wall -Wextra)
endif()

