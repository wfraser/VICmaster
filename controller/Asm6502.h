#pragma once

#include "IOLayer.h"

class Asm6502
{
public:
    // Implied (no arguments)
    enum class InstrImplied : uint8_t
    {
        BEQ = 0xf0,
        BRK = 0x00,
        CLC = 0x18,
        CLD = 0xd8,
        CLI = 0x58,
        CLV = 0xb8,
        DEX = 0xca,
        DEY = 0x88,
        INX = 0xe8,
        INY = 0xc8,
        NOP = 0xea,
        PHA = 0x48,
        PHP = 0x08,
        PLA = 0x68,
        PLP = 0x28,
        RTI = 0x40,
        RTS = 0x60,
        SEC = 0x38,
        SED = 0xf8,
        SEI = 0x78,
        TAX = 0xaa,
        TAY = 0xa8,
        TSX = 0xba,
        TXA = 0x8a,
        TXS = 0x9a,
        TYA = 0x98,
    };

    // Immediate
    enum class InstrImmed : uint8_t
    {
        ADC = 0x69,
        AND = 0x29,
        CMD = 0xc9,
        CPX = 0xe0,
        CPY = 0xc0,
        EOR = 0x49,
        LDA = 0xa9,
        LDX = 0xa2,
        LDY = 0xa0,
        ORA = 0x09,
        SBC = 0xe9,
    };

    // 'A' Register
    enum class InstrA : uint8_t
    {
        ASL = 0x0a,
        LSR = 0x4a,
        ROL = 0x2a,
        ROR = 0x2a,
    };

    // Relative
    enum class InstrRel : uint8_t
    {
        BCC = 0x90,
        BCS = 0xb0,
        BMI = 0x30,
        BNE = 0xd0,
        BPL = 0x10,
        BVC = 0x50,
        BVS = 0x70,
    };

    // Zero Page
    enum class InstrZP : uint8_t
    {
        ADC = 0x65,
        AND = 0x25,
        ASL = 0x06,
        BIT = 0x24,
        CMP = 0xc5,
        CPX = 0xe4,
        CPY = 0xc4,
        DEC = 0xc6,
        EOR = 0x45,
        INC = 0xe6,
        LDA = 0xa5,
        LDX = 0xa6,
        LDY = 0xa4,
        LSR = 0x46,
        ORA = 0x05,
        ROL = 0x26,
        ROR = 0x66,
        SBC = 0xe5,
        STA = 0x85,
        STX = 0x86,
        STY = 0x84,
    };

    // Zero Page Indexed by 'X' Register
    enum class InstrZPX : uint8_t
    {
        ADC = 0x75,
        AND = 0x35,
        ASL = 0x16,
        CMP = 0xd5,
        DEC = 0xd6,
        EOR = 0x55,
        INC = 0xf6,
        LDA = 0xb5,
        LDY = 0xb4,
        LSR = 0x56,
        ORA = 0x15,
        ROL = 0x36,
        ROR = 0x76,
        SBC = 0xf5,
        STA = 0x95,
        STY = 0x94,
    };

    // Zero Page Indexed by 'Y' Register
    enum class InstrZPY : uint8_t
    {
        LDX = 0xb6,
        STX = 0x96,
    };

    // Absolute
    enum class InstrAbs : uint8_t
    {
        ADC = 0x6d,
        AND = 0x2d,
        ASL = 0x0e,
        BIT = 0x2c,
        CMP = 0xcd,
        CPX = 0xec,
        CPY = 0xcc,
        DEC = 0xce,
        EOR = 0x4d,
        INC = 0xee,
        JMP = 0x4c,
        JSR = 0x20,
        LDA = 0xad,
        LDX = 0xae,
        LDY = 0xac,
        LSR = 0x4e,
        ORA = 0x0d,
        ROL = 0x2e,
        ROR = 0x6e,
        SBC = 0xed,
        STA = 0x8d,
        STX = 0x8e,
        STY = 0x8c,
    };

    // Absolute Indexed by 'X' Register
    enum class InstrAbsX : uint8_t
    {
        ADC = 0x7d,
        AND = 0x3d,
        ASL = 0x1e,
        CMP = 0xdd,
        DEC = 0xde,
        EOR = 0x5d,
        INC = 0xfe,
        LDA = 0xbd,
        LDY = 0xbc,
        LSR = 0x5e,
        ORA = 0x1d,
        ROL = 0x3e,
        ROR = 0x7e,
        SBC = 0xfd,
        STA = 0x9d,
    };

    // Absolute Indexed by 'Y' Register
    enum class InstrAbsY : uint8_t
    {
        ADC = 0x79,
        AND = 0x39,
        CMP = 0xd9,
        EOR = 0x59,
        LDA = 0xb9,
        LDX = 0xbe,
        ORA = 0x19,
        SBC = 0xf9,
        STA = 0x99,
    };

    // Indirect from Pointer in the Zero Page
    enum class InstrInd : uint8_t
    {
        JMP = 0x6c,
    };

    // Indirect from Pointer in the Zero Page Indexed by 'X' Register Before Dereferencing
    enum class InstrIndX : uint8_t
    {
        ADC = 0x61,
        AND = 0x21,
        CMP = 0xc1,
        EOR = 0x41,
        LDA = 0xa1,
        ORA = 0x01,
        SBC = 0xe1,
        STA = 0x81,
    };

    // Indirect from Pointer in the Zero Page Indexed by 'Y' Register After Dereferencing
    enum class InstrIndY : uint8_t
    {
        ADC = 0x71,
        AND = 0x31,
        CMP = 0xd1,
        EOR = 0x51,
        LDA = 0xb1,
        ORA = 0x11,
        SBC = 0xf1,
        STA = 0x91,
    };

    enum class Instruction : uint8_t
    {
        ADC = 0,// Add to A and Carry
        AND,    // AND with A
        ASL,    // Arithmetic Shift Left
        BCC,    // Branch if Carry is Clear
        BCS,    // Branch if Carry is Set
        BEQ,    // Branch if Equal (Z is Set)
        BIT,    // Test bits in Memory by masking with A
        BMI,    // Branch if Sign is Set
        BNE,    // Branch if Not Equal (Z is Clear)
        BPL,    // Branch if Sign is Clear
        BRK,    // IRQ
        BVC,    // Branch if Overflow is Clear
        BVS,    // Branch if Overflow is Set
        CLC,    // Clear Carry
        CLD,    // Clear Decimal
        CLI,    // Clear Interrupt Disable
        CLV,    // Clear Overflow
        CMP,    // Compare with A
        CPX,    // Compare with X
        CPY,    // Compare with Y
        DEC,    // Decrement by One
        DEX,    // Decrement X
        DEY,    // Decrement Y
        EOR,    // XOR with A
        INC,    // Increment by One
        INX,    // Increment X
        INY,    // Increment Y
        JMP,    // Branch Unconditionally
        JSR,    // Jump to Subroutine
        LDA,    // Load A
        LDX,    // Load X
        LDY,    // Load Y
        LSR,    // Logical Shift Right by One
        NOP,    // No Operation
        ORA,    // Or with A
        PHA,    // Push A
        PHP,    // Push P
        PLA,    // Pop to A
        PLP,    // Pop to P
        ROL,    // Rotate Left by One
        ROR,    // Rotate Right by One
        RTI,    // Return from Interrupt
        RTS,    // Return from Subroutine
        SBC,    // Subtract from A with Borrow
        SEC,    // Set Carry
        SED,    // Set Decimal
        SEI,    // Set Interrupt Disable
        STA,    // Store A
        STX,    // Store X
        STY,    // Store Y
        TAX,    // Transfer A to X
        TAY,    // Transfer A to Y
        TSX,    // Transfer Stack Pointer to X
        TXA,    // Transfer X to A
        TXS,    // Transfer X to Stack Pointer
        TYA,    // Transfer Y to A
        MAX_VALUE,
        INVALID = 0xff  // An unused opcode used to represent invalid entries in the opcode-mode table.
    };

    Asm6502(std::shared_ptr<IOLayer> io);

    void Emit(InstrImplied);
    void Emit(InstrImmed, uint8_t value);
    void Emit(InstrA);
    void Emit(InstrRel, uint8_t addrOffset);
    void Emit(InstrZP, uint8_t address);
    void Emit(InstrZPX, uint8_t address);
    void Emit(InstrZPY, uint8_t address);
    void Emit(InstrAbs, uint16_t address);
    void Emit(InstrAbsX, uint16_t address);
    void Emit(InstrAbsY, uint16_t address);
    void Emit(InstrInd, uint8_t ptrAddress);
    void Emit(InstrIndX, uint8_t ptrAddress);
    void Emit(InstrIndY, uint8_t ptrAddress);

    void EmitBytes(const uint8_t* bytes, size_t nBytes);
    void EmitByte(uint8_t byte);
    void EmitAddr(uint16_t addr);

    uint16_t CurrentAddress;

private:
    static const uint8_t Opcodes[];
    enum class Mode : uint8_t
    {
        Implied = 0,// Implied (no arguments)
        Immed,      // Immediate
        A,          // 'A' Register
        Rel,        // Relative
        ZP,         // Zero Page
        ZPX,        // Zero Page Indexed by 'X' Register
        ZPY,        // Zero Page Indexed by 'Y' Register
        Abs,        // Absolute
        AbsX,       // Absolute Indexed by 'X' Register
        AbsY,       // Absolute Indexed by 'Y' Register
        Ind,        // Indirect from Pointer in the Zero Page
        IndX,       // Indirect from Pointer in the Zero Page Indexed by 'X' Register Before Dereferencing
        IndY,       // Indirect from Pointer in the Zero Page Indexed by 'Y' Register After Dereferencing
        MAX_VALUE
    };

    static uint8_t Opcode(Instruction, Mode);

    std::shared_ptr<IOLayer> m_io;
};