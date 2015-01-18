#include <cstdint>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "StdioLayer.h"

using namespace std;

StdioLayer::StdioLayer(size_t memorySize)
{
    if (memorySize > (1 << 16) || memorySize == 0)
        throw new exception("memory size must be between 1 and 65536");
    m_memory.resize(memorySize);
}

void StdioLayer::Output(uint8_t value, uint16_t address)
{
    m_memory[address] = value;
}

uint8_t StdioLayer::Input(uint16_t address)
{
    return m_memory[address];
}

void StdioLayer::Print() const
{
    stringstream line;
    bool old_nonzero = true;
    bool nonzero = false;
    for (size_t i = 0, n = m_memory.size(); i < n; i++)
    {
        if (m_memory[i] != 0)
            nonzero = true;
        line << hex << setfill('0') << setw(2) << +m_memory[i];
        if ((i + 1) % 16 == 0)
        {
            if (nonzero)
            {
                cout << hex << setfill('0') << setw(4) << (i - 15) << ": " << line.str() << endl;
                old_nonzero = true;
                nonzero = false;
            }
            else if (old_nonzero)
            {
                cout << "...\n";
                old_nonzero = false;
            }
            line.str("");
        }
        else if ((i + 1) % 8 == 0)
        {
            line << "    ";
        }
        else
        {
            line << ' ';
        }
    }
}