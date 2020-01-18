########################################################################
# Toolchain file for building native on an ARM Cortex A53 w/ NEON
# Usage: cmake -DCMAKE_TOOLCHAIN_FILE=<this file> <source directory>
########################################################################

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)

set(CMAKE_CXX_FLAGS "-march=armv8-a -mtune=cortex-a53 -mfpu=neon-fp-armv8 -mfloat-abi=hard -funsafe-math-optimizations -ffast-math -Wno-psabi" CACHE STRING "")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "")
