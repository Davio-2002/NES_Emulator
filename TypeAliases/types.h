#pragma once

#include <cstdint>

// Unsigned types
using u8  = uint8_t;   // 8-bit unsigned
using u16 = uint16_t;  // 16-bit unsigned
using u32 = uint32_t;  // 32-bit unsigned
using u64 = uint64_t;  // 64-bit unsigned

// Signed types
using i8  = int8_t;    // 8-bit signed
using i16 = int16_t;   // 16-bit signed
using i32 = int32_t;   // 32-bit signed
using i64 = int64_t;   // 64-bit signed

// Floating-point types
using f32 = float;
using f64 = double;

// Common aliases for NES emulator
using byte  = u8;   // Alternative name for 8-bit unsigned
using word  = u16;  // 16-bit word ( useful for memory addressing )
using dword = u32;  // 32-bit double word


// #TODO maybe I don't need this, remove if not necessary

// Special masks and flags for NES bitwise operations
// constexpr u8 BIT_0 = 0x01;
// constexpr u8 BIT_1 = 0x02;
// constexpr u8 BIT_2 = 0x04;
// constexpr u8 BIT_3 = 0x08;
// constexpr u8 BIT_4 = 0x10;
// constexpr u8 BIT_5 = 0x20;
// constexpr u8 BIT_6 = 0x40;
// constexpr u8 BIT_7 = 0x80;

