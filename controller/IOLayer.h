#pragma once

class IOLayer
{
public:
    virtual void Output(uint8_t value, uint16_t address) = 0;
    virtual uint8_t Input(uint16_t address) = 0;
};