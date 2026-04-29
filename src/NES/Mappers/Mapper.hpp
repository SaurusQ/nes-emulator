#pragma once

#include "Definitions.hpp"

#include <cstdint>

enum class Addressspace
{
    CPU,
    PPU,
    UNK
};


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
        void write(uint16_t address, uint8_t data)
        {
            if constexpr (AS == Addressspace::CPU)
            {
                this->writeCPU(address, data);
            } else if constexpr (AS == Addressspace::PPU)
            {
                this->readPPU(address, data);
            }
            else {
                static_assert(dependent_false<AS>, "Invalid address space for write operation");
            }
        };

        void writeCPU(uint16_t address, uint8_t data);
        void writePPU(uint16_t address, uint8_t data);
        void readCPU(uint16_t address, uint8_t& data);
        void readPPU(uint16_t address, uint8_t& data);

    private:
        
};
