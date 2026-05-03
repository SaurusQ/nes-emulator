#pragma once

#include "Registers.hpp"
#include "Definitions.hpp"
#include "VRAM.hpp"
#include "../Cartridge/Mapper.hpp"
#include "../Addressable.hpp"

#include <cstdint>
#include <vector>

constexpr size_t PPU_REGISTERS_SIZE = 8;
namespace PPU
{
    class PPU : public Addressable
    {
        public:
            PPU(Mapper& mapper);
            ~PPU() = default;

            void reset();
            void tick();

            void copyScreenBuffer(std::vector<Pixel>& dst) const { dst = screenBuffer_; }
            std::vector<Pixel> getScreenBuffer() const { return screenBuffer_; }

            size_t size() const { return PPU_REGISTERS_SIZE; }
        protected:
            inline uint8_t* getMemoryPtr() { return reinterpret_cast<uint8_t*>(&reg_); }
        private:
            uint16_t getBaseNameTableAddress();
            uint16_t getSpritePatternTableAddress();
    
            Mapper& mapper_;
            Registers reg_;
            uint64_t cycle_ = 0;
            uint16_t dot_ = 0;
            std::vector<Pixel> screenBuffer_;
    };
}
