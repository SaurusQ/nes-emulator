#pragma once

#include "Definitions.hpp"
#include "CPU/CPU.hpp"
#include "PPU/PPU.hpp"
#include "Cartridge/Mapper.hpp"

#include <cstdint>

class Bus
{
    public:
        Bus(CPU::CPU& cpu, PPU::PPU& ppu, Cartridge::Mapper& mapper);
        ~Bus() = default;

        template<Addressspace AS>
        void read(uint16_t address, uint8_t& data);
        template<Addressspace AS>
        void write(uint16_t address, uint8_t data);

    private:
        CPU::CPU& cpu_;
        PPU::PPU& ppu_;
        Cartridge::Mapper& mapper_;
};
