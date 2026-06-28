#pragma once

#include "CPU/CPU.hpp"
#include "PPU/PPU.hpp"
#include "RAM.hpp"
#include "VRAM.hpp"
#include "Cartridge/Mapper.hpp"

#include <cstdint>
#include <vector>
#include <functional>

class Bus
{
    public:
        Bus(CPU_t *cpu, PPU_t *ppu, RAM *ram, VRAM *vram);
        ~Bus() = default;

        void attachMapper(Mapper* mapper) { mapper_ = mapper; }

        void readCPU(uint16_t address, uint8_t& data);
        void storeCPU(uint16_t address, uint8_t data);

        void readPPU(uint16_t address, uint8_t& data);
        void storePPU(uint16_t address, uint8_t data);

    private:

        CPU_t *cpu_ = nullptr;
        PPU_t *ppu_ = nullptr;
        RAM *ram_ = nullptr;
        VRAM *vram_ = nullptr;
        Mapper *mapper_ = nullptr;

        uint8_t lastRead_ = 0x00;
};
