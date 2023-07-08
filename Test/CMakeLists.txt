cmake_minimum_required(VERSION 3.0.0)

project(Test VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 14)
set(INCLUDE_DIR "../Diary/include/")
set(LIBRARY_DIR "../Diary/libs/")

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")
endif()

link_directories(${LIBRARY_DIR})
include_directories(${INCLUDE_DIR})

add_executable(Test db_helper.cpp main.cpp)

target_link_libraries(Test sqlite3.lib)

# 输出 include 目录路径
message("-- Include directory: ${INCLUDE_DIR}")
# 输出 library 目录路径
message("-- Library directory: ${LIBRARY_DIR}")
# 当前使用的c++编译器
message("-- CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER_ID}")
# 当前使用的c编译器
message("-- CMAKE_C_COMPILER: ${CMAKE_C_COMPILER_ID}")
# 当前使用的c编译器的版本
message("-- CMAKE_C_COMPILER_VERSION: ${CMAKE_C_COMPILER_VERSION}")
# 当前使用的c++编译器的版本
message("-- CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")

message("-- CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")
message("-- CMAKE_C_STANDARD: ${CMAKE_C_STANDARD}")