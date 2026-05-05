#pragma once

#include "Registers.hpp"
#include "Definitions.hpp"
#include "../Bus.hpp"
#include "../Addressable.hpp"

#include <cstdint>
#include <vector>


class Mapper;
namespace PPU
{
    class PPU
    {
        public:
            PPU(Bus& bus);
            ~PPU() = default;

            void reset();
            void tick();

            void copyScreenBuffer(std::vector<Pixel>& dst) const { dst = screenBuffer_; }
            std::vector<Pixel> getScreenBuffer() const { return screenBuffer_; }

            Registers& getRegisters() { return reg_; }
        private:
            uint16_t getBaseNameTableAddress();
            uint16_t getSpritePatternTableAddress();
    
            Bus& bus_;
            Registers reg_;
            uint64_t cycle_ = 0;
            uint16_t dot_ = 0;
            std::vector<Pixel> screenBuffer_;
    };
}
