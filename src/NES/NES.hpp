#pragma once

#include "CPU.hpp"
#include "PPU/PPU.hpp"
#include "Memory.hpp"

class NES
{
    public:   
        NES();
        ~NES();

        void powerOn();
        void reset();
        void runCycle();

        void loadDotNESDirectToMemory(const char* filename);

        const CPU& getCPU() const { return cpu_; }
        const PPU::PPU& getPPU() const { return ppu_; }
        const Memory& getMemory() const { return memory_; }

    private:

        Memory memory_;
        CPU cpu_;
        PPU::PPU ppu_;
};
