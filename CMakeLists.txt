# Copyright 2020 Peter Horvath, Miklos Maroti.
#
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

cmake_minimum_required (VERSION 3.4)
project(smoggnd C)

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Wsign-conversion)
endif()

message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR is ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "CMAKE_CXX_COMPILER is ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_FLAGS is ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CROSS_COMPILING is ${CMAKE_CROSS_COMPILING}")
message(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

find_package(PkgConfig)
find_package(LibUSB)
find_package(LibRTLSDR)
find_package(CURL)

add_executable(smogpgnd
    src/main.c
    src/lib/packet_check.c
    src/lib/tsprint.c
    src/ao40/long/ao40_decode_message.c
    src/ao40/long/ao40_decode_rs.c
    src/ao40/long/ao40_spiral-vit_scalar.c
    src/ao40/short/ao40short_decode_message.c
    src/ao40/short/ao40short_decode_rs.c
    src/ao40/short/ao40short_spiral-vit_scalar_1280.c
    src/ts_radecoder/ra_config.c
    src/ts_radecoder/ra_decoder_gen.c
    src/ts_radecoder/ra_decoder.c
    src/ts_radecoder/ra_lfsr.c
    src/lib/getline.c
    )
target_compile_definitions(smogpgnd PRIVATE BUILD_SMOGP)

target_link_libraries(smogpgnd
    pthread)

add_executable(atlgnd
    src/main.c
    src/lib/packet_check.c
    src/lib/tsprint.c
    src/ao40/long/ao40_decode_message.c
    src/ao40/long/ao40_decode_rs.c
    src/ao40/long/ao40_spiral-vit_scalar.c
    src/ao40/short/ao40short_decode_message.c
    src/ao40/short/ao40short_decode_rs.c
    src/ao40/short/ao40short_spiral-vit_scalar_1280.c
    src/ts_radecoder/ra_config.c
    src/ts_radecoder/ra_decoder_gen.c
    src/ts_radecoder/ra_decoder.c
    src/ts_radecoder/ra_lfsr.c
    src/lib/getline.c
    )
target_compile_definitions(atlgnd PRIVATE BUILD_ATL1)

target_link_libraries(atlgnd
    pthread)

add_executable(rtl2cf
    src/demod/rtl2cf.c)

