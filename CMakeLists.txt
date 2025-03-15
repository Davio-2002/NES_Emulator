cmake_minimum_required(VERSION 3.30)
project(NES_Emulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(NES_Emulator main.cpp
        Sources/Bus.cpp
        Sources/cpu6502.cpp
        Includes/Bus.h
        Includes/cpu6502.h
        TypeAliases/types.h
        TypeAliases/pch.h
)

target_include_directories(NES_Emulator SYSTEM PUBLIC Includes TypeAliases)

target_precompile_headers( NES_Emulator PUBLIC TypeAliases/pch.h )
