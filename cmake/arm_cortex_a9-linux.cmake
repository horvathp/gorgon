########################################################################
# Toolchain file for cross compiling for ARM Cortex A9 w/ NEON (PLUTO)
# Usage: cmake -DCMAKE_TOOLCHAIN_FILE=<this file> <source directory>
########################################################################

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)

set(CMAKE_CXX_FLAGS "-mcpu=cortex-a9 -mtune=cortex-a9 -mfpu=neon-fp16 -mfloat-abi=hard -funsafe-math-optimizations -ffast-math" CACHE STRING "")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_CROSS_COMPILING TRUE)
