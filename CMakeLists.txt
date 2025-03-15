cmake_minimum_required(VERSION 3.10)
project(FileCompressor)

set(CMAKE_CXX_STANDARD 17)

find_package(SQLite3 REQUIRED)

add_executable(file_compressor main.cpp huffman.cpp file_database.cpp)
target_link_libraries(file_compressor SQLite::SQLite3)
