#pragma once

#include "CPU.hpp"
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

        const CPU& getCpu() const { return cpu_; }
        const Memory& getMemory() const { return memory_; }

    private:

        Memory memory_;
        CPU cpu_;    
};
