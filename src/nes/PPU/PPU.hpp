#pragma once

#include "Registers.hpp"

#include <cstdint>
#include <vector>

namespace PPU
{
    struct Pixel
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    class PPU
    {
        public:
            PPU();
            ~PPU() = default;

            void reset();
            void tick();

        private:
            uint16_t getBaseNameTableAddress();
            uint16_t getSpritePatternTableAddress();
    
            Registers reg_;
            uint64_t cycle_ = 0;
            uint16_t dot_ = 0;
            std::vector<Pixel> screenBuffer_;
    };
}
