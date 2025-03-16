#pragma once

#include <memory>
#include <functional>

class Bus;

class cpu6502 {
public:
	explicit cpu6502();

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
    u8 A       = 0x00;
    u8 X       = 0x00;
    u8 Y       = 0x00;
    u8 SP      = 0x00;
    u16 PC     = 0x0000;
    u8 STATUS  = 0x00;

    //// Addressing Modes
    u8 IMP(); u8 IMM();
    u8 ZP0() ; u8 ZPX();
    u8 ZPY(); u8 REL();
    u8 ABS(); u8 ABX();
    u8 ABY(); u8 IND();
    u8 IZX(); u8 IZY();

    ////Opcodes
    uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
    uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
    uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
    uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
    uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
    uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
    uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
    uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
    uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
    uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
    uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
    uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
    uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
    uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

    u8 XXX();

    void Clock();
    void Reset();
    void InterruptRequest();
    void NonMaskableInterruptRequest();

    u8 Fetch();
    u8 fetched_ = 0x00;

    u16 addr_abs = 0x0000;
    u8 addr_rel = 0x00;
    u8 opcode = 0x00;
    u8 cycles = 0;

	struct Instruction {
		std::string name;
		std::function<u8()> operate;
		std::function<u8()> addrMode;
		u8 cycles = 0;
	};

	std::vector<Instruction> lookup;

public:

    void ConnectBus(const std::shared_ptr<Bus> &n );

private:
    std::shared_ptr<Bus> bus;

    u8 Read(u16 address) const;

    void Write(u16 address, u8 data) const;
};
