#pragma once

#include "Cartridge/Mapper.hpp"
#include "RAM.hpp"
#include "VRAM.hpp"

#include <cstdint>

class Bus
{
    public:
        Bus(Mapper* mapper, PPU::Registers& ppu, RAM& ram);
        ~Bus() = default;

        void readCPU(uint16_t address, uint8_t& data);
        void storeCPU(uint16_t address, uint8_t data);

    private:
        Mapper*         mapper_;
        PPU::Registers& ppu_;
        RAM&            ram_;
    
        uint8_t lastReadCPU_ = 0x00;
        uint8_t lastReadPPU_ = 0x00;
};

