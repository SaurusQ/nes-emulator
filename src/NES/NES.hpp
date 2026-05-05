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

        const CPU::CPU& getCPU() const { return cpu_; }
        const PPU::PPU& getPPU() const { return ppu_; }
        const Mapper& getMapper() const { return *mapper_; }

    private:
        CPU::CPU cpu_;
        PPU::PPU ppu_;
        Bus bus_;
        RAM ram_;
        VRAM vram_;
        Mapper* mapper_;
};
