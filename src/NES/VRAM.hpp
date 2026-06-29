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
        inline const uint8_t* getMemoryPtr() const { return vram_; }

    protected:
        uint8_t* getMemoryPtrInternal() { return vram_; }
    private:
        uint8_t vram_[PPU_VRAM_SIZE];
};
