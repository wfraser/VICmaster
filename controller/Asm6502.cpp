#include <cstdint>
#include <exception>
#include <string>
#include <memory>
#include "Asm6502.h"

using namespace std;

#define xxx static_cast<uint8_t>(Asm6502::Instruction::INVALID)
const uint8_t Asm6502::Opcodes[] = {
    //          Implied Immed   A       Rel     ZP      ZPX     ZPY     Abs     AbsX    AbsY    Ind     IndX    IndY
    /* ADC */   xxx,    0x69,   xxx,    xxx,    0x65,   0x75,   xxx,    0x6d,   0x7d,   0x79,   xxx,    0x61,   0x71,
    /* AND */   xxx,    0x29,   xxx,    xxx,    0x25,   0x35,   xxx,    0x2d,   0x3d,   0x39,   xxx,    0x21,   0x31,
    /* ASL */   xxx,    xxx,    0x0a,   xxx,    0x06,   0x16,   xxx,    0x0e,   0x1e,   xxx,    xxx,    xxx,    xxx,
    /* BCC */   xxx,    xxx,    xxx,    0x90,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* BCS */   xxx,    xxx,    xxx,    0xb0,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* BEQ */   0xf0,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* BIT */   xxx,    xxx,    xxx,    xxx,    0x24,   xxx,    xxx,    0x2c,   xxx,    xxx,    xxx,    xxx,    xxx,
    /* BMI */   xxx,    xxx,    xxx,    0x30,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* BNE */   xxx,    xxx,    xxx,    0xd0,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* BPL */   xxx,    xxx,    xxx,    0x10,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* BRK */   0x00,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* BVC */   xxx,    xxx,    xxx,    0x50,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* BVS */   xxx,    xxx,    xxx,    0x70,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* CLC */   0x18,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* CLD */   0xd8,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* CLI */   0x58,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* CLV */   0xb8,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* CMP */   xxx,    0xc9,   xxx,    xxx,    0xc5,   0xd5,   xxx,    0xcd,   0xdd,   0xd9,   xxx,    0xc1,   0xd1,
    /* CPX */   xxx,    0xe0,   xxx,    xxx,    0xe4,   xxx,    xxx,    0xec,   xxx,    xxx,    xxx,    xxx,    xxx,
    /* CPY */   xxx,    0xc0,   xxx,    xxx,    0xc4,   xxx,    xxx,    0xcc,   xxx,    xxx,    xxx,    xxx,    xxx,
    /* DEC */   xxx,    xxx,    xxx,    xxx,    0xc6,   0xd6,   xxx,    0xce,   0xde,   xxx,    xxx,    xxx,    xxx,
    /* DEX */   0xca,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* DEY */   0x88,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* EOR */   xxx,    0x49,   xxx,    xxx,    0x45,   0x55,   xxx,    0x4d,   0x5d,   0x59,   xxx,    0x41,   0x51,
    /* INC */   xxx,    xxx,    xxx,    xxx,    0xe6,   0xf6,   xxx,    0xee,   0xfe,   xxx,    xxx,    xxx,    xxx,
    /* INX */   0xe8,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* INY */   0xc8,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* JMP */   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    0x4c,   xxx,    xxx,    0x6c,   xxx,    xxx,

    //          Implied Immed   A       Rel     ZP      ZPX     ZPY     Abs     AbsX    AbsY    Ind     IndX    IndY
    /* JSR */   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    0x20,   xxx,    xxx,    xxx,    xxx,    xxx,
    /* LDA */   xxx,    0xa9,   xxx,    xxx,    0xa5,   0xb5,   xxx,    0xad,   0xbd,   0xb9,   xxx,    0xa1,   0xb1,
    /* LDX */   xxx,    0xa2,   xxx,    xxx,    0xa6,   xxx,    0xb6,   0xae,   xxx,    0xbe,   xxx,    xxx,    xxx,
    /* LDY */   xxx,    0xa0,   xxx,    xxx,    0xa4,   0xb4,   xxx,    0xac,   0xbc,   xxx,    xxx,    xxx,    xxx,
    /* LSR */   xxx,    xxx,    0x4a,   xxx,    0x46,   0x56,   xxx,    0x4e,   0x5e,   xxx,    xxx,    xxx,    xxx,
    /* NOP */   0xea,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* ORA */   xxx,    0x09,   xxx,    xxx,    0x05,   0x15,   xxx,    0x0d,   0x1d,   0x19,   xxx,    0x01,   0x11,
    /* PHA */   0x48,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* PHP */   0x08,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* PLA */   0x68,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* PLP */   0x28,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* ROL */   xxx,    xxx,    0x2a,   xxx,    0x26,   0x36,   xxx,    0x2e,   0x3e,   xxx,    xxx,    xxx,    xxx,
    /* ROR */   xxx,    xxx,    0x6a,   xxx,    0x66,   0x76,   xxx,    0x6e,   0x7e,   xxx,    xxx,    xxx,    xxx,
    /* RTI */   0x40,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* RTS */   0x60,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* SBC */   xxx,    0xe9,   xxx,    xxx,    0xe5,   0xf5,   xxx,    0xed,   0xfd,   0xf9,   xxx,    0xe1,   0xf1,
    /* SEC */   0x38,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* SED */   0xf8,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* SEI */   0x78,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* STA */   xxx,    xxx,    xxx,    xxx,    0x85,   0x95,   xxx,    0x8d,   0x9d,   0x99,   xxx,    0x81,   0x91,
    /* STX */   xxx,    xxx,    xxx,    xxx,    0x86,   xxx,    0x96,   0x8e,   xxx,    xxx,    xxx,    xxx,    xxx,
    /* STY */   xxx,    xxx,    xxx,    xxx,    0x84,   0x94,   xxx,    0x8c,   xxx,    xxx,    xxx,    xxx,    xxx,
    /* TAX */   0xaa,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* TAY */   0xa8,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* TSX */   0xba,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* TXA */   0x8a,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* TXS */   0x9a,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,
    /* TYA */   0x98,   xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx,    xxx
};

Asm6502::Asm6502(std::shared_ptr<IOLayer> io)
    : CurrentAddress(0)
    , m_io(io)
{
}

uint8_t Asm6502::Opcode(Instruction i, Mode m)
{
    return Asm6502::Opcodes[static_cast<size_t>(i) * static_cast<size_t>(Mode::MAX_VALUE) + static_cast<size_t>(m)];
}

void Asm6502::EmitAddr(uint16_t addr)
{
#ifdef HOST_BIG_ENDIAN
    EmitByte(static_cast<uint8_t>(addr >> 8));
    EmitByte(static_cast<uint8_t>(addr));
#else
    EmitByte(static_cast<uint8_t>(addr));
    EmitByte(static_cast<uint8_t>(addr >> 8));
#endif
}

void Asm6502::EmitByte(uint8_t byte)
{
    m_io->Output(byte, CurrentAddress);
    CurrentAddress++;
}

void Asm6502::Emit(InstrImplied i)
{
    EmitByte(static_cast<uint8_t>(i));
}

void Asm6502::EmitImm(InstrImmed i, uint8_t value)
{
    EmitByte(static_cast<uint8_t>(i));
    EmitByte(value);
}

void Asm6502::EmitA(InstrA i)
{
    EmitByte(static_cast<uint8_t>(i));
}

void Asm6502::EmitRel(InstrRel i, uint8_t addrOffset)
{
    EmitByte(static_cast<uint8_t>(i));
    EmitByte(addrOffset);
}

void Asm6502::EmitZP(InstrZP i, uint8_t address)
{
    EmitByte(static_cast<uint8_t>(i));
    EmitByte(address);
}

void Asm6502::EmitZPX(InstrZPX i, uint8_t address)
{
    EmitByte(static_cast<uint8_t>(i));
    EmitByte(address);
}

void Asm6502::EmitZPY(InstrZPY i, uint8_t address)
{
    EmitByte(static_cast<uint8_t>(i));
    EmitByte(address);
}

void Asm6502::EmitAbs(InstrAbs i, uint16_t address)
{
    EmitByte(static_cast<uint8_t>(i));
    EmitAddr(address);
}

void Asm6502::EmitAbsX(InstrAbsX i, uint16_t address)
{
    EmitByte(static_cast<uint8_t>(i));
    EmitAddr(address);
}

void Asm6502::EmitAbsY(InstrAbsY i, uint16_t address)
{
    EmitByte(static_cast<uint8_t>(i));
    EmitAddr(address);
}

void Asm6502::EmitInd(InstrInd i, uint8_t address)
{
    EmitByte(static_cast<uint8_t>(i));
    EmitByte(address);
}

void Asm6502::EmitIndX(InstrIndX i, uint8_t address)
{
    EmitByte(static_cast<uint8_t>(i));
    EmitByte(address);
}

void Asm6502::EmitIndY(InstrIndY i, uint8_t address)
{
    EmitByte(static_cast<uint8_t>(i));
    EmitByte(address);
}