#pragma once

#include "IOLayer.h"

class Asm6502
{
public:
    class BadInstruction : public std::exception
    {
        std::string what()
        {
            return "Invalid 6502 Instruction";
        }
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

    void Emit(Instruction);
    void EmitImm(Instruction, uint8_t value);
    void EmitA(Instruction);
    void EmitRel(Instruction, uint8_t addrOffset);
    void EmitZP(Instruction, uint8_t address);
    void EmitZPX(Instruction, uint8_t address);
    void EmitZPY(Instruction, uint8_t address);
    void EmitAbs(Instruction, uint16_t address);
    void EmitAbsX(Instruction, uint16_t address);
    void EmitAbsY(Instruction, uint16_t address);
    void EmitInd(Instruction, uint8_t ptrAddress);
    void EmitIndX(Instruction, uint8_t ptrAddress);
    void EmitIndY(Instruction, uint8_t ptrAddress);

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

    uint8_t Opcode(Instruction, Mode);

    void EmitInstruction(Instruction i, Mode m)
    {
        uint8_t op = Opcode(i, m);
        if (op == static_cast<uint8_t>(Instruction::INVALID))
            throw new BadInstruction();
        EmitByte(op);
    }

    std::shared_ptr<IOLayer> m_io;
};