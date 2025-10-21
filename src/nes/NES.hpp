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

        const Memory& getMemory() const { return memory_; }

    private:

        Memory memory_;
        CPU cpu_;    
};
