#pragma once

#include "../Mapper.hpp"

class M_000 : public Mapper
{
    public:
        M_000() = default;
        ~M_000() = default;

        void storeCPU(uint16_t address, uint8_t data)
        {
            prgRom_[address & 0x7FFF] = data;
        }
        bool readCPU(uint16_t address, uint8_t& data) const
        {
            data = prgRom_[address & 0x7FFF];
            return true;
        }
        
        void storePPU(uint16_t address, uint8_t data) override
        {
            chrRom_[address & 0x7FFF] = data;
        }

        bool readPPU(uint16_t address, uint8_t& data) const
        {
            data = chrRom_[address & 0x7FFF];
            return true;
        }

    private:
        std::vector<uint8_t> prgRom_ = std::vector<uint8_t>(0xFFFF, 0x00);
        std::vector<uint8_t> chrRom_ = std::vector<uint8_t>(0xFFFF, 0x00);

};