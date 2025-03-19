#include <pch.h>

#include <cpu6502.h>
#include <Bus.h>

using cpu = cpu6502;

cpu6502::cpu6502() {
    auto bind = [this](const std::string &name, u8 (cpu6502::*op)(), u8 (cpu6502::*mode)(), const u8 cycles) {
        return Instruction{
            name, [this, op] { return (this->*op)(); }, [this, mode] { return (this->*mode)(); }, cycles
        };
    };

    lookup =
    {
        bind("BRK", &cpu::BRK, &cpu::IMM, 7), bind("ORA", &cpu::ORA, &cpu::IZX, 6),
        bind("???", &cpu::XXX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 8),
        bind("???", &cpu::NOP, &cpu::IMP, 3), bind("ORA", &cpu::ORA, &cpu::ZP0, 3),
        bind("ASL", &cpu::ASL, &cpu::ZP0, 5), bind("???", &cpu::XXX, &cpu::IMP, 5),
        bind("PHP", &cpu::PHP, &cpu::IMP, 3), bind("ORA", &cpu::ORA, &cpu::IMM, 2),
        bind("ASL", &cpu::ASL, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 2),
        bind("???", &cpu::NOP, &cpu::IMP, 4), bind("ORA", &cpu::ORA, &cpu::ABS, 4),
        bind("ASL", &cpu::ASL, &cpu::ABS, 6), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("BPL", &cpu::BPL, &cpu::REL, 2), bind("ORA", &cpu::ORA, &cpu::IZY, 5),
        bind("???", &cpu::XXX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 8),
        bind("???", &cpu::NOP, &cpu::IMP, 4), bind("ORA", &cpu::ORA, &cpu::ZPX, 4),
        bind("ASL", &cpu::ASL, &cpu::ZPX, 6), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("CLC", &cpu::CLC, &cpu::IMP, 2), bind("ORA", &cpu::ORA, &cpu::ABY, 4),
        bind("???", &cpu::NOP, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 7),
        bind("???", &cpu::NOP, &cpu::IMP, 4), bind("ORA", &cpu::ORA, &cpu::ABX, 4),
        bind("ASL", &cpu::ASL, &cpu::ABX, 7), bind("???", &cpu::XXX, &cpu::IMP, 7),
        bind("JSR", &cpu::JSR, &cpu::ABS, 6), bind("AND", &cpu::AND, &cpu::IZX, 6),
        bind("???", &cpu::XXX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 8),
        bind("BIT", &cpu::BIT, &cpu::ZP0, 3), bind("AND", &cpu::AND, &cpu::ZP0, 3),
        bind("ROL", &cpu::ROL, &cpu::ZP0, 5), bind("???", &cpu::XXX, &cpu::IMP, 5),
        bind("PLP", &cpu::PLP, &cpu::IMP, 4), bind("AND", &cpu::AND, &cpu::IMM, 2),
        bind("ROL", &cpu::ROL, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 2),
        bind("BIT", &cpu::BIT, &cpu::ABS, 4), bind("AND", &cpu::AND, &cpu::ABS, 4),
        bind("ROL", &cpu::ROL, &cpu::ABS, 6), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("BMI", &cpu::BMI, &cpu::REL, 2), bind("AND", &cpu::AND, &cpu::IZY, 5),
        bind("???", &cpu::XXX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 8),
        bind("???", &cpu::NOP, &cpu::IMP, 4), bind("AND", &cpu::AND, &cpu::ZPX, 4),
        bind("ROL", &cpu::ROL, &cpu::ZPX, 6), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("SEC", &cpu::SEC, &cpu::IMP, 2), bind("AND", &cpu::AND, &cpu::ABY, 4),
        bind("???", &cpu::NOP, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 7),
        bind("???", &cpu::NOP, &cpu::IMP, 4), bind("AND", &cpu::AND, &cpu::ABX, 4),
        bind("ROL", &cpu::ROL, &cpu::ABX, 7), bind("???", &cpu::XXX, &cpu::IMP, 7),
        bind("RTI", &cpu::RTI, &cpu::IMP, 6), bind("EOR", &cpu::EOR, &cpu::IZX, 6),
        bind("???", &cpu::XXX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 8),
        bind("???", &cpu::NOP, &cpu::IMP, 3), bind("EOR", &cpu::EOR, &cpu::ZP0, 3),
        bind("LSR", &cpu::LSR, &cpu::ZP0, 5), bind("???", &cpu::XXX, &cpu::IMP, 5),
        bind("PHA", &cpu::PHA, &cpu::IMP, 3), bind("EOR", &cpu::EOR, &cpu::IMM, 2),
        bind("LSR", &cpu::LSR, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 2),
        bind("JMP", &cpu::JMP, &cpu::ABS, 3), bind("EOR", &cpu::EOR, &cpu::ABS, 4),
        bind("LSR", &cpu::LSR, &cpu::ABS, 6), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("BVC", &cpu::BVC, &cpu::REL, 2), bind("EOR", &cpu::EOR, &cpu::IZY, 5),
        bind("???", &cpu::XXX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 8),
        bind("???", &cpu::NOP, &cpu::IMP, 4), bind("EOR", &cpu::EOR, &cpu::ZPX, 4),
        bind("LSR", &cpu::LSR, &cpu::ZPX, 6), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("CLI", &cpu::CLI, &cpu::IMP, 2), bind("EOR", &cpu::EOR, &cpu::ABY, 4),
        bind("???", &cpu::NOP, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 7),
        bind("???", &cpu::NOP, &cpu::IMP, 4), bind("EOR", &cpu::EOR, &cpu::ABX, 4),
        bind("LSR", &cpu::LSR, &cpu::ABX, 7), bind("???", &cpu::XXX, &cpu::IMP, 7),
        bind("RTS", &cpu::RTS, &cpu::IMP, 6), bind("ADC", &cpu::ADC, &cpu::IZX, 6),
        bind("???", &cpu::XXX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 8),
        bind("???", &cpu::NOP, &cpu::IMP, 3), bind("ADC", &cpu::ADC, &cpu::ZP0, 3),
        bind("ROR", &cpu::ROR, &cpu::ZP0, 5), bind("???", &cpu::XXX, &cpu::IMP, 5),
        bind("PLA", &cpu::PLA, &cpu::IMP, 4), bind("ADC", &cpu::ADC, &cpu::IMM, 2),
        bind("ROR", &cpu::ROR, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 2),
        bind("JMP", &cpu::JMP, &cpu::IND, 5), bind("ADC", &cpu::ADC, &cpu::ABS, 4),
        bind("ROR", &cpu::ROR, &cpu::ABS, 6), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("BVS", &cpu::BVS, &cpu::REL, 2), bind("ADC", &cpu::ADC, &cpu::IZY, 5),
        bind("???", &cpu::XXX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 8),
        bind("???", &cpu::NOP, &cpu::IMP, 4), bind("ADC", &cpu::ADC, &cpu::ZPX, 4),
        bind("ROR", &cpu::ROR, &cpu::ZPX, 6), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("SEI", &cpu::SEI, &cpu::IMP, 2), bind("ADC", &cpu::ADC, &cpu::ABY, 4),
        bind("???", &cpu::NOP, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 7),
        bind("???", &cpu::NOP, &cpu::IMP, 4), bind("ADC", &cpu::ADC, &cpu::ABX, 4),
        bind("ROR", &cpu::ROR, &cpu::ABX, 7), bind("???", &cpu::XXX, &cpu::IMP, 7),
        bind("???", &cpu::NOP, &cpu::IMP, 2), bind("STA", &cpu::STA, &cpu::IZX, 6),
        bind("???", &cpu::NOP, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("STY", &cpu::STY, &cpu::ZP0, 3), bind("STA", &cpu::STA, &cpu::ZP0, 3),
        bind("STX", &cpu::STX, &cpu::ZP0, 3), bind("???", &cpu::XXX, &cpu::IMP, 3),
        bind("DEY", &cpu::DEY, &cpu::IMP, 2), bind("???", &cpu::NOP, &cpu::IMP, 2),
        bind("TXA", &cpu::TXA, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 2),
        bind("STY", &cpu::STY, &cpu::ABS, 4), bind("STA", &cpu::STA, &cpu::ABS, 4),
        bind("STX", &cpu::STX, &cpu::ABS, 4), bind("???", &cpu::XXX, &cpu::IMP, 4),
        bind("BCC", &cpu::BCC, &cpu::REL, 2), bind("STA", &cpu::STA, &cpu::IZY, 6),
        bind("???", &cpu::XXX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("STY", &cpu::STY, &cpu::ZPX, 4), bind("STA", &cpu::STA, &cpu::ZPX, 4),
        bind("STX", &cpu::STX, &cpu::ZPY, 4), bind("???", &cpu::XXX, &cpu::IMP, 4),
        bind("TYA", &cpu::TYA, &cpu::IMP, 2), bind("STA", &cpu::STA, &cpu::ABY, 5),
        bind("TXS", &cpu::TXS, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 5),
        bind("???", &cpu::NOP, &cpu::IMP, 5), bind("STA", &cpu::STA, &cpu::ABX, 5),
        bind("???", &cpu::XXX, &cpu::IMP, 5), bind("???", &cpu::XXX, &cpu::IMP, 5),
        bind("LDY", &cpu::LDY, &cpu::IMM, 2), bind("LDA", &cpu::LDA, &cpu::IZX, 6),
        bind("LDX", &cpu::LDX, &cpu::IMM, 2), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("LDY", &cpu::LDY, &cpu::ZP0, 3), bind("LDA", &cpu::LDA, &cpu::ZP0, 3),
        bind("LDX", &cpu::LDX, &cpu::ZP0, 3), bind("???", &cpu::XXX, &cpu::IMP, 3),
        bind("TAY", &cpu::TAY, &cpu::IMP, 2), bind("LDA", &cpu::LDA, &cpu::IMM, 2),
        bind("TAX", &cpu::TAX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 2),
        bind("LDY", &cpu::LDY, &cpu::ABS, 4), bind("LDA", &cpu::LDA, &cpu::ABS, 4),
        bind("LDX", &cpu::LDX, &cpu::ABS, 4), bind("???", &cpu::XXX, &cpu::IMP, 4),
        bind("BCS", &cpu::BCS, &cpu::REL, 2), bind("LDA", &cpu::LDA, &cpu::IZY, 5),
        bind("???", &cpu::XXX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 5),
        bind("LDY", &cpu::LDY, &cpu::ZPX, 4), bind("LDA", &cpu::LDA, &cpu::ZPX, 4),
        bind("LDX", &cpu::LDX, &cpu::ZPY, 4), bind("???", &cpu::XXX, &cpu::IMP, 4),
        bind("CLV", &cpu::CLV, &cpu::IMP, 2), bind("LDA", &cpu::LDA, &cpu::ABY, 4),
        bind("TSX", &cpu::TSX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 4),
        bind("LDY", &cpu::LDY, &cpu::ABX, 4), bind("LDA", &cpu::LDA, &cpu::ABX, 4),
        bind("LDX", &cpu::LDX, &cpu::ABY, 4), bind("???", &cpu::XXX, &cpu::IMP, 4),
        bind("CPY", &cpu::CPY, &cpu::IMM, 2), bind("CMP", &cpu::CMP, &cpu::IZX, 6),
        bind("???", &cpu::NOP, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 8),
        bind("CPY", &cpu::CPY, &cpu::ZP0, 3), bind("CMP", &cpu::CMP, &cpu::ZP0, 3),
        bind("DEC", &cpu::DEC, &cpu::ZP0, 5), bind("???", &cpu::XXX, &cpu::IMP, 5),
        bind("INY", &cpu::INY, &cpu::IMP, 2), bind("CMP", &cpu::CMP, &cpu::IMM, 2),
        bind("DEX", &cpu::DEX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 2),
        bind("CPY", &cpu::CPY, &cpu::ABS, 4), bind("CMP", &cpu::CMP, &cpu::ABS, 4),
        bind("DEC", &cpu::DEC, &cpu::ABS, 6), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("BNE", &cpu::BNE, &cpu::REL, 2), bind("CMP", &cpu::CMP, &cpu::IZY, 5),
        bind("???", &cpu::XXX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 8),
        bind("???", &cpu::NOP, &cpu::IMP, 4), bind("CMP", &cpu::CMP, &cpu::ZPX, 4),
        bind("DEC", &cpu::DEC, &cpu::ZPX, 6), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("CLD", &cpu::CLD, &cpu::IMP, 2), bind("CMP", &cpu::CMP, &cpu::ABY, 4),
        bind("NOP", &cpu::NOP, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 7),
        bind("???", &cpu::NOP, &cpu::IMP, 4), bind("CMP", &cpu::CMP, &cpu::ABX, 4),
        bind("DEC", &cpu::DEC, &cpu::ABX, 7), bind("???", &cpu::XXX, &cpu::IMP, 7),
        bind("CPX", &cpu::CPX, &cpu::IMM, 2), bind("SBC", &cpu::SBC, &cpu::IZX, 6),
        bind("???", &cpu::NOP, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 8),
        bind("CPX", &cpu::CPX, &cpu::ZP0, 3), bind("SBC", &cpu::SBC, &cpu::ZP0, 3),
        bind("INC", &cpu::INC, &cpu::ZP0, 5), bind("???", &cpu::XXX, &cpu::IMP, 5),
        bind("INX", &cpu::INX, &cpu::IMP, 2), bind("SBC", &cpu::SBC, &cpu::IMM, 2),
        bind("NOP", &cpu::NOP, &cpu::IMP, 2), bind("???", &cpu::SBC, &cpu::IMP, 2),
        bind("CPX", &cpu::CPX, &cpu::ABS, 4), bind("SBC", &cpu::SBC, &cpu::ABS, 4),
        bind("INC", &cpu::INC, &cpu::ABS, 6), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("BEQ", &cpu::BEQ, &cpu::REL, 2), bind("SBC", &cpu::SBC, &cpu::IZY, 5),
        bind("???", &cpu::XXX, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 8),
        bind("???", &cpu::NOP, &cpu::IMP, 4), bind("SBC", &cpu::SBC, &cpu::ZPX, 4),
        bind("INC", &cpu::INC, &cpu::ZPX, 6), bind("???", &cpu::XXX, &cpu::IMP, 6),
        bind("SED", &cpu::SED, &cpu::IMP, 2), bind("SBC", &cpu::SBC, &cpu::ABY, 4),
        bind("NOP", &cpu::NOP, &cpu::IMP, 2), bind("???", &cpu::XXX, &cpu::IMP, 7),
        bind("???", &cpu::NOP, &cpu::IMP, 4), bind("SBC", &cpu::SBC, &cpu::ABX, 4),
        bind("INC", &cpu::INC, &cpu::ABX, 7), bind("???", &cpu::XXX, &cpu::IMP, 7),
    };
}

void cpu6502::ConnectBus(const std::shared_ptr<Bus> &n) {
    bus = n;
}

u8 cpu6502::Read(const u16 address) const {
    return bus->Read(address);
}

void cpu6502::Write(const u16 address, const u8 data) const {
    bus->Write(address, data);
}

u8 cpu6502::GetFlag(const FLAG6502 f) const {
    return (STATUS & static_cast<u8>(f)) > 0 ? 1 : 0;
}

// Sets or clears a specific bit of the status register
void cpu6502::SetFlag(const FLAG6502 f, const bool v) {
    if (v)
        STATUS |= static_cast<u8>(f);
    else
        STATUS &= ~static_cast<u8>(f);
}

void cpu6502::Clock() {
    if (0 == cycles) {
        opcode = Read(PC);
        ++PC;

        cycles = lookup[opcode].cycles;

        const u8 additional_cycle1 = lookup[opcode].operate();
        const u8 additional_cycle2 = lookup[opcode].addrMode();

        cycles += additional_cycle1 + additional_cycle2;
    }

    --cycles;
}

u8 cpu6502::IMP() {
    fetched_ = A;
    return 0;
}

u8 cpu6502::IMM() {
    addr_abs = PC++;
    return 0;
}

u8 cpu6502::ZP0() {
    addr_abs = Read(PC);
    PC++;
    addr_abs &= 0xFF;
    return 0;
}

u8 cpu6502::ZPX() {
    addr_abs = Read(PC) + X ;
    PC++;
    addr_abs &= 0xFF;
    return 0;
}

u8 cpu6502::ZPY() {
    addr_abs = Read(PC) + Y ;
    PC++;
    addr_abs &= 0xFF;
    return 0;
}

u8 cpu6502::ABS() {
    const u16 lower = Read(PC);
    PC++;
    const u16 higher = Read(PC);
    PC++;

    addr_abs = (higher << 8) | lower;

    return 0;
}

u8 cpu6502::ABX() {
    const u16 lower = Read(PC);
    PC++;
    const u16 higher = Read(PC);
    PC++;

    addr_abs = (higher << 8) | lower;
    addr_abs += X;


    if ((addr_abs & 0xFF) != higher << 8) {
        return 1;
    }

    return 0;
}

u8 cpu6502::ABY() {
    const u16 lower = Read(PC);
    PC++;
    const u16 higher = Read(PC);
    PC++;

    addr_abs = (higher << 8) | lower;
    addr_abs += Y;

    if ((addr_abs & 0xFF) != higher << 8) {
        return 1;
    }

    return 0;
}

// Indirect addressing, this is a sort of 6502 implementation of a concept called "pointer" in C
u8 cpu6502::IND() {
    u16 ptr_lower = Read(PC);
    PC++;
    u16 ptr_higher = Read(PC);
    PC++;

    u16 ptr = (ptr_higher << 8) | ptr_lower;

    // Simulate page boundary hardware bug
    if (ptr_lower == 0x00FF) {
        addr_abs = (Read(ptr) << 8) | Read(ptr + 0);
    }
    // Normal behaviour
    else {
        addr_abs = (Read(ptr + 1) << 8) | Read(ptr + 0);
    }
    
}