#include <pch.h>

#include <cpu6502.h>
#include <Bus.h>

using a = cpu6502;

cpu6502::cpu6502() {
    auto bind = [this](const std::string &name, auto op, auto mode, const u8 cycles){
        return Instruction{name, op, mode, cycles};
    };

        lookup =
        {
            bind("BRK", &a::BRK, &a::IMM, 7), bind("ORA", &a::ORA, &a::IZX, 6), bind("???", &a::XXX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 8), bind("???", &a::NOP, &a::IMP, 3), bind("ORA", &a::ORA, &a::ZP0, 3), bind("ASL", &a::ASL, &a::ZP0, 5), bind("???", &a::XXX, &a::IMP, 5), bind("PHP", &a::PHP, &a::IMP, 3), bind("ORA", &a::ORA, &a::IMM, 2), bind("ASL", &a::ASL, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 2), bind("???", &a::NOP, &a::IMP, 4), bind("ORA", &a::ORA, &a::ABS, 4), bind("ASL", &a::ASL, &a::ABS, 6), bind("???", &a::XXX, &a::IMP, 6),
            bind("BPL", &a::BPL, &a::REL, 2), bind("ORA", &a::ORA, &a::IZY, 5), bind("???", &a::XXX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 8), bind("???", &a::NOP, &a::IMP, 4), bind("ORA", &a::ORA, &a::ZPX, 4), bind("ASL", &a::ASL, &a::ZPX, 6), bind("???", &a::XXX, &a::IMP, 6), bind("CLC", &a::CLC, &a::IMP, 2), bind("ORA", &a::ORA, &a::ABY, 4), bind("???", &a::NOP, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 7), bind("???", &a::NOP, &a::IMP, 4), bind("ORA", &a::ORA, &a::ABX, 4), bind("ASL", &a::ASL, &a::ABX, 7), bind("???", &a::XXX, &a::IMP, 7),
            bind("JSR", &a::JSR, &a::ABS, 6), bind("AND", &a::AND, &a::IZX, 6), bind("???", &a::XXX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 8), bind("BIT", &a::BIT, &a::ZP0, 3), bind("AND", &a::AND, &a::ZP0, 3), bind("ROL", &a::ROL, &a::ZP0, 5), bind("???", &a::XXX, &a::IMP, 5), bind("PLP", &a::PLP, &a::IMP, 4), bind("AND", &a::AND, &a::IMM, 2), bind("ROL", &a::ROL, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 2), bind("BIT", &a::BIT, &a::ABS, 4), bind("AND", &a::AND, &a::ABS, 4), bind("ROL", &a::ROL, &a::ABS, 6), bind("???", &a::XXX, &a::IMP, 6),
            bind("BMI", &a::BMI, &a::REL, 2), bind("AND", &a::AND, &a::IZY, 5), bind("???", &a::XXX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 8), bind("???", &a::NOP, &a::IMP, 4), bind("AND", &a::AND, &a::ZPX, 4), bind("ROL", &a::ROL, &a::ZPX, 6), bind("???", &a::XXX, &a::IMP, 6), bind("SEC", &a::SEC, &a::IMP, 2), bind("AND", &a::AND, &a::ABY, 4), bind("???", &a::NOP, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 7), bind("???", &a::NOP, &a::IMP, 4), bind("AND", &a::AND, &a::ABX, 4), bind("ROL", &a::ROL, &a::ABX, 7), bind("???", &a::XXX, &a::IMP, 7),
            bind("RTI", &a::RTI, &a::IMP, 6), bind("EOR", &a::EOR, &a::IZX, 6), bind("???", &a::XXX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 8), bind("???", &a::NOP, &a::IMP, 3), bind("EOR", &a::EOR, &a::ZP0, 3), bind("LSR", &a::LSR, &a::ZP0, 5), bind("???", &a::XXX, &a::IMP, 5), bind("PHA", &a::PHA, &a::IMP, 3), bind("EOR", &a::EOR, &a::IMM, 2), bind("LSR", &a::LSR, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 2), bind("JMP", &a::JMP, &a::ABS, 3), bind("EOR", &a::EOR, &a::ABS, 4), bind("LSR", &a::LSR, &a::ABS, 6), bind("???", &a::XXX, &a::IMP, 6),
            bind("BVC", &a::BVC, &a::REL, 2), bind("EOR", &a::EOR, &a::IZY, 5), bind("???", &a::XXX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 8), bind("???", &a::NOP, &a::IMP, 4), bind("EOR", &a::EOR, &a::ZPX, 4), bind("LSR", &a::LSR, &a::ZPX, 6), bind("???", &a::XXX, &a::IMP, 6), bind("CLI", &a::CLI, &a::IMP, 2), bind("EOR", &a::EOR, &a::ABY, 4), bind("???", &a::NOP, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 7), bind("???", &a::NOP, &a::IMP, 4), bind("EOR", &a::EOR, &a::ABX, 4), bind("LSR", &a::LSR, &a::ABX, 7), bind("???", &a::XXX, &a::IMP, 7),
            bind("RTS", &a::RTS, &a::IMP, 6), bind("ADC", &a::ADC, &a::IZX, 6), bind("???", &a::XXX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 8), bind("???", &a::NOP, &a::IMP, 3), bind("ADC", &a::ADC, &a::ZP0, 3), bind("ROR", &a::ROR, &a::ZP0, 5), bind("???", &a::XXX, &a::IMP, 5), bind("PLA", &a::PLA, &a::IMP, 4), bind("ADC", &a::ADC, &a::IMM, 2), bind("ROR", &a::ROR, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 2), bind("JMP", &a::JMP, &a::IND, 5), bind("ADC", &a::ADC, &a::ABS, 4), bind("ROR", &a::ROR, &a::ABS, 6), bind("???", &a::XXX, &a::IMP, 6),
            bind("BVS", &a::BVS, &a::REL, 2), bind("ADC", &a::ADC, &a::IZY, 5), bind("???", &a::XXX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 8), bind("???", &a::NOP, &a::IMP, 4), bind("ADC", &a::ADC, &a::ZPX, 4), bind("ROR", &a::ROR, &a::ZPX, 6), bind("???", &a::XXX, &a::IMP, 6), bind("SEI", &a::SEI, &a::IMP, 2), bind("ADC", &a::ADC, &a::ABY, 4), bind("???", &a::NOP, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 7), bind("???", &a::NOP, &a::IMP, 4), bind("ADC", &a::ADC, &a::ABX, 4), bind("ROR", &a::ROR, &a::ABX, 7), bind("???", &a::XXX, &a::IMP, 7),
            bind("???", &a::NOP, &a::IMP, 2), bind("STA", &a::STA, &a::IZX, 6), bind("???", &a::NOP, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 6), bind("STY", &a::STY, &a::ZP0, 3), bind("STA", &a::STA, &a::ZP0, 3), bind("STX", &a::STX, &a::ZP0, 3), bind("???", &a::XXX, &a::IMP, 3), bind("DEY", &a::DEY, &a::IMP, 2), bind("???", &a::NOP, &a::IMP, 2), bind("TXA", &a::TXA, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 2), bind("STY", &a::STY, &a::ABS, 4), bind("STA", &a::STA, &a::ABS, 4), bind("STX", &a::STX, &a::ABS, 4), bind("???", &a::XXX, &a::IMP, 4),
            bind("BCC", &a::BCC, &a::REL, 2), bind("STA", &a::STA, &a::IZY, 6), bind("???", &a::XXX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 6), bind("STY", &a::STY, &a::ZPX, 4), bind("STA", &a::STA, &a::ZPX, 4), bind("STX", &a::STX, &a::ZPY, 4), bind("???", &a::XXX, &a::IMP, 4), bind("TYA", &a::TYA, &a::IMP, 2), bind("STA", &a::STA, &a::ABY, 5), bind("TXS", &a::TXS, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 5), bind("???", &a::NOP, &a::IMP, 5), bind("STA", &a::STA, &a::ABX, 5), bind("???", &a::XXX, &a::IMP, 5), bind("???", &a::XXX, &a::IMP, 5),
            bind("LDY", &a::LDY, &a::IMM, 2), bind("LDA", &a::LDA, &a::IZX, 6), bind("LDX", &a::LDX, &a::IMM, 2), bind("???", &a::XXX, &a::IMP, 6), bind("LDY", &a::LDY, &a::ZP0, 3), bind("LDA", &a::LDA, &a::ZP0, 3), bind("LDX", &a::LDX, &a::ZP0, 3), bind("???", &a::XXX, &a::IMP, 3), bind("TAY", &a::TAY, &a::IMP, 2), bind("LDA", &a::LDA, &a::IMM, 2), bind("TAX", &a::TAX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 2), bind("LDY", &a::LDY, &a::ABS, 4), bind("LDA", &a::LDA, &a::ABS, 4), bind("LDX", &a::LDX, &a::ABS, 4), bind("???", &a::XXX, &a::IMP, 4),
            bind("BCS", &a::BCS, &a::REL, 2), bind("LDA", &a::LDA, &a::IZY, 5), bind("???", &a::XXX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 5), bind("LDY", &a::LDY, &a::ZPX, 4), bind("LDA", &a::LDA, &a::ZPX, 4), bind("LDX", &a::LDX, &a::ZPY, 4), bind("???", &a::XXX, &a::IMP, 4), bind("CLV", &a::CLV, &a::IMP, 2), bind("LDA", &a::LDA, &a::ABY, 4), bind("TSX", &a::TSX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 4), bind("LDY", &a::LDY, &a::ABX, 4), bind("LDA", &a::LDA, &a::ABX, 4), bind("LDX", &a::LDX, &a::ABY, 4), bind("???", &a::XXX, &a::IMP, 4),
            bind("CPY", &a::CPY, &a::IMM, 2), bind("CMP", &a::CMP, &a::IZX, 6), bind("???", &a::NOP, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 8), bind("CPY", &a::CPY, &a::ZP0, 3), bind("CMP", &a::CMP, &a::ZP0, 3), bind("DEC", &a::DEC, &a::ZP0, 5), bind("???", &a::XXX, &a::IMP, 5), bind("INY", &a::INY, &a::IMP, 2), bind("CMP", &a::CMP, &a::IMM, 2), bind("DEX", &a::DEX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 2), bind("CPY", &a::CPY, &a::ABS, 4), bind("CMP", &a::CMP, &a::ABS, 4), bind("DEC", &a::DEC, &a::ABS, 6), bind("???", &a::XXX, &a::IMP, 6),
            bind("BNE", &a::BNE, &a::REL, 2), bind("CMP", &a::CMP, &a::IZY, 5), bind("???", &a::XXX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 8), bind("???", &a::NOP, &a::IMP, 4), bind("CMP", &a::CMP, &a::ZPX, 4), bind("DEC", &a::DEC, &a::ZPX, 6), bind("???", &a::XXX, &a::IMP, 6), bind("CLD", &a::CLD, &a::IMP, 2), bind("CMP", &a::CMP, &a::ABY, 4), bind("NOP", &a::NOP, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 7), bind("???", &a::NOP, &a::IMP, 4), bind("CMP", &a::CMP, &a::ABX, 4), bind("DEC", &a::DEC, &a::ABX, 7), bind("???", &a::XXX, &a::IMP, 7),
            bind("CPX", &a::CPX, &a::IMM, 2), bind("SBC", &a::SBC, &a::IZX, 6), bind("???", &a::NOP, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 8), bind("CPX", &a::CPX, &a::ZP0, 3), bind("SBC", &a::SBC, &a::ZP0, 3), bind("INC", &a::INC, &a::ZP0, 5), bind("???", &a::XXX, &a::IMP, 5), bind("INX", &a::INX, &a::IMP, 2), bind("SBC", &a::SBC, &a::IMM, 2), bind("NOP", &a::NOP, &a::IMP, 2), bind("???", &a::SBC, &a::IMP, 2), bind("CPX", &a::CPX, &a::ABS, 4), bind("SBC", &a::SBC, &a::ABS, 4), bind("INC", &a::INC, &a::ABS, 6), bind("???", &a::XXX, &a::IMP, 6),
            bind("BEQ", &a::BEQ, &a::REL, 2), bind("SBC", &a::SBC, &a::IZY, 5), bind("???", &a::XXX, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 8), bind("???", &a::NOP, &a::IMP, 4), bind("SBC", &a::SBC, &a::ZPX, 4), bind("INC", &a::INC, &a::ZPX, 6), bind("???", &a::XXX, &a::IMP, 6), bind("SED", &a::SED, &a::IMP, 2), bind("SBC", &a::SBC, &a::ABY, 4), bind("NOP", &a::NOP, &a::IMP, 2), bind("???", &a::XXX, &a::IMP, 7), bind("???", &a::NOP, &a::IMP, 4), bind("SBC", &a::SBC, &a::ABX, 4), bind("INC", &a::INC, &a::ABX, 7), bind("???", &a::XXX, &a::IMP, 7),
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
