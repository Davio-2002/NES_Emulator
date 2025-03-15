#pragma once

#include <cpu6502.h>

struct Constants {
    static constexpr ushort KiB = 1024;
    static constexpr ushort RAM_SIZE = 64 * KiB;
};

class Bus {
public:
    explicit Bus();

private:
    //// Devices which are on the Bus

    cpu6502 cpu_;

    std::array<u8, Constants::RAM_SIZE> ram_;

public:
    //// Bus read and write

    u16 Read(u16 addr, bool readOnly = false) const;

    void Write(u16 addr, u8 data);
};
