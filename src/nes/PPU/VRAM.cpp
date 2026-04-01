#include "VRAM.hpp"

#include <algorithm>

constexpr size_t VRAM_SIZE = 0x4000;

namespace PPU
{
    VRAM::VRAM()
    {
        vram_ = std::make_unique<uint8_t[]>(VRAM_SIZE);
        std::fill(vram_.get(), vram_.get() + VRAM_SIZE, 0x00);
    }

    void VRAM::read(uint16_t address, uint8_t& data) const
    {
        data = vram_[address];
    }

    void VRAM::store(uint16_t address, uint8_t data)
    {
        vram_[address] = data;
    }
}