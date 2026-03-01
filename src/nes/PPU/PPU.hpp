#pragma once

#include "Registers.hpp"

#include <cstdint>

class PPU
{
    public:
        PPU();
        ~PPU();

    private:
        uint16_t getBaseNameTableAddress();
        uint16_t getSpritePatternTableAddress();

        Registers reg_;
};
