#pragma once

#include "IOLayer.h"

class StdioLayer : public IOLayer
{
public:
    StdioLayer(size_t memorySize);
    void Print() const;

    virtual void Load(std::vector<uint8_t> bytes, uint16_t address = 0);
    virtual void Output(uint8_t value, uint16_t address);
    virtual uint8_t Input(uint16_t address);

private:
    std::vector<uint8_t> m_memory;
};