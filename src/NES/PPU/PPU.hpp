#pragma once

#include "Registers.hpp"
#include "Definitions.hpp"
#include "VRAM.hpp"

#include <cstdint>
#include <vector>

namespace PPU
{
    class PPU
    {
        public:
            PPU();
            ~PPU() = default;

            void reset();
            void tick();

            void copyScreenBuffer(std::vector<Pixel>& dst) const { dst = screenBuffer_; }
            std::vector<Pixel> getScreenBuffer() const { return screenBuffer_; }

            const uint8_t* getPatternTableAddress() const { return vram_.getMemoryPtr(); }
        
        private:
            uint16_t getBaseNameTableAddress();
            uint16_t getSpritePatternTableAddress();
    
            Registers reg_;
            uint64_t cycle_ = 0;
            uint16_t dot_ = 0;
            std::vector<Pixel> screenBuffer_;

            VRAM vram_;
    };
}
