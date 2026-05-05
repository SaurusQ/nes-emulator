#pragma once

#include "../RAM.hpp"
#include "../VRAM.hpp"
#include "../PPU/PPU.hpp"

#include <cstdint>

template<auto... T> inline constexpr bool dependent_false = false;

enum class Addressspace
{
    CPU,
    PPU,
    UNK
};

class Mapper
{
    public:
        Mapper() = default;
        ~Mapper() = default;

        void attach(VRAM* vram) { vram_ = vram; }

        virtual void storeCPU(uint16_t address, uint8_t data) = 0;
        virtual bool readCPU(uint16_t address, uint8_t& data) const = 0;
        
        virtual void storePPU(uint16_t address, uint8_t data) = 0;
        virtual bool readPPU(uint16_t address, uint8_t& data) const = 0;
        
    protected:
        VRAM* vram_ = nullptr;
};
