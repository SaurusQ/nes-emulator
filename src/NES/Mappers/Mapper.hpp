#pragma once

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
        Mapper();
        ~Mapper() = default;

        template<Addressspace AS>
        void read(uint16_t address, uint8_t& data) const
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
        void store(uint16_t address, uint8_t data)
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

        void storeCPU(uint16_t address, uint8_t data);
        void storePPU(uint16_t address, uint8_t data);
        void readCPU(uint16_t address, uint8_t& data) const;
        void readPPU(uint16_t address, uint8_t& data) const;

    private:
        
};
