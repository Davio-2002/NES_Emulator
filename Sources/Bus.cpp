#include <pch.h>

#include <Bus.h>

Bus::Bus() {
    /* Clear RAM contents before initializing */
    ram_.fill(0);
}

u16 Bus::Read(const u16 addr, bool readOnly) const {
    if (/* addr <= 0x0000 && */ addr <= 0xFFFF) {
        return ram_[addr];
    }

    return 0x00;
}

void Bus::Write(const u16 addr, const u8 data) {
    if (/* addr <= 0x0000 && */ addr <= 0xFFFF) {
        ram_[addr] = data;
    }
}
