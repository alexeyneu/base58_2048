# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
#add_executable (CMakeProject1 "CMakeProject1.cpp" "CMakeProject1.h" "base58_c.cpp" "libbase58.h")
add_executable (decompressor "decompressor.cpp" "CMakeProject1.h" "base58_c.cpp" "libbase58.h")
add_executable (compressor "compressor.cpp" "CMakeProject1.h" "base58_c.cpp" "libbase58.h" )
include_directories("${PROJECT_SOURCE_DIR}/New Folder/include")


#target_link_directories(CMakeProject1 PUBLIC "${PROJECT_SOURCE_DIR}/New Folder")
#target_link_libraries(CMakeProject1 libcrypto)

target_link_directories(decompressor PUBLIC "${PROJECT_SOURCE_DIR}/New Folder")
target_link_libraries(decompressor libcrypto)

target_link_directories(compressor PUBLIC "${PROJECT_SOURCE_DIR}/New Folder")
target_link_libraries(compressor libcrypto)
# TODO: Add tests and install targets if needed.
