#pragma once

#include "CPU/CPU.hpp"
#include "PPU/PPU.hpp"

class NES
{
    public:   
        NES();
        ~NES();

        void powerOn();
        void reset();
        void runCycle();

        void loadDotNESDirectToMemory(const char* filename);

        const CPU::CPU& getCPU() const { return cpu_; }
        const PPU::PPU& getPPU() const { return ppu_; }

    private:
        CPU::CPU cpu_;
        PPU::PPU ppu_;
        Mapper mapper_;
};
