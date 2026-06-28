#pragma once

#include "CPU/CPU.hpp"
#include "PPU/PPU.hpp"
#include "Bus.hpp"
#include "RAM.hpp"
#include "VRAM.hpp"
#include "Cartridge/Mapper.hpp"

class NES
{
    public:   
        NES(Mapper* mapper);
        ~NES();

        void powerOn();
        void reset();
        void runCycle();

        void loadDotNESDirectToMemory(const char* filename);

        const CPU_t& getCPU() const { return cpu_; }
        const PPU_t& getPPU() const { return ppu_; }
        const Mapper* getMapper() const { return mapper_; }
        const RAM& getRAM() const { return ram_; }
        const VRAM& getVRAM() const { return vram_; }
        const Bus& getBus() const { return bus_; }

    private:
        Mapper* mapper_;
        RAM ram_;
        VRAM vram_;
        CPU_t cpu_;
        PPU_t ppu_;
        Bus bus_;
};
