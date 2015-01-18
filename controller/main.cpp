#include <cstdint>
#include <string>
#include <exception>
#include <memory>
#include <vector>
#include "StdioLayer.h"
#include "Asm6502.h"

using I = Asm6502::Instruction;

const uint16_t BLK1 = 0x2000;   // to 0x3fff
const uint16_t BLK2 = 0x4000;   // to 0x5fff
const uint16_t BLK3 = 0x6000;   // to 0x7fff
const uint16_t BLK5 = 0xa000;   // to 0xbfff
const uint16_t RAM1 = 0x0400;   // to 0x07ff
const uint16_t RAM2 = 0x0800;   // to 0x0bff
const uint16_t RAM3 = 0x0c00;   // to 0x0fff

const uint16_t VIC_ColorRegister = 0x900F;  // bits 0-2: border color
                                            // bit    3: inverted/normal
                                            // bit  4-7: background color

int wmain(int argc, wchar_t* argv[])
{
    auto io = std::make_shared<StdioLayer>(1<<16);
    Asm6502 cpu(io);

    // Output a basic test program.

    cpu.CurrentAddress = BLK5;                  // Start of cartridge ROM program
    cpu.EmitAbs(I::INC, VIC_ColorRegister);     // Increment the VIC's draw color
    cpu.EmitAbs(I::JMP, BLK5);                  // jump back

    io->Print();

    return 0;
}