#pragma once

#include <memory>

class Bus;

class cpu6502 {
public:
    enum class FLAG6502 {
        C = (1 << 0),  // Carry Bit
        Z = (1 << 1),  // Zero
        I = (1 << 2),  // Disable Interrupts
        D = (1 << 3),  // Decimal Mode (unused in this implementation)
        B = (1 << 4),  // Break
        U = (1 << 5),  // Unused
        V = (1 << 6),  // Overflow
        N = (1 << 7)   // Negative
    };

    //// Registers


public:

    void ConnectBus(const std::shared_ptr<Bus> &n );

private:
    std::shared_ptr<Bus> bus;

    u8 Read(u16 address) const;

    void Write(u16 address, u8 data) const;
};
