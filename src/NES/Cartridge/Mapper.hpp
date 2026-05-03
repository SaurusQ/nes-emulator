#pragma once

#include "../RAM.hpp"
#include "../PPU/PPU.hpp"

#include <cstdint>

template<auto... T> inline constexpr bool dependent_false = false;

enum class Addressspace
{
    CPU,
    PPU,
    UNK
};

namespace AS
{
    constexpr Addressspace CPU = Addressspace::CPU;
    constexpr Addressspace PPU = Addressspace::PPU;
}

class Mapper
{
    public:
        Mapper() =  default;
        ~Mapper() = default;

        void attach(PPU::PPU& ppu, RAM& ram, VRAM& vram);

        template<Addressspace AS>
        inline void read(uint16_t address, uint8_t& data) const
        {
            if constexpr (AS == Addressspace::CPU)
            {
                this->readCPU(address, data);
            } else if constexpr (AS == Addressspace::PPU)
            {
                this->readPPU(address, data);
            }
            else {
                static_assert(dependent_false<AS>, "Invalid address space for read operation");
            }
        };
        template<Addressspace AS>
        inline void store(uint16_t address, uint8_t data)
        {
            if constexpr (AS == Addressspace::CPU)
            {
                this->storeCPU(address, data);
            } else if constexpr (AS == Addressspace::PPU)
            {
                this->storePPU(address, data);
            }
            else {
                static_assert(dependent_false<AS>, "Invalid address space for write operation");
            }
        };

        inline void storeCPU(uint16_t address, uint8_t data);
        inline void readCPU(uint16_t address, uint8_t& data) const;
        
        inline void storePPU(uint16_t address, uint8_t data);
        inline void readPPU(uint16_t address, uint8_t& data) const;
        
    private:
        inline virtual void mapperReadCPU(uint16_t address, uint8_t& data) const;
        inline virtual void mapperStoreCPU(uint16_t address, uint8_t data);
        
        inline virtual void mapperReadPPU(uint16_t address, uint8_t& data) const;
        inline virtual void mapperStorePPU(uint16_t address, uint8_t data);
        
        PPU::PPU&   ppu_;
        RAM&        ram_;
        VRAM&       vram_;
};
