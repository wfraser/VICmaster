#pragma once

#include "IOLayer.h"

class Asm6502
{
public:
    // Implied (no arguments)
    enum class InstrImplied : uint8_t
    {
        BRK = 0x00, // Simulate IRQ
        CLC = 0x18, // Clear Carry
        CLD = 0xd8, // Clear Decimal
        CLI = 0x58, // Clear Interrupt Dis
        CLV = 0xb8, // Clear Overflow
        DEX = 0xca, // Decrement X
        DEY = 0x88, // Decrement Y
        INX = 0xe8, // Increment X
        INY = 0xc8, // Increment Y
        NOP = 0xea, // No Operation
        PHA = 0x48, // Push A
        PHP = 0x08, // Push P
        PLA = 0x68, // Pop to A
        PLP = 0x28, // Pop to P
        RTI = 0x40, // Return from Interrupt
        RTS = 0x60, // Return from Subroutine
        SEC = 0x38, // Set Carry
        SED = 0xf8, // Set Decimal
        SEI = 0x78, // Set Interrupt Disable
        TAX = 0xaa, // Transfer A to X
        TAY = 0xa8, // Transfer A to Y
        TSX = 0xba, // Transfer Stack Pointer to X
        TXA = 0x8a, // Transfer X to A
        TXS = 0x9a, // Transfer X to Stack Pointer
        TYA = 0x98, // Transfer Y to A
    };

    // Immediate
    enum class InstrImmed : uint8_t
    {
        ADC = 0x69, // Add to A and Carry
        AND = 0x29, // AND with A
        CMD = 0xc9, // Compare with A
        CPX = 0xe0, // Compare with X
        CPY = 0xc0, // Compare with Y
        EOR = 0x49, // XOR with A
        LDA = 0xa9, // Load A
        LDX = 0xa2, // Load X
        LDY = 0xa0, // Load Y
        ORA = 0x09, // Or with A
        SBC = 0xe9, // Subtract from A with Borrow
    };

    // 'A' Register
    enum class InstrA : uint8_t
    {
        ASL = 0x0a, // Arithmetic Shift Left
        LSR = 0x4a, // Logical Shift Right by One
        ROL = 0x2a, // Rotate Left by One
        ROR = 0x2a, // Rotate Right by One
    };

    // Relative
    enum class InstrRel : uint8_t
    {
        BCC = 0x90, // Branch if Carry is Clear
        BCS = 0xb0, // Branch if Carry is Set
        BEQ = 0xf0, // Branch if Equal (Z is Set)
        BMI = 0x30, // Branch if Sign is Set
        BNE = 0xd0, // Branch if Not Equal (Z is C
        BPL = 0x10, // Branch if Sign is Clear
        BVC = 0x50, // Branch if Overflow is Clear
        BVS = 0x70, // Branch if Overflow is Set
    };

    // Zero Page
    enum class InstrZP : uint8_t
    {
        ADC = 0x65, // Add to A and Carry
        AND = 0x25, // AND with A
        ASL = 0x06, // Arithmetic Shift Left
        BIT = 0x24, // Test bits in Memory by masking with A
        CMP = 0xc5, // Compare with A
        CPX = 0xe4, // Compare with X
        CPY = 0xc4, // Compare with Y
        DEC = 0xc6, // Decrement by One
        EOR = 0x45, // XOR with A
        INC = 0xe6, // Increment by One
        LDA = 0xa5, // Load A
        LDX = 0xa6, // Load X
        LDY = 0xa4, // Load Y
        LSR = 0x46, // Logical Shift Right by One
        ORA = 0x05, // Or with A
        ROL = 0x26, // Rotate Left by One
        ROR = 0x66, // Rotate Right by One
        SBC = 0xe5, // Subtract from A with Borrow
        STA = 0x85, // Store A
        STX = 0x86, // Store X
        STY = 0x84, // Store Y
    };

    // Zero Page Indexed by 'X' Register
    enum class InstrZPX : uint8_t
    {
        ADC = 0x75, // Add to A and Carry
        AND = 0x35, // AND with A
        ASL = 0x16, // Arithmetic Shift Left
        CMP = 0xd5, // Compare with A
        DEC = 0xd6, // Decrement by One
        EOR = 0x55, // XOR with A
        INC = 0xf6, // Increment by One
        LDA = 0xb5, // Load A
        LDY = 0xb4, // Load Y
        LSR = 0x56, // Logical Shift Right by One
        ORA = 0x15, // Or with A
        ROL = 0x36, // Rotate Left by One
        ROR = 0x76, // Rotate Right by One
        SBC = 0xf5, // Subtract from A with Borrow
        STA = 0x95, // Store A
        STY = 0x94, // Store Y
    };

    // Zero Page Indexed by 'Y' Register
    enum class InstrZPY : uint8_t
    {
        LDX = 0xb6, // Load X
        STX = 0x96, // Store X
    };

    // Absolute
    enum class InstrAbs : uint8_t
    {
        ADC = 0x6d, // Add to A and Carry
        AND = 0x2d, // AND with A
        ASL = 0x0e, // Arithmetic Shift Left
        BIT = 0x2c, // Test bits in Memory by masking with A
        CMP = 0xcd, // Compare with A
        CPX = 0xec, // Compare with X
        CPY = 0xcc, // Compare with Y
        DEC = 0xce, // Decrement by One
        EOR = 0x4d, // XOR with A
        INC = 0xee, // Increment by One
        JMP = 0x4c, // Branch Unconditionally
        JSR = 0x20, // Jump to Subroutine
        LDA = 0xad, // Load A
        LDX = 0xae, // Load X
        LDY = 0xac, // Load Y
        LSR = 0x4e, // Logical Shift Right by One
        ORA = 0x0d, // Or with A
        ROL = 0x2e, // Rotate Left by One
        ROR = 0x6e, // Rotate Right by One
        SBC = 0xed, // Subtract from A with Borrow
        STA = 0x8d, // Store A
        STX = 0x8e, // Store X
        STY = 0x8c, // Store Y
    };

    // Absolute Indexed by 'X' Register
    enum class InstrAbsX : uint8_t
    {
        ADC = 0x7d, // Add to A and Carry
        AND = 0x3d, // AND with A
        ASL = 0x1e, // Arithmetic Shift Left
        CMP = 0xdd, // Compare with A
        DEC = 0xde, // Decrement by One
        EOR = 0x5d, // XOR with A
        INC = 0xfe, // Increment by One
        LDA = 0xbd, // Load A
        LDY = 0xbc, // Load Y
        LSR = 0x5e, // Logical Shift Right by One
        ORA = 0x1d, // Or with A
        ROL = 0x3e, // Rotate Left by One
        ROR = 0x7e, // Rotate Right by One
        SBC = 0xfd, // Subtract from A with Borrow
        STA = 0x9d, // Store A
    };

    // Absolute Indexed by 'Y' Register
    enum class InstrAbsY : uint8_t
    {
        ADC = 0x79, // Add to A and Carry
        AND = 0x39, // AND with A
        CMP = 0xd9, // Compare with A
        EOR = 0x59, // XOR with A
        LDA = 0xb9, // Load A
        LDX = 0xbe, // Load X
        ORA = 0x19, // Or with A
        SBC = 0xf9, // Subtract from A with Borrow
        STA = 0x99, // Store A
    };

    // Indirect from Pointer in the Zero Page
    enum class InstrInd : uint8_t
    {
        JMP = 0x6c, // Branch Unconditionally
    };

    // Indirect from Pointer in the Zero Page Indexed by 'X' Register Before Dereferencing
    enum class InstrIndX : uint8_t
    {
        ADC = 0x61, // Add to A and Carry
        AND = 0x21, // AND with A
        CMP = 0xc1, // Compare with A
        EOR = 0x41, // XOR with A
        LDA = 0xa1, // Load A
        ORA = 0x01, // Or with A
        SBC = 0xe1, // Subtract from A with Borrow
        STA = 0x81, // Store A
    };

    // Indirect from Pointer in the Zero Page Indexed by 'Y' Register After Dereferencing
    enum class InstrIndY : uint8_t
    {
        ADC = 0x71, // Add to A and Carry
        AND = 0x31, // AND with A
        CMP = 0xd1, // Compare with A
        EOR = 0x51, // XOR with A
        LDA = 0xb1, // Load A
        ORA = 0x11, // Or with A
        SBC = 0xf1, // Subtract from A with Borrow
        STA = 0x91, // Store A
    };

    // All Instructions
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

    // Addressing Modes
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

    struct Disassembly
    {
        uint16_t Address;
        Instruction Instruction;
        Mode Mode;
        union
        {
            uint8_t u8;
            uint16_t u16;
        } Arg;
    };

    std::vector<Disassembly> Disassemble(
        uint16_t start = 0,
        uint16_t end = std::numeric_limits<uint16_t>::max());
    static void PrintDisassembly(const std::vector<Disassembly>& disassembly);

    uint16_t CurrentAddress;

private:
    std::shared_ptr<IOLayer> m_io;
};