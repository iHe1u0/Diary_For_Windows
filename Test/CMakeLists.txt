cmake_minimum_required(VERSION 3.0.0)

project(Test VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(INCLUDE_DIR "../Diary/include/")
set(LIBRARY_DIR "../Diary/libs/")

# 输出 include 目录路径
message("Include directory: ${INCLUDE_DIR}")
# 输出 library 目录路径
message("Library directory: ${LIBRARY_DIR}")

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")
endif()

link_directories(${LIBRARY_DIR})
include_directories(${INCLUDE_DIR})

add_executable(Test db_helper.cpp main.cpp)


target_link_libraries(Test sqlite3.lib)
