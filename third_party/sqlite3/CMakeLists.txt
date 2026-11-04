cmake_minimum_required(VERSION 3.14)
project(sqlite3_lib C)

add_library(sqlite3 STATIC sqlite3.c sqlite3.h sqlite3ext.h)

target_include_directories(sqlite3 PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

if(MSVC)
    target_compile_options(sqlite3 PRIVATE /W0)
else()
    target_compile_options(sqlite3 PRIVATE -w)
endif()