#pragma once

#include <cstdint>
#include <memory>

constexpr size_t PPU_VRAM_SIZE = 0x2000;

class VRAM
{
    public:
        VRAM() = default;
        ~VRAM() = default;

        size_t size() const { return PPU_VRAM_SIZE; }
    protected:
        uint8_t* getMemoryPtr() { return vram_; }
    private:
        uint8_t vram_[PPU_VRAM_SIZE];
};
