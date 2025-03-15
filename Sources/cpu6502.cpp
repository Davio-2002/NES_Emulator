#include <pch.h>

#include <cpu6502.h>
#include <Bus.h>

void cpu6502::ConnectBus(const std::shared_ptr<Bus> &n) {
    bus = n;
}

u8 cpu6502::Read(const u16 address) const {
    return bus->Read(address);
}

void cpu6502::Write(const u16 address, const u8 data) const {
    bus->Write(address, data);
}
