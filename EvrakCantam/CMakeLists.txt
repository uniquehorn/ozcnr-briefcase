# CMakeList.txt : CMake project for EvrakCantam, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source to this project's executable.
add_executable (EvrakCantam "EvrakCantam.cpp" "EvrakCantam.h")

# TODO: Add tests and install targets if needed.
