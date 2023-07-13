cmake_minimum_required(VERSION 3.10)

project(SQlite3Library VERSION 1.0.0 LANGUAGES C)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories("sqlite3")

aux_source_directory(sqlite3 src_dir)

add_library(sqlite3 ${src_dir})

add_executable (SQlite3Executable "SQlite3Library.cpp" "SQlite3Library.h")

target_link_libraries(SQlite3Executable sqlite3)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SQlite3Executable PROPERTY CXX_STANDARD 20)
endif()