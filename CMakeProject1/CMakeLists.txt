# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (decompressor "decompressor.cpp" "base58_2048.h"  "base58_2048.cpp")
add_executable (compressor "compressor.cpp" "base58_2048.h"   "base58_2048.cpp")
include_directories("${PROJECT_SOURCE_DIR}/New Folder/include")


target_link_directories(decompressor PUBLIC "${PROJECT_SOURCE_DIR}/New Folder")
target_link_libraries(decompressor libcrypto libsodium)

target_link_directories(compressor PUBLIC "${PROJECT_SOURCE_DIR}/New Folder")
target_link_libraries(compressor libcrypto libsodium)
# TODO: Add tests and install targets if needed.
